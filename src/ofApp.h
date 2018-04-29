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

		// scale buttons
		ofxButton b_flat_scale;
		ofxButton e_flat_scale;
		ofxButton a_flat_scale;
		ofxButton d_flat_scale;
		ofxButton g_flat_scale;
		ofxButton b_major_scale;
		ofxButton a_major_scale;
		ofxButton d_major_scale;
		ofxButton g_major_scale;
		ofxButton c_major_scale;
		ofxButton f_major_scale;
		ofxButton chromatic_scale;

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
		std::map<string, vector<string>>* scales;

		std::vector<pair<double, string>>* tune;
	
		void loadImages();
	
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

		void drawLeftSideElements();
		void drawRightSideElements();
		void drawFingering(string note);

		void audioOut(float *output, int bufferSize, int nChannels);
		void playScale(string scale_name);
		void playTune();
		void noteKeyPressed(int upper_key);
};


