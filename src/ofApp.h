#pragma once
#include "../addons/ofxGui/src/ofxSlider.h"
#include "../addons/ofxGui/src/ofxButton.h"
#include "ofMain.h"
#include "../clarinet.h"

class ofApp : public ofBaseApp {
	private:
		clarinet::Clarinet* clarinet_;

		ofxFloatSlider volume_slider;
		ofxToggle upper_octave;

		ofxButton play_tune;
		ofxIntSlider tempo_slider;
		ofxFloatSlider style_;

	// Fingerings for each note
		ofImage lowG;
		ofImage lowAb;
		ofImage lowA;
		ofImage lowBb;
		ofImage lowB;
		ofImage lowC;
		ofImage lowDb;
		ofImage lowD;
		ofImage lowEb;
		ofImage lowE;
		ofImage lowF;
		ofImage middleGb;
		ofImage middleG;
		ofImage middleAb;
		ofImage middleA;
		ofImage middleBb;
		ofImage middleB;
		ofImage middleC;
		ofImage middleDb;
		ofImage middleD;
		ofImage middleEb;
		ofImage middleE;
		ofImage middleF;
		ofImage highGb;
		ofImage highG;
		std::map<string, ofImage> fingering_images;
	
		void loadImages();
		void drawSliders();
		void drawFingering(string note);
		void audioOut(float * output, int buffer_size, int n_channels);
		void noteKeyPressed(int upper_key);
	
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg); 

};


