#include "ofApp.h"

const double fVolumeInterval = .05;
const int fRightSideFirstColumn = 725;
const int fRightSideSecondColumn = 850;
const int fScaleButtonSize = 50;

const double fDefaultScaleTempo = 120;
const double fSecPerMin = 60;

const std::pair<string, vector<string>> fBbScale = { "Bb", {"lowC", "lowD", "lowE", "lowF", "middleG", "middleA", "middleB", "middleC"} };
const std::pair<string, vector<string>> fEbScale = { "Eb", {"lowF", "middleG", "middleA", "middleBb", "middleC", "middleD", "middleE", 
													"middleF"} };
const std::pair<string, vector<string>> fAbScale = { "Ab", {"lowBb", "lowC", "lowD", "lowEb", "lowF", "middleG", "middleA", "middleBb"} };
const std::pair<string, vector<string>> fDbScale = { "Db", {"lowEb", "lowF", "middleG", "middleAb", "middleBb", "middleC", "middleD", 
													"middleEb"} };
const std::pair<string, vector<string>> fGbScale = { "Gb", {"lowAb", "lowBb", "lowC", "lowDb", "lowEb", "lowF", "middleG", "middleAb"} };
const std::pair<string, vector<string>> fBMajorScale = { "BMajor", {"lowDb", "lowEb", "lowF", "middleGb", "middleAb", "middleBb", "middleC", 
														"middleDb" } };
const std::pair<string, vector<string>> fAMajorScale = { "AMajor", {"lowB", "lowDb", "lowEb", "lowE", "middleGb", "middleAb", "middleBb", 
														"middleB"} };
const std::pair<string, vector<string>> fDMajorScale = { "DMajor", {"lowE", "middleGb", "middleAb", "middleA", "middleB", "middleDb",
														"middleEb", "middleE"} };
const std::pair<string, vector<string>> fGMajorScale = { "GMajor", {"lowA", "lowB", "lowDb", "lowD", "lowE", "middleGb", "middleAb", 
														"middleA"} };
const std::pair<string, vector<string>> fCMajorScale = { "CMajor", {"lowD", "lowE", "middleGb", "middleG", "middleA", "middleB", 
														"middleDb", "middleD"} };
const std::pair<string, vector<string>> fFMajorScale = { "FMajor", {"lowG", "lowA", "lowB", "lowC", "lowD", "lowE", "middleGb", "middleG"} };
const std::pair<string, vector<string>> fChromaticScale = { "chromatic", {"lowG", "lowAb", "lowA", "lowBb", "lowB", "lowC", "lowDb",
															"lowD", "lowEb", "lowE", "lowF", "middleGb", "middleG"} };

//--------------------------------------------------------------
void ofApp::setup() {
	loadImages();

	audio_thread = new AudioThread();

	current_note = "middleG";
	current_scale = {};

	upper_octave.setup("Upper Octave", false, 75, 75);
	upper_octave.addListener(this, &ofApp::upperOctavePressed);

	volume_slider.addListener(this, &ofApp::volumeChanged);
    volume_slider.setup("Volume", .5, 0.0, 1.0, 200, 60);

	b_flat_scale.setup("Bb", fScaleButtonSize, fScaleButtonSize);
	b_flat_scale.addListener(this, &ofApp::bFlatScalePressed);
	e_flat_scale.setup("Eb", fScaleButtonSize, fScaleButtonSize);
	e_flat_scale.addListener(this, &ofApp::eFlatScalePressed);
	a_flat_scale.setup("Ab", fScaleButtonSize, fScaleButtonSize);
	a_flat_scale.addListener(this, &ofApp::aFlatScalePressed);
	d_flat_scale.setup("Db", fScaleButtonSize, fScaleButtonSize);
	d_flat_scale.addListener(this, &ofApp::dFlatScalePressed);
	g_flat_scale.setup("Gb", fScaleButtonSize, fScaleButtonSize);
	g_flat_scale.addListener(this, &ofApp::gFlatScalePressed);

	b_major_scale.setup("B Major", fScaleButtonSize, fScaleButtonSize);
	b_major_scale.addListener(this, &ofApp::bMajorScalePressed);
	a_major_scale.setup("A Major", fScaleButtonSize, fScaleButtonSize);
	a_major_scale.addListener(this, &ofApp::aMajorScalePressed);
	d_major_scale.setup("D Major", fScaleButtonSize, fScaleButtonSize);
	d_major_scale.addListener(this, &ofApp::dMajorScalePressed);
	g_major_scale.setup("G Major", fScaleButtonSize, fScaleButtonSize);
	g_major_scale.addListener(this, &ofApp::gMajorScalePressed);
	c_major_scale.setup("C Major", fScaleButtonSize, fScaleButtonSize);
	c_major_scale.addListener(this, &ofApp::cMajorScalePressed);
	f_major_scale.setup("F Major", fScaleButtonSize, fScaleButtonSize);
	f_major_scale.addListener(this, &ofApp::fMajorScalePressed);

	chromatic_scale.setup("Chromatic", fScaleButtonSize, fScaleButtonSize);
	chromatic_scale.addListener(this, &ofApp::chromaticScalePressed);

	play_tune.setup("Play Tune", 100, 100);

	scale_tempo_slider.addListener(this, &ofApp::scaleTempoChanged);
	scale_tempo_slider.setup("Scale Tempo BPM", fDefaultScaleTempo, 0.0, fDefaultScaleTempo * 2, 200, 60);

	style_.setup("Style", 100.0, 0.0, 200.0, 200, 60);

	scales = new std::map<string, vector<string>>();
	*scales = { fBbScale, fEbScale, fAbScale, fDbScale, fGbScale, fBMajorScale, fAMajorScale, fDMajorScale, fGMajorScale, 
				fCMajorScale, fFMajorScale, fChromaticScale };
	audio_thread->setScales(*scales);

	ofSetFrameRate(60);
}

