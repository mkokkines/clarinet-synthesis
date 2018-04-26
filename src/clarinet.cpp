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

Clarinet::Clarinet() {}

void Clarinet::copy(Clarinet& source) {
	tone_ = SineWave().freq(source.tone_->freq);
	modulator_ = SineWave().freq(source.modulator_->freq);
	metronome_ = SineWave().freq(source.tremolo->freq);
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
	synth_* = new Synth();
	tone_ = new SineWave()->freq(0);
	modulator_ = new SineWave()->freq(0);
	metronome_ = new ControlMetro()->bpm(fDefaultBpm);
	synth_.setOutputGen(tone_);
}

void Clarinet::setBeat(int beat) {
	beat_ = beat;
}

void Clarinet::setArticulation(char articulation) {
	articulation_ = articulation;
}

void setVolume(double percent_change) {

}

void generateNote(char final_pitch, double attack_magnitude, double decay_magnitude,
	double hold_time, double release_magnitude) {

	double final_frequency = note_frequencies.at(final_pitch); // NOTE: need to handle exception
	double overshoot_frequency = final_frequency * fOverShoot;

	this->attack(attack_magnitude, overshoot_frequency);
	this->decay(decay_magnitude, final_frequency);
	this->sustain(hold_time);
	this->release(release_magnitude, final_frequency);

}

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
}

#endif //CLARINET_CPP
