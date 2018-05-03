#include "../apps/myApps/clarinet_synthesis/clarinet_synthesis/src/clarinet.h"
#ifndef CLARINET_CPP
#define CLARINET_CPP

using namespace clarinet;
using namespace Tonic;

// Initializes the synth, the output generator, and the map of note frequencies
Clarinet::Clarinet() {
	synth_ = new Synth();
	output_ = new Generator();

	volume_ = fDefaultVolume;
	higher_octave = fStartOctave;

	note_frequencies = new std::map<string, double>();
	*note_frequencies = { fLowGb, fLowG, fLowAb, fLowA, fLowBb, fLowB, fLowC, fLowDb, fLowD, fLowEb, fLowE, fLowF,
		fMiddleGb, fMiddleG, fMiddleAb, fMiddleA, fMiddleBb, fMiddleB, fMiddleC, fMiddleDb,
		fMiddleD, fMiddleEb, fMiddleE, fMiddleF };
}

void Clarinet::clear() {
	delete synth_;
	synth_ = nullptr;

	delete output_;
	output_ = nullptr;

	delete note_frequencies;
	note_frequencies = nullptr;

	volume_ = 0;
	higher_octave = false;
}

void Clarinet::copy(const Clarinet& source) {
	synth_ = source.synth_;
	output_ = source.output_;
	note_frequencies = source.note_frequencies;
	volume_ = source.volume_;
	higher_octave = source.higher_octave;
}

void Clarinet::move(Clarinet&& source) {
	synth_ = source.synth_;
	output_ = source.output_;
	note_frequencies = source.note_frequencies;
	volume_ = source.volume_;
	higher_octave = source.higher_octave;

	delete source.synth_;
	delete source.output_;
	delete source.note_frequencies;
}

Clarinet::~Clarinet() {
	clear();
}

Clarinet::Clarinet(const Clarinet& source) {
	copy(source);
}

Clarinet::Clarinet(Clarinet&& source) noexcept {
	move(source);
}

Clarinet& Clarinet::operator=(const Clarinet& source) {
	copy(source);
	return *this;
}

Clarinet& Clarinet::operator=(Clarinet&& source) noexcept {
	move(source);
	return *this;
}

Tonic::Synth Clarinet::getSynth() {
	return *synth_;
}

double Clarinet::getVolume() {
	return volume_;
}

bool Clarinet::getHigherOctave() {
	return higher_octave;
}

void Clarinet::setVolume(double new_volume) {
	volume_ = new_volume;
}

void Clarinet::setHigherOctave(bool new_octave) {
	higher_octave = new_octave;
}

// Uses a base tone and six modulators to make the note sound akin to a real woodwind instrument
// Note: this method, as ofApp is currently, will never be called with a nonexistent note name, but 
// the first conditional is a precaution
void Clarinet::generateNote(string note_name) {
	if (note_frequencies->at(note_name) == note_frequencies->end()) {
		return;
	}

	double base_frequency = note_frequencies->at(note_name);

	if (higher_octave) {
		base_frequency *= 2;
	}

	// Modulators alter the base tone. The frequency for each is the next odd number (1,3,5,...) 
	// multiplied by the base frequency
	modulator_one = fModOneAmplitude * SineWave().freq(3 * base_frequency);
	modulator_two = fModTwoAmplitude * SineWave().freq(5 * base_frequency);
	modulator_three = fModThreeAmplitude * SineWave().freq(7 * base_frequency);
	modulator_four = fModFourAmplitude * SineWave().freq(9 * base_frequency);
	modulator_five = fModFiveAmplitude * SineWave().freq(11 * base_frequency);
	modulator_six = fModSixAmplitude * SineWave().freq(13 * base_frequency);

	*output_ = SineWave().freq(base_frequency) + modulator_one + modulator_two + modulator_three
		+ modulator_four + modulator_five + modulator_six;

	synth_->setOutputGen(*output_ * volume_);	// Changes the amplitude of the wave based on the volume
}

#endif //CLARINET_CPP