void ofApp::loadImages() {
	lowGb.load("note_images/lowGb.png");
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

	fingering_images = { {"lowGb", lowGb}, { "lowG", lowG }, {"lowAb", lowAb}, { "lowA", lowA }, {"lowBb", lowBb}, { "lowB", lowB },
						 { "lowC", lowC }, {"lowDb", lowDb}, { "lowD", lowD }, {"lowEb", lowEb}, { "lowE", lowE },
						 { "lowF", lowF }, {"middleGb", middleGb}, { "middleG", middleG }, {"middleAb", middleAb},
						 {"middleA", middleA}, {"middleBb", middleBb}, {"middleB", middleB}, {"middleC", middleC},
						 {"middleDb", middleDb}, {"middleD", middleD}, {"middleEb", middleEb}, {"middleE", middleE},
						 {"middleF", middleF}, {"highGb", highGb}, {"highG", highG} };
} 

//--------------------------------------------------------------
void ofApp::update() {
	if (!current_scale.empty()) {
		double time_elapsed = (std::clock() - scale_clock) / (double)CLOCKS_PER_SEC;
		bool enough_time_elapsed = time_elapsed > (fSecPerMin / scale_tempo_slider);

		if (enough_time_elapsed && current_scale.size() != 1) {
			current_scale.erase(current_scale.begin());
			current_note = current_scale[0];
			scale_clock = std::clock();
		} else if (enough_time_elapsed) {
			current_scale.erase(current_scale.begin());
			audio_thread->stopThread();
		}
	} 
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(255, 255, 255);
	drawLeftSideElements();
	drawRightSideElements();
	drawFingering(current_note);
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
	scale_tempo_slider.draw();
	scale_tempo_slider.setPosition(712, 50);

	b_flat_scale.draw();
	b_flat_scale.setPosition(fRightSideFirstColumn, 150);
	b_flat_scale.setTextColor(0);

	e_flat_scale.draw();
	e_flat_scale.setPosition(fRightSideFirstColumn, 250);
	e_flat_scale.setTextColor(0);

	a_flat_scale.draw();
	a_flat_scale.setPosition(fRightSideFirstColumn, 350);
	a_flat_scale.setTextColor(0);

	d_flat_scale.draw();
	d_flat_scale.setPosition(fRightSideFirstColumn, 450);
	d_flat_scale.setTextColor(0);

	g_flat_scale.draw();
	g_flat_scale.setPosition(fRightSideFirstColumn, 550);
	g_flat_scale.setTextColor(0);

	b_major_scale.draw();
	b_major_scale.setPosition(fRightSideFirstColumn, 650);
	b_major_scale.setTextColor(0);

	a_major_scale.draw();
	a_major_scale.setPosition(fRightSideSecondColumn, 150);
	a_major_scale.setTextColor(0);

	d_major_scale.draw();
	d_major_scale.setPosition(fRightSideSecondColumn, 250);
	d_major_scale.setTextColor(0);

	g_major_scale.draw();
	g_major_scale.setPosition(fRightSideSecondColumn, 350);
	g_major_scale.setTextColor(0);

	c_major_scale.draw();
	c_major_scale.setPosition(fRightSideSecondColumn, 450);
	c_major_scale.setTextColor(0);

	f_major_scale.draw();
	f_major_scale.setPosition(fRightSideSecondColumn, 550);
	f_major_scale.setTextColor(0);

	chromatic_scale.draw();
	chromatic_scale.setPosition(fRightSideSecondColumn, 650);
	chromatic_scale.setTextColor(0);
}

