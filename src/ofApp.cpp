#include "ofApp.h"

const double fVolumeInterval = .05;
const int fRightSideFirstColumn = 700;
const int fRightSideSecondColumn = 825;

const std::pair<string, vector<string>> fBbScale = { "Bb", {"lowC", "lowD", "lowE", "lowF", "middleG", "middleA", "middleB", "middleC"} };
const std::pair<string, vector<string>> fEbScale = { "Eb", {"lowF", "middleG", "middleA", "middleBb", "middleC", "middleD", "middleE", 
													"middleF"} };
const std::pair<string, vector<string>> fAbScale = { "Ab", {"lowBb", "lowC", "lowD", "lowEb", "lowF", "middleG", "middleA", "middleBb"} };
const std::pair<string, vector<string>> fDbScale = { "Db", {"lowEb", "lowF", "middleG", "middleAb", "middleBb", "middleC", "middleD", 
													"middleEb"} };
const std::pair<string, vector<string>> fGbScale = { "Gb", {"lowAb", "lowBb", "lowC", "lowDb", "lowEb", "lowF", "middleG", "middleAb"} };
const std::pair<string, vector<string>> fBMajorScale = { "BMajor", {"lowDb", "lowEb", "lowF", "lowGb", "lowAb", "lowBb", "lowC", 
														"lowDb" } };
const std::pair<string, vector<string>> fAMajorScale = { "AMajor", {"lowB", "lowDb", "lowEb", "lowE", "middleGb", "lowAb", "lowBb", 
														"lowB"} };
const std::pair<string, vector<string>> fDMajorScale = { "DMajor", {"lowE", "middleGb", "middleAb", "middleA", "middleB", "middleDb",
														"middleEb", "middleE"} };
const std::pair<string, vector<string>> fGMajorScale = { "GMajor", {"lowA", "lowB", "lowDb", "lowD", "lowE", "middleGb", "middleAb", 
														"middleA"} };
const std::pair<string, vector<string>> fCMajorScale = { "CMajor", {"lowD", "lowE", "middleGb", "middleG", "middleA", "middleB", 
														"middleD", "middleDb"} };
const std::pair<string, vector<string>> fFMajorScale = { "FMajor", {"lowG", "lowA", "lowB", "lowC", "lowD", "lowE", "lowGb", "lowG"} };
const std::pair<string, vector<string>> fChromaticScale = { "chromatic", {"lowG", "lowAb", "lowA", "lowBb", "lowB", "lowC", "lowDb",
															"lowD", "lowEb", "lowE", "lowF", "middleGb", "middleG"} };

//--------------------------------------------------------------
void ofApp::setup() {
	loadImages();

	clarinet_ = new clarinet::Clarinet();
	clarinet_->setCurrentNote("middleG");

	upper_octave.setup("Upper Octave", false, 75, 75);
	volume_slider.setup("Volume", .5, 0.0, 1.0, 200, 60);

	b_flat_scale.setup("Bb Scale", 75, 75);
	e_flat_scale.setup("Eb Scale", 75, 75);
	a_flat_scale.setup("Ab Scale", 75, 75);
	d_flat_scale.setup("Db Scale", 75, 75);
	g_flat_scale.setup("Gb Scale", 75, 75);
	b_major_scale.setup("B Major Scale", 75, 75);
	a_major_scale.setup("A Major Scale", 75, 75);
	d_major_scale.setup("D Major Scale", 75, 75);
	g_major_scale.setup("G Major Scale", 75, 75);
	c_major_scale.setup("C Major Scale", 75, 75);
	f_major_scale.setup("F Major Scale", 75, 75);
	chromatic_scale.setup("Chromatic Scale", 75, 75);

	play_tune.setup("Play Tune", 100, 100);
	tempo_slider.setup("Tempo", 100.0, 0.0, 200.0, 200, 60);
	style_.setup("Style", 100.0, 0.0, 200.0, 200, 60);

	scales = new std::map<string, vector<string>>();
	*scales = { fBbScale, fEbScale, fAbScale, fDbScale, fGbScale, fBMajorScale, fAMajorScale, fDMajorScale, fGMajorScale, 
				fCMajorScale, fFMajorScale, fChromaticScale };

	ofSetFrameRate(60);
	ofSoundStreamSetup(2, 0, this, 48000, 256, 4);
	ofSoundStreamStop();
}

