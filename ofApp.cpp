#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	loadImages();
	ofSoundStreamSetup(4, 0, this, 44100, 256, 4);
}

void ofApp::loadImages() {
	lowG.load("../note_images/lowG");
	lowA.load("../note_images/lowA");
	lowB.load("../note_images/lowB");
	lowC.load("../note_images/lowC");
	lowD.load("../note_images/lowD");
	middleE.load("../note_images/middleE");
	middleF.load("../note_images/middleF");
	middleG.load("../note_images/middleG");

	fingering_images = { {"lowG", lowG}, { "lowA", lowA}, { "lowB", lowB}, { "lowC", lowC},
						 {"lowD", lowD}, {"middleE", middleE}, {"middleF", middleF},
						 {"middleG", middleG} };
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

void ofApp::drawFingering(string note) {
	ofImage current_fingering = fingering_images.at(note);
	current_fingering.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
