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
void    generateRatioTrack(MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile);
void    generateDrumTrack (MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile);
void    buildTimemap      (HTp sstart, HumdrumFile& infile);
void    buildNullTimemap  (HumdrumFile& infile);
double  getMidiNoteNumber (string refpitch);
int     getEndTime        (HTp stok);
void    addTempoMessages  (MidiFile& outfile, HTp sstart);
void    addTempoMessagesNull(MidiFile& outfile, HumdrumFile& infile);
void    addGlissando      (MidiFile& outfile, int track, HTp current, double spitch, double reference, int channel);
double  getPitchAsMidi    (HTp token, double reference);
double  getPitchBend      (double pitch, int channel);
double  getPitchBend      (double pitch, double spitch, int channel);
HTp     getNextPitchToken (HTp token);
int     getAttackVelocity (HTp rtoken, int baseline, int step);
void    prepareTimeline   (HumdrumFile& infile);
void    getTimeData       (HTp sstart, vector<double>& numbers,
                           vector<double>& tempo, int lines);
void    prepareTimelineRecip(vector<double>& timeline, HTp sstart, int lines);
void    prepareTimelineDtime(vector<double>& timeline, HTp sstart, int lines);
void    prepareTimelineTime(vector<double>& timeline, HTp sstart, int lines);
void    prepareTimelineNull(vector<double>& timeline, HumdrumFile& infile);
double  getTimeNumber     (HTp token);
void    addSecondsSpine   (ostream& out, HumdrumFile& infile);
double  getReferencePitchAsMidi(const string& token);
double  getMaxGlissRange  (HTp pstart);
double  getGlissWidth     (vector<double>& gliss);
void    fillCurrentTempo  (HumdrumFile& infile, HTp timespine);
void    fillCurrentTempoNull(HumdrumFile& infile);
void    fillGraceDur      (HumdrumFile& infile, HTp timespine);
HTp     getVelToken       (HTp current);
vector<int> getDrumsAsMidi(HTp current);
void    getSubstitutions  (HumdrumFile& infile);
string  applyRatioSubstitutions(const string& input);
string  applyDrumSubstitutions(const string& input);
void    simplifyOperations(string &cleaned);
void    sortLongestToShortest(vector<pair<string, string>>& subs);
bool    reallyHasGliss    (HTp token);


// variables:
vector<HTp> m_sstarts;               // starting tokens of spines
vector<HTp> m_velStarts;             // starting tokens of **vel spines
vector<HTp> m_velStartsDrum;         // starting tokens of **vel spines for **drum.
vector<HTp> m_volStarts;             // starting tokens of **vol spines
vector<HTp> m_volStartsDrum;         // starting tokens of **vol spines for **drum.
vector<HTp> m_ratioStarts;           // starting tokens of **ratio spines
vector<HTp> m_drumStarts;            // starting tokens of **drum spines
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
vector<int> m_graceDur;              // grace note duration (ms units)
double      m_maxtime = 0.0;         // maximum time of output MIDI file
vector<double> m_timeline;           // used with --max-time option
bool        m_printTimemap = false; // used with -t option
bool        m_debugQ = false;        // used with --debug option
vector<double> m_currTempo;          // used for grate calculations
vector<pair<string, string>> m_ratioSubs; // used with !!!RDF**ratio:
vector<pair<string, string>> m_drumSubs;  // used with !!!RDF**drum:
int         m_pad = 0;

