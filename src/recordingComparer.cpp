#include "RecordingComparer.h"

RecordingComparer::RecordingComparer() {}

RecordingComparer::~RecordingComparer() {}

// Calls the private helper functions obtain a pair of output strings for the user
pair<string, string> RecordingComparer::compareRecordings(vector<pair<string, double>> &correct_recording,
	vector<pair<string, double>> &attempted_recording) {

	vector<pair<string, string>> incorrect_notes = compareNoteNames(correct_recording, attempted_recording);
	string incorrect_note_message = getIncorrectNoteMessage(incorrect_notes);

	vector<int> poorly_timed_notes = compareNoteLengths(correct_recording, attempted_recording);
	string poorly_timed_note_message = getPoorlyTimedNoteMessage(poorly_timed_notes);

	return make_pair(incorrect_note_message, poorly_timed_note_message);
}

// Compares the strings at each index of the two recording vectors, adding the pairs of strings that differ
// to the vector that is returned. If the recording vectors differ in length, any entries in the longer vector
// after the final index of the shorter vector are added as well
vector<pair<string, string>> RecordingComparer::compareNoteNames(vector<pair<string, double>> &correct_recording,
	vector<pair<string, double>> &attempted_recording) {
	vector<pair<string, string>> incorrect_notes;
	int final_index = std::min(attempted_recording.size(), correct_recording.size());

	for (int i = 0; i < final_index; i++) {
		if (attempted_recording.size() <= i) {
			incorrect_notes.push_back({ "nothing", correct_recording[i].first });
		}
		else if (correct_recording.size() <= i) {
			incorrect_notes.push_back({ attempted_recording[i].first, "nothing" });
		}
		else if (correct_recording[i].first != attempted_recording[i].first) {
			incorrect_notes.push_back({ attempted_recording[i].first, correct_recording[i].first });
		}
	}

	return incorrect_notes;
}

// Loops through the vector of incorrect notes and assembles a string detailing the errors.
string RecordingComparer::getIncorrectNoteMessage(vector<pair<string, string>> incorrect_notes) {
	string message_start = "The following notes were incorrect:\n";
	string message_end;

	for (pair<string, string> wrong_note : incorrect_notes) {
		message_end += "You played " + wrong_note.first + " when you should have played " + wrong_note.second + "\n";
	}

	return message_start + message_end;
}

// Compares the length of the notes at each index of the recording vectors. If their lengths differ by 
// a significant amount (more than .05 seconds), the index of the note is added to the return vector
vector<int> RecordingComparer::compareNoteLengths(vector<pair<string, double>> &correct_recording,
	vector<pair<string, double>> &attempted_recording) {


	vector<int> poorly_timed_notes;
	int final_index = std::min(attempted_recording.size(), correct_recording.size());

	for (int i = 0; i < final_index; i++) {
		double time_difference = abs(attempted_recording[i].second - correct_recording[i].second);

		if (time_difference > fTimeDiffThreshold) {
			poorly_timed_notes.push_back(i + 1);
		}
	}

	return poorly_timed_notes;
}

// Loops through each element of the poorly timed notes vector and returns a string listing the indices of 
// notes that were held for an incorrect period of time
string RecordingComparer::getPoorlyTimedNoteMessage(vector<int> poorly_timed_notes) {
	string message_start = "The following notes were held too short or too long:\n";
	string message_end;

	for (int note_number : poorly_timed_notes) {
		message_end = message_end + "note number " + to_string(note_number) + ", ";
	}

	return message_start + message_end;
}
