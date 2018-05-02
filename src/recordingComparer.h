#pragma once
#include "ofMain.h"
#include <cmath>

// double fTimeDiffThreshold = 0.05;

class RecordingComparer {
private:
	vector<pair<string, string>> compareNoteNames(vector<pair<string, double>> &correct_recording,
											vector<pair<string, double>> &attempted_recording);

	vector<int> compareNoteLengths(vector<pair<string, double>> &correct_recording,
								   vector<pair<string, double>> &attempted_recording);

	string getIncorrectNoteMessage(vector<pair<string, string>> incorrect_notes);
	string getPoorlyTimedNoteMessage(vector<int> poorly_timed_notes);
public:
	RecordingComparer();
	~RecordingComparer();

	pair<string, string> compareRecordings(vector<pair<string, double>> &correct_recording,
										   vector<pair<string, double>> &attempted_recording);

};

