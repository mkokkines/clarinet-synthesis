#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	private:
		// Fingerings for each note
		ofImage lowG;
		ofImage lowA;
		ofImage lowB;
		ofImage lowC;
		ofImage lowD;
		ofImage middleE;
		ofImage middleF;
		ofImage middleG;
		std::map<string, ofImage> fingering_images;

		void loadImages();
		void drawFingering(string note);

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