///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	Options options;
	options.define("o|output=s",       "output name for MIDI file when using standard input.");
	options.define("r|raw=b",          "output raw MIDI data to stdout.");
	options.define("x|max-time=d:0.0", "maximum duration of output MIDI file in seconds");
	options.define("s|seconds=b",      "add time in seconds spine (resolving tempo changes)");
	options.define("p|pad=i:0",        "padding time in ms to start of MIDI data");
	options.define("t|timeline=b",     "print timeline");
	options.define("debug=b",          "display debugging information");
	options.process(argc, argv);
	m_maxtime = options.getDouble("max-time");
	m_debugQ = options.getBoolean("debug");
	m_pad = options.getInteger("pad");
	m_printTimemap = options.getBoolean("timeline");

	HumdrumFile infile;

	MidiFile outfile;
	outfile.clear();

	// Set ticks-per-quarter note.  Could be adjusted if **recip timeline.
	outfile.setTicksPerQuarterNote(1000);  // using millisecond ticks

	Tool_filter filter;

	m_pbrange.resize(16);
	fill(m_pbrange.begin(), m_pbrange.end(), 2.0);

	if (options.getArgCount() == 0) {
		HumdrumFileStream instream(options);
		HumdrumFile infile;
		while (instream.read(infile)) {
			infile.analyzeStructure();  // instream import not running analyzeStructure();
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
		}

		outfile.addTempo(0, 0, 60.0);
		outfile.markSequence();
		outfile.sortTracks();

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
		HumdrumFileStream instream(options);
		HumdrumFile infile;
		while (instream.read(infile)) {
			infile.analyzeStructure();  // instream import not running analyzeStructure();

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
		}

		outfile.addTempo(0, 0, 60.0);
		outfile.markSequence();
		outfile.sortTracks();

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
			outfile.clear();
			outfile.setTicksPerQuarterNote(1000);  // using millisecond ticks
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

			outfile.addTempo(0, 0, 60.0);
			outfile.markSequence();
			outfile.sortTracks();

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
		// return false;
	}

	m_ratioStarts.resize(0);
	m_drumStarts.resize(0);
	m_velStarts.resize(0);
	m_volStarts.resize(0);
	m_velStartsDrum.resize(0);
	m_volStartsDrum.resize(0);
	m_hasDyn = false;
	HTp velStart = NULL;
	HTp volStart = NULL;

	getSubstitutions(infile);

	for (int i=(int)m_sstarts.size() - 1; i>=0; i--) {
		if (*m_sstarts[i] == "**vel") {
			velStart = m_sstarts[i];
		}
		if (*m_sstarts[i] == "**vol") {
			volStart = m_sstarts[i];
		}

		if (*m_sstarts[i] == "**ratio") {
			m_ratioStarts.push_back(m_sstarts[i]);
			if (velStart) {
				m_velStarts.push_back(velStart);
				velStart = NULL;
				m_hasDyn = true;
			} else {
				m_velStarts.push_back(NULL);
			}
			if (volStart) {
				m_volStarts.push_back(volStart);
				volStart = NULL;
				m_hasDyn = true;
			} else {
				m_volStarts.push_back(NULL);
			}
		}

		if (*m_sstarts[i] == "**drum") {
			m_drumStarts.push_back(m_sstarts[i]);
			if (velStart) {
				m_velStartsDrum.push_back(velStart);
				velStart = NULL;
				m_hasDyn = true;
			} else {
				m_velStartsDrum.push_back(NULL);
			}
			if (volStart) {
				m_volStarts.push_back(volStart);
				volStart = NULL;
				m_hasDyn = true;
			} else {
				m_volStarts.push_back(NULL);
			}
		}

	}

	fillGraceDur(infile, timespine);
	fillCurrentTempo(infile, timespine);
	// needs to be done after fillCurrentTempo due to grace note calculations
	buildTimemap(timespine, infile);

	int newtracks = (int)(m_ratioStarts.size() + m_drumStarts.size());
	if (newtracks <= 0) {
		return false;
	}

	int starttracks = outfile.getTrackCount();

	outfile.addTracks(newtracks); // originally one track, which is for expression


	int ratiotracks = (int)m_ratioStarts.size();
	for (int i=0; i<ratiotracks; i++) {
		generateRatioTrack(outfile, i+starttracks, m_ratioStarts[i], m_velStarts[i], infile);
	}
	for (int i=0; i<(int)m_drumStarts.size(); i++) {
		generateDrumTrack(outfile, ratiotracks+i+starttracks, m_drumStarts[i], m_velStartsDrum[i], infile);
	}

	if (timespine) {
		addTempoMessages(outfile, timespine);
	} else {
		addTempoMessagesNull(outfile, infile);
	}

	return true;
}



//////////////////////////////
//
// getSubstitutions --
//

void getSubstitutions(HumdrumFile& infile) {
	HumRegex hre;

	m_ratioSubs.clear();
	m_drumSubs.clear();

	for (int i=0; i<infile.getLineCount(); i++) {
		if (infile[i].hasSpines()) {
			continue;
		}
		HTp token = infile.token(i, 0);
		if (hre.search(token, "^!!!RDF\\*\\*ratio\\s*:\\s*([^\\s]+)\\s*=\\s*(.*)\\s*")) {
			string symbol = hre.getMatch(1);
			string replacement = hre.getMatch(2);
			hre.replaceDestructive(replacement, " ", "\t", "g");
			m_ratioSubs.push_back(make_pair(symbol, replacement));
		}
		if (hre.search(token, "^!!!RDF\\*\\*drum\\s*:\\s*([^\\s]+)\\s*=\\s*(.*)\\s*")) {
			string symbol = hre.getMatch(1);
			string replacement = hre.getMatch(2);
			hre.replaceDestructive(replacement, " ", "\t", "g");
			m_drumSubs.push_back(make_pair(symbol, replacement));
		}
	}

	sortLongestToShortest(m_ratioSubs);
	sortLongestToShortest(m_drumSubs);
}



//////////////////////////////
//
// sortLongestToShortest -- For substitutions, apply the longest
//      substitutions first then the shortest to avoid overlaps
//      in the substitution patterns from interfering with each other.
//

void sortLongestToShortest(vector<pair<string, string>>& subs) {
	sort(subs.begin(), subs.end(),
		[](const pair<string, string> &a, 
		   const pair<string, string> &b)
		{
			int sizea = (int)a.first.size();
			int sizeb = (int)b.first.size();
			return sizea > sizeb;
		}
	);
}



//////////////////////////////
//
// fillCurrentTempoNull -- If there is no timeline, then read tempo markings
//     from any (and all) **ratio and **drum spines instead.
//

