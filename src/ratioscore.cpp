//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed May 20 09:52:32 PDT 2020
// Last Modified: Sat 03 Apr 2021 10:58:34 PM PDT
// Filename:      ratioscore.cpp
// URL:           https://github.com/craigsapp/ratioscore/blob/master/src/ratioscore.cpp
// Syntax:        C++11
// vim:           ts=3 noexpandtab nowrap
//
// Description:   Convert a ratio score into a MIDI file.
//
// **time	**ratio	**ratio	**mdyn
// *	*ref:C4	*ref:G3	*
// 0	1	1	20S
// 1.5	2	2	30
// 1.64	3	0	.
// 2.6	3/2g	5/4+100c	50
// 3.1	.	3/2	50
// 4.2	6/5G	.	.
// *-	*-	*-	*-
//
// *MM120   = 120 quarter notes (seconds) per minute
// *I#20 = use MIDI instrument 20 (0-indexed, range 0 to 127)
// *Ivioln = use general MIDI instrument for violin
// *Iviola = use general MIDI instrument for viola
// *Icello = use general MIDI instrument for cello
// See
//     https://github.com/craigsapp/humlib/blob/master/src/HumInstrument.cpp
// for a list of known instrument labels.
// H = start of glissando (slide)
// h = end of glissando (slide)
//

#include "humlib.h"
#include "MidiFile.h"

#include <string>
#include <cmath>

using namespace std;
using namespace smf;
using namespace hum;

#define GLISS_START "H"
#define GLISS_END "h"

// function declarations:
string  getOutputFilename (const string& filename);
bool    convertFile       (MidiFile& outfile, HumdrumFile& infile);
void    generateTrack     (MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile);
void    buildTimemap      (HTp sstart, HumdrumFile& infile);
double  getMidiNoteNumber (string refpitch);
int     getEndTime        (HTp stok);
void    addTempoMessages  (MidiFile& outfile, HTp sstart);
void    addGlissando      (MidiFile& outfile, int track, HTp current, double spitch, double reference, int channel);
double  getPitchAsMidi    (HTp token, double reference);
double  getPitchBend      (double pitch, int channel);
double  getPitchBend      (double pitch, double spitch, int channel);
HTp     getNextPitchToken (HTp token);
int     getVelocity       (HTp rtoken);
void    prepareTimeline   (HumdrumFile& infile);
void    getTimeData       (HTp sstart, vector<double>& numbers,
                           vector<double>& tempo, int lines);
void    prepareTimelineRecip(vector<double>& timeline, HTp sstart, int lines);
void    prepareTimelineDtime(vector<double>& timeline, HTp sstart, int lines);
void    prepareTimelineTime(vector<double>& timeline, HTp sstart, int lines);
double  getTimeNumber     (HTp token);
void    addSecondsSpine   (ostream& out, HumdrumFile& infile);
double  getReferencePitchAsMidi(const string& token);
double  getMaxGlissRange  (HTp pstart);
double  getGlissWidth     (vector<double>& gliss);


// variables:
vector<HTp> m_sstarts;               // starting tokens of spines
vector<HTp> m_dynStarts;             // starting tokens of dynamics spines
vector<HTp> m_partStarts;            // starting tokens of parts
bool        m_hasDyn = false;        // does the score have dynamics
bool        m_hasTime = true;        // does the score have a timeline
int         m_timeTrack = -1;        // track number for time spine
int         m_dtimeTrack = -1;       // track number for dtime spine
int         m_recipTrack = -1;       // track number for recip spine
int         m_msTrack = -1;          // track number for millisecond spine
int         m_dmsTrack = -1;         // track number for millisecond spine
vector<int> m_timemap;               // timestamp for each line of file
double      m_tuning = 440.0;        // Tuning of A4 (current fixed: add RPN to change)
int         m_first_tempo_time = -1; // timestamp of first tempo message in score (default MM60)
vector<double> m_pbrange;            // pitch bend range by channel
vector<int> m_glissTime;             // time between gliss adjustments
int         m_pbadjust = 0;          // anticipation time for pitch bend before note
int         m_lastDuration = 1000;   // duration of last event in score (if not rest).
int         m_velocity = 64;         // default attack velocity of notes
double      m_maxtime = 0.0;         // maximum time of output MIDI file
vector<double> m_timeline;           // used with --max-time option.
bool        m_debugQ = false;        // used with --debug option


