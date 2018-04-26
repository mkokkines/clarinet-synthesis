#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	current_note = "middleG";
	loadImages();
	// ofSoundStreamSetup(4, 0, this, 44100, 256, 4);
	// ofSoundStreamStart();

	// clarinet_ = new clarinet::Clarinet();
	// clarinet_->setUp();

	play_tune.setup("Play Tune", 100, 100);
	volume_.setup("Volume", 100.0, 0.0, 200.0, 200, 60);
	tempo_.setup("Tempo", 100.0, 0.0, 200.0, 200, 60);
	style_.setup("Style", 100.0, 0.0, 200.0, 200, 60);

	ofSetFrameRate(60);
}

void ofApp::loadImages() {
	lowG.load("note_images/lowG.png");
	lowA.load("note_images/lowA.png");
	lowB.load("note_images/lowB.png");
	lowC.load("note_images/lowC.png");
	lowD.load("note_images/lowD.png");
	middleE.load("note_images/middleE.png");
	middleF.load("note_images/middleF.png");
	middleG.load("note_images/middleG.png");

	fingering_images = { { "lowG", lowG },{ "lowA", lowA },{ "lowB", lowB },{ "lowC", lowC },
	{ "lowD", lowD },{ "middleE", middleE },{ "middleF", middleF },
	{ "middleG", middleG } };
} 

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(255, 255, 255);
	drawSliders();
	drawFingering(current_note);
}

void ofApp::drawSliders() {
	play_tune.draw();
	play_tune.setPosition(800, 50);
	play_tune.setTextColor(0);
	play_tune.setBackgroundColor(230);

	volume_.draw();
	volume_.setPosition(750, 200);
	tempo_.draw();
	tempo_.setPosition(750, 300);
	style_.draw();
	style_.setPosition(750, 400);
}

void ofApp::drawFingering(string note) {
	ofImage current_fingering = fingering_images.at(note);
	current_fingering.draw(425, 0, 200, 700);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int upper_key = toupper(key);

	if (upper_key == 'S') {
	//	clarinet_->setArticulation('s');
	} else if (upper_key == 'L') {
	//	clarinet_->setArticulation('l');
	} else if (upper_key == 'N') {
	//	clarinet_->setArticulation('n');
	} else if (upper_key == '-') {
	//	clarinet_->setVolume(0.9);
	} else if (upper_key == '+') {
	//	clarinet_->setVolume(1.1);
	} else if (upper_key == '1') {
	//	clarinet_->generateNote(440);
	current_note = "lowG";
	} else if (upper_key == '2') {
	//	clarinet_->generateNote(440);
	current_note = "lowA";
	} else if (upper_key == '3') {
	//	clarinet_->generateNote(440);
	current_note = "lowB";
	} else if (upper_key == '4') {
	//	clarinet_->generateNote(440);
	current_note = "lowC";
	} else if (upper_key == '5') {
	//	clarinet_->generateNote(440);
	current_note = "lowD";
	} else if (upper_key == '6') {
	//	clarinet_->generateNote(440);
	current_note = "middleE";
	} else if (upper_key == '7') {
	//	clarinet_->generateNote(440);
	current_note = "middleF";
	} else if (upper_key == '8') {
	//	clarinet_->generateNote(440);
	current_note = "middleG";
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
void ofApp::dragEvent(ofDragInfo dragInfo){ 

} 
