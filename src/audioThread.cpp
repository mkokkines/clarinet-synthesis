#include "audioThread.h"

const double fDefaultScaleTempo = 120;
const double fSecPerMin = 60;

AudioThread::AudioThread() {
	clarinet_ = new clarinet::Clarinet();

	scales = new map<string, vector<string>>();
	scale_to_play = "";
	scale_tempo = fDefaultScaleTempo;

	sound_stream = new ofSoundStream();
	sound_stream->setup(2, 0, 48000, 256, 2);
	sound_stream->stop();
	sound_stream->setOutput(this);
}

AudioThread::~AudioThread() {
	clarinet_ = nullptr;
	current_note = nullptr;
}

clarinet::Clarinet* AudioThread::getClarinet() {
	return clarinet_;
}

void AudioThread::setScales(map<string, vector<string>> copy_scale) {
	*scales = copy_scale;
}

void AudioThread::setScaleToPlay(string scale) {
	scale_to_play = scale;
}

void AudioThread::setCurrentNote(string note) {
	current_note = note;
}

void AudioThread::setScaleTempo(double tempo) {
	scale_tempo = tempo;
}

void AudioThread::threadedFunction() {
	while (isThreadRunning()) {
		if (scale_to_play != "") {
			outputScale();
		} else {
			sound_stream->start();
		}
	}

	sound_stream->stop();
}

void AudioThread::audioOut(float *output, int bufferSize, int nChannels) {
	clarinet_->generateNote(current_note);

	if (clarinet_->synth_ != NULL) {
		clarinet_->synth_->fillBufferOfFloats(output, bufferSize, nChannels);
	}
}

void AudioThread::outputScale() {
	clarinet_->setHigherOctave(false);

	vector<string> scale_notes = scales->at(scale_to_play);
	int note_number = 0;

	std::clock_t start = std::clock();

	while (note_number < scale_notes.size()) {
		current_note = scale_notes[note_number];
		sound_stream->start();

		double elapsed_seconds = (std::clock() - start) / (double) CLOCKS_PER_SEC;

		if (elapsed_seconds >= (fSecPerMin / scale_tempo)) {
			sound_stream->stop();
			note_number++;
			start = std::clock();
		}
	}

	clarinet_->setHigherOctave(false);
	scale_to_play = "";
}