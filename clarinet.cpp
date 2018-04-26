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
const double fPi = 3.1415926535897932384626;
const double fPhaseConstant = -1 * fPi / 2;
const double fModulatorConversion = 1.5;

Clarinet::Clarinet() {}
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
}

void Clarinet::setUp() {
	articulation_ = 'n';
	synth_ = new Synth();
	generator_ = new Generator();

	tone_ = new SineWave();
	tone_->freq(0);

	modulator_ = new SineWave();
	modulator_->freq(0);

	metronome_ = new ControlMetro();
	metronome_->bpm(fDefaultBpm);

	synth_->setOutputGen(*generator_);
}

void Clarinet::setBeat(int beat) {
	beat_ = beat;
}

void Clarinet::setArticulation(char articulation) {
	articulation_ = articulation;
}

void setVolume(double percent_change) {

}

double Clarinet::generateFrequency(string note_name, double time) {
	double tone_frequency = note_frequencies.at(note_name);
	double modulator_frequency = fModulatorConversion * note_frequencies.at(note_name);
	return tone_frequency - (modulation_index_envelope * modulator_frequency);
}

void Clarinet::generateNote(double frequency) {
	tone_->freq(frequency * 2);
	modulator_->freq(frequency * 3);
	*generator_ = *tone_ * *modulator_;
	synth_->setOutputGen(*generator_);
}

void Clarinet::setVolume(double percent_change) {

}

/*
void Clarinet::attack(double attack_magnitude, double final_frequency) {
attack_magnitude = std::min(attack_magnitude, fMaxAttack);
attack_magnitude = std::max(attack_magnitude, fMinAttack);

Tonic::ControlParameter volume = addParameter("volume", -12.f).displayName("Volume (dbFS)").min(-60.f).max(0.f);

while (pitch->freq < final_frequency) {
pitch->freq += final_frequency / 10000;
this->sustain(10);
}
}

void Clarinet::decay(double decay_magnitude, correct_frequency) {
decay_magnitude;
decay_magntiude /= -1;
correct_frequency *= -1;

this->attack(decay_magntiude, correct_frequency);
}

void Clarinet::sustain(double length) {
clock_t wait = length * nanosecs + clock();
while (wait > clock()) continue;
}

void Clarinet::release(double release_magnitude) {
release_magnitude *= -1;
this->attack(release_magnitude, this->freq() * -1);
} */

#endif //CLARINET_CPP