#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//ofSetBackgroundAuto(false);
	ofBackground(0);
	for (int i = 0; i < 100; i++) {
		particle temporaryP;
		p.push_back(temporaryP);
	}

	for (int i = 0; i < p.size(); i++) {
		p[i].setup();
	}
	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle("Framerate:"+ofToString(ofGetFrameRate()));
	ofSetFrameRate(60);

	for (int i = 0; i < p.size(); i++) {
		p[i].update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(255,255);

	for (int i = 0; i < p.size(); i++) {
		p[i].draw(3);
		p[i].drawTrail();
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
