#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	audio_thread = new AudioThread();
	current_note = "middleG";

	loadImages();
	setupScales();
	setupAudioVariables();
	setupRecordPlayback();
	ofSetFrameRate(fDefaultFrameRate);
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

	fingering_images = { { "lowGb", lowGb },{ "lowG", lowG },{ "lowAb", lowAb },{ "lowA", lowA },{ "lowBb", lowBb },{ "lowB", lowB },
	{ "lowC", lowC },{ "lowDb", lowDb },{ "lowD", lowD },{ "lowEb", lowEb },{ "lowE", lowE },
	{ "lowF", lowF }, { "middleGb", middleGb },{ "middleG", middleG }, { "middleAb", middleAb },
	{ "middleA", middleA },{ "middleBb", middleBb },{ "middleB", middleB }, { "middleC", middleC },
	{ "middleDb", middleDb },{ "middleD", middleD },{ "middleEb", middleEb }, { "middleE", middleE },
	{ "middleF", middleF }, { "highGb", highGb }, { "highG", highG } };
}

void ofApp::setupScales() {
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

	scales = new std::map<string, vector<string>>();
	*scales = { fBbScale, fEbScale, fAbScale, fDbScale, fGbScale, fBMajorScale, fAMajorScale, fDMajorScale, fGMajorScale,
		fCMajorScale, fFMajorScale, fChromaticScale };
	audio_thread->setScales(*scales);

	scale_notes = {};
}

void ofApp::setupAudioVariables() {
	upper_octave.setup("Upper Octave", fToggleDefault, fNonScaleButtonSize, fNonScaleButtonSize);
	upper_octave.addListener(this, &ofApp::upperOctavePressed);
	upper_octave.setPosition(fLeftSideXCoord, fUpOctaveYCoord);
	upper_octave.setTextColor(BLACKNESS);

	volume_slider.addListener(this, &ofApp::volumeChanged);
	volume_slider.setup("Volume", fVolumeStart, fVolumeMin, fVolumeMax, fDefaultSliderWidth, fDefaultSliderHeight);
	volume_slider.setPosition(fLeftSideXCoord, fVolumeYCoord);

	scale_tempo_slider.addListener(this, &ofApp::scaleTempoChanged);
	scale_tempo_slider.setup("Scale Tempo BPM", fDefaultTempo, fMinTempo, fMaxTempo, fDefaultSliderWidth, fDefaultSliderHeight);
	scale_tempo_slider.setPosition(fTempoSliderXCoord, fTempoSliderYCoord);
}

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
}

//--------------------------------------------------------------
void ofApp::update() {
	if (playback_ && recorded_notes.empty()) {
		playback_ = false;
	} else if (playback_) {
		updateNoteList(recorded_notes);
	} else if (!scale_notes.empty()) {
		updateNoteList(scale_notes);
	} 
}

