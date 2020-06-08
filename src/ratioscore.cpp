//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed May 20 09:52:32 PDT 2020
// Last Modified: Tue Jun  2 22:45:42 PDT 2020
// Filename:      ratioscore.cpp
// URL:           https://github.com/craigsapp/ratioscore/blob/master/src/ratioscore.cpp
// Syntax:        C++11
// vim:           ts=3 noexpandtab nowrap
//
// Description:   Convert a ratio score into a MIDI file.
//
// **time	**ratio	**ratio	**mdyn
// *	*ref:C4	*ref:G3	*
// 0	1	1	20g
// 1.5	2	2	30
// 1.64	3	0	.
// 2.6	3/2g	5/4+c100	50
// 3.1	.	3/2	50
// 4.2	6/5G	.	.
// *-	*-	*-	*-
//
// *I#20 = use MIDI instrument 20 (0-indexed, range 0 to 127)
// *Ivioln = use general MIDI instrument for violin
// *Iviola = use general MIDI instrument for violin
// *Icello = use general MIDI instrument for violin
// See 
//     https://github.com/craigsapp/humlib/blob/master/src/HumInstrument.cpp
// for a list of known instrument labels.
// H = start of glissando
// h = end of glissando
//

#include "humlib.h"
#include "MidiFile.h"

#include <string>
#include <cmath>

using namespace std;
using namespace smf;
using namespace hum;


// function declarations:
string  getOutputFilename (const string& filename);
bool    convertFile       (MidiFile& outfile, HumdrumFile& infile);
void    generateTrack     (MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile);
void    buildTimemap      (HTp sstart, HumdrumFile& infile);
double  getMidiNoteNumber (string refpitch);
int     getEndTime        (HTp stok);
void    addTempoMessages  (MidiFile& outfile, HTp sstart);
void    addGlissando      (MidiFile& outfile, int track, HTp current, double spitch, double reference, int channel);
double  getPitchInfo      (HTp token, double reference);
double  getPitchBend      (double pitch, int channel);
double  getPitchBend      (double pitch, double spitch, int channel);
HTp     getNextPitchToken (HTp token);
int     getVelocity       (HTp rtoken);


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


///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	Options options;
	options.define("o|output=s", "output name for MIDI file when using standard input.");
	options.process(argc, argv);

	HumdrumFile infile;
	MidiFile outfile;

	m_pbrange.resize(16);
	fill(m_pbrange.begin(), m_pbrange.end(), 2.0);

	if (options.getArgCount() == 0) {
		infile.read(cin);
		bool status = convertFile(outfile, infile);
		if (!status) {
			cerr << "Problem converting score." << endl;
			exit(1);
		}
		string filename = options.getString("output");
		if (filename.empty()){ 
			cout << outfile;
		} else {
			if (filename.find(".mid") == string::npos) {
				filename += ".mid";
			}
			outfile.write(filename);
		}
	} else if (options.getArgCount() == 1) {
		infile.read(options.getArg(1));
		bool status = convertFile(outfile, infile);
		if (!status) {
			cerr << "Problem converting score." << endl;
			exit(1);
		}
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
	} else {
		for (int i=0; i<options.getArgCount(); i++) {
			infile.read(options.getArg(i+1));
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

	bool dtime = false;
	bool recip = false;
	bool ms = false;
	bool dms = false;
	bool delta = false;
	double lasttime = 0.0;
	if (sstart->find("dtime") != string::npos) {
		dtime = true;
	}
	if (sstart->find("recip") != string::npos) {
		recip = true;
		delta = true;
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
			} else { // **time
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
//    should be given a unique channel.  Currently the channel is derive from
//    the track number (avoiding the drum channel of general MIDI).
//

void generateTrack(MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile) {
	HTp current = pstart;
	HumRegex hre;
	double rcents;
	string refpitch;
	string refcents;
	string direction;
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

	while (current) {
		if (current->isInterpretation()) {
			if (hre.search(current, "^\\*I[a-z]{3,6}$")) {
				// Process an instrument name
				int inst = instrument.getGM(*current);
				int starttime = m_timemap[current->getLineIndex()];
				outfile.addTimbre(track, starttime, channel, inst);
			} else if (hre.search(current, "^\\*I#(\\d{1,3})$")) {
				// Process an instrument name
				int inst = hre.getMatchInt(1);
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
				m_pbrange.at(channel) = range;
			} else if (hre.search(current, "^\\*gliss[:=]?(\\d+)$")) {
				int value = hre.getMatchInt(1);
				if (value > 0) {
					int track = current->getTrack();
					m_glissTime[track] = value;
				}
			} else if (hre.search(current, "^\\*ref[:=]?([A-G][#-b]?\\d+)([+-]c?\\d+\\.?\\d*)?")) {
				refpitch = hre.getMatch(1);
				reference = getMidiNoteNumber(refpitch);
				refcents  = hre.getMatch(2);
				if (!refcents.empty()) {
					if (hre.search(refcents, "([+-])(\\d+\\.?\\d*)c")) {
						direction = hre.getMatch(1);
						rcents = hre.getMatchDouble(2);
						if (direction == "-") {
							reference -= rcents / 100.0;
						} else {
							reference += rcents / 100.0;
						}
					}
				}
			}
		} else if (current->isData()) {
			if (current->isNull()) {
				current = current->getNextToken();
				continue;
			}
			if (*current == "0") {
				// ignore rest
				current = current->getNextToken();
				continue;
			}

			double pitch = getPitchInfo(current, reference);
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

			if (current->find('H') != string::npos) {
				addGlissando(outfile, track, current, pitch, reference, channel);
			}
		}
		current = current->getNextToken();
		continue;
	}
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
// getPitchInfo -- Convert ratio token into floating-point MIDI note number.
//

double getPitchInfo(HTp token, double reference) {
	int top;
	int bot;
	HumNum value;
	HumRegex hre;
	double pcents;
	string botstring;

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

	double npitch = getPitchInfo(nexttok, reference);
	double sspitch = getPitchInfo(starttok, reference);
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
			cerr << "Warning: Pitch bend exceeds maximum (increase pitch bend range)" << endl;
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

	if (nexttok->find('h') == string::npos) {
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



