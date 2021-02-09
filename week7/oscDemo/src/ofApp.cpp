#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	receiver.setup(8000);
	sender.setup("192.168.178.97", 9000);
}

//--------------------------------------------------------------
void ofApp::update(){

	ofxOscMessage m;
	m.setAddress("/mouse/position");
	m.addFloatArg(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1));
	m.addFloatArg(ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 1));

	sender.sendMessage(m, false);

	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		cout << m.getAddress() << endl;
		cout << m.getArgAsFloat(0) << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

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
