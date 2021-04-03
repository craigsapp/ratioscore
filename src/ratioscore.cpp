//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed May 20 09:52:32 PDT 2020
// Last Modified: Wed May 20 12:00:31 PDT 2020
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
// *MM120   = 120 quarter notes (seconds) per minute
// *Ivioln  = use violin sound
// *I#40    = use General MIDI instrument 40 (0-indexed)
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
void    generateTrack     (MidiFile& outfile, int track, HTp pstart, int dtrack, HumdrumFile& infile);
void    buildTimemap      (HTp sstart, HumdrumFile& infile);
double  getMidiNoteNumber (string refpitch);
int     getEndTime        (HTp stok);
void    addTempoMessages  (MidiFile& outfile, HTp sstart);


// variables:
vector<HTp> m_sstarts;
vector<HTp> m_partStarts;
int         m_timeTrack = -1;
vector<int> m_dynTrack;
vector<int> m_timemap;
double      m_tuning = 440.0; // A4
int         m_first_tempo_time = -1;


///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	Options options;
	options.define("o|output=s", "output name for MIDI file when using standard input.");
	options.process(argc, argv);

	HumdrumFile infile;
	MidiFile outfile;

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

	outfile.setTPQ(1000);

	for (int i=0; i<(int)m_sstarts.size(); i++) {
		if (*m_sstarts[i] == "**time") {
			m_timeTrack = m_sstarts[i]->getTrack();
			timespine = m_sstarts[i];
			break;
		}
	}
	if (m_timeTrack < 0) {
		return false;
	}

	m_partStarts.resize(0);
	m_dynTrack.resize(0);

	int dtrack = -1;
	for (int i=(int)m_sstarts.size() - 1; i>=0; i--) {
		if (*m_sstarts[i] == "**mdyn") {
			dtrack = m_sstarts[i]->getTrack();
		}
		if (*m_sstarts[i] == "**ratio") {
			m_partStarts.push_back(m_sstarts[i]);
			m_dynTrack.push_back(dtrack);
			dtrack = -1;
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
		generateTrack(outfile, i+1, m_partStarts[i], m_dynTrack[i], infile);
	}

	addTempoMessages(outfile, timespine);

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
			m_timemap[line] = int(stod(*current) * 1000.0 + 0.5);
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
// generateTrack --
//

void generateTrack(MidiFile& outfile, int track, HTp pstart, int dtrack, HumdrumFile& infile) {
	HTp current = pstart;
	HumRegex hre;
	HumNum value;
	double rcents;
	double pcents;
	string refpitch;
	string refcents;
	string direction;
	int top;
	int bot;
	int channel = track;
	int velocity = 64;
	string botstring;
	double reference;
	HumInstrument instrument;

	while (current) {
		if (current->isInterpretation()) {
			if (hre.search(current, "^\\*I[a-z]{3,6}$")) {
				// Process an instrument name
				int inst = instrument.getGM(*current);
				int starttime = m_timemap[current->getLineIndex()];
				outfile.addTimbre(track, starttime, channel, inst);
			} else if (hre.search(current, "^\\*I#(\\d{,3})")) {
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
			} else if (hre.search(current, "^\\*ref:([A-G][#-b]?\\d+)([+-]c?\\d+\\.?\\d*)?")) {
				refpitch = hre.getMatch(1);
				reference = getMidiNoteNumber(refpitch);
				refcents  = hre.getMatch(2);
				// cerr << "REF PITCH " << refpitch << ", " << reference << endl;
				// cerr << "REF CENTS " << refcents << endl;
				if (!refcents.empty()) {
					if (hre.search(refcents, "([+-])c?(\\d+\\.?\\d*)")) {
						direction = hre.getMatch(1);
						rcents = hre.getMatchDouble(2);
						if (direction == "-") {
							reference -= rcents / 100.0;
						} else {
							reference += rcents / 100.0;
						}
					}
				}
				// cerr << "NEW REFERENCE " << reference << endl;
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
			if (hre.search(current, "^(\\d+)(?:/(\\d+))?")) {
				top = hre.getMatchInt(1);
				botstring = hre.getMatch(2);
				if (botstring.empty()) {
					bot = 1;
				} else {
					bot = hre.getMatchInt(2);
				}
				if (top == 0) {
					cerr << "TOP should not be zero: " << current << endl;
					current = current->getNextToken();
					continue;
				}
				if (bot == 0) {
					cerr << "Error cannot use 0 as the denominator, setting to 1" << endl;
					bot = 1;
				}
				value = top;
				value /= bot;
				double cvalue = log2(value.getFloat()) * 12;
				if (hre.search(current, "([+-])c?(\\d+\\.\\d*)")) {
					pcents = hre.getMatchDouble(2);
					string direction = hre.getMatch(1);
					if (direction == "-") {
						pcents = hre.getMatchDouble(2);
					} else {
						pcents = -hre.getMatchDouble(2);
					}
				}
				double pitch = reference + cvalue + pcents;
				// cerr << "\tRATIO " << value << " CENTS " << pcents << "\t";
				// cerr << "CRATIO " << cvalue << endl;
				// cerr << "\tPITCH: " << pitch << endl;
				int starttime = m_timemap[current->getLineIndex()];
				int endtime = getEndTime(current);
				// cerr << "\t\tSTARTTIME: " << starttime << "\tENDTIME: " << endtime << endl;
				outfile.addNoteOn(track, starttime, channel, int(pitch), velocity);
				outfile.addNoteOff(track, endtime, channel, int(pitch), velocity);
				double pbend = pitch - int(pitch);
				pbend = pbend * 0.5;   // range is +/- 200 cents by default so normalize
				int ptime = starttime - 1;
				if (ptime < 0) {
					ptime = 0;
				}
				// cerr << "STARTTIME " << starttime << " PTIME " << ptime << endl;
				outfile.addPitchBend(track, ptime, channel, pbend);
			}
		}
		current = current->getNextToken();
		continue;
	}
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
		int line = current->getLineIndex();
		return m_timemap[line];
		current = current->getNextToken();
	}
	return m_timemap.back() + 1000;  // note at end given 1.0 second duration
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



