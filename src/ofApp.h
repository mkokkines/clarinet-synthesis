#pragma once
#include "../addons/ofxGui/src/ofxSlider.h"
#include "../addons/ofxGui/src/ofxButton.h"
#include "ofMain.h"
#include "clarinet.h"
#include "../audioThread.h"

class ofApp : public ofBaseApp {
	private:
		AudioThread* audio_thread;

		string current_note;
		vector<string> current_scale;
		std::clock_t scale_clock;

		ofxFloatSlider volume_slider;
		ofxToggle upper_octave;

		ofxButton play_tune;
		ofxFloatSlider scale_tempo_slider;
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
		ofImage lowGb;
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

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void draw();
		void drawLeftSideElements();
		void drawRightSideElements();
		void drawFingering(string note);

		void scaleTempoChanged(float &scale_tempo_slider);
		void volumeChanged(float &volume);

		string ofApp::adjustForOctave(string note);

		// void playScale(string scale_name);
		// void playTune();
		void noteKeyPressed(int upper_key);

		void ofApp::upperOctavePressed(bool &pressed);

		// Scale Buttons Pressed
		void bFlatScalePressed();
		void eFlatScalePressed();
		void aFlatScalePressed();
		void dFlatScalePressed();
		void gFlatScalePressed();
		void bMajorScalePressed();
		void aMajorScalePressed();
		void dMajorScalePressed();
		void gMajorScalePressed();
		void cMajorScalePressed();
		void fMajorScalePressed();
		void chromaticScalePressed();
};
