#include "ofApp.h"

//--------------------------------------------------------------
// Sets up the application
void ofApp::setup() {
	audio_thread = new AudioThread();
	current_note = fNoFingersNote;

	loadImages();
	setupScales();
	setupAudioVariables();
	setupRecordPlayback();
	ofSetFrameRate(fDefaultFrameRate);
}

// Loads images of fingerings; a folder entitled note images contains the images below and must be included in bin
// Note: these file addresses are not used elsewhere
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

	fingering_images = { { "lowGb", lowGb },{ "lowG", lowG },{ "lowAb", lowAb },{ "lowA", lowA },{ "lowBb", lowBb },{ "lowB", lowB },
	{ "lowC", lowC },{ "lowDb", lowDb },{ "lowD", lowD },{ "lowEb", lowEb },{ "lowE", lowE },
	{ "lowF", lowF }, { "middleGb", middleGb },{ "middleG", middleG }, { "middleAb", middleAb },
	{ "middleA", middleA },{ "middleBb", middleBb },{ "middleB", middleB }, { "middleC", middleC },
	{ "middleDb", middleDb },{ "middleD", middleD },{ "middleEb", middleEb }, { "middleE", middleE },
	{ "middleF", middleF }, { "highGb", highGb }, { "highG", highG } };
}

// Etablishes the color, names, sizes, and listeners for the scale buttons
// Note: Also sets up the scales map in the audioThread object
void ofApp::setupScales() {
	scales = new std::map<string, vector<string>>();
	*scales = { fBbScale, fEbScale, fAbScale, fDbScale, fGbScale, fBMajorScale, fAMajorScale, fDMajorScale, fGMajorScale,
		fCMajorScale, fFMajorScale, fChromaticScale };

	audio_thread->setScales(*scales);
	scale_notes = {};

	b_flat_scale.setup("Bb", fScaleButtonSize, fScaleButtonSize);
	b_flat_scale.addListener(this, &ofApp::bFlatScalePressed);
	b_flat_scale.setTextColor(BLACKNESS);
	b_flat_scale.setPosition(fRightSideFirstColumn, fFirstRow);

	e_flat_scale.setup("Eb", fScaleButtonSize, fScaleButtonSize);
	e_flat_scale.addListener(this, &ofApp::eFlatScalePressed);
	e_flat_scale.setTextColor(BLACKNESS);
	e_flat_scale.setPosition(fRightSideFirstColumn, fSecondRow);

	a_flat_scale.setup("Ab", fScaleButtonSize, fScaleButtonSize);
	a_flat_scale.addListener(this, &ofApp::aFlatScalePressed);
	a_flat_scale.setTextColor(BLACKNESS);
	a_flat_scale.setPosition(fRightSideFirstColumn, fThirdRow);

	d_flat_scale.setup("Db", fScaleButtonSize, fScaleButtonSize);
	d_flat_scale.addListener(this, &ofApp::dFlatScalePressed);
	d_flat_scale.setTextColor(BLACKNESS);
	d_flat_scale.setPosition(fRightSideFirstColumn, fFourthRow);

	g_flat_scale.setup("Gb", fScaleButtonSize, fScaleButtonSize);
	g_flat_scale.addListener(this, &ofApp::gFlatScalePressed);
	g_flat_scale.setTextColor(BLACKNESS);
	g_flat_scale.setPosition(fRightSideFirstColumn, fFifthRow);

	b_major_scale.setup("B Major", fScaleButtonSize, fScaleButtonSize);
	b_major_scale.addListener(this, &ofApp::bMajorScalePressed);
	b_major_scale.setTextColor(BLACKNESS);
	b_major_scale.setPosition(fRightSideFirstColumn, fSixthRow);

	a_major_scale.setup("A Major", fScaleButtonSize, fScaleButtonSize);
	a_major_scale.addListener(this, &ofApp::aMajorScalePressed);
	a_major_scale.setTextColor(BLACKNESS);
	a_major_scale.setPosition(fRightSideSecondColumn, fFirstRow);

	d_major_scale.setup("D Major", fScaleButtonSize, fScaleButtonSize);
	d_major_scale.addListener(this, &ofApp::dMajorScalePressed);
	d_major_scale.setTextColor(BLACKNESS);
	d_major_scale.setPosition(fRightSideSecondColumn, fSecondRow);

	g_major_scale.setup("G Major", fScaleButtonSize, fScaleButtonSize);
	g_major_scale.addListener(this, &ofApp::gMajorScalePressed);
	g_major_scale.setTextColor(BLACKNESS);
	g_major_scale.setPosition(fRightSideSecondColumn, fThirdRow);

	c_major_scale.setup("C Major", fScaleButtonSize, fScaleButtonSize);
	c_major_scale.addListener(this, &ofApp::cMajorScalePressed);
	c_major_scale.setTextColor(BLACKNESS);
	c_major_scale.setPosition(fRightSideSecondColumn, fFourthRow);

	f_major_scale.setup("F Major", fScaleButtonSize, fScaleButtonSize);
	f_major_scale.addListener(this, &ofApp::fMajorScalePressed);
	f_major_scale.setTextColor(BLACKNESS);
	f_major_scale.setPosition(fRightSideSecondColumn, fFifthRow);

	chromatic_scale.setup("Chromatic", fScaleButtonSize, fScaleButtonSize);
	chromatic_scale.addListener(this, &ofApp::chromaticScalePressed);
	chromatic_scale.setTextColor(BLACKNESS);
	chromatic_scale.setPosition(fRightSideSecondColumn, fSixthRow);
}

