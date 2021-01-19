#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(slider.setup("slider", 0.5, 0.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	float top = ofGetHeight()*0.1;
	float bottom = ofGetHeight() - top;

	ofBackgroundGradient(ofColor(25), ofColor(5), OF_GRADIENT_LINEAR);
	ofSetColor(255, 30, 30);
	ofDrawLine(0, top, ofGetWidth(), top);
	ofDrawLine(0, bottom, ofGetWidth(), bottom);

	ofSetColor(255, 255, 255);
	float radius = 20;
	int gap = 160;
	ofDrawCircle(gap *1,ofMap(cos(ofGetElapsedTimef()),-1,1,top,bottom), radius);
	ofDrawBitmapStringHighlight("cos", gap * 1, bottom);

	ofDrawCircle(gap * 2, ofMap(sin(ofGetElapsedTimef()), -1, 1, top, bottom), radius);
	ofDrawBitmapStringHighlight("sin", gap * 2, bottom);

	ofDrawCircle(gap * 3, ofMap(ofSignedNoise(ofGetElapsedTimef()), -1, 1, top, bottom), radius);
	ofDrawBitmapStringHighlight("signed\nnoise", gap * 3, bottom);

	ofDrawCircle(gap * 4, ofMap(ofRandom(1.0), 0, 1, top, bottom), radius);
	ofDrawBitmapStringHighlight("random", gap * 4, bottom);

	ofDrawCircle(gap * 5, ofMap(fmod(ofGetElapsedTimef(),1),0,1,top,bottom), radius);
	ofDrawBitmapStringHighlight("modulo", gap * 5, bottom);

	ofDrawCircle(gap * 6, ofLerp(top,bottom,slider), radius);
	ofDrawBitmapStringHighlight("gui", gap * 6, bottom);

	float radiusOrbit = (bottom - top) / 2;
	ofVec3f orbitPt((gap * 9) + cos(ofGetElapsedTimef())*radiusOrbit, radiusOrbit + top + sin(ofGetElapsedTimef())*radiusOrbit,0);
	ofDrawCircle(orbitPt, radius);
	
	trail.push_back(orbitPt);
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < trail.size(); i++) {
		ofVertex(trail[i]);
	}
	ofEndShape();
	if (trail.size() > 200) {
		trail.erase(trail.begin());
	}
	ofFill();
	ofDrawBitmapStringHighlight("cos and sin", gap * 9, bottom);
	gui.draw();

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
