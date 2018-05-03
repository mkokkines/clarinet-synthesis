#include "audioThread.h"

// Initializes a clarinet, sets up a sound stream to output audio, and switches the default audio output 
// from the main thread to this thread 
AudioThread::AudioThread() {
	clarinet_ = new clarinet::Clarinet();

	play_sequence_complete = false;

	sound_stream = new ofSoundStream();
	sound_stream->setup(fNumOutputChannels, fNumInputChannels, fSamplesPerSec, fBufferSize, fNumBuffers);
	sound_stream->stop();
	sound_stream->setOutput(this);
}

void AudioThread::clear() {
	delete clarinet_;
	clarinet_ = nullptr;

	delete sound_stream;
	sound_stream->close();
}

void AudioThread::copy(const AudioThread& source) {
	clarinet_ = source.clarinet_;
	sound_stream = source.sound_stream;
	play_sequence_complete = source.play_sequence_complete;

	sound_stream->setOutput(this);
}

void AudioThread::move(AudioThread&& source) {
	clarinet_ = source.clarinet_;
	sound_stream = source.sound_stream;
	play_sequence_complete = source.play_sequence_complete;

	delete source.clarinet_;
	delete source.sound_stream;

	sound_stream->setOutput(this);
}

AudioThread::~AudioThread() {
	clear();
}

AudioThread::AudioThread(const AudioThread& source) {
	copy(source);
}

AudioThread::AudioThread(AudioThread&& source) noexcept {
	move(source);
}

AudioThread& AudioThread::operator=(const AudioThread& source) {
	copy(source);
	return *this;
}

AudioThread& AudioThread::operator=(AudioThread&& source) noexcept {
	move(source);
	return *this;
}

clarinet::Clarinet* AudioThread::getClarinet() {
	return clarinet_;
}

void AudioThread::setCurrentNote(string note) {
	current_note = note;
}

void AudioThread::setNotesToPlay(vector<pair<string, double>> notes) {
	notes_to_play = notes;
}

// This method is called whenever the audio_thread is started in the ofApp class. 
// While the thread continues running, it either calls the method to play a sequence of notes, or calls
// the audioOut method to play a single note.
// Note: This thread and the main thread are out of sync by a short fraction of a second. Hence, when playing
// a sequence, one additional note it output before the main thread closes this thread unless 
// play_sequence_complete is used as a control variable
void AudioThread::threadedFunction() {
	while (isThreadRunning() && !play_sequence_complete) {

		if (!notes_to_play.empty()) {
			playSequenceOfNotes();
		}
		else {
			sound_stream->start();	// Calls audioOut
		}
	}

	sound_stream->stop();
	play_sequence_complete = false;
}

// This is called whenever the sound stream is opened. It fills the output buffer with the sounds generated
// by the clarinet
void AudioThread::audioOut(float *output, int bufferSize, int nChannels) {
	clarinet_->generateNote(current_note);

	if (clarinet_->getSynth() != NULL) {
		clarinet_->getSynth->fillBufferOfFloats(output, bufferSize, nChannels);
	}
}

// This method loops through a list of notes and outputs them for the period of time specified in the list.
// The clarinet's generate note method (called in audioOut) will adjust for the octave 
// when playing higher notes; hence, the octave here is set to the lower octave before beginning.
// The list of notes is cleared after being played. 
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

	play_sequence_complete = true;
	notes_to_play.clear();
}