// Establishes the size, position, color, and listeners for the octave, volume, and tempo elements
void ofApp::setupAudioVariables() {
	upper_octave.setup("Upper Octave", fToggleDefault, fNonScaleButtonSize, fNonScaleButtonSize);
	upper_octave.addListener(this, &ofApp::upperOctavePressed);
	upper_octave.setPosition(fLeftSideXCoord, fUpOctaveYCoord);
	upper_octave.setTextColor(BLACKNESS);

	volume_slider.addListener(this, &ofApp::volumeChanged);
	volume_slider.setup("Volume", fVolumeStart, fVolumeMin, fVolumeMax, fDefaultSliderWidth, fDefaultSliderHeight);
	volume_slider.setPosition(fLeftSideXCoord, fVolumeYCoord);

	scale_tempo_slider.setup("Scale Tempo BPM", fDefaultTempo, fMinTempo, fMaxTempo, fDefaultSliderWidth, fDefaultSliderHeight);
	scale_tempo_slider.setPosition(fTempoSliderXCoord, fTempoSliderYCoord);
}

// Establishes the buttons for the record, playback, and compare elements
void ofApp::setupRecordPlayback() {
	record_.setup("Record", fToggleDefault, fNonScaleButtonSize, fNonScaleButtonSize);
	record_.addListener(this, &ofApp::recordPressed);
	record_.setPosition(fLeftSideXCoord, fRecordYCoord);
	record_.setTextColor(BLACKNESS);
	record_.setBackgroundColor(ofColor::red);

	playback_.setup("Playback", fToggleDefault, fNonScaleButtonSize, fNonScaleButtonSize);
	playback_.addListener(this, &ofApp::playbackPressed);
	playback_.setPosition(fLeftSideXCoord, fPlaybackYCoord);
	playback_.setTextColor(BLACKNESS);
	playback_.setBackgroundColor(ofColor::darkOliveGreen);

	compare_recordings.setup("Compare Recordings", fToggleDefault, fNonScaleButtonSize, fNonScaleButtonSize);
	compare_recordings.addListener(this, &ofApp::comparePressed);
	compare_recordings.setPosition(fLeftSideXCoord, fCompareYCoord);
	compare_recordings.setTextColor(BLACKNESS);
	compare_recordings.setBackgroundColor(ofColor::blue);
}

