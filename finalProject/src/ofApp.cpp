#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
	// Load the image - from http://openframeworks.cc/documentation/utils/ofSystemUtils/#!show_ofSystemLoadDialog
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		test.loadImage(path);
	}
	else {
		test.loadImage("https://timedotcom.files.wordpress.com/2016/05/rts8haa.jpg");
	}

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
		//img.drawROI(5, 5);
		drag.draw(100, 100);
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
	/*if (x < ofGetWidth() / 4) {
		start_x = ofGetWidth() / 4;
	}
	else if (x > ofGetWidth() / 4 + img.getWidth()) {
		start_x = ofGetWidth() / 4 + img.getWidth();
	}
	else {
		start_x = x;
	}

	if (y < ofGetHeight() / 4) {
		start_y = ofGetHeight() / 4;
	}
	else if (y > ofGetHeight() / 4 + img.getHeight()) {
		start_y = ofGetHeight() / 4 + img.getHeight();
	}
	else {
		start_y = y;
	}*/
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	//int end_x = x;
	//int end_y = y;

	//if (end_x < start_x) {
	//	end_x = start_x;
	//	start_x = x;
	//}
	//if (end_y < start_y) {
	//	end_y = start_y;
	//	start_y = y;
	//}

	//ofPoint s(start_x, start_y);
	//ofPoint e(end_x, end_y);
	//rect.set(s, e);
	////img.setROI(start_x, start_y, end_x - start_x, end_y - start_y);
	//img.setROI(rect);
	//drag.setFromPixels(img.getRoiPixels());
	////rect = img.getROI();
	//img.resetROI();
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
