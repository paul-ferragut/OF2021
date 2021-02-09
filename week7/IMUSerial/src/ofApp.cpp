#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	serial.setup("COM11", 115200);

	model.loadModel("penguin.dae");
	//model.setRotation(0, 180, 1, 0, 0);
	light.setPosition(0, 0, 500);

}

//--------------------------------------------------------------
void ofApp::update(){
	uint8_t buffer[1024];//uint8_t is equivalent unsigned char, it take 1 byte [0-255]
	string newString = "";
	while (serial.available() > 0) {
		int sizeBuffer = serial.readBytes(buffer, 1024);

		for (int i = 0; i < sizeBuffer; i++) {
			newString += buffer[i];
		}

	}
	//cout << newString << endl;
	vector<string>stringSplit = ofSplitString(newString, " ");

	if (stringSplit.size() == 4) {
		roll = ofToFloat(stringSplit[1]);
		pitch = ofToFloat(stringSplit[2]);
		yaw = ofToFloat(stringSplit[3]);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	ofEnableLighting();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	ofRotateZ(yaw);
	ofRotateX(pitch);
	ofRotateY(roll);

	light.enable();
	model.drawFaces();
	light.disable();
	ofPopMatrix();
	ofDisableLighting();
	ofDisableDepthTest();
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