void fillCurrentTempoNull(HumdrumFile& infile) {
	int lines = infile.getLineCount();
	m_currTempo.resize(lines);
	fill(m_currTempo.begin(), m_currTempo.end(), 60.0);

	HumRegex hre;
	double tempo = 60.0;
	for (int i=0; i<lines; i++) {
		if (!infile[i].isInterpretation()) {
			m_currTempo[i] = tempo;
			continue;
		}
		for (int j=0; j<infile[i].getFieldCount(); j++) {
			HTp token = infile.token(i, j);
			if (hre.search(token, "^\\*MM(\\d+\\.?\\d*)")) {
				tempo = hre.getMatchDouble(1);
			}
		}
		if (tempo <= 0.0) {
			tempo = 60.0;
		}
		m_currTempo.at(i) = tempo;
	}
}



//////////////////////////////
//
// fillCurrentTempo -- Record the active tempo at each line in the
//    score.  This is used for the *grate: (gliss update rate) value.
//    The default is *grate:50 (50 millisecond updates), but *grate:20
//    would be 20 millisecond updates.
//

void fillCurrentTempo(HumdrumFile& infile, HTp timespine) {
	if (!timespine) {
		fillCurrentTempoNull(infile);
		return;
	}
	m_currTempo.resize(infile.getLineCount());
	fill(m_currTempo.begin(), m_currTempo.end(), 60.0);
	HTp current = timespine->getNextToken();
	HumRegex hre;
	double tempo = 60.0;
	while (current) {
		if (hre.search(current, "^\\*MM(\\d+\\.?\\d*)")) {
			tempo = hre.getMatchDouble(1);
		} else if (hre.search(current, "^\\*MM(\\d*\\.?\\d+)")) {
			tempo = hre.getMatchDouble(1);
		}
		if (tempo <= 0.0) {
			tempo = 60.0;
		}
		int lindex = current->getLineIndex();
		m_currTempo.at(lindex) = tempo;
		current = current->getNextToken();
	}

	if (m_debugQ) {
		cerr << "TEMPO ======================\n";
		for (int i=0; i<(int)m_currTempo.size(); i++) {
			cerr << m_currTempo.at(i) << "\t" << infile[i] << endl;
		}
		cerr << "============================" << endl;
	}

}



//////////////////////////////
//
// fillGraceDur -- Keep track of the grace note duration.
//    The default is *grace:100 (100 millisecond gracenotes).
//

void fillGraceDur(HumdrumFile& infile, HTp timespine) {
	m_graceDur.resize(infile.getLineCount());
	if (!timespine) {
		fill(m_graceDur.begin(), m_graceDur.end(), 100);
		return;
	}
	fill(m_graceDur.begin(), m_graceDur.end(), -1);

	HTp current = timespine->getNextToken();
	HumRegex hre;
	int gracetime = 100;
	while (current) {
		if (hre.search(current, "^\\*grace:(\\d+)")) {
			gracetime = hre.getMatchInt(1);
		} else {
			current = current->getNextToken();
			continue;
		}
		if (gracetime <= 10) {
			gracetime = 10;
		}
		int lindex = current->getLineIndex();
		m_graceDur.at(lindex) = gracetime;
		current = current->getNextToken();
	}

	m_graceDur[0] = 100;
	for (int i=1; i<(int)m_graceDur.size(); i++) {
		if (m_graceDur[i] < 0) {
			m_graceDur[i] = m_graceDur[i-1];
		}
	}

	if (m_debugQ) {
		cerr << "GRADEDUR ======================\n";
		for (int i=0; i<(int)m_graceDur.size(); i++) {
			cerr << m_graceDur.at(i) << "\t" << infile[i] << endl;
		}
		cerr << "============================" << endl;
	}

}



//////////////////////////////
//
// addTempoMessagesNull -- Check spines for tempo changes.
//

