#pragma once
#ifndef CLARINET
#define CLARINET

#include <iostream>
#include <vector>
#include <map>
#include <../apps/myApps/final project/Tonic-master/Tonic-master/src/Tonic.h>

const int fDefaultBpm = 60;
const double fDefaultVolume = .03;
const char fNormalArticulation = 'n';
const bool fStartOctave = false;

const std::pair<string, double> fLowGb{ "lowGb", 164.81 };
const std::pair<string, double> fLowG = { "lowG", 174.61 };
const std::pair<string, double> fLowAb = { "lowAb", 185.00 };
const std::pair<string, double> fLowA = { "lowA", 196.0 };
const std::pair<string, double> fLowBb = { "lowBb", 207.65 };
const std::pair<string, double> fLowB = { "lowB", 220.00 };
const std::pair<string, double> fLowC = { "lowC", 233.08 };
const std::pair<string, double> fLowDb = { "lowDb", 246.94 };
const std::pair<string, double> fLowD = { "lowD", 261.63 };
const std::pair<string, double> fLowEb = { "lowEb", 277.18 };
const std::pair<string, double> fLowE = { "lowE", 293.66 };
const std::pair<string, double> fLowF = { "lowF", 311.13 };

namespace clarinet {
	class Clarinet {
		Tonic::Generator* output_;
		Tonic::ControlMetro* metronome_;

		Tonic::Generator modulator_one;
		Tonic::Generator modulator_two;
		Tonic::Generator modulator_three;
		Tonic::Generator modulator_four;
		Tonic::Generator modulator_five;
		Tonic::Generator modulator_six;

		Tonic::ADSR amplitude_envelope;
		Tonic::ADSR modulation_index_envelope;

		char articulation_;
		double volume_;
		string current_note;
		bool higher_octave;

		std::map<string, double>* note_frequencies;
		std::map<string, vector<string>>* scales;

		/* void Clarinet::copy(Clarinet& source);
		void Clarinet::move(Clarinet&& source);
		void Clarinet::clear(); */

	public:
		Tonic::Synth* synth_;
		Clarinet();

		double Clarinet::getVolume();
		bool Clarinet::getHigherOctave();

		void Clarinet::setVolume(double new_volume);
		void Clarinet::setHigherOctave(bool new_octave);

		void Clarinet::setArticulation(char articulation);
		void Clarinet::setBeat(int beat);

		string adjustForOctave(string note);

		void Clarinet::generateNote(string note_name);
	};

}
#endif //CLARINET_H

#pragma once
