#pragma once
#ifndef CLARINET
#define CLARINET

#include <iostream>
#include <vector>
#include <map>
#include <../apps/myApps/final project/Tonic-master/Tonic-master/src/Tonic.h>
#include <utility>
#include <algorithm>
#include <chrono>
#include <ctime>

const int fDefaultBpm = 60;
const double fDefaultVolume = .03;
const bool fStartOctave = false;
const double fHigherOctaveFrequencyFactor = 2;

const double fModOneAmplitude = .75;
const double fModTwoAmplitude = .5;
const double fModThreeAmplitude = .14;
const double fModFourAmplitude = .5;
const double fModFiveAmplitude = .12;
const double fModSixAmplitude = .17;

// Name of note followed by its base frequency
const std::pair<string, double> fLowGb = { "lowGb", 164.81 };
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
const std::pair<string, double> fMiddleGb = { "middleGb", 329.62 };
const std::pair<string, double> fMiddleG = { "middleG", 349.22 };
const std::pair<string, double> fMiddleAb = { "middleAb", 370.00 };
const std::pair<string, double> fMiddleA = { "middleA", 392.00 };
const std::pair<string, double> fMiddleBb = { "middleBb", 415.30 };
const std::pair<string, double> fMiddleB = { "middleB", 440.00 };
const std::pair<string, double> fMiddleC = { "middleC", 466.16 };
const std::pair<string, double> fMiddleDb = { "middleDb", 493.88 };
const std::pair<string, double> fMiddleD = { "middleD", 523.26 };
const std::pair<string, double> fMiddleEb = { "middleEb", 554.36 };
const std::pair<string, double> fMiddleE = { "middleE", 587.32 };
const std::pair<string, double> fMiddleF = { "middleF", 622.26 };

// This class generates the sinewaves for each clarinet note
namespace clarinet {
	class Clarinet {
		Tonic::Synth* synth_;
		Tonic::Generator* output_;

		Tonic::Generator modulator_one;
		Tonic::Generator modulator_two;
		Tonic::Generator modulator_three;
		Tonic::Generator modulator_four;
		Tonic::Generator modulator_five;
		Tonic::Generator modulator_six;

		double volume_;
		bool higher_octave;

		std::map<string, double>* note_frequencies;

		void clear();
		void copy(const Clarinet&& source);
		void move(Clarinet&& source);

	public:
		Clarinet();
		~Clarinet();

		Clarinet(const Clarinet& source);                                           // Copy constructor
		Clarinet(Clarinet&& source) noexcept;                                       // Move constructor
		Clarinet& operator=(const Clarinet& source);								// Copy assignment operator
		Clarinet& operator=(Clarinet&& source) noexcept;							// Move assignment operator

		Tonic::Synth Clarinet::getSynth();

		double Clarinet::getVolume();
		bool Clarinet::getHigherOctave();

		void Clarinet::setVolume(double new_volume);
		void Clarinet::setHigherOctave(bool new_octave);

		void Clarinet::generateNote(string note_name); // Uses frequency modulation to generate the sinewaves
													   // for clarinet notes
	};

}
#endif //CLARINET_H

#pragma once
