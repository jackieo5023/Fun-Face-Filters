#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
	// Load the image
	test.loadImage("http://i0.kym-cdn.com/entries/icons/original/000/013/564/doge.jpg");

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

	is_grayscale = false;
	img.setFromPixels(test.getPixels());
	gray_img.setFromColorImage(img);

	// Load the grayscale button
	gui.setup();
	gui.add(grayscale_button.setup("Grayscale"));

	grayscale_button.addListener(this, &ofApp::buttonPressed);
}

void ofApp::buttonPressed(const void *sender) {
	is_grayscale = true;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	if (is_grayscale) {
		gray_img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
	}
	else {
		img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
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