// Draws the clarinet images
void ofApp::drawFingering(string note) {
	note = adjustForOctave(note);
	ofImage current_fingering = fingering_images.at(note);
	current_fingering.draw(425, 0, 200, 700);
}

string ofApp::adjustForOctave(string note) {
	if (upper_octave && note.substr(0, 3) == "low") {
		return note.replace(0, 3, "middle");
	} else {
		return note;
	}
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
		bool isHigherOctave = audio_thread->getClarinet()->getHigherOctave();
		audio_thread->getClarinet()->setHigherOctave(!isHigherOctave);
	} else {
		noteKeyPressed(upper_key);
	}

}

void ofApp::noteKeyPressed(int upper_key) {
	if (upper_key == 'Q') {
		current_note = "lowGb";
		audio_thread->setCurrentNote("lowGb");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'A') {
		current_note = "lowG";
		audio_thread->setCurrentNote("lowG");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'W') {
		current_note = "lowAb";
		audio_thread->setCurrentNote("lowAb");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'S') {
		current_note = "lowA";
		audio_thread->setCurrentNote("lowA");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'E') {
		current_note = "lowBb";
		audio_thread->setCurrentNote("lowBb");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'D') {
		current_note = "lowB";
		audio_thread->setCurrentNote("lowB");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'F') {
		current_note = "lowC";
		audio_thread->setCurrentNote("lowC");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'T') {
		current_note = "lowDb";
		audio_thread->setCurrentNote("lowDb");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'G') {
		current_note = "lowD";
		audio_thread->setCurrentNote("lowD");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'Y') {
		current_note = "lowEb";
		audio_thread->setCurrentNote("lowEb");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'H') {
		current_note = "lowE";
		audio_thread->setCurrentNote("lowE");
		audio_thread->startThread(true, false);
	} else if (upper_key == 'J') {
		current_note = "lowF";
		audio_thread->setCurrentNote("lowF");
		audio_thread->startThread(true, false);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	audio_thread->stopThread();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::scaleTempoChanged(float &scale_tempo_slider) {
	audio_thread->setScaleTempo(scale_tempo_slider);
}

void ofApp::volumeChanged(float &volume_slider) {
	audio_thread->getClarinet()->setVolume(volume_slider);
}

//--------------------------------------------------------------
void ofApp::upperOctavePressed(bool &pressed) {
	upper_octave = !upper_octave;
	bool isHigherOctave = audio_thread->getClarinet()->getHigherOctave();
	audio_thread->getClarinet()->setHigherOctave(pressed);
	scale_clock = std::clock();
}

void ofApp::bFlatScalePressed() {
	audio_thread->setScaleToPlay("Bb");
	audio_thread->startThread();
	current_scale = scales->at("Bb");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::eFlatScalePressed() {
	audio_thread->setScaleToPlay("Eb");
	audio_thread->startThread();
	current_scale = scales->at("Eb");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::aFlatScalePressed() {
	audio_thread->setScaleToPlay("Ab");
	audio_thread->startThread();
	current_scale = scales->at("Ab");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::dFlatScalePressed() {
	audio_thread->setScaleToPlay("Db");
	audio_thread->startThread();
	current_scale = scales->at("Db");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::gFlatScalePressed() {
	audio_thread->setScaleToPlay("Gb");
	audio_thread->startThread();
	current_scale = scales->at("Gb");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::bMajorScalePressed() {
	audio_thread->setScaleToPlay("BMajor");
	audio_thread->startThread();
	current_scale = scales->at("BMajor");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::aMajorScalePressed() {
	audio_thread->setScaleToPlay("AMajor");
	audio_thread->startThread();
	current_scale = scales->at("AMajor");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::dMajorScalePressed() {
	audio_thread->setScaleToPlay("DMajor");
	audio_thread->startThread();
	current_scale = scales->at("DMajor");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::gMajorScalePressed() {
	audio_thread->setScaleToPlay("GMajor");
	audio_thread->startThread();
	current_scale = scales->at("GMajor");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::cMajorScalePressed() {
	audio_thread->setScaleToPlay("CMajor");
	audio_thread->startThread();
	current_scale = scales->at("CMajor");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::fMajorScalePressed() {
	audio_thread->setScaleToPlay("FMajor");
	audio_thread->startThread();
	current_scale = scales->at("FMajor");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

void ofApp::chromaticScalePressed() {
	audio_thread->setScaleToPlay("chromatic");
	audio_thread->startThread();
	current_scale = scales->at("chromatic");
	current_note = current_scale[0];
	scale_clock = std::clock();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

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
