#include "ofApp.h"

const double fVolumeInterval = .05;

//--------------------------------------------------------------
void ofApp::setup() {
	loadImages();

	clarinet_ = new clarinet::Clarinet();
	clarinet_->setCurrentNote("middleG");

	play_tune.setup("Play Tune", 100, 100);
	upper_octave.setup("Upper Octave", false, 75, 75);

	volume_slider.setup("Volume", .5, 0.0, 1.0, 200, 60);
	tempo_slider.setup("Tempo", 100.0, 0.0, 200.0, 200, 60);
	style_.setup("Style", 100.0, 0.0, 200.0, 200, 60);

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
	highGb.load("note_images/highGb.png");
	highG.load("note_images/highG.png");

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
void ofApp::audioOut(float *output, int buffer_size, int n_channels) {
	clarinet_->generateNote(clarinet_->getCurrentNote());

	if (clarinet_->synth_ != NULL) {
		clarinet_->synth_->fillBufferOfFloats(output, buffer_size, n_channels);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	string title = "Clarinet Synthesis Studio";

	ofSetBackgroundColor(255, 255, 255);
	drawSliders();
	drawFingering(clarinet_->getCurrentNote());
}

void ofApp::drawSliders() {
	play_tune.draw();
	play_tune.setPosition(800, 50);
	play_tune.setTextColor(0);
	play_tune.setBackgroundColor(230);

	upper_octave.draw();
	upper_octave.setPosition(150, 150);
	upper_octave.setTextColor(0);

	volume_slider.draw();
	volume_slider.setPosition(100, 50);
	tempo_slider.draw();
	tempo_slider.setPosition(750, 200);
	style_.draw();
	style_.setPosition(750, 300);
}

void ofApp::drawFingering(string note) {
	string test_string = note.substr(0, 6);

	if (clarinet_->getHigherOctave() && note.substr(0, 3) == "low") {
		note.replace(0, 3, "middle");
	} else if (clarinet_->getHigherOctave() && note.substr(0, 6) == "middle") {
		note.replace(0, 6, "high");
	}

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
	} else if (upper_key == 'I') {
		clarinet_->setCurrentNote("middleGb");
		ofSoundStreamStart();
	} else if (upper_key == 'K') {
		clarinet_->setCurrentNote("middleG");
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
