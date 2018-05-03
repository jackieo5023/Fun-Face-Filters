#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(226, 234, 255);

	// Load the default image of our good man Carl and images for filters
	current_pic.loadImage("http://xpacc.illinois.edu/files/2014/12/xpacc3-250x375.jpg");
	updateImage();
	top_hat.load("top_hat.png");
	harry_potter.load("hp.png");
	game_of_thrones_crown.load("got.png");

	// Load the gui
	gui.setup();
	gui.add(load_image_from_file_button.setup("Choose image file"));
	gui.add(revert_button.setup("Revert"));
	gui.add(grayscale_toggle.setup("Grayscale", false));
	gui.add(faces_toggle.setup("Show faces", false));
	gui.add(faceblur_toggle.setup("Blur faces", false));
	gui.add(top_hat_toggle.setup("Add top hat", false));
	gui.add(hp_toggle.setup("Add Harry Potter", false));
	gui.add(got_toggle.setup("Add Game of Thrones", false));
	gui.add(video_toggle.setup("Show video", false));

	// Set up the button listeners
	load_image_from_file_button.addListener(this, &ofApp::loadImageFromFileButtonPressed);
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

	cv_img.allocate(current_pic.getWidth(), current_pic.getHeight());
	cv_img.setFromPixels(current_pic.getPixels());
	gray_img.allocate(cv_img.getWidth(), cv_img.getHeight());
	gray_img.setFromColorImage(cv_img);
}

void ofApp::revertButtonPressed(const void *sender) {
	cv_img.setFromPixels(current_pic.getPixels());
	grayscale_toggle = false;
	faces_toggle = false;
	faceblur_toggle = false;
	top_hat_toggle = false;
	hp_toggle = false;
	got_toggle = false;
}

// From http://openframeworks.cc/documentation/utils/ofSystemUtils/#!show_ofSystemLoadDialog
void ofApp::loadImageFromFileButtonPressed(const  void *sender) {
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		// Only works with jpg
		if (path.substr(path.length() - 3, path.length()) != "jpg") {
			ofSystemAlertDialog("Use a jpg");
			return;
		}
		current_pic.loadImage(path);
		updateImage();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	// Updates the video feed and/or face detector
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
	ofSetColor(255, 255, 255);

	if (video_toggle) {
		current_pic.setFromPixels(camera.getPixels());
	}
	else {
		// Update the picture to be the last one before video turned on
		current_pic = previous_pic;
	}

	drawHelper();
}

void ofApp::drawHelper() {
	updateImage();
	if (grayscale_toggle) {
		drawGray();
	}
	else {
		ofSetColor(255, 255, 255);
		cv_img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
	}

	if (faces_toggle) {
		drawFaceBox();
	}

	if (faceblur_toggle) {
		drawBlurredFace();
	}

	if (top_hat_toggle) {
		drawTopHat();
	}

	if (hp_toggle) {
		drawHP();
	}

	if (got_toggle) {
		drawGOT();
	}
}

void ofApp::drawGray() {
	ofSetColor(255, 255, 255);
	gray_img.draw(ofGetWidth() / 4, ofGetHeight() / 4);
}

void ofApp::drawFaceBox() {
	ofNoFill();
	ofSetColor(0, 0, 250);

	ofRectangle face;
	for (unsigned int i = 0; i < finder.size(); i++) {
		face = finder.getObject(i);
		face.setPosition(face.x + ofGetWidth() / 4, face.y + ofGetHeight() / 4);
		ofDrawRectangle(face);
	}
}

void ofApp::drawBlurredFace() {
	ofRectangle face;
	for (unsigned int i = 0; i < finder.size(); i++) {
		face = finder.getObject(i);
		face.setPosition(face.x + ofGetWidth() / 4, face.y + ofGetHeight() / 4);

		ofxCvImage *img;

		if (grayscale_toggle) {
			gray_img.setROI(face.x - ofGetWidth() / 4, face.y - ofGetHeight() / 4, face.width, face.height);

			img = new ofxCvGrayscaleImage();
			ofPixels &pixels = gray_img.getRoiPixels();
			img->allocate(pixels.getWidth(), pixels.getHeight());
			img->setFromPixels(pixels);
		}
		else {
			cv_img.setROI(face.x - ofGetWidth() / 4, face.y - ofGetHeight() / 4, face.width, face.height);

			img = new  ofxCvColorImage();
			ofPixels &pixels = cv_img.getRoiPixels();
			img->allocate(pixels.getWidth(), pixels.getHeight());
			img->setFromPixels(pixels);
		}

		for (int j = 0; j < 100; j++) {
			img->blurGaussian();
		}
		ofSetColor(255, 255, 255);
		img->draw(face.x, face.y);

		delete img;
	}
	gray_img.resetROI();
	cv_img.resetROI();
}

void ofApp::drawHat(ofImage &hat) {
	ofSetColor(255, 255, 255);
	// Lots of interseting guess and check/math to get the hat in the correct spot
	ofRectangle face;
	for (int i = 0; i < finder.size(); i++) {
		ofRectangle face = finder.getObjectSmoothed(i);
		int x = face.x;
		int y = face.y;
		face.setPosition(face.x + ofGetWidth() / 4, face.y + ofGetHeight() / 4);
		float scaleAmount = face.width / hat.getWidth();
		ofPushMatrix();
		ofTranslate(x + ofGetWidth() / 4, y + ofGetHeight() / 4);
		ofScale(scaleAmount, scaleAmount);
		hat.draw(x - face.getWidth() / 4, y - hat.getHeight());
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(face.getPosition());
		ofPopMatrix();
	}
}

void ofApp::drawTopHat() {
	drawHat(top_hat);
}

void ofApp::drawHP() {
	ofSetColor(255, 255, 255);
	// Lots of interseting guess and check/math to get the glasses in the correct spot
	for (int i = 0; i < finder.size(); i++) {
		ofRectangle face = finder.getObjectSmoothed(i);
		int x = face.x;
		int y = face.y;
		face.setPosition(face.x + ofGetWidth() / 4, face.y + ofGetHeight() / 4);
		float scaleAmount = .85 * face.width / harry_potter.getWidth();
		ofPushMatrix();
		ofTranslate(x + ofGetWidth() / 4, y + ofGetHeight() / 4);
		ofScale(scaleAmount, scaleAmount);
		harry_potter.draw(2 * x, -2 * y);
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(face.getPosition());
		ofPopMatrix();
	}
}

void ofApp::drawGOT() {
	drawHat(game_of_thrones_crown);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// Saves the image to bin/data
	if (key == ' ') {
		ofImage img_to_save;
		img_to_save.grabScreen(ofGetWidth() / 4, ofGetHeight() / 4, cv_img.getWidth(), cv_img.getHeight());
		img_to_save.save("filtered_picture_" + ofGetTimestampString() + ".jpg");
	}
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
