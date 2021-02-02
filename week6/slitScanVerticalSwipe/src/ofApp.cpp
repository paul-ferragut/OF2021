#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


	width = 1920;
	height = 1080;
	cameraId = 1;

	webcam.setDeviceID(cameraId);
	webcam.setup(width, height);


	scanCursor = 0;

	for (int i = 0; i < webcam.getWidth(); i++) {
		ofFbo fboS;
		if (i%SCAN_SPEED==0) {//this is to save memory so we don't allocate FBO we won't be using, nonetheless for the index convenience we still want those FBO to exist
			fboS.allocate(SCAN_SPEED, webcam.getHeight(), GL_RGB);
		}
		else {
			fboS.allocate(0, 0, GL_RGB);
		}
		fboSlice.push_back(fboS);
	}

	for (int i = 0; i < webcam.getWidth(); i++) {
		ofFbo fboS;
		fboS.allocate(webcam.getHeight(), webcam.getHeight(), GL_RGB);
		pastFrames.push_back(fboS);

	}
}


//--------------------------------------------------------------
void ofApp::update(){
	ofSetFrameRate(120);

	webcam.update();

	//store the current camera into the fbo corresponding to the cursor position
	pastFrames[scanCursor].begin();
	ofClear(0, 0, 0, 0);
	webcam.draw(0, 0);
	pastFrames[scanCursor].end();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);

	for (int i = 0;i < fboSlice.size();i++) {

		if (scanCursor - i >= 0) {//all the slices before the moving cursor
			fboSlice[i].begin();
			ofClear(0, 0, 0, 0);
			pastFrames[scanCursor - i].draw(-i, 0, webcam.getWidth(), webcam.getHeight());//the slice equal the frame at the time of the cursor minus i
			fboSlice[i].end();
		}
		else {//all the slices after the moving cursor
			fboSlice[i].begin();
			ofClear(0, 0, 0, 0);
			pastFrames[(webcam.getWidth()+scanCursor)-i].draw(-i, 0, webcam.getWidth(), webcam.getHeight());//the slice equal the frame at the time of the cursor one cycle before and minus i
			fboSlice[i].end();

		}
	}

	scanCursor += SCAN_SPEED;
	if (scanCursor >= webcam.getWidth()) {
		scanCursor = 0;
	}


	for (int i = 0;i < fboSlice.size();i+=SCAN_SPEED) {
		fboSlice[i].draw(i, 0, fboSlice[i].getWidth(), fboSlice[i].getHeight());
	}

	


		ofSetColor(255, 255, 255);
		webcam.draw(ofGetWidth()-320,0,320,240);
		
		ofDrawLine(ofPoint((ofGetWidth() - 320) + (scanCursor / (webcam.getWidth() / 320)), 0), ofPoint((ofGetWidth() - 320) + (scanCursor / (webcam.getWidth() / 320)), 240));


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

//--------------------------------------------------------------
void ofApp::exit() {
	
}