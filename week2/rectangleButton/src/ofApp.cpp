#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofRectangle button;
	button.set(300, 300, 600, 400);

	if (ofGetMouseX() > button.x && ofGetMouseX() < button.x + button.width && ofGetMouseY() > button.y && ofGetMouseY() < button.y + button.height) {
		ofSetColor(10, 250, 30);// TRUE -> GREEN
	}
	else {
		ofSetColor(200, 50, 0);// FALSE -> ORANGE
	}

	/*
	//Second way, using the inside() function included with ofRectangle
	if (button.inside(ofGetMouseX(), ofGetMouseY()) == true) {
		ofSetColor(10, 250, 30);// TRUE -> GREEN
	}
	else {
		ofSetColor(200, 50, 0);// FALSE -> ORANGE
	}
	*/

	ofDrawRectangle(button);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}