///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	Options options;
	options.define("o|output=s", "output name for MIDI file when using standard input.");
	options.define("r|raw=b",    "output raw MIDI data to stdout.");
	options.define("x|max-time=d:0.0", "maximum duration of output MIDI file in seconds");
	options.define("s|seconds=b", "add time in seconds spine (resolving tempo changes)");
	options.define("debug=b", "display debugging information");
	options.process(argc, argv);
	m_maxtime = options.getDouble("max-time");
	m_debugQ = options.getBoolean("debug");

	HumdrumFile infile;
	MidiFile outfile;
	Tool_filter filter;

	m_pbrange.resize(16);
	fill(m_pbrange.begin(), m_pbrange.end(), 2.0);

	if (options.getArgCount() == 0) {
		infile.read(cin);
		if (infile.hasGlobalFilters()) {
			filter.run(infile);
			if (filter.hasHumdrumText()) {
				infile.readString(filter.getHumdrumText());
			}
		}
		if (options.getBoolean("seconds")) {
			addSecondsSpine(cout, infile);
			return 0;
		}
		bool status = convertFile(outfile, infile);
		if (!status) {
			cerr << "Problem converting score." << endl;
			exit(1);
		}
		if (options.getBoolean("raw")) {
			outfile.write(cout);
		} else {
			string filename = options.getString("output");
			if (filename.empty()) {
				cout << outfile;
			} else {
				if (filename.find(".mid") == string::npos) {
					filename += ".mid";
				}
				outfile.write(filename);
			}
		}
	} else if (options.getArgCount() == 1) {
		infile.read(options.getArg(1));
		if (infile.hasGlobalFilters()) {
			filter.run(infile);
			if (filter.hasHumdrumText()) {
				infile.readString(filter.getHumdrumText());
			}
		}
		if (options.getBoolean("seconds")) {
			addSecondsSpine(cout, infile);
			return 0;
		}
		bool status = convertFile(outfile, infile);
		if (!status) {
			cerr << "Problem converting score." << endl;
			exit(1);
		}
		if (options.getBoolean("raw")) {
			outfile.write(cout);
		} else {
			if (options.getBoolean("output")) {
				string filename = options.getString("output");
				if (filename.empty()){
					cout << outfile;
				} else {
					if (filename.find(".mid") == string::npos) {
						filename += ".mid";
					}
					outfile.write(filename);
				}
			} else {
				string filename = getOutputFilename(options.getArg(1));
				outfile.write(filename);
			}
		}
	} else {
		for (int i=0; i<options.getArgCount(); i++) {
			infile.read(options.getArg(i+1));
			if (infile.hasGlobalFilters()) {
				filter.run(infile);
				if (filter.hasHumdrumText()) {
					infile.readString(filter.getHumdrumText());
				}
			}
			bool status = convertFile(outfile, infile);
			if (!status) {
				cerr << "Problem converting score " << options.getArg(i+1) << "." << endl;
			}
			string filename = getOutputFilename(options.getArg(i+1));
			outfile.write(filename);
		}
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////


//////////////////////////////
//
// convertFile -- Convert ratio score to MIDI file.
//

bool convertFile(MidiFile& outfile, HumdrumFile& infile) {
	infile.getSpineStartList(m_sstarts);
	HTp timespine = NULL;
	if (m_maxtime > 0.0) {
		prepareTimeline(infile);
	} else {
		m_timeline.clear();
	}

	m_glissTime.resize(infile.getTrackCount() + 1);
	fill(m_glissTime.begin(), m_glissTime.end(), 50);

	outfile.setTPQ(1000);

	for (int i=0; i<(int)m_sstarts.size(); i++) {
		if (*m_sstarts[i] == "**time") {
			m_timeTrack = m_sstarts[i]->getTrack();
			timespine = m_sstarts[i];
			m_hasTime = true;
			break;
		} else if (*m_sstarts[i] == "**dtime") {
			m_dtimeTrack = m_sstarts[i]->getTrack();
			timespine = m_sstarts[i];
			m_hasTime = true;
			break;
		} else if (*m_sstarts[i] == "**recip") {
			m_recipTrack = m_sstarts[i]->getTrack();
			timespine = m_sstarts[i];
			m_hasTime = true;
			break;
		} else if (*m_sstarts[i] == "**ms") {
			m_msTrack = m_sstarts[i]->getTrack();
			timespine = m_sstarts[i];
			m_hasTime = true;
			break;
		} else if (*m_sstarts[i] == "**dms") {
			m_dmsTrack = m_sstarts[i]->getTrack();
			timespine = m_sstarts[i];
			m_hasTime = true;
			break;
		}
	}
	if (!m_hasTime) {
		// need a timing spine
		return false;
	}

	m_partStarts.resize(0);
	m_dynStarts.resize(0);
	m_hasDyn = false;
	HTp dynStart = NULL;

	for (int i=(int)m_sstarts.size() - 1; i>=0; i--) {
		if (*m_sstarts[i] == "**mdyn") {
			dynStart = m_sstarts[i];
		}
		if (*m_sstarts[i] == "**ratio") {
			m_partStarts.push_back(m_sstarts[i]);
			if (dynStart) {
				m_dynStarts.push_back(dynStart);
				dynStart = NULL;
				m_hasDyn = true;
			} else {
				m_dynStarts.push_back(NULL);
			}
		}
	}

	buildTimemap(timespine, infile);
	// for (int i=0; i<(int)m_timemap.size(); i++) {
	// 	cout << m_timemap[i] << endl;
	// }

	outfile.clear();
	if (m_partStarts.empty()) {
		return false;
	}

	outfile.addTracks(m_partStarts.size());
	outfile.setTicksPerQuarterNote(1000);  // using millisecond ticks
	outfile.addTempo(0, 0, 60.0);

	for (int i=0; i<(int)m_partStarts.size(); i++) {
		generateTrack(outfile, i+1, m_partStarts[i], m_dynStarts[i], infile);
	}

	addTempoMessages(outfile, timespine);

	outfile.markSequence();
	outfile.sortTracks();
	return true;
}



//////////////////////////////
//
// addTempoMessages -- Check **time spine for tempo changes.
//

void addTempoMessages(MidiFile& outfile, HTp sstart) {
	HumRegex hre;
	HTp current = sstart->getNextToken();
	while (current) {
		if (!current->isInterpretation()) {
			current = current->getNextToken();
			continue;
		}
		if (hre.search(current, "^\\*MM(\\d+\\.?\\d*)$")) {
			double tempo = hre.getMatchDouble(1);
			int starttime = m_timemap[current->getLineIndex()];
			if (m_first_tempo_time >= 0) {
				if (starttime < m_first_tempo_time) {
					m_first_tempo_time = starttime;
				}
			} else {
				m_first_tempo_time = starttime;
			}
			outfile.addTempo(0, starttime, tempo);
		}
		current = current->getNextToken();
	}

	if (m_first_tempo_time != 0) {
		// set the default tempo to 60 bpm:
		outfile.addTempo(0, 0, 60.0);
	}
}



//////////////////////////////
//
// buildTimemap -- Convert time spine into millisecond values, interpolating
//   evenly when the data contains a null.
//

void buildTimemap(HTp sstart, HumdrumFile& infile) {
	m_timemap.clear();
	m_timemap.resize(infile.getLineCount());

	vector<int*> tdata;
	tdata.reserve(m_timemap.size());

	bool time = false;
	bool dtime = false;
	bool recip = false;
	bool ms = false;
	bool dms = false;
	bool delta = false;
	double lasttime = 0.0;
	if (sstart->find("dtime") != string::npos) {
		dtime = true;
		delta = true;
	} else if (sstart->find("recip") != string::npos) {
		recip = true;
		delta = true;
	} else if (sstart->find("dms") != string::npos) {
		dms = true;
		delta = true;
	} else if (sstart->find("ms") != string::npos) {
		ms = true;
	} else if (sstart->find("time") != string::npos) {
		time = true;
	} else {
		cerr << "Error: unknown time spine: " << sstart << endl;
	}

	fill(m_timemap.begin(), m_timemap.end(), -2);
	HTp current = sstart;
	while (current) {
		if (!current->isData()) {
			current = current->getNextToken();
			continue;
		}
		int line = current->getLineIndex();
		tdata.push_back(&m_timemap.at(line));

		if (current->isNull()) {
			m_timemap[line] = -1;
		} else {
			if (recip) {
				double value = Convert::recipToDuration(*current).getFloat();
				m_timemap[line] = int(value * 1000.0 + 0.5);
			} else if (ms) {
				m_timemap[line] = stoi(*current);
			} else if (dms) {
				m_timemap[line] = stoi(*current);
			} else { // **time or **dtime
				m_timemap[line] = int(stod(*current) * 1000.0 + 0.5);
			}
		}
		if (delta) {
			m_lastDuration = m_timemap[line];
			int tempval = m_timemap[line] += lasttime;
			m_timemap[line] = lasttime;
			lasttime = tempval;
		}

		current = current->getNextToken();
	}

	if (tdata.empty()) {
		// no time data
		return;
	}

	// set initial part of score to zero:
	for (int i=0; i<(int)m_timemap.size(); i++) {
		if (m_timemap[i] < 0) {
			m_timemap[i] = 0;
		} else {
			break;
		}
	}

	// interpolate null tokens as evenly spaced data
	int lastone = 0;
	int nextone = 0;
	int counter = 0;
	for (int i=1; i<(int)tdata.size(); i++) {
		if (*tdata[i] == -1) {
			counter++;
			if (*tdata[i-1] > -1) {
				lastone = *tdata[i-1];
			}
		} else if (counter > 0) {
			nextone = *tdata[i];
			double increment = (nextone - lastone) / (double)(counter + 1);
			for (int j=0; j<counter; j++) {
				*tdata[i-counter+j] = int((lastone + increment * (j + 1)) * 1000.0 + 0.5);
			}
		}
	}

	// fill in timgs for nondata:
	for (int i=1; i<(int)m_timemap.size(); i++) {
		if (m_timemap[i] < 0) {
			m_timemap[i] = m_timemap[i-1];
		}
	}

}



//////////////////////////////
//
// generateTrack -- Convert a part spine into a MIDI track.  Each track
//    should be given a unique channel.  Currently the channel is derived from
//    the track number (avoiding the drum channel of general MIDI).
//

void generateTrack(MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile) {
	HTp current = pstart;
	HumRegex hre;
	int channel = track - 1;
	if (channel >= 9) {
		// avoid the drum channel
		channel++;
	}
	double lastattack = 0.0;

	int velocity = m_velocity;
	double reference;
	HumInstrument instrument;
	bool hasDyn = false;
	if (dstart != NULL) {
		hasDyn = true;
	}
	bool hasBend = false;
	bool wroteBend = false;

	while (current) {
		if (m_maxtime > 0.0) {
			if (m_timeline[current->getLineIndex()] > m_maxtime) {
				// limit the length of the output MIDI file.
				cerr << "LIMITING MIDIFILE " << m_maxtime << " == " << m_timeline[current->getLineIndex()] << endl;
				break;
			}
		}
		if (current->isInterpretation()) {
			if (hre.search(current, "^\\*I[a-z]{3,6}$")) {
				// Process an instrument name
				int inst = instrument.getGM(*current);
				int starttime = m_timemap[current->getLineIndex()];
				outfile.addTimbre(track, starttime, channel, inst);
			} else if (hre.search(current, "^\\*I#(\\d{1,3})")) {
				// Process an instrument number
				int inst = hre.getMatchInt(1);
				if (inst > 127) {
					inst = 127;
				}
				int starttime = m_timemap[current->getLineIndex()];
				outfile.addTimbre(track, starttime, channel, inst);
			} else if (hre.search(current, "^\\*MM(\\d+\\.?\\d*)$")) {
				// Process a tempo change.  It should not be
				// here, but rather in the **time spine, but
				// process these anyway.
				double tempo = hre.getMatchDouble(1);
				int starttime = m_timemap[current->getLineIndex()];
				if (m_first_tempo_time >= 0) {
					if (starttime < m_first_tempo_time) {
						m_first_tempo_time = starttime;
					}
				} else {
					m_first_tempo_time = starttime;
				}
				outfile.addTempo(0, starttime, tempo);
			} else if (hre.search(current, "^\\*bend[:=]?(\\d+\\.?\\d*)$")) {
				// Set the pitch bend range/depth/sensitivity
				// Default is 2.0.
				double range = hre.getMatchDouble(1);
				if (range <= 1.0) {
					range = 2.0;
				}
				int starttime = m_timemap[current->getLineIndex()];
				outfile.setPitchBendRange(track, starttime, channel, range);
				hasBend = true;
				wroteBend = true;
				m_pbrange.at(channel) = range;
			} else if (hre.search(current, "^\\*gliss[:=]?(\\d+)$")) {
				int value = hre.getMatchInt(1);
				if (value > 0) {
					int track = current->getTrack();
					m_glissTime[track] = value;
				}
			} else if (hre.search(current, "^\\*pan[:=]?(-?\\d*\\.\\d*)$")) {
				string match = hre.getMatch(1);
				if (!match.empty()) {
					double panvalue = hre.getMatchDouble(1);
					int pan = int(((panvalue + 1.0)/2.0) * 127);
					if (pan < 0) {
						pan = 0;
					} else if (pan > 127) {
						pan = 127;
					}
					int starttime = m_timemap[current->getLineIndex()];
					outfile.addController(track, starttime, channel, 10, pan);
				}
			} else if (hre.search(current, "^\\*ref[:=]?[A-G][#-b]?\\d+")) {
				reference = getReferencePitchAsMidi(*current);
			}
		} else if (current->isData()) {
			if (!wroteBend) {
				double glissRange = getMaxGlissRange(pstart);
				// force writing of pitch bend depth (in case the synthesizer
				// channel is set to a non-default value).
				m_pbrange.at(channel) = glissRange;
				outfile.setPitchBendRange(track, 0, channel, m_pbrange.at(channel));
				wroteBend = true;
			}
			if (current->isNull()) {
				current = current->getNextToken();
				continue;
			}
			if (*current == "0") {
				// ignore rest
				current = current->getNextToken();
				continue;
			}

			double pitch = getPitchAsMidi(current, reference);
			double pbend = getPitchBend(pitch, channel);

			int starttime = m_timemap[current->getLineIndex()];
			int endtime = getEndTime(current) - 1;
			int ptime = starttime - m_pbadjust;
			if (ptime < 0) {
				ptime = 0;
			}

			if (hasDyn) {
				velocity = getVelocity(current);
			}

			if (current->find('_') == string::npos) {
				outfile.addPitchBend(track, ptime, channel, pbend);
				outfile.addNoteOn(track, starttime, channel, int(pitch), velocity);
				outfile.addNoteOff(track, endtime, channel, int(pitch), velocity);
				lastattack = pitch;
			} else {
				// this is a tied note, so ignored for note attacks, but add
				// pitch bend:
				pbend = getPitchBend(pitch, lastattack, channel);
				outfile.addPitchBend(track, ptime, channel, pbend);
			}

			if (current->find(GLISS_START) != string::npos) {
				addGlissando(outfile, track, current, pitch, reference, channel);
			}
		}
		current = current->getNextToken();
		continue;
	}
}



//////////////////////////////
//
// getReferencePitchAsMidi --
//

double getReferencePitchAsMidi(const string& token) {
	HumRegex hre;
	double reference = 60.0;  // default reference
	if (hre.search(token, "^\\*ref[:=]?([A-G][#-b]?\\d+)([+-]\\d+\\.?\\d*c)?")) {
		string refpitch = hre.getMatch(1);
		reference = getMidiNoteNumber(refpitch);
		string refcents = hre.getMatch(2);
		if (!refcents.empty()) {
			if (hre.search(refcents, "([+-])(\\d+\\.?\\d*)c")) {
				string direction = hre.getMatch(1);
				double rcents = hre.getMatchDouble(2);
				if (direction == "-") {
					reference -= rcents / 100.0;
				} else {
					reference += rcents / 100.0;
				}
			}
		}
		if (reference <= 0) {
			reference = 60.0;
		}
		if (reference > 127.0) {
			reference = 60.0;
		}
	}
	return reference;
}



//////////////////////////////
//
// getVelocity --
//

int getVelocity(HTp rtoken) {
	HTp current = rtoken->getNextField();
	while (current) {
		if (current->isDataType("**ratio")) {
			break;
		}
		if (current->isDataType("**mdyn")) {
			if (current->isNull()) {
				HTp resolve = current->resolveNull();
				if (resolve->isNull()) {
					break;
				}
				int value = stoi(*resolve);
				if (value < 0) {
					value = 1;
				}
				if (value > 127) {
					value = 127;
				}
				return value;
			} else {
				int value = stoi(*current);
				if (value < 0) {
					value = 1;
				}
				if (value > 127) {
					value = 127;
				}
				return value;
			}
		}
		current = current->getNextField();
	}
	return m_velocity;
}



//////////////////////////////
//
// getPitchBend --
//

double getPitchBend(double pitch, int channel) {
	double pbend = pitch - int(pitch);
	double prange = m_pbrange.at(channel);
	pbend = pbend / prange;  // normalize to pitch bend range
	return pbend;
}

double getPitchBend(double pitch, double spitch, int channel) {
	double pbend = pitch - int(spitch);
	double prange = m_pbrange.at(channel);
	pbend = pbend / prange;  // normalize to pitch bend range
	return pbend;
}



//////////////////////////////
//
// getPitchAsMidi -- Convert ratio token into floating-point MIDI note number.
//      reference: MIDI note number (with possible fractional value if not equaltemperament).
//
//      pitches can be in these formats:
//      intervals:
//          5        == a rational number value with no denominator (a harmonic)
//          5/4      == a rational number
//          (5/4)^3  == a rational number with exponentiation
//          235.35c  == a cent interval above the reference pitch
//         +235.35c  == a cent interval above the reference pitch
//         -235.35c  == a cent interval above the reference pitch
//       frequencies:
//           440.23z == 440.23 Hertz
//

double getPitchAsMidi(HTp token, double reference) {
	int top;
	int bot;
	HumNum value;
	HumRegex hre;
	double pcents;
	string botstring;

	// remove non-pitch information from token:
	string cleaned = *token;
	hre.replaceDestructive(cleaned, "", "[Hh_]", "g");

	// Check if only a cent interval:
	if (hre.search(cleaned, "^([+-]?\\d+\\.?\\d*)c$")) {
		double cents = hre.getMatchDouble(1);
		return cents/100.0 + reference;
	}

	// Check if only a frequency:
	if (hre.search(cleaned, "^([+]?\\d+\\.?\\d*)z$")) {
		double frequency = hre.getMatchDouble(1);
		if (frequency <= 0.0) {
			return 0.0;
		}
		double midi = 12.0 * log2(frequency / 440.0) + 69.0;
		return midi;
	}


	if (!hre.search(token, "(\\d+)(?:/(\\d+))?")) {
		cerr << "Problem with ratio: " << token << endl;
		return 0.0;
	}

	top = hre.getMatchInt(1);
	botstring = hre.getMatch(2);
	if (botstring.empty()) {
		bot = 1;
	} else {
		bot = hre.getMatchInt(2);
	}
	if (top == 0) {
		cerr << "TOP should not be zero: " << token << endl;
		return 0.0;
	}
	if (bot == 0) {
		cerr << "Error cannot use 0 as the denominator, setting to 1" << endl;
		bot = 1;
	}

	if (hre.search(token, "\\(\\d+/?\\d*\\)\\^(\\d+)")) {
		int power = hre.getMatchInt(1);
		top = pow(top, power);
		bot = pow(bot, power);
		if (top < 0) {
			cerr << "Error: integer overflow for numerator in " << token << endl;
			return reference;
		}
		if (bot < 0) {
			cerr << "Error: integer overflow for denominator in " << token << endl;
			return reference;
		}
	}

	value = top;
	value /= bot;

	double cvalue = log2(value.getFloat()) * 12;
	if (hre.search(token, "([+-])(\\d+\\.?\\d*)c")) {
		pcents = hre.getMatchDouble(2);
		string direction = hre.getMatch(1);
		if (direction == "-") {
			pcents = hre.getMatchDouble(2);
		} else {
			pcents = -hre.getMatchDouble(2);
		}
	} else {
		pcents = 0;
	}
	double pitch = reference + cvalue + pcents / 100.0;
	return pitch;
}



//////////////////////////////
//
// addGlissando -- do a linear interpolation between the starting and ending pitches.
//

void addGlissando(MidiFile& outfile, int track, HTp starttok, double spitch, double reference, int channel) {
	HTp nexttok = getNextPitchToken(starttok);
	if (nexttok == NULL) {
		return;
	}
	int humtrack = starttok->getTrack();

	double npitch = getPitchAsMidi(nexttok, reference);
	double sspitch = getPitchAsMidi(starttok, reference);
	double starttime = m_timemap[starttok->getLineIndex()];
	double endtime = m_timemap[nexttok->getLineIndex()];

	double x1 = starttime;
	double x2 = endtime;
	double y1 = sspitch;
	double y2 = npitch;

	if (x2 <= x1) {
		return;
	}

	double m = (y2 - y1)/(x2 - x1);
	double b = (x2*y1 - x1*y2)/(x2 - x1);
	double x = x1 + m_glissTime.at(humtrack);
	double y;
	while (x < x2) {
		y = m * x + b;
		double pbend = getPitchBend(y, spitch, channel);
		if (fabs(pbend) > 1.0) {
			cerr << "Warning: Pitch bend " << pbend << " exceeds maximum";
			cerr << " (increase pitch bend range)" << endl;
			cerr << "Pitch bend depth is currently set to " << m_pbrange[channel] << endl;
			return;
		}
		outfile.addPitchBend(track, x, channel, pbend);
		x += m_glissTime.at(humtrack);
	}
	//if (nexttok->find('_') != string::npos) {
	//	// add ending glissando on next note if it is not an attack
	//	double pbend = getPitchBend(y2, spitch, channel);
	//	outfile.addPitchBend(track, x2-1, channel, pbend);
	//}

	if (nexttok->find(GLISS_END) == string::npos) {
		addGlissando(outfile, track, nexttok, spitch, reference, channel);
	}
}




//////////////////////////////
//
// getNextPitchToken --
//

HTp getNextPitchToken(HTp token) {
	HTp current = token->getNextNonNullDataToken();
	return current;
}



//////////////////////////////
//
// getEndTime --
//

int getEndTime(HTp stok) {
	HTp current = stok->getNextToken();
	while (current) {
		if (!current->isData()) {
			current = current->getNextToken();
			continue;
		}
		if (current->isNull()) {
			current = current->getNextToken();
			continue;
		}
		if (current->find('_') != string::npos) {
			// skip sustain notes
			current = current->getNextToken();
			continue;
		}
		int line = current->getLineIndex();
		return m_timemap[line];
		current = current->getNextToken();
	}
	return m_timemap.back() + m_lastDuration;
}



//////////////////////////////
//
// getOutputFilename -- Remove the .krn or similar extension, and replace with .mid.
//

string getOutputFilename(const string& filename) {
	string output = filename;
	if (filename.empty()) {
		output = "output";
	}
	auto pos = output.rfind('.');
	if (pos != string::npos) {
		output.resize(pos);
		output += ".mid";
	} else {
		output += ".mid";
	}
	return output;
}




/////////////////////////////
//
// getMidiNoteNumber -- Input:
//     [A-G][-bf#s+]*\d+
//

double getMidiNoteNumber(string refpitch) {
	string diatonic;
	string accid;
	string octave;
	HumRegex hre;
	if (!hre.search(refpitch, "([A-G])([-bf#s+]*)(\\d+)")) {
		return 0.0;
	}
	diatonic = hre.getMatch(1);
	accid    = hre.getMatch(2);
	octave   = hre.getMatch(3);

	int alter = 0;
	if (!accid.empty()) {
		for (int i=0; i<(int)accid.size(); i++) {
			switch (accid[i]) {
				case '-':
				case 'f':
				case 'b':
					alter--;
					break;
				case '#':
				case 's':
					alter++;
			}
		}
	}
	int output = 0;
	switch (refpitch[0]) {
		case 'C': output = 0;  break;
		case 'D': output = 2;  break;
		case 'E': output = 4;  break;
		case 'F': output = 5;  break;
		case 'G': output = 7;  break;
		case 'A': output = 9;  break;
		case 'B': output = 11; break;
	}
	output += alter;
	// octave must be 1 or higher for now.
	int oct = stoi(octave);
	output += 12 * (oct + 1);
	return output;
}



//////////////////////////////
//
// prepareTimeline --
//

void prepareTimeline(HumdrumFile& infile) {
	vector<HTp> starts;
	HTp timespine = NULL;
	infile.getSpineStartList(starts);
	for (int i=0; i<(int)starts.size(); i++) {
		if (*starts[i] == "**time") {
			timespine = starts[i];
			break;
		} else if (*starts[i] == "**dtime") {
			timespine = starts[i];
			break;
		} else if (*starts[i] == "**recip") {
			timespine = starts[i];
			break;
		}
	}

	if (*timespine == "**time") {
		prepareTimelineTime(m_timeline, timespine, infile.getLineCount());
	} else if (*timespine == "**dtime") {
		prepareTimelineDtime(m_timeline, timespine, infile.getLineCount());
	} else if (*timespine == "**recip") {
		prepareTimelineRecip(m_timeline, timespine, infile.getLineCount());
	}
}



//////////////////////////////
//
// prepareTimelineTime --
//

void prepareTimelineTime(vector<double>& timeline, HTp sstart, int lines) {
	vector<double> tempos;
	vector<double> numbers;
	getTimeData(sstart, numbers, tempos, lines);
	m_timeline.resize(lines);
	fill(m_timeline.begin(), m_timeline.end(), -1);
	double lastvalue = 0.0;
	double value;
	double lasttime = 0.0;
	double curtime = 0.0;
	double deltavalue;
	double deltatime;
	double tempo = 60;
	for (int i=0; i<(int)m_timeline.size(); i++) {
		if (tempos[i] > 0.0) {
			tempo = tempos[i];
		}
		if (numbers[i] >= 0) {
			value = numbers[i];
			deltavalue = value - lastvalue;
			deltatime = deltavalue * 60.0 / tempo;
			curtime = lasttime + deltatime;
			m_timeline[i] = curtime;
			lasttime = curtime;
			lastvalue = value;
		}
	}
}



//////////////////////////////
//
// prepareTimelineDtime --
//

void prepareTimelineDtime(vector<double>& timeline, HTp sstart, int lines) {
	vector<double> tempos;
	vector<double> numbers;
	getTimeData(sstart, numbers, tempos, lines);
	m_timeline.resize(lines);
	fill(m_timeline.begin(), m_timeline.end(), -1);
	double lastvalue = 0.0;
	double value;
	double lasttime = 0.0;
	double curtime = 0.0;
	double deltavalue;
	double deltatime;
	double tempo = 60;
	double nexttempo = -1;
	for (int i=0; i<(int)m_timeline.size(); i++) {
		if (numbers[i] >= 0) {
			value = numbers[i];
			deltavalue = lastvalue;
			deltatime = deltavalue * 60.0 / tempo;
			curtime = lasttime + deltatime;
			m_timeline[i] = curtime;
			lasttime = curtime;
			lastvalue = value;
			if (nexttempo > 0.0) {
				tempo = nexttempo;
				nexttempo = -1;
			}
		}
		if (tempos[i] > 0.0) {
			nexttempo = tempos[i];
		}
	}
}



//////////////////////////////
//
// prepareTimelineRecip --
//

void prepareTimelineRecip(vector<double>& timeline, HTp sstart, int lines) {
	vector<double> tempos;
	vector<double> numbers;
	getTimeData(sstart, numbers, tempos, lines);
	m_timeline.resize(lines);
	fill(m_timeline.begin(), m_timeline.end(), -1);
	double lastvalue = 0.0;
	double value;
	double lasttime = 0.0;
	double curtime = 0.0;
	double deltavalue;
	double deltatime;
	double tempo = 60;
	double nexttempo = -1;
	for (int i=0; i<(int)m_timeline.size(); i++) {
		if (numbers[i] >= 0) {
	 		value = numbers[i] / 4.0; // convert from whole notes to quarter note units
			deltavalue = lastvalue;
			deltatime = deltavalue * 60.0 / tempo;
			curtime = lasttime + deltatime;
			m_timeline[i] = curtime;
			lasttime = curtime;
			lastvalue = value;
			if (nexttempo > 0.0) {
				tempo = nexttempo;
				nexttempo = -1;
			}
		}
		if (tempos[i] > 0.0) {
			nexttempo = tempos[i];
		}
	}
}



//////////////////////////////
//
// getTimeData --
//

void getTimeData(HTp sstart, vector<double>& numbers,
		vector<double>& tempo, int lines) {
	numbers.resize(lines);
	tempo.resize(lines);
	fill(numbers.begin(), numbers.end(), -1);
	fill(tempo.begin(), tempo.end(), -1);
	HTp current = sstart;
	HumRegex hre;
	while (current) {
		if (current->isInterpretation()) {
			if (hre.search(current, "^\\*MM(\\d+\\.?\\d*)")) {
				tempo[current->getLineIndex()] = hre.getMatchDouble(1);
			}
		}
		if (!current->isData()) {
			current = current->getNextToken();
			continue;
		}
		if (current->isNull()) {
			current = current->getNextToken();
			continue;
		}
		double number = getTimeNumber(current);
		numbers[current->getLineIndex()] = number;
		current = current->getNextToken();
		continue;
	}
}



//////////////////////////////
//
// getTimeNumber --  floating-point number, rational number, or compound rational number.
//

double getTimeNumber(HTp token) {
	HumRegex hre;
	if (hre.search(token, "^(\\d+\\.?\\d*)$")) {
		return hre.getMatchDouble(1);
	} else if (hre.search(token, "^(\\d*\\.?\\d+)$")) {
		return hre.getMatchDouble(1);
	} else if (hre.search(token, "^(\\d+)/(\\d+)")) {
		int value1 = hre.getMatchInt(1);
		int value2 = hre.getMatchInt(2);
		if (value2 == 0) {
			return 0;
		}
		double value = value1;
		value /= value2;
		return value;
	} else if (hre.search(token, "^(\\d+)\\s*(\\+|\\s+)\\s*(\\d+)/(\\d+)")) {
		int integer = hre.getMatchInt(1);
		int value1 = hre.getMatchInt(3);
		int value2 = hre.getMatchInt(4);
		double value = integer;
		value += (double)value1/(double)value2;
		return value;
	}
	return -1;
}



//////////////////////////////
//
// addSecondsSpine -- Compile timeline into pure floating-point seconds,
//     removing tempo changes and rational times.
//

void addSecondsSpine(ostream& out, HumdrumFile& infile) {
	prepareTimeline(infile);
	for (int i=0; i<infile.getLineCount(); i++) {
		if (!infile[i].hasSpines()) {
			out << infile[i] << "\n";
			continue;
		}
		if (infile[i].isInterpretation()) {
			HTp token = infile.token(i, 0);
			if (token->compare(0, 2, "**") == 0) {
				out << "**sec";
			} else if (*token == "*-") {
				out << "*-";
			} else {
				out << "*";
			}
		} else if (infile[i].isComment()) {
			out << "!";
		} else if (infile[i].isBarline()) {
			HTp token = infile.token(i, 0);
			out << token;
		} else {
			out << m_timeline[i];
		}
		out << "\t" << infile[i] << endl;
	}
}



//////////////////////////////
//
// getMaxGlissRange -- if there are any glissandos in the part, then
//     measure the maximum depth needed for it.  This will be used
//     to automatically adjust the pitch bend depth factor if a
//     manual bend depth was not given.
//

double getMaxGlissRange(HTp pstart) {
	vector<vector<double>> glisses;
	glisses.reserve(1000);

	HTp current = pstart->getNextToken();
	double reference = 60.0;
	bool ingliss = false;
	HumRegex hre;
	while (current) {
		if (current->isInterpretation()) {
			if (hre.search(current, "^\\*ref[:=]?[A-G][#-b]?\\d+")) {
				reference = getReferencePitchAsMidi(*current);
			}
		}
		if (!current->isData()) {
			current = current->getNextToken();
			continue;
		}

		if (current->find(GLISS_END) != string::npos) {
			if (ingliss && !glisses.empty()) {
				double pitch = getPitchAsMidi(current, reference);
				if (pitch > 0.0) {
					glisses.back().push_back(pitch);
				}
			}
			ingliss = false;
		}
		if (current->find(GLISS_START) != string::npos) {
				//start of glissando
			glisses.resize(glisses.size()+1);
			ingliss = true;
			double pitch = getPitchAsMidi(current, reference);
			if (pitch > 0.0) {
				glisses.back().push_back(pitch);
			}
		}
		if (!ingliss) {
			current = current->getNextToken();
			continue;
		}
		double pitch = getPitchAsMidi(current, reference);
		if (pitch > 0.0) {
			glisses.back().push_back(pitch);
		}
		current = current->getNextToken();
		continue;
	}

	int glisscount = glisses.size();
	double maxwidth = 0.0;
	for (int i=0; i<glisscount; i++) {
		double width = getGlissWidth(glisses[i]);
		if (width > maxwidth) {
			maxwidth = width;
		}
	}
	double output = 2.0 * maxwidth + 1.0;
	if (output < 2.0) {
		output = 2.0;
	}
	if ((output > 2.0) && (output < 23.0)) {
		// add extra safety buffer
		output += 1.0;
	}
	if (output > 24.0) {
		output = 24.0;
	}
	if (m_debugQ) {
		int track = pstart->getTrack();
		cerr << "Glissando list for track " << track << ":" << endl;
		for (int i=0; i<(int)glisses.size(); i++) {
			cerr << "\t";
			for (int j=0; j<(int)glisses[i].size(); j++) {
				cerr << glisses[i][j] << " ";
			}
		}
		cerr << endl;
		cerr << "GLISSANDO DEPTH FOR TRACK " << track << ": " << output << endl;
	}

	return output;
}



//////////////////////////////
//
// getGlissWidth -- return the maximum absolute distance from the first
//     note in the gliss to any following note in the gliss.
//

double getGlissWidth(vector<double>& gliss) {
	if (gliss.empty()) {
		return 0.0;
	}
	if (gliss.size() == 1) {
		return 0.0;
	}
	if (gliss[0] <= 0.0) {
		return 0.0;
	}
	double maxdiff = 0.0;
	for (int i=1; i<(int)gliss.size(); i++) {
		if (gliss[i] <= 0.0) {
			continue;
		}
		double diff = fabs(gliss[i] - gliss[0]);
		if (diff > maxdiff) {
			maxdiff = diff;
		}
	}
	return maxdiff;
}



