#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofColor bgColor;
	bgColor.set(0, 0, 0);
	ofBackground(bgColor);
	ofSetBackgroundAuto(false);

	incrementRotation = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

	noiseValue1 = ofNoise(ofGetElapsedTimef());//ofNoise is a random value between 0.0 and 1.0
	noiseValue2 = ofNoise(ofGetElapsedTimef() + 10);
	noiseValue3 = ofNoise(ofGetElapsedTimef() + 20)*0.2;
	incrementRotation += noiseValue3;
}

//--------------------------------------------------------------
void ofApp::draw() {


	ofSetLineWidth(1.0);

	ofVec3f mousePos;
	mousePos.set(ofGetMouseX(), ofGetMouseY());

	ofSetColor(255 * noiseValue1, 255 * noiseValue2, 255, 10);

	float lineLenght = noiseValue1 * 500;

	ofPushMatrix();
	ofTranslate(mousePos);
	ofTranslate(lineLenght / 2, lineLenght / 2);
	ofRotateZ(incrementRotation);
	ofTranslate(-lineLenght / 2, -lineLenght / 2);

	if (ofGetMousePressed() == true) {
		ofDrawLine(0, 0, lineLenght, lineLenght);
	}

	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'r') {

		ofBackground(0, 0, 0);

	}
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