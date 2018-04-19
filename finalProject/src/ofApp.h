#pragma once

#include "ofMain.h"
#include "../addons/ofxGui/src/ofxGui.h"
#include "../addons/ofxOpenCv/src/ofxOpenCv.h"
#include "../addons/ofxCv/src/ofxCv.h"

class ofApp : public ofBaseApp{
	ofImage test;
	ofxCvColorImage img;
	ofxCvGrayscaleImage gray_img;

	ofxPanel gui;
	ofxButton grayscale_button;

	bool is_grayscale;

	public:
		void setup();
		void update();
		void draw();

		void buttonPressed(const void *sender);

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
