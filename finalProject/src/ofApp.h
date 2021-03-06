#pragma once

#include "ofMain.h"
#include "../addons/ofxGui/src/ofxGui.h"
#include "../addons/ofxOpenCv/src/ofxOpenCv.h"
#include "../addons/ofxCv/src/ofxCv.h"

class ofApp : public ofBaseApp {
	// Images to manipulate
	ofImage previous_pic;
	ofImage current_pic;
	ofxCvColorImage cv_img;
	ofxCvGrayscaleImage gray_img;

	// Video/facial tracking
	ofxCv::ObjectFinder finder;
	ofVideoGrabber camera;

	// GUI
	ofxPanel gui;
	ofxButton load_image_from_file_button;
	ofxButton revert_button;
	ofxToggle grayscale_toggle;
	ofxToggle faces_toggle;
	ofxToggle faceblur_toggle;
	ofxToggle top_hat_toggle;
	ofxToggle hp_toggle;
	ofxToggle got_toggle;
	ofxToggle video_toggle;

	// Images for filters
	ofImage top_hat;
	ofImage harry_potter;
	ofImage game_of_thrones_crown;

	int start_x;
	int start_y;

	public:
		void setup();
		void update();
		void draw();

		void updateImage();
		void drawHelper();
		void drawHat(ofImage &hat);

		void drawGray();
		void drawFaceBox();
		void drawBlurredFace();
		void drawTopHat();
		void drawHP();
		void drawGOT();

		// Button listeners
		void revertButtonPressed(const void *sender);
		void loadImageFromFileButtonPressed(const void *sender);

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
