#pragma once
#ifndef CLARINET
#define CLARINET

#include <iostream>
#include <vector>
#include <../apps/myApps/final project/Tonic-master/Tonic-master/src/Tonic.h>

namespace clarinet {

	class Clarinet {
	/*	Tonic::Synth* synth_;
		Tonic::Generator* generator_;
		Tonic::SineWave* tone_;
		Tonic::SineWave* modulator_;
		Tonic::ControlMetro* metronome_;

		double amplitude_envelope;
		double modulation_index_envelope;

		char articulation_;
		int beat_;

		std::map<string, double> note_frequencies;

		void Clarinet::copy(Clarinet& source);
		void Clarinet::move(Clarinet&& source);
		void Clarinet::clear(); */

	public:
		Clarinet();                                         // Default constructor
															// Big 5
		/*Clarinet(Clarinet& source);							   // Copy constructor
															   // Clarinet(Clarinet&& source) noexcept;            // Move constructor
															   // ~Clarinet();                                        // Destructor
															   // 	Clarinet& operator=(Clarinet source);      // Copy assignment operator
															   //	Clarinet& operator=(Clarinet&& source) noexcept; // Move assignment operator

		void Clarinet::setArticulation(char articulation);
		void Clarinet::setBeat(int beat);
		void Clarinet::setVolume(double percent_change);

		void Clarinet::setUp();
		void Clarinet::generateNote(double frequency);
		double Clarinet::generateFrequency(string note_name, double time);
		// void Clarinet::trigger();
		// void Clarinet::crescendo(double percentage); */
	};

} 
#endif //CLARINET_H

#pragma once
