#pragma once

#include "ofMain.h"
#include "../addons/ofxGui/src/ofxGui.h"
#include "../addons/ofxOpenCv/src/ofxOpenCv.h"
#include "../addons/ofxCv/src/ofxCv.h"

class ofApp : public ofBaseApp{
	ofImage test;
	// Remember to ask Patrick about separate class for Image that has a ofxCvImage pointer, 
	// and each time toggle from grey to color create new image on heap and delete old
	// Class will keep track of filters applied
	ofxCvColorImage img;

	ofxCv::ObjectFinder finder;
	ofVideoGrabber camera;

	ofxPanel gui;
	ofxButton load_image_from_file_button;
	ofxButton load_image_from_link_button;
	ofxButton revert_button;
	ofxToggle grayscale_toggle;
	ofxToggle faces_toggle;
	ofxToggle video_toggle;



	ofRectangle rect;
	//ofImage drag;
	ofxCvColorImage drag;

	int start_x;
	int start_y;

	public:
		void setup();
		void update();
		void draw();

		void updateImage();

		void revertButtonPressed(const void *sender);
		void loadImageFromFileButtonPressed(const void *sender);
		void loadImageFromLinkButtonPressed(const void *sender);

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