void addTempoMessagesNull(MidiFile& outfile, HumdrumFile& infile) {
	HumRegex hre;

	int lines = infile.getLineCount();
	for (int i=0; i<lines; i++) {
		if (!infile[i].isInterpretation()) {
			continue;
		}
		for (int j=0; j<infile[i].getFieldCount(); j++) {
			HTp token = infile.token(i, j);
			if (hre.search(token, "^\\*MM(\\d+\\.?\\d*)$")) {
				double tempo = hre.getMatchDouble(1);
				int starttime = m_timemap[i] + m_pad;
				if (m_first_tempo_time >= 0) {
					if (starttime < m_first_tempo_time) {
						m_first_tempo_time = starttime;
					}
				} else {
					m_first_tempo_time = starttime;
				}
				outfile.addTempo(0, starttime, tempo);
			}
		}
	}

	if (m_first_tempo_time != 0) {
		// set the default tempo to 60 bpm:
		outfile.addTempo(0, 0, 60.0);
	}
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
			int starttime = m_timemap[current->getLineIndex()] + m_pad;
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
// buildNullTimemap -- Convert an implicit time spine into
//   millisecond values, interpolating evenly when the
//   data contains a null.
//

void buildNullTimemap(HumdrumFile& infile) {

	int lines = infile.getLineCount();
	m_timemap.clear();
	m_timemap.resize(lines);
	fill(m_timemap.begin(), m_timemap.end(), -2);

	vector<int*> tdata;
	tdata.reserve(m_timemap.size());

	bool dtime = true;
	bool delta = true;
	double lasttime = 0.0;

	for (int i=0; i<lines; i++) {
		if (!infile[i].isData()) {
			continue;
		}
		int line = i;
		tdata.push_back(&m_timemap.at(line));
		m_timemap[line] = int(1.0 * 1000.0 + 0.5);
		if (delta) {
			m_lastDuration = m_timemap[line];
			int tempval = m_timemap[line] += lasttime;
			m_timemap[line] = lasttime;
			lasttime = tempval;
		}
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

	// fill in timings for nondata:
	for (int i=1; i<(int)m_timemap.size(); i++) {
		if (m_timemap[i] < 0) {
			m_timemap[i] = m_timemap[i-1];
		}
	}
}


//////////////////////////////
//
// buildTimemap -- Convert time spine into millisecond values, interpolating
//   evenly when the data contains a null.
//

void buildTimemap(HTp sstart, HumdrumFile& infile) {
	if (!sstart) {
		buildNullTimemap(infile);
		return;
	}

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


	vector<int*> points;
	vector<int> index;
	for (int i=0; i<infile.getLineCount(); i++) {
		if (infile[i].isData()) {
			points.push_back(&m_timemap.at(i));
			index.push_back(i);
		}
	}

	// Check for grace notes and adjust timeline to fit them in.
	// Currently only one grace note in a row is expected.
	for (int i=1; i<(int)points.size() - 1; i++) {
		int value0 = *points[i-1];
		int value1 = *points[i];
		int value2 = *points[i+1];
		int dur = value2 - value1;
		double tempo = m_currTempo.at(index.at(i));
		int olddur = value1 - value0;
		int gracetime = int(m_graceDur.at(index.at(i)) * tempo / 60.0 + 0.5);
		if (dur <= 0) {
			if (olddur < 2 * gracetime) {
				*points[i] -= olddur / 2;
			} else {
				*points[i] -= gracetime;
			}
		}
	}

	// fill in timings for nondata:
	for (int i=1; i<(int)m_timemap.size(); i++) {
		if (m_timemap[i] < 0) {
			m_timemap[i] = m_timemap[i-1];
		}
	}

	if (m_printTimemap) {
		for (int i=0; i<m_timemap.size(); i++) {
			cout << m_timemap.at(i) << "\t" << infile[i] << endl;
		}
	}
}



//////////////////////////////
//
// generateRatioTrack -- Convert a ratio spine into a MIDI track.  Each track
//    should be given a unique channel.  Currently the channel is derived from
//    the track number (avoiding the drum channel of general MIDI).
//

void generateRatioTrack(MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile) {
	HTp current = pstart;
	HumRegex hre;
	int channel = track - 1;
	if (channel >= 9) {
		// avoid the drum channel
		channel++;
	}
	double lastattack = 0.0;

	int velstep = 10;
	int baseattackvel = m_velocity;
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
				int starttime = m_timemap[current->getLineIndex()] + m_pad;
				outfile.addTimbre(track, starttime, channel, inst);
			} else if (hre.search(current, "^\\*I#(\\d{1,3})")) {
				// Process an instrument number
				int inst = hre.getMatchInt(1);
				if (inst > 127) {
					inst = 127;
				}
				int starttime = m_timemap[current->getLineIndex()] + m_pad;
				outfile.addTimbre(track, starttime, channel, inst);
			} else if (hre.search(current, "^\\*MM(\\d+\\.?\\d*)$")) {
				// Process a tempo change.  It should not be
				// here, but rather in the **time spine, but
				// process these anyway.
				double tempo = hre.getMatchDouble(1);
				int starttime = m_timemap[current->getLineIndex()] + m_pad;
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
				int starttime = m_timemap[current->getLineIndex()] + m_pad;
				outfile.setPitchBendRange(track, starttime, channel, range);
				hasBend = true;
				wroteBend = true;
				m_pbrange.at(channel) = range;
			} else if (hre.search(current, "^\\*grate[:=]?(\\d+)$")) {
				int value = hre.getMatchInt(1);
				if (value > 0) {
					int track = current->getTrack();
					m_glissTime[track] = value;
				}
			} else if (hre.search(current, "^\\*vel[:=]?(\\d+)$")) {
				int value = hre.getMatchInt(1);
				if ((value > 0) && (value <128)) {
					baseattackvel = value;
				}
			} else if (hre.search(current, "^\\*vstep[:=]?(\\d+)$")) {
				// attack velocity increment for v/V encodings.
				int value = hre.getMatchInt(1);
				velstep = value;
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
					int starttime = m_timemap[current->getLineIndex()] + m_pad;
					outfile.addController(track, starttime, channel, 10, pan);
				}
			} else if (hre.search(current, "^\\*ref[:=]?.*\\d")) {
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

			int starttime = m_timemap[current->getLineIndex()] + m_pad;
			int endtime = getEndTime(current) - 1;
			int ptime = starttime - m_pbadjust;
			if (ptime < 0) {
				ptime = 0;
			}

			// if (hasDyn) {
			// 	volume = getAttackVelocity(current, baseattackvel);
			// }
			int attack = getAttackVelocity(current, baseattackvel, velstep);

			if (current->find('_') == string::npos) {
				outfile.addPitchBend(track, ptime, channel, pbend);
				outfile.addNoteOn(track, starttime, channel, int(pitch), attack);
				outfile.addNoteOff(track, endtime, channel, int(pitch), attack);
				lastattack = pitch;
			} else {
				// this is a tied note, so ignored for note attacks, but add
				// pitch bend:
				pbend = getPitchBend(pitch, lastattack, channel);
				outfile.addPitchBend(track, ptime, channel, pbend);
			}

			if (current->find(GLISS_START) != string::npos) {
				if (reallyHasGliss(current)) {
					addGlissando(outfile, track, current, pitch, reference, channel);
				}
			}
		}
		current = current->getNextToken();
		continue;
	}
}



