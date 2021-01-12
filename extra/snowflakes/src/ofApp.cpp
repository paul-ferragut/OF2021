#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);


	float sides = 30;
	gridW = ofGetWidth() / sides;
	gridH = ofGetHeight() / (sides/2);
	float height=  sides * sqrt(3.0) / 2.0;
	bool odd = false;
	for (int i = 0; i < gridW; i++) {
		if (odd) {
			for (int j = 0; j < gridH; j++) {
				flake tF;
				tF.setup(ofVec2f((sides / 2) + (sides*j), height*i), sides,  1);
				flakes.push_back(tF);
			}
		}
		else {
			for (int j = 0; j < gridH; j++) {
				flake tF;
				tF.setup(ofVec2f((sides*j), height*i), sides, 1);
				flakes.push_back(tF);
			}
		}
		odd = !odd;
	}


	sides = 60;
	gridW = ofGetWidth() / sides;
	gridH = ofGetHeight() / (sides / 2);
	height = sides * sqrt(3.0) / 2.0;
	odd = false;
	for (int i = 0; i < gridW; i++) {
		if (odd) {
			for (int j = 0; j < gridH; j++) {
				flake tF;
				tF.setup(ofVec2f((sides / 2) + (sides*j), height*i), sides,3);
				flakes2.push_back(tF);
			}
		}
		else {
			for (int j = 0; j < gridH; j++) {
				flake tF;
				tF.setup(ofVec2f((sides*j), height*i), sides, 3);
				flakes2.push_back(tF);
			}
		}
		odd = !odd;
	}

	sides = 90;
	gridW = ofGetWidth() / sides;
	gridH = ofGetHeight() / (sides / 2);
	height = sides * sqrt(3.0) / 2.0;
	odd = false;
	for (int i = 0; i < gridW; i++) {
		if (odd) {
			for (int j = 0; j < gridH; j++) {
				flake tF;
				tF.setup(ofVec2f((sides / 2) + (sides*j), height*i), sides,6);
				flakes2.push_back(tF);
			}
		}
		else {
			for (int j = 0; j < gridH; j++) {
				flake tF;
				tF.setup(ofVec2f((sides*j), height*i), sides, 6);
				flakes2.push_back(tF);
			}
		}
		odd = !odd;
	}

	saveScreen = false;

	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < flakes.size(); i++) {
		flakes[i].update(ofGetMousePressed(), ofVec2f(ofGetMouseX(), ofGetMouseY()));
	}

	for (int i = 0; i < flakes2.size(); i++) {
		flakes2[i].update(ofGetMousePressed(), ofVec2f(ofGetMouseX(), ofGetMouseY()));
	}

	for (int i = 0; i < flakes3.size(); i++) {
		flakes3[i].update(ofGetMousePressed(), ofVec2f(ofGetMouseX(), ofGetMouseY()));
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	

	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);//MOVE TO THE CENTER OF THE SCREEN

	for (int i = 0; i < 6; i++) {
		
		ofPushMatrix();
		ofRotate(60 * i);//ROTATE 6 TIMES AT +60 Degrees
		for (int i = 0; i < flakes.size(); i++) {
			flakes[i].draw(false);
		}
		ofPopMatrix();
	}


	for (int i = 0; i < 6; i++) {

		ofPushMatrix();
		ofRotate(60 * i);
		for (int i = 0; i < flakes2.size(); i++) {
			flakes2[i].draw(false);
		}
		ofPopMatrix();
	}


	for (int i = 0; i < 6; i++) {

		ofPushMatrix();
		ofRotate(60 * i);
		for (int i = 0; i < flakes3.size(); i++) {
			flakes3[i].draw(false);
		}
		ofPopMatrix();
	}


	ofPopMatrix();


	if (saveScreen==false) {
		for (int i = 0; i < flakes.size(); i++) {
			flakes[i].draw(false);
		}
		for (int i = 0; i < flakes2.size(); i++) {
			flakes2[i].draw(false);
		}
		for (int i = 0; i < flakes3.size(); i++) {
			flakes3[i].draw(false);
		}
	}
	if (saveScreen) {
		ofHideCursor();
		ofSaveScreen("snowflake" + ofGetTimestampString() + ".png");
		saveScreen = false;
		for (int i = 0; i < flakes.size(); i++) {
			flakes[i].reset();
		}
		for (int i = 0; i < flakes2.size(); i++) {
			flakes2[i].reset();
		}
		for (int i = 0; i < flakes3.size(); i++) {
			flakes3[i].reset();
		}
		ofShowCursor();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		for (int i = 0; i < flakes.size(); i++) {
			flakes[i].reset();
		}
		for (int i = 0; i < flakes2.size(); i++) {
			flakes2[i].reset();
		}
		for (int i = 0; i < flakes3.size(); i++) {
			flakes3[i].reset();
		}
	}
	if (key == 's') {
		saveScreen = true;
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