void ofApp::updateNoteList(vector<pair<string, double>> &note_list) {
	double time_elapsed = (std::clock() - timer_) / (double) CLOCKS_PER_SEC;
	bool enough_time_elapsed = time_elapsed > note_list[0].second;

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
void ofApp::draw() {
	if (is_paused && current_scale.empty()) {
		drawPaused();
	} else {
		ofSetBackgroundColor(ofColor::white);
		drawFingering(current_note);

		volume_slider.draw();
		upper_octave.draw();
		record_.draw();
		playback_.draw();
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

void ofApp::drawFingering(string note) {
	note = adjustForOctave(note);

	if (note.empty()) {
		note = "middleG";	// middleG shows no fingers
	}

	ofImage current_fingering = fingering_images.at(note);

	double width_factor = (double) ofGetWindowWidth() / fDefaultWindowWidth;
	double height_factor = (double) ofGetWindowHeight() / fDefaultWindowHeight;
	current_fingering.draw(fClarinetImgXCoord * width_factor, fClarinetImgYCoord * height_factor, 
						   fClarinetImgWidth * width_factor, fClarinetImgHeight * height_factor);
}

void ofApp::drawPaused() {
	ofDrawBitmapString(fPauseMessage, 400, 400);
	SetTextColor(0, 0);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	double w_resize_factor = (double) w / fDefaultWindowWidth;
	double h_resize_factor = (double) h / fDefaultWindowHeight;

	resizeScales(w_resize_factor, h_resize_factor);
	resizeAudioVariables(w_resize_factor, h_resize_factor);
	resizeRecordPlayback(w_resize_factor, h_resize_factor);
}

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

void ofApp::resizeAudioVariables(double w_resize_factor, double h_resize_factor) {
	scale_tempo_slider.setSize(fDefaultSliderWidth * w_resize_factor, fDefaultSliderHeight * h_resize_factor);
	scale_tempo_slider.setPosition(fTempoSliderXCoord * w_resize_factor, fTempoSliderYCoord * h_resize_factor);

	volume_slider.setSize(fDefaultSliderWidth * w_resize_factor, fDefaultSliderHeight * h_resize_factor);
	volume_slider.setPosition(fLeftSideXCoord * w_resize_factor, fVolumeYCoord * h_resize_factor);

	double non_scale_button_size = fNonScaleButtonSize * std::min(w_resize_factor, h_resize_factor);
	upper_octave.setSize(non_scale_button_size, non_scale_button_size);
	upper_octave.setPosition(fLeftSideXCoord * w_resize_factor, fUpOctaveYCoord * h_resize_factor);
}

void ofApp::resizeRecordPlayback(double w_resize_factor, double h_resize_factor) {
	double non_scale_button_size = fNonScaleButtonSize * std::min(w_resize_factor, h_resize_factor);

	record_.setPosition(fLeftSideXCoord * w_resize_factor, fRecordYCoord * h_resize_factor);
	record_.setSize(non_scale_button_size, non_scale_button_size);

	playback_.setPosition(fLeftSideXCoord * w_resize_factor, fPlaybackYCoord * h_resize_factor);
	playback_.setSize(non_scale_button_size, non_scale_button_size);
}

//--------------------------------------------------------------
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
		bool new_octave = !audio_thread->getClarinet()->getHigherOctave();
		audio_thread->getClarinet()->setHigherOctave(new_octave);
		upper_octave = new_octave;
	} else if (upper_key == 'P') {
		is_paused = !is_paused;
	} else {
		noteKeyPressed(upper_key);
	}

}

void ofApp::noteKeyPressed(int upper_key) {
	if (record_) {
		double time_elapsed = fProgramDelay * (std::clock() - timer_) / (double) CLOCKS_PER_SEC;
		recorded_notes.push_back({ "", time_elapsed });	// empty string indicates a pause
		timer_ = std::clock();
	}

	if (key_to_note.find(upper_key) != key_to_note.end()) {
		current_note = key_to_note.at(upper_key);
		audio_thread->setCurrentNote(current_note);
		audio_thread->startThread(true, false);
	}		
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	audio_thread->stopThread();

	if (record_) {
		int upper_key = toupper(key);
		double time_elapsed = (std::clock() - timer_) / (double) CLOCKS_PER_SEC;
		string note = adjustForOctave(key_to_note.at(upper_key));
		recorded_notes.push_back({ note, time_elapsed });
	}
}

//--------------------------------------------------------------
void ofApp::scaleTempoChanged(float &scale_tempo_slider) {
	audio_thread->setScaleTempo(scale_tempo_slider);
}

void ofApp::volumeChanged(float &volume_slider) {
	audio_thread->getClarinet()->setVolume(volume_slider);
}

//--------------------------------------------------------------
void ofApp::recordPressed(bool &pressed) {
	is_recording = pressed;

	if (pressed) {
		recorded_notes.clear();
		timer_ = std::clock();
	}
}

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

void ofApp::fillScaleNotes(vector<string> scale) {
	double seconds = fSecPerMin / scale_tempo_slider;
	scale_notes.clear();

	for (string note : scale) {
		scale_notes.push_back({ note, seconds });
	}
}

void ofApp::upperOctavePressed(bool &pressed) {
	upper_octave = pressed;
	audio_thread->getClarinet()->setHigherOctave(pressed);
	timer_ = std::clock();
}

//--------------------------------------------------------------
void ofApp::bFlatScalePressed() {
	fillScaleNotes(scales->at("Bb"));
	current_note = scale_notes[0].first;
	audio_thread->setNotesToPlay(scale_notes);
	audio_thread->startThread();
	timer_ = std::clock();
}

void ofApp::eFlatScalePressed() {
	audio_thread->setScaleToPlay("Eb");
	audio_thread->startThread();
	current_scale = scales->at("Eb");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::aFlatScalePressed() {
	audio_thread->setScaleToPlay("Ab");
	audio_thread->startThread();
	current_scale = scales->at("Ab");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::dFlatScalePressed() {
	audio_thread->setScaleToPlay("Db");
	audio_thread->startThread();
	current_scale = scales->at("Db");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::gFlatScalePressed() {
	audio_thread->setScaleToPlay("Gb");
	audio_thread->startThread();
	current_scale = scales->at("Gb");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::bMajorScalePressed() {
	audio_thread->setScaleToPlay("BMajor");
	audio_thread->startThread();
	current_scale = scales->at("BMajor");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::aMajorScalePressed() {
	audio_thread->setScaleToPlay("AMajor");
	audio_thread->startThread();
	current_scale = scales->at("AMajor");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::dMajorScalePressed() {
	audio_thread->setScaleToPlay("DMajor");
	audio_thread->startThread();
	current_scale = scales->at("DMajor");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::gMajorScalePressed() {
	audio_thread->setScaleToPlay("GMajor");
	audio_thread->startThread();
	current_scale = scales->at("GMajor");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::cMajorScalePressed() {
	audio_thread->setScaleToPlay("CMajor");
	audio_thread->startThread();
	current_scale = scales->at("CMajor");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::fMajorScalePressed() {
	audio_thread->setScaleToPlay("FMajor");
	audio_thread->startThread();
	current_scale = scales->at("FMajor");
	current_note = current_scale[0];
	timer_ = std::clock();
}

void ofApp::chromaticScalePressed() {
	audio_thread->setScaleToPlay("chromatic");
	audio_thread->startThread();
	current_scale = scales->at("chromatic");
	current_note = current_scale[0];
	timer_ = std::clock();
}
