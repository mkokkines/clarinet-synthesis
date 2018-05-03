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

	vector<pair<string, double>> notes_to_play;
	bool play_sequence_complete;

	void clear();
	void copy(const AudioThread& source);
	void move(AudioThread&& source);

public:
	AudioThread();
	~AudioThread();

	AudioThread(const AudioThread& source);                                           // Copy constructor
	AudioThread(AudioThread&& source) noexcept;                                       // Move constructor
	AudioThread& operator=(const AudioThread& source);								// Copy assignment operator
	AudioThread& operator=(AudioThread&& source) noexcept;							// Move assignment operator

	clarinet::Clarinet* getClarinet();

	void setCurrentNote(string note);
	void setNotesToPlay(vector<pair<string, double>> notes);

	void threadedFunction();	// Called when the thread is opened; determines wherther to output a single note 
								// or a sequence depending on variables above
	void audioOut(float *output, int bufferSize, int nChannels); // Outputs a note, called the sound stream starts														
	void playSequenceOfNotes();				// Loops through and outputs a list of notes
};
