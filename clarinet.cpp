#include "clarinet.h"
#ifndef CLARINET_CPP
#define CLARINET_CPP
#include <utility>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace clarinet;
using namespace Tonic;

const int fDefaultBpm = 100;
const double fDefaultVolume = .5;
const char fNormalArticulation = 'n';
const bool fStartOctave = false;

const std::pair<string, double> fLowG = { "lowG", 174.61 };
const std::pair<string, double> fLowAb = {"lowAb", 185.00};
const std::pair<string, double> fLowA = { "lowA", 196.0 };
const std::pair<string, double> fLowBb = { "lowBb", 207.65 };
const std::pair<string, double> fLowB = { "lowB", 220.00 };
const std::pair<string, double> fLowC = { "lowC", 233.08 };
const std::pair<string, double> fLowDb = { "lowDb", 246.94 };
const std::pair<string, double> fLowD = { "lowD", 261.63 };
const std::pair<string, double> fLowEb = { "lowEb", 277.18 };
const std::pair<string, double> fLowE = { "lowE", 293.66 };
const std::pair<string, double> fLowF = { "lowF", 311.13 };
const std::pair<string, double> fMiddleGb = { "middleGb", 329.63 };
const std::pair<string, double> fMiddleG = { "middleG", 349.23 };


Clarinet::Clarinet() {
	synth_ = new Synth();
	output_ = new Generator();
	metronome_ = new ControlMetro();

	volume_ = fDefaultVolume;
	articulation_ = fNormalArticulation;
	higher_octave = fStartOctave;

	note_frequencies = new std::map<string, double>();
	*note_frequencies = {fLowG, fLowAb, fLowA, fLowBb, fLowB, fLowC, fLowDb, fLowD, fLowEb, fLowE, fLowF, 
						fMiddleGb, fMiddleG};
}
/*
void Clarinet::copy(Clarinet& source) {
	// tone_ = SineWave().freq(source.tone_->freq);
	// modulator_ = SineWave().freq(source.modulator_->freq);
	// metronome_ = SineWave().freq(source.tremolo->freq);
}

void Clarinet::move(Clarinet&& source) {
	tone_ = source.tone_;
	modulator_ = source.modulator_;
	metronome_ = source.metronome_;
	articulation_ = source.articulation_;
	beat_ = source.beat_;

	source.clear();
}

void Clarinet::clear() {
	tone_ = nullptr;
	modulator_ = nullptr;
	metronome_ = nullptr;
	articulation_ = NULL;
	beat_ = NULL;
}

Clarinet::Clarinet(Clarinet& source) {
	this->copy(source);
}


Clarinet::Clarinet(Clarinet&& source) noexcept {
	this->move(source);
}

Clarinet::~Clarinet() {
	this->clear();
}

Clarinet& Clarinet::operator=(Clarinet& source) {
	this->copy(source);
	return *this;
}

Clarinet& Clarinet::operator=(Clarinet&& source) noexcept {
	this->move(source);
	return *this;
} */

string Clarinet::getCurrentNote() {
	return current_note;
}

double Clarinet::getVolume() {
	return volume_;
}

bool Clarinet::getHigherOctave() {
	return higher_octave;
}

void Clarinet::setCurrentNote(string note_name) {
	current_note = note_name;
}

void Clarinet::setVolume(double new_volume) {
	volume_ = new_volume;
}

void Clarinet::setHigherOctave(bool new_octave) {
	higher_octave = new_octave;
}

void Clarinet::setBeat(int beat) {
	metronome_->bpm(beat);
}

void Clarinet::setArticulation(char articulation) {
	articulation_ = articulation;
}

void Clarinet::generateNote(string note_name) {
	double base_frequency = note_frequencies->at(note_name);

	if (higher_octave) {
		base_frequency *= 2;
	}

	// amplitude_envelope = ADSR().attack(.1).decay(.13).sustain(0).release(0);

	modulator_one = .75 * SineWave().freq(3 * base_frequency);
	modulator_two = 0.5 * SineWave().freq(5 * base_frequency);
	modulator_three = .14 * SineWave().freq(7 * base_frequency);
	modulator_four = .5 * SineWave().freq(9 * base_frequency);
	modulator_five = .12 * SineWave().freq(11 * base_frequency);
	modulator_six = .17 * SineWave().freq(13 * base_frequency);

	*output_ = SineWave().freq(base_frequency) + modulator_one + modulator_two + modulator_three
		+ modulator_four + modulator_five + modulator_six;

	synth_->setOutputGen(*output_ * volume_);
}

#endif //CLARINET_CPP