//--------------------------------------------------------------
// changes the state of playback and the list of notes being played where applicable
void ofApp::update() {
	if (playback_ && recorded_notes.empty()) {	// sets playback to false after the final note has been played
		playback_ = false;
	} else if (playback_) {
		updateNoteList(recorded_notes);
	} else if (!scale_notes.empty()) {
		updateNoteList(scale_notes);
	} 
}

// Determines if the note has been played for a sufficient period of time
// If so, it moves to the next element of the note list being played and restarts the clock
// If there are no more notes to play, the audio thread is terminated
void ofApp::updateNoteList(vector<pair<string, double>> &note_list) {
	double time_elapsed = (std::clock() - timer_) / (double) CLOCKS_PER_SEC;
	bool enough_time_elapsed = time_elapsed >= note_list[0].second;

	if (enough_time_elapsed && note_list.size() != 1) {
		note_list.erase(note_list.begin());
		current_note = note_list[0].first;
		timer_ = std::clock();
	} else if (enough_time_elapsed) {
		audio_thread->stopThread();
		note_list.erase(note_list.begin());
	}
}

//--------------------------------------------------------------
// Draws the elements of the GUI on the screen
void ofApp::draw() {
	if (is_paused && scale_notes.empty()) {		// Can't pause while playing a scale
		drawPaused();
	} else {
		ofSetBackgroundColor(ofColor::white);
		drawCompareMessages();
		ofSetColor(ofColor::white);	// Must reset after the compare messages because they change the color to black
		drawFingering(current_note);

		volume_slider.draw();
		upper_octave.draw();
		record_.draw();
		playback_.draw();
		compare_recordings.draw();
		scale_tempo_slider.draw();

		b_flat_scale.draw();
		e_flat_scale.draw();
		a_flat_scale.draw();
		d_flat_scale.draw();
		g_flat_scale.draw();
		b_major_scale.draw();
		a_major_scale.draw();
		d_major_scale.draw();
		g_major_scale.draw();
		c_major_scale.draw();
		f_major_scale.draw();
		chromatic_scale.draw();
	}
}

// Firsts adjusts the note for the octave and then draws the fingering images to the screen.
// Sets the size of the images based upon the width and height of the screen -- cannot be set during
// setup because a new images is potentially loaded every time
void ofApp::drawFingering(string note) {
	note = adjustForOctave(note);

	if (note.empty()) {
		note = fNoFingersNote;
	}

	ofImage current_fingering = fingering_images.at(note);

	double width_factor = (double) ofGetWindowWidth() / fDefaultWindowWidth;
	double height_factor = (double) ofGetWindowHeight() / fDefaultWindowHeight;
	current_fingering.draw(fClarinetImgXCoord * width_factor, fClarinetImgYCoord * height_factor, 
						   fClarinetImgWidth * width_factor, fClarinetImgHeight * height_factor);
}

// Prints a list of instructions to the screen while the game is paused.
// Roboto-Black.ttf, the font being used, must be placed in the data folder
void ofApp::drawPaused() {
	string print_message = fPauseFirstLine + fPauseSecondLine + fPauseThirdLine + fPauseFourthLine
		+ fPauseFifthLine + fPauseSixthLine + fPauseSeventhLine + fPauseEighthLine + fPauseEighthLine
		+ fPauseNinthLine + fPauseTenthLine;

	ofTrueTypeFont font;
	font.loadFont(fFontFileAddress, fFontSize);
	ofSetColor(ofColor::black);
	font.drawString(print_message, fPauseXCoord, fPauseYCoord);
}

