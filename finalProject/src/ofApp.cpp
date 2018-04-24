#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
	// Load the image
	test.loadImage("https://timedotcom.files.wordpress.com/2016/05/rts8haa.jpg");

	double ideal_height = ofGetHeight() / 2;
	double ideal_width = ofGetWidth() / 2;
	double height = test.getHeight();
	double width = test.getWidth();
	// Scales the image so it is still the same aspect ratio, but the dimensions are no more than 500x500
	if ((height > ideal_height || width > ideal_width) || (height < ideal_height && width < ideal_width)) {
		double scale_factor;
		if (height > width) {
			scale_factor = ideal_height / height;
		}
		else {
			scale_factor = ideal_width / width;
		}
		test.resize(scale_factor * width, scale_factor * height);
	}

	img.setFromPixels(test.getPixels());

	// Load the gui
	gui.setup();
	gui.add(revert_button.setup("Revert"));
	gui.add(grayscale_toggle.setup("Grayscale", false));
	gui.add(faces_toggle.setup("Show faces", false));

	revert_button.addListener(this, &ofApp::revertButtonPressed);

	finder.setup("haarcascade_frontalface_default.xml");
	finder.setPreset(ObjectFinder::Fast);
}

void ofApp::revertButtonPressed(const void *sender) {
	img.setFromPixels(test.getPixels());
	grayscale_toggle = false;
	faces_toggle = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	finder.update(img);
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();

	if (grayscale_toggle) {
		ofSetColor(255, 255, 255);
		ofxCvGrayscaleImage gray_img;
		gray_img.setFromColorImage(img);
		gray_img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
	}
	else {
		ofSetColor(255, 255, 255);
		img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
	}

	if (faces_toggle) {
		ofNoFill();
		ofSetColor(0, 0, 250);
		ofRectangle face;
		for (unsigned int i = 0; i < finder.size(); i++) {
			face = finder.getObject(i);
			face.setPosition(face.x + ofGetWidth() / 4, face.y + ofGetHeight() / 4);
			ofDrawRectangle(face);
		}

	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