//////////////////////////////
//
// reallyHasGliss --
//

bool reallyHasGliss(HTp token) {
	string subvalue = applyRatioSubstitutions(*token);
	if (subvalue.find(GLISS_START) != string::npos) {
		return true;
	} else {
		return false;
	}
}



//////////////////////////////
//
// generateDrumTrack -- Convert a drum spine into a MIDI track.  Each track
//    should be given a unique channel.  Currently the channel is derived from
//    the track number (avoiding the drum channel of general MIDI).
//

void generateDrumTrack(MidiFile& outfile, int track, HTp pstart, HTp dstart, HumdrumFile& infile) {
	HTp current = pstart;
	HumRegex hre;
	int channel = 9;
	double lastattack = 0.0;

	int velstep = 10;
	int baseattackvel = m_velocity;
	double reference;
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
			if (hre.search(current, "^\\*vel[:=]?(\\d+)$")) {
				int value = hre.getMatchInt(1);
				if ((value > 0) && (value <128)) {
					baseattackvel = value;
				}
			} else if (hre.search(current, "^\\*vstep[:=]?(\\d+)$")) {
				// Attack velocity increment for v/V encodings.
				int value = hre.getMatchInt(1);
				velstep = value;
			} else if (hre.search(current, "^\\*pan[:=]?(-?\\d*\\.\\d*)$")) {
				// Only one pan value shared across all drum tracks.
				string match = hre.getMatch(1);
				if (!match.empty()) {
					double panvalue = hre.getMatchDouble(1);
					int pan = int(((panvalue + 1.0)/2.0) * 127);
					if (pan < 0) {
						pan = 0;
					} else if (pan > 127) {
						pan = 127;
					}
					int starttime = m_timemap[current->getLineIndex()] + m_pad;
					outfile.addController(track, starttime, channel, 10, pan);
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

			vector<int> drums = getDrumsAsMidi(current);
			int starttime = m_timemap[current->getLineIndex()] + m_pad;

			// if (hasDyn) {
			// 	volume = getAttackVelocity(current, baseattackvel);
			// }
			// allow independent adjustment of volumes of drum notes?
			int attack = getAttackVelocity(current, baseattackvel, velstep);

			for (int j=0; j<(int)drums.size(); j++) {
				outfile.addNoteOn(track, starttime, channel, drums.at(j), attack);
			}
		}
		current = current->getNextToken();
		continue;
	}
}



//////////////////////////////
//
// getDrumsAsMidi --
//

vector<int> getDrumsAsMidi(HTp current){
	HumRegex hre;
	string text = applyDrumSubstitutions(*current);
	vector<int> output;
	while (hre.search(text, "(\\d+)")) {
		int value = hre.getMatchInt(1);
		output.push_back(value);
		hre.replaceDestructive(text, "",  "\\d+");
	}
	return output;
}



//////////////////////////////
//
// getReferencePitchAsMidi --
//