// Writes the compare messages -- detailling which notes were played incorrectly -- to the 
// screen in black font.
void ofApp::drawCompareMessages() {
	ofSetColor(ofColor::black);
	ofDrawBitmapString(compare_messages.first, fCompareMessageXCoord, fFirstCompareMessageYCoord);
	ofDrawBitmapString(compare_messages.second, fCompareYCoord, fSecondCompareMessageYCoord);
}

//--------------------------------------------------------------
// Resizes the GUI in response to the window being resized
void ofApp::windowResized(int w, int h) {
	double w_resize_factor = (double) w / fDefaultWindowWidth;
	double h_resize_factor = (double) h / fDefaultWindowHeight;

	resizeScales(w_resize_factor, h_resize_factor);
	resizeAudioVariables(w_resize_factor, h_resize_factor);
	resizeRecordPlayback(w_resize_factor, h_resize_factor);
}

// Resets the position and size of the scale buttons after window resizing
void ofApp::resizeScales(double w_resize_factor, double h_resize_factor) {
	double new_scale_button_size = fScaleButtonSize * std::min(w_resize_factor, h_resize_factor);
	b_flat_scale.setSize(new_scale_button_size, new_scale_button_size);
	e_flat_scale.setSize(new_scale_button_size, new_scale_button_size);
	a_flat_scale.setSize(new_scale_button_size, new_scale_button_size);
	d_flat_scale.setSize(new_scale_button_size, new_scale_button_size);
	g_flat_scale.setSize(new_scale_button_size, new_scale_button_size);
	b_major_scale.setSize(new_scale_button_size, new_scale_button_size);
	a_major_scale.setSize(new_scale_button_size, new_scale_button_size);
	d_major_scale.setSize(new_scale_button_size, new_scale_button_size);
	g_major_scale.setSize(new_scale_button_size, new_scale_button_size);
	c_major_scale.setSize(new_scale_button_size, new_scale_button_size);
	f_major_scale.setSize(new_scale_button_size, new_scale_button_size);
	chromatic_scale.setSize(new_scale_button_size, new_scale_button_size);

	b_flat_scale.setPosition(fRightSideFirstColumn * w_resize_factor, fFirstRow * h_resize_factor);
	e_flat_scale.setPosition(fRightSideFirstColumn * w_resize_factor, fSecondRow * h_resize_factor);
	a_flat_scale.setPosition(fRightSideFirstColumn * w_resize_factor, fThirdRow * h_resize_factor);
	d_flat_scale.setPosition(fRightSideFirstColumn * w_resize_factor, fFourthRow * h_resize_factor);
	g_flat_scale.setPosition(fRightSideFirstColumn * w_resize_factor, fFifthRow * h_resize_factor);
	b_major_scale.setPosition(fRightSideFirstColumn * w_resize_factor, fSixthRow * h_resize_factor);
	a_major_scale.setPosition(fRightSideSecondColumn * w_resize_factor, fFirstRow * h_resize_factor);
	d_major_scale.setPosition(fRightSideSecondColumn * w_resize_factor, fSecondRow * h_resize_factor);
	g_major_scale.setPosition(fRightSideSecondColumn * w_resize_factor, fThirdRow * h_resize_factor);
	c_major_scale.setPosition(fRightSideSecondColumn * w_resize_factor, fFourthRow * h_resize_factor);
	f_major_scale.setPosition(fRightSideSecondColumn * w_resize_factor, fFifthRow * h_resize_factor);
	chromatic_scale.setPosition(fRightSideSecondColumn * w_resize_factor, fSixthRow * h_resize_factor);
} 