void ofApp::loadImages() {
	lowG.load("note_images/lowG.png");
	lowAb.load("note_images/lowAb.png");
	lowA.load("note_images/lowA.png");
	lowBb.load("note_images/lowBb.png");
	lowB.load("note_images/lowB.png");
	lowC.load("note_images/lowC.png");
	lowDb.load("note_images/lowDb.png");
	lowD.load("note_images/lowD.png");
	lowEb.load("note_images/lowEb.png");
	lowE.load("note_images/lowE.png");
	lowF.load("note_images/lowF.png");
	middleGb.load("note_images/middleGb.png");
	middleG.load("note_images/middleG.png");
	middleAb.load("note_images/middleAb.png");
	middleA.load("note_images/middleA.png");
	middleBb.load("note_images/middleBb.png");
	middleB.load("note_images/middleB.png");
	middleC.load("note_images/middleC.png");
	middleDb.load("note_images/middleDb.png");
	middleD.load("note_images/middleD.png");
	middleEb.load("note_images/middleEb.png");
	middleE.load("note_images/middleE.png");
	middleF.load("note_images/middleF.png");

	fingering_images = { { "lowG", lowG }, {"lowAb", lowAb}, { "lowA", lowA }, {"lowBb", lowBb}, { "lowB", lowB },
						 { "lowC", lowC }, {"lowDb", lowDb}, { "lowD", lowD }, {"lowEb", lowEb}, { "lowE", lowE },
						 { "lowF", lowF }, {"middleGb", middleGb}, { "middleG", middleG }, {"middleAb", middleAb},
						 {"middleA", middleA}, {"middleBb", middleBb}, {"middleB", middleB}, {"middleC", middleC},
						 {"middleDb", middleDb}, {"middleD", middleD}, {"middleEb", middleEb}, {"middleE", middleE},
						 {"middleF", middleF}, {"highGb", highGb}, {"highG", highG} };
} 

//--------------------------------------------------------------
void ofApp::update() {
	clarinet_->setVolume(volume_slider);
	clarinet_->setHigherOctave(upper_octave);
}

//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels) {
	clarinet_->generateNote(clarinet_->getCurrentNote());


	if (clarinet_->synth_ != NULL) {
		clarinet_->synth_->fillBufferOfFloats(output, bufferSize, nChannels);
	 }
}

// Plays each note in a scale for a specified period of time -- 60 divided by specified the beats per minute
void ofApp::playScale(string scale_name) {
	vector<string> scale_notes = scales->at(scale_name);
	int note_number = 0;

	std::clock_t start = std::clock();

	while (note_number < scale_notes.size()) {
		clarinet_->setCurrentNote(scale_notes[note_number]);
		ofSoundStreamStart();
		double elapsed_time = (std::clock() - start) / (double) CLOCKS_PER_SEC; // finds the number of elapsed seconds

		if (elapsed_time >= .3) {   // NOTE: .2 seconds is a temporary test value
			note_number++;
			start = std::clock();
		}
	}

}

