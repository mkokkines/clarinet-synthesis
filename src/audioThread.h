#pragma once
#include "ofMain.h"
#include "clarinet.h"

class AudioThread : public ofThread, public ofBaseSoundOutput {
	private:
		clarinet::Clarinet* clarinet_;
		string current_note;
		ofSoundStream* sound_stream;

		string scale_to_play;	// When scale_to_play = "", the thread will not call outputScale
		std::map<string, vector<string>>* scales;
		double scale_tempo;


	public:
		AudioThread();
		~AudioThread();

		clarinet::Clarinet* getClarinet();

		void setScales(map<string, vector<string>> copy_scale);
		void setScaleToPlay(string scale);
		void setCurrentNote(string note);
		void setScaleTempo(double tempo);

		void threadedFunction();
		void audioOut(float *output, int bufferSize, int nChannels);
		void outputScale();
}; 