// Resets the size and position of the sliders and buttons for audio variables after
// window resizing.
void ofApp::resizeAudioVariables(double w_resize_factor, double h_resize_factor) {
	scale_tempo_slider.setSize(fDefaultSliderWidth * w_resize_factor, fDefaultSliderHeight * h_resize_factor);
	scale_tempo_slider.setPosition(fTempoSliderXCoord * w_resize_factor, fTempoSliderYCoord * h_resize_factor);

	volume_slider.setSize(fDefaultSliderWidth * w_resize_factor, fDefaultSliderHeight * h_resize_factor);
	volume_slider.setPosition(fLeftSideXCoord * w_resize_factor, fVolumeYCoord * h_resize_factor);

	double non_scale_button_size = fNonScaleButtonSize * std::min(w_resize_factor, h_resize_factor);
	upper_octave.setSize(non_scale_button_size, non_scale_button_size);
	upper_octave.setPosition(fLeftSideXCoord * w_resize_factor, fUpOctaveYCoord * h_resize_factor);
}

// Resets the size and position for the record, playback, and compare buttons after window resizing
void ofApp::resizeRecordPlayback(double w_resize_factor, double h_resize_factor) {
	double non_scale_button_size = fNonScaleButtonSize * std::min(w_resize_factor, h_resize_factor);

	record_.setPosition(fLeftSideXCoord * w_resize_factor, fRecordYCoord * h_resize_factor);
	record_.setSize(non_scale_button_size, non_scale_button_size);

	playback_.setPosition(fLeftSideXCoord * w_resize_factor, fPlaybackYCoord * h_resize_factor);
	playback_.setSize(non_scale_button_size, non_scale_button_size);

	compare_recordings.setPosition(fLeftSideXCoord * w_resize_factor, fCompareYCoord * h_resize_factor);
	compare_recordings.setSize(non_scale_button_size, non_scale_button_size);
}

//--------------------------------------------------------------
// Since the pressed key function below only sets the current_note variable to notes in the lower octave
// (limited keyboard space), this method switches the name to correspond to notes in the higher octave 
// when applicable
string ofApp::adjustForOctave(string note) {
	if (upper_octave && note.substr(0, 3) == "low") {
		return note.replace(0, 3, "middle");
	} else {
		return note;
	}
}

//--------------------------------------------------------------
// Performs actions corresponding to keys pressed by the user
void ofApp::keyPressed(int key) {
	int upper_key = toupper(key);

	if (upper_key == '-') {	
		volume_slider = volume_slider - fVolumeInterval;
	} else if (upper_key == '+') {
		volume_slider = volume_slider + fVolumeInterval;
	} else if (upper_key == OF_KEY_SHIFT) {
		bool new_octave = !audio_thread->getClarinet()->getHigherOctave();
		audio_thread->getClarinet()->setHigherOctave(new_octave);
		upper_octave = new_octave;
	} else if (upper_key == 'P') {
		is_paused = !is_paused;
	} else {
		noteKeyPressed(upper_key);
	}

}

// Called when the user presses a key that does not change one of the audio parameters.
// The first piece, when the record button has been pressed, records the time between the last note
// being released and this button being pressed and records it as a pause in the list of notes to be 
// played back. The second part determines which note (if any) the pressed key corresponds to, and 
// calls the methods to play that note
void ofApp::noteKeyPressed(int upper_key) {
	bool key_matches_note = key_to_note.find(upper_key) != key_to_note.end();

	if (record_ && key_matches_note && !recorded_notes.empty()  && recorded_notes.back().first != "") {
		double time_elapsed = fProgramDelay * (std::clock() - timer_) / (double) CLOCKS_PER_SEC;
		recorded_notes.push_back({ "", time_elapsed });	// empty string indicates a pause
		timer_ = std::clock();
	}

	if (key_matches_note) {
		current_note = key_to_note.at(upper_key);
		adjustForOctave(current_note);
		audio_thread->setCurrentNote(current_note);
		audio_thread->startThread(true, false);
	}		
}

