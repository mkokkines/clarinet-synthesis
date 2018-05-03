#pragma once
#include "ofMain.h"
#include <cmath>

const double fTimeDiffThreshold = 0.05; // Time differences less than 1/20th of a second are insignificant

// This class contains methods that compare to lists of recorded scales. It determines which wrong 
// notes were played and which notes were played for incorrect periods of time.
class RecordingComparer {
private:
	// Returns pairs of note names that differed between the two lists -- attempted recording first
	vector<pair<string, string>> compareNoteNames(vector<pair<string, double>> &correct_recording,
		vector<pair<string, double>> &attempted_recording);

	// Returns the numbers of notes that were held for an incorrect period of time
	vector<int> compareNoteLengths(vector<pair<string, double>> &correct_recording,
		vector<pair<string, double>> &attempted_recording);

	// Convert the contents of the vectors to comprehensible outpuut strings
	string getIncorrectNoteMessage(vector<pair<string, string>> incorrect_notes);
	string getPoorlyTimedNoteMessage(vector<int> poorly_timed_notes);

public:
	RecordingComparer();
	~RecordingComparer();

	// Treats the earlier recording as the correct recording.
	// Returns two strings -- one detailing which incorrect notes the second recording played, and one
	// detailing which notes were played for the incorrect amount of time.
	pair<string, string> compareRecordings(vector<pair<string, double>> &correct_recording,
		vector<pair<string, double>> &attempted_recording);

};

