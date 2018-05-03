#include "catch.hpp"
#include "ofApp.h"

TEST_CASE("Generate Note Different Notes") {
	clarinet::Clarinet first_clarinet();
	first_clarinet.generateNote("LowGb");
	
	clarinet::Clarinet second_clarinet();
	second_clarinet.generateNote("LowG");

	REQUIRE(first_clarinet.getSynth->getOutputGen() != second_clarinet.getSynth->getOutputGen());
}

TEST_CASE("Generate Note Same Note") {
	clarinet::Clarinet first_clarinet();
	first_clarinet.generateNote("LowGb");

	clarinet::Clarinet second_clarinet();
	second_clarinet.generateNote("LowGb");

	REQUIRE(first_clarinet.getSynth->getOutputGen() == second_clarinet.getSynth->getOutputGen());
}

TEST_CASE("Generate Note Nonexistent Note") {
	clarinet::Clarinet clarinet_();
	clarinet_.generateNote("jfks");
	REQUIRE(clarinet_.getSynth()->getOutputGen() == NULL);
}

TEST_CASE("Output Notes One Element") {
	AudioThread audio_thread();
	audio_thread->setCurrentNote("lowBb");
	audio_thread->start();

	clarinet::Clarinet clarinet_();
	clarinet_.generateNote("lowBb");

	audio_thread->stop();

	ASSERT(audio_thread->getClarinet()->getSynth()->getOutputGen() == clarinet_->getSynth()->getOutputGen());
}

TEST_CASE("Output Notes Multiple Elements") {
	pair<string, double> first_note = make_pair("lowBb", .5);
	pair<string, double> second_note = make_pair("lowEb", .2);
	vector < pair<string, double> notes = {first_note, second_note};

	AudioThread audio_thread();
	audio_thread->setNotesToPlay(notes);
	audio_thread->start();
	audio_thread->stop();


	clarinet::Clarinet clarinet_();
	clarinet_.generateNote("lowEb");

	audio_thread->stop();

	ASSERT(audio_thread->getClarinet()->getSynth()->getOutputGen() == clarinet_->getSynth()->getOutputGen());
}