void ofApp::playTune() {
	int note_number = 0;

	while (note_number < tune->size()) {
		// clarinet_->setCurrentNote(*tune[note_number].second);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	string title = "Clarinet Synthesis Studio";

	ofSetBackgroundColor(255, 255, 255);
	drawLeftSideElements();
	drawRightSideElements();
	drawFingering(clarinet_->getCurrentNote());
}

void ofApp::drawLeftSideElements() {
	volume_slider.draw();
	volume_slider.setPosition(100, 50);

	upper_octave.draw();
	upper_octave.setPosition(150, 150);
	upper_octave.setTextColor(0);

	play_tune.draw();
	play_tune.setPosition(100, 250);
	play_tune.setTextColor(0);
	play_tune.setBackgroundColor(230);

	style_.draw();
	style_.setPosition(100, 450);
}

void ofApp::drawRightSideElements() {
	tempo_slider.draw();
	tempo_slider.setPosition(600, 50);

	b_flat_scale.draw();
	b_flat_scale.setPosition(fRightSideFirstColumn, 150);

	e_flat_scale.draw();
	e_flat_scale.setPosition(fRightSideFirstColumn, 275);

	a_flat_scale.draw();
	a_flat_scale.setPosition(fRightSideFirstColumn, 400);

	d_flat_scale.draw();
	d_flat_scale.setPosition(fRightSideFirstColumn, 525);

	g_flat_scale.draw();
	g_flat_scale.setPosition(fRightSideFirstColumn, 650);

	b_major_scale.draw();
	b_major_scale.setPosition(fRightSideFirstColumn, 775);

	a_major_scale.draw();
	a_major_scale.setPosition(fRightSideSecondColumn, 150);

	d_major_scale.draw();
	d_major_scale.setPosition(fRightSideSecondColumn, 275);

	g_major_scale.draw();
	g_major_scale.setPosition(fRightSideSecondColumn, 400);

	c_major_scale.draw();
	c_major_scale.setPosition(fRightSideSecondColumn, 525);

	f_major_scale.draw();
	f_major_scale.setPosition(fRightSideSecondColumn, 650);

	chromatic_scale.draw();
	chromatic_scale.setPosition(fRightSideSecondColumn, 775);
}

// Draws the clarinet images
void ofApp::drawFingering(string note) {
	note = clarinet_->adjustForOctave(note);
	ofImage current_fingering = fingering_images.at(note);
	current_fingering.draw(425, 0, 200, 700);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	int upper_key = toupper(key);

	if (upper_key == '-') {
		volume_slider = volume_slider - fVolumeInterval;
	} else if (upper_key == '+') {
		volume_slider = volume_slider + fVolumeInterval;
	} else if (upper_key == OF_KEY_SHIFT) {	 
		upper_octave = !upper_octave;
	} else if (upper_key == 'Z') {
		playScale("Bb");
	} else {
		noteKeyPressed(upper_key);
	}

}

void ofApp::noteKeyPressed(int upper_key) {
	if (upper_key == 'A') {
		clarinet_->setCurrentNote("lowG");
		ofSoundStreamStart();
	} else if (upper_key == 'W') {
		clarinet_->setCurrentNote("lowAb");
		ofSoundStreamStart();
	} else if (upper_key == 'S') {
		clarinet_->setCurrentNote("lowA");
		ofSoundStreamStart();
	} else if (upper_key == 'E') {
		clarinet_->setCurrentNote("lowBb");
		ofSoundStreamStart();
	} else if (upper_key == 'D') {
		clarinet_->setCurrentNote("lowB");
		ofSoundStreamStart();
	} else if (upper_key == 'F') {
		clarinet_->setCurrentNote("lowC");
		ofSoundStreamStart();
	} else if (upper_key == 'T') {
		clarinet_->setCurrentNote("lowDb");
		ofSoundStreamStart();
	} else if (upper_key == 'G') {
		clarinet_->setCurrentNote("lowD");
		ofSoundStreamStart();
	} else if (upper_key == 'Y') {
		clarinet_->setCurrentNote("lowEb");
		ofSoundStreamStart();
	} else if (upper_key == 'H') {
		clarinet_->setCurrentNote("lowE");
		ofSoundStreamStart();
	} else if (upper_key == 'J') {
		clarinet_->setCurrentNote("lowF");
		ofSoundStreamStart();
	} 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	ofSoundStreamStop();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

} 
