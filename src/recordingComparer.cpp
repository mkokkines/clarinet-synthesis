#include "RecordingComparer.h"

RecordingComparer::RecordingComparer() {
}

RecordingComparer::~RecordingComparer() {
}

pair<string, string> RecordingComparer::compareRecordings(vector<pair<string, double>> &correct_recording, 
										  vector<pair<string, double>> &attempted_recording) {

	vector<pair<string, string>> incorrect_notes = compareNoteNames(correct_recording, attempted_recording);
	string incorrect_note_message = getIncorrectNoteMessage(incorrect_notes);

	vector<int> poorly_timed_notes = compareNoteLengths(correct_recording, attempted_recording);
	string poorly_timed_note_message = getPoorlyTimedNoteMessage(poorly_timed_notes);

	return make_pair(incorrect_note_message, poorly_timed_note_message);
}

vector<pair<string, string>> RecordingComparer::compareNoteNames(vector<pair<string, double>> &correct_recording,
														         vector<pair<string, double>> &attempted_recording) {
	vector<pair<string, string>> incorrect_notes;
	int final_index = std::min(attempted_recording.size(), correct_recording.size());

	for (int i = 0; i < final_index; i++) {
		if (attempted_recording.size() <= i) {
			incorrect_notes.push_back({ "nothing", correct_recording[i].first });
		} else if (correct_recording.size() <= i) {
			incorrect_notes.push_back({attempted_recording[i].first, "nothing"});
		} else if (correct_recording[i].first != attempted_recording[i].first) {
			incorrect_notes.push_back({ attempted_recording[i].first, correct_recording[i].first });
		}
	}

	return incorrect_notes;
}

string RecordingComparer::getIncorrectNoteMessage(vector<pair<string, string>> incorrect_notes) {
	string message_start = "The following notes were incorrect:\n";
	string message_end;

	for (pair<string, string> wrong_note : incorrect_notes) {
		message_end += "You played " + wrong_note.first + " when you should have played " + wrong_note.second + "\n";
	}

	return message_start + message_end;
}

vector<int> RecordingComparer::compareNoteLengths(vector<pair<string, double>> &correct_recording,
												  vector<pair<string, double>> &attempted_recording) {
	vector<int> poorly_timed_notes;
	int final_index = std::min(attempted_recording.size(), correct_recording.size());

	for (int i = 0; i < final_index; i++) {
		double time_difference = abs(attempted_recording[i].second - correct_recording[i].second);
		
		if (time_difference > .05) {
			poorly_timed_notes.push_back(i);
		}
	}

	return poorly_timed_notes;
}

string RecordingComparer::getPoorlyTimedNoteMessage(vector<int> poorly_timed_notes) {
	string message_start = "The following notes were held too short or too long:\n";
	string message_end;

	for (int note_number : poorly_timed_notes) {
		message_end = message_end + "note number " + to_string(note_number) + ", ";
	}

	return message_start + message_end;
}
