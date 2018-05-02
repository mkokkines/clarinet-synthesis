#pragma once
#include "../addons/ofxGui/src/ofxSlider.h"
#include "../addons/ofxGui/src/ofxButton.h"
#include "ofMain.h"
#include "clarinet.h"
#include "../audioThread.h"

const double fVolumeInterval = .05;

const int fDefaultWindowWidth = 1024;
const int fDefaultWindowHeight = 768;
const int fDefaultFrameRate = 60;

const int fLeftSideXCoord = 150;

const int fVolumeYCoord = 50;
const double fVolumeMin = 0;
const double fVolumeMax = 1;
const double fVolumeStart = 0.5;

const int fUpOctaveYCoord = 150;
const int fUpOctaveSize = 75;
const int fRecordYCoord = 275;
const int fPlaybackYCoord = 400;
const int fNonScaleButtonSize = 100;
const bool fToggleDefault = false;

const int fRightSideFirstColumn = 725;
const int fRightSideSecondColumn = 850;
const int fFirstRow = 150;
const int fSecondRow = 250;
const int fThirdRow = 350;
const int fFourthRow = 450;
const int fFifthRow = 550;
const int fSixthRow = 650;

const int fDefaultSliderWidth = 200;
const int fDefaultSliderHeight = 60;

const int fTempoSliderXCoord = 712;
const int fTempoSliderYCoord = 50;

const int fScaleButtonSize = 50;
const int fClarinetImgXCoord = 425;
const int fClarinetImgYCoord = 0;
const int fClarinetImgWidth = 200;
const int fClarinetImgHeight = 700;

const double fDefaultTempo = 120;
const double fMinTempo = 0;
const double fMaxTempo = 240;
const double fSecPerMin = 60;

const double fProgramDelay = .63;

const string fPauseMessage = "Welcome to the clarinet music synthesis application. The aim of this application is to allow you to play realistic-sounding clarinet music and learn the basics of the instrument. The commands are as follows:\n 1) Press + to increase the volume and - to decrease the volume. Alternatively, you can drag the slider. \n 2) Press shift to change the octave. Alternatively, you can press the button. 3) Press any of the scale buttons to see that scale played.\n 4) Drag the tempo slider to change the speed at which the scales are played.";

const map<char, string> key_to_note = { { 'Q', "lowGb" },{ 'A', "lowG" },{ 'W', "lowAb" },{ 'S', "lowA" },{ 'E', "lowBb" },
{ 'D', "lowB" },{ 'F', "lowC" },{ 'T', "lowDb" },{ 'G', "lowD" },{ 'Y', "lowEb" },
{ 'H', "lowE" },{ 'J', "lowF" } };

const std::pair<string, vector<string>> fBbScale = { "Bb",{ "lowC", "lowD", "lowE", "lowF", "middleG", "middleA", "middleB", "middleC" } };
const std::pair<string, vector<string>> fEbScale = { "Eb",{ "lowF", "middleG", "middleA", "middleBb", "middleC", "middleD", "middleE",
"middleF" } };
const std::pair<string, vector<string>> fAbScale = { "Ab",{ "lowBb", "lowC", "lowD", "lowEb", "lowF", "middleG", "middleA", "middleBb" } };
const std::pair<string, vector<string>> fDbScale = { "Db",{ "lowEb", "lowF", "middleG", "middleAb", "middleBb", "middleC", "middleD",
"middleEb" } };
const std::pair<string, vector<string>> fGbScale = { "Gb",{ "lowAb", "lowBb", "lowC", "lowDb", "lowEb", "lowF", "middleG", "middleAb" } };
const std::pair<string, vector<string>> fBMajorScale = { "BMajor",{ "lowDb", "lowEb", "lowF", "middleGb", "middleAb", "middleBb", "middleC",
"middleDb" } };
const std::pair<string, vector<string>> fAMajorScale = { "AMajor",{ "lowB", "lowDb", "lowEb", "lowE", "middleGb", "middleAb", "middleBb",
"middleB" } };
const std::pair<string, vector<string>> fDMajorScale = { "DMajor",{ "lowE", "middleGb", "middleAb", "middleA", "middleB", "middleDb",
"middleEb", "middleE" } };
const std::pair<string, vector<string>> fGMajorScale = { "GMajor",{ "lowA", "lowB", "lowDb", "lowD", "lowE", "middleGb", "middleAb",
"middleA" } };
const std::pair<string, vector<string>> fCMajorScale = { "CMajor",{ "lowD", "lowE", "middleGb", "middleG", "middleA", "middleB",
"middleDb", "middleD" } };
const std::pair<string, vector<string>> fFMajorScale = { "FMajor",{ "lowG", "lowA", "lowB", "lowC", "lowD", "lowE", "middleGb", "middleG" } };
const std::pair<string, vector<string>> fChromaticScale = { "chromatic",{ "lowG", "lowAb", "lowA", "lowBb", "lowB", "lowC", "lowDb",
"lowD", "lowEb", "lowE", "lowF", "middleGb", "middleG" } };


class ofApp : public ofBaseApp {
private:
	AudioThread * audio_thread;

	bool is_paused;
	bool is_recording;

	vector<pair<string, double>> scale_notes;
	vector<pair<string, double>> recorded_notes;

	string current_note;
	vector<string> current_scale;
	std::clock_t timer_;

	ofxFloatSlider volume_slider;
	ofxFloatSlider scale_tempo_slider;
	ofxToggle upper_octave;
	ofxToggle record_;
	ofxToggle playback_;

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
	void setupScales();
	void setupAudioVariables();
	void setupRecordPlayback();

	void update();
	void updateNoteList(vector<pair<string, double>> &note_list);

	void keyPressed(int key);
	void keyReleased(int key);

	void windowResized(int w, int h);
	void resizeScales(double w_resize_factor, double h_resize_factor);
	void resizeAudioVariables(double w_resize_factor, double h_resize_factor);
	void resizeRecordPlayback(double w_resize_factor, double h_resize_factor);
	
	void draw();
	void drawFingering(string note);
	void drawPaused();

	void scaleTempoChanged(float &scale_tempo_slider);
	void volumeChanged(float &volume);

	string ofApp::adjustForOctave(string note);

	void noteKeyPressed(int upper_key);

	void ofApp::upperOctavePressed(bool &pressed);

	void recordPressed(bool &pressed);
	void playbackPressed(bool &pressed);
	void fillScaleNotes(vector<string> scale);

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
