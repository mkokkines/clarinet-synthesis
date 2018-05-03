#pragma once
#include "ofMain.h"
#include "clarinet.h"

const double fDefaultScaleTempo = 120;
const double fSecPerMin = 60;
const int fSamplesPerSec = 48000;
const int fNumOutputChannels = 2;
const int fNumInputChannels = 0;
const int fBufferSize = 256;
const int fNumBuffers = 2;

// This class builds a thread that is used to output the audio for the application.
class AudioThread : public ofThread, public ofBaseSoundOutput {
private:
	clarinet::Clarinet* clarinet_;
	string current_note;
	ofSoundStream* sound_stream;

	string scale_to_play;
	std::map<string, vector<string>>* scales;
	double scale_tempo;

	vector<pair<string, double>> notes_to_play;
	bool play_sequence_complete;

public:
	AudioThread();
	~AudioThread();

	clarinet::Clarinet* getClarinet();

	void setScales(map<string, vector<string>> copy_scale);
	void setScaleToPlay(string scale);
	void setCurrentNote(string note);
	void setScaleTempo(double tempo);
	void setNotesToPlay(vector<pair<string, double>> notes);

	void threadedFunction();	// Called when the thread is opened; determines wherther to output a single note 
								// or a sequence depending on variables above
	void audioOut(float *output, int bufferSize, int nChannels); // Outputs a note, called the sound stream starts														
	void playSequenceOfNotes();				// Loops through and outputs a list of notes
};