// Closes the audio thread.
// When the record button has been pressed, the release of the key marks the moment when the time is calculated 
// for a new note, after which that note is added to the list of recorded notes. 
void ofApp::keyReleased(int key) {
	audio_thread->stopThread();

	if (record_ && recorded_notes.empty()) {
		int upper_key = toupper(key);
		double time_elapsed = fProgramDelay * (std::clock() - timer_) / (double)CLOCKS_PER_SEC;
		string note = adjustForOctave(key_to_note.at(upper_key));
		recorded_notes.push_back({ note, time_elapsed });
	} else if (record_) {
		int upper_key = toupper(key);
		double time_elapsed = (std::clock() - timer_) / (double) CLOCKS_PER_SEC;
		string note = adjustForOctave(key_to_note.at(upper_key));
		recorded_notes.push_back({ note, time_elapsed });
	}
}

//--------------------------------------------------------------
// Changes the volume output by the audio thread when the volume slider is dragged
void ofApp::volumeChanged(float &volume_slider) {
	audio_thread->getClarinet()->setVolume(volume_slider);
}

// Places the previous list of recorded notes in past_recorded notes (for comaprison purposes), and 
// begins the process of recording a new sequence of notes
void ofApp::recordPressed(bool &pressed) {
	if (pressed) {
		past_recorded_notes = recorded_notes;
		recorded_notes.clear();
		timer_ = std::clock();
	}
}

// If the list of recorded notes is not emptyand the playback button is switched to true, opens
// the audio thread to play the sequence of notes. If the playback is stopped, the thread is stopped.
void ofApp::playbackPressed(bool &pressed) {
	if (!recorded_notes.empty() && pressed) {
		audio_thread->setNotesToPlay(recorded_notes);
		audio_thread->startThread();
		current_note = recorded_notes[0].first;
		timer_ = std::clock();
	} else if (!pressed) {
		audio_thread->stopThread();
	}
}

// Calls the functions to determine and list which notes were played incorrectly, and resets the button
// to false once this process is complete
void ofApp::comparePressed(bool &pressed) {
	if (pressed && !past_recorded_notes.empty() && !recorded_notes.empty()) {
		compare_messages = comparer.compareRecordings(past_recorded_notes, recorded_notes);
		compare_recordings = false;
	}
}

// Changes the octave being played in the audio thread when the octave button is pressed
void ofApp::upperOctavePressed(bool &pressed) {
	upper_octave = pressed;
	audio_thread->getClarinet()->setHigherOctave(pressed);
}

//--------------------------------------------------------------
// When a button is pressed to play a scale, this method takes the list of notes that correspond to 
// the specified scale and assigns time values to each of the notes (60 / beats-per-minute).
// The notes are then added to the scale_notes variable.
void ofApp::fillScaleNotes(vector<string> scale) {
	double seconds = fSecPerMin / scale_tempo_slider;
	scale_notes.clear();

	for (string note : scale) {
		scale_notes.push_back({ note, seconds });
	}
}

//--------------------------------------------------------------
// The following twelve methods are called when scale buttons are pressed. They get a list of notes
// corresponding to the scale, start the audio thread, and begin the clock.
void ofApp::bFlatScalePressed() {
	fillScaleNotes(scales->at("Bb"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::eFlatScalePressed() {
	fillScaleNotes(scales->at("Eb"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::aFlatScalePressed() {
	fillScaleNotes(scales->at("Ab"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::dFlatScalePressed() {
	fillScaleNotes(scales->at("Db"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::gFlatScalePressed() {
	fillScaleNotes(scales->at("Gb"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::bMajorScalePressed() {
	fillScaleNotes(scales->at("BMajor"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::aMajorScalePressed() {
	fillScaleNotes(scales->at("AMajor"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::dMajorScalePressed() {
	fillScaleNotes(scales->at("DMajor"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::gMajorScalePressed() {
	fillScaleNotes(scales->at("GMajor"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::cMajorScalePressed() {
	fillScaleNotes(scales->at("CMajor"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::fMajorScalePressed() {
	fillScaleNotes(scales->at("FMajor"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::chromaticScalePressed() {
	fillScaleNotes(scales->at("chromatic"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}