double getReferencePitchAsMidi(const string& token) {
	HumRegex hre;
	double reference = 60; // default reference

	// Read reference as frequency:
	if (hre.search(token, "^\\*ref[:=]?(\\d+\\.?\\d*)z")) {
		double frequency = hre.getMatchDouble(1);
		reference = 12.0 * log2(frequency / 440.0) + 69.0;
	}
	else if (hre.search(token, "^\\*ref[:=]?(\\d+\\.?\\d*)$")) {
		// Allow incorrectly labeled frequency (missing "z"):
		double frequency = hre.getMatchDouble(1);
		reference = 12.0 * log2(frequency / 440.0) + 69.0;
	}

	// Read reference as MIDI key number:
	else if (hre.search(token, "^\\*ref[:=]?(\\d+\\.?\\d*)m")) {
		reference = hre.getMatchDouble(1);
	}

	// Read reference as note name:
	else if (hre.search(token, "^\\*ref[:=]?([A-G][#-b]?\\d+)([+-]\\d+\\.?\\d*c)?")) {
		reference = 60.0;  // default reference
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
// getVelToken -- search for the next **vel spine after the current one,
//     but before any **ratio spines.
//

HTp getVelToken(HTp current) {
	if (!current) {
		return NULL;
	}
	current = current->getNextFieldToken();
	if (!current) {
		return NULL;
	}
	while (current) {
		if (current->isDataType("**ratio")) {
			return NULL;
		}
		if (current->isDataType("**vel")) {
			return current;
		}
		current = current->getNextFieldToken();
	}
	return NULL;
}



//////////////////////////////
//
// getAttackVelocity --
//

int getAttackVelocity(HTp rtoken, int basevel, int velstep) {
	int output = basevel;
	HTp veltok = getVelToken(rtoken);
	if (veltok) {
		if (veltok->isNull()) {
			veltok = veltok->resolveNull();
		}
		if (!veltok) {
			return output;
		}
		HumRegex hre;
		if (!hre.search(veltok, "(\\d+)")) {
			return output;
		}
		output = hre.getMatchInt(1);
		return output;
	}

	for (int i=0; i<(int)rtoken->size(); i++) {
		if (rtoken->at(i) == 'v') {
			output -= velstep;
		} else if (rtoken->at(i) == 'V') {
			output += velstep;
		}
	}
	if (output < 1) {
		output = 1;
	} else if (output > 127) {
		output = 127;
	}
	return output;
}

/*  This code will be used for volume continuous controllers
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

*/


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
//          5            == a rational number value with no denominator (a harmonic)
//          5/4          == a rational number
//          (5/4)^3      == a rational number with exponentiation
//          3^(5/4)      == a rational number exponent
//          (3/2)^(5/4)  == a rational number with rational number exponent
//          235.35c      == a cent interval above the reference pitch
//         +235.35c      == a cent interval above the reference pitch
//         -235.35c      == a cent interval above the reference pitch
//       frequencies:
//           440.23z     == 440.23 Hertz
//

double getPitchAsMidi(HTp token, double reference) {
	int top;
	int bot;
	HumNum value;
	HumRegex hre;
	double pcents;
	string botstring;

	if (m_debugQ) {
		cerr << "CONVERTING " << token << " TO MIDI NOTE NUMBER" << endl;
	}

	// Convert substitutions to actual data:
	string cleaned = applyRatioSubstitutions(*token);

	if (m_debugQ) {
		cerr << "\tAFTER SUBSTITUTIONS " << cleaned << endl;
	}

	// Convert ":" to "/"
	hre.replaceDestructive(cleaned, "/", ":", "g");

	string tempclean = cleaned;
	// Remove non-pitch information from token, including whitespace:
	hre.replaceDestructive(tempclean, "", "[ Hh_]", "g");

	// Check if only a cent interval (not allowed have expressions yet)::
	if (hre.search(tempclean, "^([+-]?\\d+\\.?\\d*)c$")) {
		double cents = hre.getMatchDouble(1);
		return cents/100.0 + reference;
	}

	// Check if only a frequency (not allowed have expressions yet):
	if (hre.search(tempclean, "^([+]?\\d+\\.?\\d*)z$")) {
		double frequency = hre.getMatchDouble(1);
		if (frequency <= 0.0) {
			return 0.0;
		}
		double midi = 12.0 * log2(frequency / 440.0) + 69.0;
		return midi;
	} else if (hre.search(tempclean, "^([+]?\\d+\\.?\\d*)m$")) {
		double midi = hre.getMatchDouble(1);
		return midi;
	}

	if (m_debugQ) {
		cerr << "\tINITIAL ROUND OF SIMPLIFICATION: " << cleaned << endl;
	}

	simplifyOperations(cleaned);

	// Remove non-pitch information from token, including whitespace:
	hre.replaceDestructive(cleaned, "", "[ Hh_]", "g");

	if (m_debugQ) {
		cerr << "\tAFTER FIRST ROUND OF CLEANING: " << cleaned << endl;
	}

	if (hre.search(cleaned, "[^0-9\\.-]")) {
		// do a second round of cleaning
		simplifyOperations(cleaned);
		if (m_debugQ) {
			cerr << "\tAFTER SECOND ROUND OF CLEANING: " << cleaned << endl;
		}

		if (hre.search(cleaned, "[^0-9\\.-]")) {
			// do a third round of cleaning
			simplifyOperations(cleaned);
			if (m_debugQ) {
				cerr << "\tAFTER THIRD ROUND OF CLEANING: " << cleaned << endl;
			}

			if (hre.search(cleaned, "[^0-9\\.-]")) {
				// do a third round of cleaning
				simplifyOperations(cleaned);
				if (m_debugQ) {
					cerr << "\tAFTER FOURTH ROUND OF CLEANING: " << cleaned << endl;
				}

				if (hre.search(cleaned, "[^0-9\\.-]")) {
					// do a third round of cleaning
					simplifyOperations(cleaned);
					if (m_debugQ) {
						cerr << "\tAFTER FIFTH ROUND OF CLEANING: " << cleaned << endl;
					}
				}
			}
		}
	}

	// check if finally reduced:
	if (hre.search(cleaned, "^(\\d+\\.?\\d*)$")) {
		// floading-point ratio
		double value = hre.getMatchDouble(1);
		double mvalue = log2(value) * 12;
		return reference + mvalue;
	}
	if (hre.search(cleaned, "^(\\d*\\.?\\d+)$")) {
		// floating-point ratio
		double value = hre.getMatchDouble(1);
		double mvalue = log2(value) * 12;
		return reference + mvalue;
	}

	//////////////////////////////

	// Reduce "#^#" (has priority over #*# and #/#)
	while (hre.search(cleaned, "(\\d+\\.?\\d*)\\^(-?\\d+\\.?\\d*)")) {
		double number1 = hre.getMatchDouble(1);
		double number2 = hre.getMatchDouble(2);
		double value = pow(number1, number2);
		stringstream sstr;
		sstr.str("");
		sstr << value;
		hre.replaceDestructive(cleaned, sstr.str(), "(\\d+\\.?\\d*)\\^(-?\\d+\\.?\\d*)");
	}

	// Reduce "#*#" (considering only integers, at least for now)
	// Maybe allow long long ints for large values
	while (hre.search(cleaned, "(\\d+)\\*(\\d+)")) {
		double number1 = hre.getMatchDouble(1);
		double number2 = hre.getMatchDouble(2);
		double value = number1 * number2;
		stringstream sstr;
		sstr.str("");
		sstr << value;
		hre.replaceDestructive(cleaned, sstr.str(), "(\\d+)\\*(\\d+)");
	}

	// Reduce "(#/#)" (considering only integers)
	while (hre.search(cleaned, "\\((\\d+\\.?\\d*)/(\\d+\\.?\\d*)\\)")) {
		double number1 = hre.getMatchDouble(1);
		double number2 = hre.getMatchDouble(2);
		double value = number1 / number2;
		stringstream sstr;
		sstr.str("");
		sstr << value;
		hre.replaceDestructive(cleaned, sstr.str(), "\\((\\d+\\.?\\d*)/(\\d+\\.?\\d*)\\)");
	}

	// Remove parentheses "(#)"
	while (hre.search(cleaned, "\\((\\d+\\.?\\d*)\\)")) {
		double number = hre.getMatchDouble(1);
		stringstream sstr;
		sstr.str("");
		sstr << number;
		hre.replaceDestructive(cleaned, sstr.str(), "\\((\\d+\\.?\\d*)\\)");
	}

	if (hre.search(cleaned, "^(\\d+\\.?\\d*)$")) {
		// floading-point ratio
		double value = hre.getMatchDouble(1);
		double mvalue = log2(value) * 12;
		return reference + mvalue;
	}

	if (hre.search(cleaned, "^(\\d*\\.?\\d+)$")) {
		// floading-point ratio
		double value = hre.getMatchDouble(1);
		double mvalue = log2(value) * 12;
		return reference + mvalue;
	}

	//////////////////////////////

	if (!hre.search(cleaned, "(\\d+)(?:/(\\d+))?")) {
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

	double mvalue = log2(value.getFloat()) * 12;
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
	double pitch = reference + mvalue + pcents / 100.0;
	return pitch;
}


//////////////////////////////
//
// simplifyOperations --
//

void simplifyOperations(string &cleaned) {
	HumRegex hre;

	// Convert cents to a floating-point ratio:
	while (hre.search(cleaned, "(-?\\d+\\.?\\d*)c")) {
		double number = hre.getMatchDouble(1);
		double value = pow(2.0, number/1200.0);
		if (m_debugQ) {
			cerr << "\t\tREDUCING " << number << " TO " << value << endl;
		}
		stringstream sstr;
		sstr.str("");
		sstr << value;
		hre.replaceDestructive(cleaned, sstr.str(), "(-?\\d+\\.?\\d*)c");
	}

	// Reduce "#^#" (has priority over #*# and #/#)
	while (hre.search(cleaned, "(\\d+\\.?\\d*)\\^(-?\\d+\\.?\\d*)")) {
		double number1 = hre.getMatchDouble(1);
		double number2 = hre.getMatchDouble(2);
		double value = pow(number1, number2);
		if (m_debugQ) {
			cerr << "\t\tREDUCING " << cleaned << " WITH " << number1 << "^" << number2 << " = " << value << endl;
		}
		stringstream sstr;
		sstr.str("");
		sstr << value;
		hre.replaceDestructive(cleaned, sstr.str(), "(\\d+\\.?\\d*)\\^(-?\\d+\\.?\\d*)");
	}

	// Reduce "#*#" (considering only integers, at least for now)
	// Maybe allow long long ints for large values
	while (hre.search(cleaned, "(^|[^^-])(\\d+\\.?\\d*)\\*(\\d+\\.?\\d*)(?!\\^)")) {
		string starting = hre.getMatch(1);
		double number1 = hre.getMatchDouble(2);
		double number2 = hre.getMatchDouble(3);
		double value = number1 * number2;
		if (m_debugQ) {
			cerr << "\t\tREDUCING " << cleaned << " WITH " << number1 << "*" << number2 << " = " << value << endl;
		}
		stringstream sstr;
		sstr.str("");
		sstr << starting << value;
		hre.replaceDestructive(cleaned, sstr.str(), "(^|[^^-])(\\d+\\.?\\d*)\\*(\\d+\\.?\\d*)(?!\\^)");
	}

	// Reduce "(#/#)"
	while (hre.search(cleaned, "\\((\\d+\\.?\\d*)/(\\d+\\.?\\d*)\\)")) {
		double number1 = hre.getMatchDouble(1);
		double number2 = hre.getMatchDouble(2);
		double value = number1 / number2;
		if (m_debugQ) {
			cerr << "\t\tREDUCING " << cleaned << " WITH " << number1 << "/" << number2 << " = " << value << endl;
		}
		stringstream sstr;
		sstr.str("");
		sstr << value;
		hre.replaceDestructive(cleaned, sstr.str(), "\\((\\d+\\.?\\d*)/(\\d+\\.?\\d*)\\)");
	}

	// Remove parentheses "(#)"
	while (hre.search(cleaned, "\\((\\d+\\.?\\d*)\\)")) {
		double number = hre.getMatchDouble(1);
		if (m_debugQ) {
			cerr << "\t\tREMOVING PAREN " << number << endl;
		}
		stringstream sstr;
		sstr.str("");
		sstr << number;
		hre.replaceDestructive(cleaned, sstr.str(), "\\((\\d+\\.?\\d*)\\)");
	}
	while (hre.search(cleaned, "\\((\\d*\\.?\\d+)\\)")) {
		double number = hre.getMatchDouble(1);
		if (m_debugQ) {
			cerr << "\t\tREMOVING PARENB " << number << endl;
		}
		stringstream sstr;
		sstr.str("");
		sstr << number;
		hre.replaceDestructive(cleaned, sstr.str(), "\\((\\d*\\.?\\d+)\\)");
	}


	// Reduce "#/#" if that is all that is in the string:
	if (hre.search(cleaned, "^\\(?(\\d+\\.?\\d*)/(\\d+\\.?\\d*)\\)?$")) {
		double number1 = hre.getMatchDouble(1);
		double number2 = hre.getMatchDouble(2);
		double value = number1 / number2;
		if (m_debugQ) {
			cerr << "\t\tREDUCING " << cleaned << " WITH " << number1 << "/" << number2 << " = " << value << endl;
		}
		stringstream sstr;
		sstr.str("");
		sstr << value;
		hre.replaceDestructive(cleaned, sstr.str(), "^\\(?(\\d+\\.?\\d*)/(\\d+\\.?\\d*)\\)?$");
	}

}



//////////////////////////////
//
// applyRatioSubstitutions --
//

string applyRatioSubstitutions(const string& input) {
	if (m_ratioSubs.empty()) {
		return input;
	}
	HumRegex hre;
	string output = input;
	for (int i=0; i<(int)m_ratioSubs.size(); i++) {
		string symbol = m_ratioSubs[i].first;
		string replacement = "(";
		replacement += m_ratioSubs[i].second;
		replacement += ")";
		hre.replaceDestructive(output, replacement, symbol, "g");
	}
	return output;
}



//////////////////////////////
//
// applyDrumSubstitutions --
//

string applyDrumSubstitutions(const string& input) {
	if (m_drumSubs.empty()) {
		return input;
	}
	HumRegex hre;
	string output = input;
	for (int i=0; i<(int)m_drumSubs.size(); i++) {
		string symbol = m_drumSubs[i].first;
		string replacement = m_drumSubs[i].second;
		hre.replaceDestructive(output, replacement, symbol, "g");
	}
	return output;
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

	// Set the glissando rate based on the starting tempo of the
	// first note in the gliss.
	// double tempo = m_currTempo.at(starttok->getLineIndex());
	// double gliss_factor = tempo / 60.0;
	double gliss_factor = 1.0;

	int humtrack = starttok->getTrack();

	double npitch = getPitchAsMidi(nexttok, reference);
	double sspitch = getPitchAsMidi(starttok, reference);
	double starttime = m_timemap[starttok->getLineIndex()] + m_pad;
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
	double x = x1 + m_glissTime.at(humtrack) * gliss_factor;
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
		x += m_glissTime.at(humtrack) * gliss_factor;
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
		if (!starts[i]) {
			continue;
		}
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

	if (!timespine) {
		prepareTimelineNull(m_timeline, infile);
	} else if (*timespine == "**time") {
		prepareTimelineTime(m_timeline, timespine, infile.getLineCount());
	} else if (*timespine == "**dtime") {
		prepareTimelineDtime(m_timeline, timespine, infile.getLineCount());
	} else if (*timespine == "**recip") {
		prepareTimelineRecip(m_timeline, timespine, infile.getLineCount());
	} else {
		prepareTimelineNull(m_timeline, infile);
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
// prepareTimelineNull -- pretend a **dtime spine with all values "1".
//

void prepareTimelineNull(vector<double>& timeline, HumdrumFile& infile) {
	int lines = infile.getLineCount();
	vector<double> numbers(lines);
	vector<double> tempos(lines);
	m_timeline.resize(lines);
	fill(m_timeline.begin(), m_timeline.end(), -1);

	HumRegex hre;
	for (int i=0; i<lines; i++) {
		if (infile[i].isInterpretation()) {
			double atempo = 0.0;
			for (int j=0; j<infile[i].getFieldCount(); j++) {
				HTp token = infile.token(i, j);
				if (hre.search(token, "^\\*MM(\\d+\\.?\\d*)")) {
				}
			}
			if (atempo > 0.0) {
				tempos[i] = atempo;
			}
		}
		if (infile[i].isData()) {
			numbers[i] = 1;
		} else {
			numbers[i] = 0;
		}
	}

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
			if (hre.search(current, "^\\*ref[:=]?.*\\d")) {
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
			if (reallyHasGliss(current)) {
				glisses.resize(glisses.size()+1);
				ingliss = true;
				double pitch = getPitchAsMidi(current, reference);
				if (pitch > 0.0) {
					glisses.back().push_back(pitch);
				}
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



