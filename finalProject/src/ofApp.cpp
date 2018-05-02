#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
	// Load the default image of our good man Carl
	current_pic.loadImage("http://xpacc.illinois.edu/files/2014/12/xpacc3-250x375.jpg");

	updateImage();

	// Load the gui
	gui.setup();
	gui.add(load_image_from_file_button.setup("Choose image file"));
	gui.add(load_image_from_link_button.setup("Choose image link"));
	gui.add(revert_button.setup("Revert"));
	gui.add(grayscale_toggle.setup("Grayscale", false));
	gui.add(faces_toggle.setup("Show faces", false));
	gui.add(video_toggle.setup("Show video", false));

	// Set up the button listeners
	load_image_from_file_button.addListener(this, &ofApp::loadImageFromFileButtonPressed);
	load_image_from_link_button.addListener(this, &ofApp::loadImageFromLinkButtonPressed);
	revert_button.addListener(this, &ofApp::revertButtonPressed);

	// Set up the camera and face detection
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	finder.setup("haarcascade_frontalface_default.xml");
	finder.setPreset(ObjectFinder::Fast);
	finder.getTracker().setSmoothingRate(.3);
	camera.setup(484, 363);
	ofEnableAlphaBlending();
}

void ofApp::updateImage() {
	// Saves the image before video turned on
	if (!video_toggle) {
		previous_pic = current_pic;
	}

	double ideal_height = ofGetHeight() / 2;
	double ideal_width = ofGetWidth() / 2;
	double height = current_pic.getHeight();
	double width = current_pic.getWidth();
	// Scales the image so it is still the same aspect ratio, but the dimensions are no more than 500x500
	if ((height > ideal_height || width > ideal_width) || (height < ideal_height && width < ideal_width)) {
		double scale_factor;
		if (height > width) {
			scale_factor = ideal_height / height;
		}
		else {
			scale_factor = ideal_width / width;
		}
		current_pic.resize(scale_factor * width, scale_factor * height);
	}

	cv_img.setFromPixels(current_pic.getPixels());
}

void ofApp::revertButtonPressed(const void *sender) {
	cv_img.setFromPixels(current_pic.getPixels());
	grayscale_toggle = false;
	faces_toggle = false;
}

// From http://openframeworks.cc/documentation/utils/ofSystemUtils/#!show_ofSystemLoadDialog
void ofApp::loadImageFromFileButtonPressed(const  void *sender) {
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		// Does not work with png
		if (path.substr(path.length() - 3, path.length()) != "jpg") {
			ofSystemAlertDialog("Use a jpg");
			return;
		}
		current_pic.loadImage(path);
		updateImage();
	}
}

void ofApp::loadImageFromLinkButtonPressed(const void *sender) {
	string link = ofSystemTextBoxDialog("What is the link?", "Link");
	current_pic.loadImage(link);
	updateImage();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (video_toggle) {
		camera.update();
		if (camera.isFrameNew()) {
			finder.update(camera);
		}
	}
	else {
		finder.update(cv_img);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();

	// Handles face tracking when taking in video
	if (video_toggle) {
		ofSetColor(255, 255, 255);
		current_pic.setFromPixels(camera.getPixels());
		updateImage();
		if (grayscale_toggle) {
			drawGray();
		}
		else {
			cv_img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
		}

		if (faces_toggle) {
			ofNoFill();
			ofSetColor(0, 0, 250);
			drawFaceBox();
		}
	}
	else {
		current_pic = previous_pic;
		updateImage();
		// Handles grayscale
		if (grayscale_toggle) {
			ofSetColor(255, 255, 255);
			drawGray();
		}
		else {
			ofSetColor(255, 255, 255);
			cv_img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
		}

		// Handles facial recognition on an image
		if (faces_toggle) {
			ofNoFill();
			ofSetColor(0, 0, 250);
			drawFaceBox();
		}
	}
}

void ofApp::drawGray() {
	ofxCvGrayscaleImage gray_img;
	gray_img.allocate(cv_img.getWidth(), cv_img.getHeight());
	gray_img.setFromColorImage(cv_img);
	gray_img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
}

void ofApp::drawFaceBox() {
	ofRectangle face;
	for (unsigned int i = 0; i < finder.size(); i++) {
		face = finder.getObject(i);
		face.setPosition(face.x + ofGetWidth() / 4, face.y + ofGetHeight() / 4);
		ofDrawRectangle(face);
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
