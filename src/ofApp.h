#pragma once
#include "../addons/ofxGui/src/ofxSlider.h"
#include "../addons/ofxGui/src/ofxButton.h"
#include "clarinet.h"
#include "../audioThread.h"
#include "../recordingComparer.h"

const double fVolumeInterval = .05;	

const int fDefaultWindowWidth = 1024;
const int fDefaultWindowHeight = 768;
const int fDefaultFrameRate = 60;

const int fLeftSideXCoord = 150;		// Left of the clarinet diagram

const int fVolumeYCoord = 50;
const double fVolumeMin = 0;
const double fVolumeMax = 1;
const double fVolumeStart = 0.5;

const int fUpOctaveYCoord = 150;
const int fUpOctaveSize = 75;
const int fRecordYCoord = 250;
const int fPlaybackYCoord = 350;
const int fCompareYCoord = 450;
const int fNonScaleButtonSize = 85;
const bool fToggleDefault = false;

const int fRightSideFirstColumn = 725;		// Right side is right of the clarinet diagram
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

const string fFontFileAddress = "Roboto-Black.ttf";
const int fFontSize = 16;
const int fPauseXCoord = 150;
const int fPauseYCoord = 250;

const int fCompareMessageXCoord = 10;
const int fFirstCompareMessageYCoord = 575;
const int fSecondCompareMessageYCoord = 700;

const double fProgramDelay = .63;	// the program instructions take a certain period of time to run, lengthening pauses

const string fPauseFirstLine = "Welcome to the clarinet music synthesis application.\n";
const string fPauseSecondLine = "The app will allow you to play/learn realistic clarinet.\n";
const string fPauseThirdLine = "The commands are as follows:\n";
const string fPauseFourthLine = "1) Keys A-J play normal notes; Q, W, E, T, Y, I play flats\n.";
const string fPauseFifthLine = "2) Press + and -, or use the slider, to change the volume.\n"; 
const string fPauseSixthLine = "3) Press shift or click the button to switch the octave.\n";
const string fPauseSeventhLine = "4) Press any of the scale buttons to see that scale played.\n";
const string fPauseEighthLine = "5) Drag the tempo slider to change the bpm of the scales.\n";
const string fPauseNinthLine = "6) Press the record button and play a series of notes to record\n";
const string fPauseTenthLine = "7) Press the playback button to hear your most recent recording\n";

const string fNoFingersNote = "middleG"; // middleG shows no fingers

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

// This class contains the graphic user interface, the functions that allow the user to interact with the GUI, the
// functions that update the GUI, and the audio thread.
class ofApp : public ofBaseApp {
private:
	AudioThread * audio_thread;

	RecordingComparer comparer;
	pair<string, string> compare_messages;

	bool is_paused;

	std::map<string, ofImage> fingering_images;
	std::map<string, vector<string>>* scales;				// List of the scales by their names
	vector<pair<string, double>> scale_notes;				// The notes corresponding to one scale
	vector<pair<string, double>> recorded_notes;			// most recent recording
	vector<pair<string, double>> past_recorded_notes;		// previous recording

	string current_note;
	std::clock_t timer_;

	ofxFloatSlider volume_slider;
	ofxFloatSlider scale_tempo_slider;
	ofxToggle upper_octave;				// true when playing the upper octave
	ofxToggle record_;
	ofxToggle playback_;
	ofxToggle compare_recordings;		

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

	// Used during setup
	void loadImages();				// Loads clarinet fingering image and places into map
	void setupScales();				// Set up scale buttons and map
	void setupAudioVariables();		// Set up buttons for volume, tempo, and octave
	void setupRecordPlayback();		// Set up record, playback, and compare functionality

	// Used during update. Moves to next note when playing scales or a recording
	void updateNoteList(vector<pair<string, double>> &note_list); 

	// Used during draw
	void drawFingering(string note);
	void drawPaused();
	void drawCompareMessages();

	// Used during window resizing
	void resizeScales(double w_resize_factor, double h_resize_factor);
	void resizeAudioVariables(double w_resize_factor, double h_resize_factor);
	void resizeRecordPlayback(double w_resize_factor, double h_resize_factor);

	string adjustForOctave(string note);		// Adjusts the name of the note being played to match the octave
	void noteKeyPressed(int upper_key);			// Helper function used during keyPressed
	void fillScaleNotes(vector<string> scale);	// Assigns time values (e.g. hold for .5 sec) to each note in scale

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void windowResized(int w, int h);

	// Change GUI elements corresponding to different variables
	void scaleTempoChanged(float &scale_tempo_slider);
	void volumeChanged(float &volume);
	void upperOctavePressed(bool &pressed);
	void recordPressed(bool &pressed);
	void playbackPressed(bool &pressed);
	void comparePressed(bool &pressed);

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
