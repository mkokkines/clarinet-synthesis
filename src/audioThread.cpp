#include "audioThread.h"

const double fDefaultScaleTempo = 120;
const double fSecPerMin = 60;

AudioThread::AudioThread() {
	clarinet_ = new clarinet::Clarinet();

	scales = new map<string, vector<string>>();
	scale_to_play = "";
	scale_tempo = fDefaultScaleTempo;
	playback_complete = false;

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

void AudioThread::setNotesToPlay(vector<pair<string, double>> notes) {
	notes_to_play = notes;
}

void AudioThread::threadedFunction() {
	while (isThreadRunning() && !playback_complete) {
		if (!notes_to_play.empty()) {
			playSequenceOfNotes();
		}
		else {
			sound_stream->start();
		}
	}

	sound_stream->stop();
	playback_complete = false;
}

void AudioThread::audioOut(float *output, int bufferSize, int nChannels) {
	clarinet_->generateNote(current_note);

	if (clarinet_->synth_ != NULL) {
		clarinet_->synth_->fillBufferOfFloats(output, bufferSize, nChannels);
	}
}

void AudioThread::playSequenceOfNotes() {
	clarinet_->setHigherOctave(false);
	int note_number = 0;
	std::clock_t start = std::clock();

	while (note_number < notes_to_play.size()) {
		current_note = notes_to_play[note_number].first;

		if (current_note != "") {
			sound_stream->start();
		}

		double elapsed_seconds = (std::clock() - start) / (double)CLOCKS_PER_SEC;

		if (elapsed_seconds >= notes_to_play[note_number].second) {
			note_number++;
			start = std::clock();
			sound_stream->stop();
		}
	}

	playback_complete = true;
	notes_to_play.clear();
}
