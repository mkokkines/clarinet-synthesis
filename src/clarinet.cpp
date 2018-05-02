#include "../apps/myApps/clarinet_synthesis/clarinet_synthesis/src/clarinet.h"
#ifndef CLARINET_CPP
#define CLARINET_CPP

using namespace clarinet;
using namespace Tonic;

Clarinet::Clarinet() {
	synth_ = new Synth();
	output_ = new Generator();
	metronome_ = new ControlMetro();

	current_note = "lowGb";

	volume_ = fDefaultVolume;
	articulation_ = fNormalArticulation;
	higher_octave = fStartOctave;

	note_frequencies = new std::map<string, double>();
	*note_frequencies = { fLowGb, fLowG, fLowAb, fLowA, fLowBb, fLowB, fLowC, fLowDb, fLowD, fLowEb, fLowE, fLowF };

	scales = new std::map<string, vector<string>>();
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

void Clarinet::setBeat(int beat) {
	metronome_->bpm(beat);
}

void Clarinet::setArticulation(char articulation) {
	articulation_ = articulation;
}

// Changes the name of the note if it is in the higher octave
string Clarinet::adjustForOctave(string note) {
	if (higher_octave && note.substr(0, 3) == "low") {
		return note.replace(0, 3, "middle");
	}
	else if (note.substr(0, 6) == "middle") {
		higher_octave = true;
	}

	return note;
}

// Firsts adjusts to ensure the correct octave is being played; then uses a base tone and six modulators to make the note sound
// akin to a real woodwind instrument
void Clarinet::generateNote(string note_name) {
	if (note_name.substr(0, 6) == "middle") {
		higher_octave = true;
		note_name.replace(0, 6, "low");
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

	synth_->setOutputGen(*output_ * volume_);
}

#endif //CLARINET_CPP

