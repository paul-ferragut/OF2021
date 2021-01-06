#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetRectMode(OF_RECTMODE_CENTER);//instead of the default ofSetRectMode(OF_RECTMODE_CORNER); then it's easier to manipulate rectangle
	ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update() {






}

//--------------------------------------------------------------
void ofApp::draw() {

	ofNoFill();//Drawing the shape outline
	ofSetLineWidth(3.0);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int i = 0; i < 50; i++) {

		ofSetColor(255, 255, 255, ofMap(i, 0, 50, 255, 0));

		ofDrawRectangle(0, 0, 20 * i, 20 * i);
	}

	ofPopMatrix();
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