#include "ofMain.h"
#include "ofApp.h"
#include "RtAudio.h"
#include "../apps/myApps/final-project-mkokkines/Tonic-master/Tonic-master/src/Tonic.h"

// using namespace Tonic;
// Synth* synth;

//========================================================================

/*
int renderCallBack(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, 
	double streamTime, RtAudioStreamStatus status, void *userData) {

	if (synth != NULL) {
		synth->fillBufferOfFloats((float*)outputBuffer, nBufferFrames, 2);
	}

	return 0;
} */

int main( ) {
/*
	RtAudio dac;
	RtAudio::StreamParameters rtParams;
	rtParams.deviceId = dac.getDefaultOutputDevice();
	rtParams.nChannels = 2;
	unsigned int sampleRate = 48000;
	unsigned int bufferFrames = 256;

	Tonic::setSampleRate(sampleRate);

	synth = new Synth();
	int w = 235.5 / 1.077;


	ControlMetro metro = ControlMetro().bpm(100);
	ControlGenerator metronome = ControlMetro().bpm(100);
	Generator modulator1 = .75 * SineWave().freq(3 * w);
	Generator modulator2 = 0.5 * SineWave().freq(5 * w);
	Generator modulator3 = .14 * SineWave().freq(7 * w);
	Generator modulator4 = .5 * SineWave().freq(9 * w);
	Generator modulator5 = .12 * SineWave().freq(11 * w);
	Generator modulator6 = .17 * SineWave().freq(13 * w);
	Generator output = SineWave().freq(w) + modulator1 + modulator2 + modulator3 + modulator4 + modulator5 + modulator6;
	synth->setOutputGen(0.03 * output);

	try {
		dac.openStream(&rtParams, NULL, RTAUDIO_FLOAT32, sampleRate, &bufferFrames, &renderCallBack, NULL, NULL);
		dac.startStream();
		cin.get();
		dac.stopStream();
	} catch (RtAudioError& e) {
		e.printMessage();
	}

	return 0; */



	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
