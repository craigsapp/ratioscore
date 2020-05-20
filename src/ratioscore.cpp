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
// 2.6	3/2g	5/4c100	50
// 3.1	.	3/2	50
// 4.2	6/5G	.	.
// *-	*-	*-	*-
//

#include "humlib.h"
#include "MidiFile.h"

#include <string>

using namespace std;
using namespace smf;
using namespace hum;


// function declarations:
string    getOutputFilename (const string& filename);
bool      convertFile       (MidiFile& outfile, HumdrumFile& infile);
void      generateTrack     (MidiFile& outfile, int track, HTp pstart, int dtrack, HumdrumFile& infile);


// variables:
vector<HTp> m_sstarts;
vector<HTp> m_partStarts;
int         m_timeTrack = -1;
vector<int> m_dynTrack;


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

	for (int i=0; i<(int)m_sstarts.size(); i++) {
		if (*m_sstarts[i] == "**time") {
			m_timeTrack = m_sstarts[i]->getTrack();
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

	return true;
}



//////////////////////////////
//
// generateTrack --
//

void generateTrack(MidiFile& outfile, int track, HTp pstart, int dtrack, HumdrumFile& infile) {
	HTp current = pstart;
	HumRegex hre;
	HumNum value;
	double cents;
	int top;
	int bot;
	string botstring;
	while (current) {
		if (current->isInterpretation()) {
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
					current = current->getNextToken();
					continue;
				}
				if (bot == 0) {
					cerr << "Error cannot use 0 as the denominator, setting to 1" << endl;
					bot = 1;
				}
				value = top;
				value /= bot;
				cents = 0.0;
				if (hre.search(current, "c(\\d+\\.\\d*)")) {
					cents = hre.getMatchDouble(1);
				}
				if (fabs(cents) > 200.0) {
					cerr << "Error: cents value is too large: " << cents << ". Clipped to 200.\n";
					cents = cents > 200.0 ? 200.0 : -200.0;
				}
				cerr << "RATIO " << value << " CENTS " << cents << endl;
			}
		}
		current = current->getNextToken();
		continue;
	}



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



