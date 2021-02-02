#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);

	

	ofSetFrameRate(60);

	gui.setup();
	
	gui.add(useNoise.setup("particle useNoise", true));
	gui.add(connectLines.setup("connect lines", true));
	gui.add(noiseAmount.setup("particle noiseAmount", 0.4, 0.01, 2.0));
	gui.add(pNum.setup("particle number", 500, 200, 3000));
	gui.add(fadeAmount.setup("fadeAmount", 20, 0, 255));
	particle nP;
	p.assign(pNum, nP);

	for (int i = 0; i < p.size(); i++) {
		p[i].setup();
	}
	
	fbo.allocate(ofGetWidth(), ofGetHeight());

	//clean up the fbo to avoid glitches
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){
	

	if (pNum != p.size()) {
		if (pNum > p.size()) {
			int newParticlesNum = pNum - p.size();
			for (int i = 0; i < newParticlesNum; i++) {
				particle nP;
				p.push_back(nP);
				p.back().setup();
			}
		}
		else if (pNum < p.size()) {
			int newParticlesNum = p.size() - pNum;
			p.erase(p.begin(), p.begin() + newParticlesNum);
		}
	}

	for (int i = 0; i < p.size(); i++) {
		p[i].reset();
		if (useNoise) {
			p[i].addNoise(noiseAmount);
		}

		p[i].addAttraction(ofVec3f(ofGetMouseX(),ofGetMouseY()), 500);

		p[i].addDampingForce();
		p[i].update();
		p[i].bounceWall();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);



		fbo.begin();

		ofSetColor(255, 255, 255, fadeAmount);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

		ofEnableAlphaBlending();
		ofFill();
		ofSetColor(255, 255, 255,255);
		for (int i = 0; i < p.size(); i++) {
			p[i].draw(3);
		}

		if(connectLines){
			ofSetLineWidth(0.3);
			ofSetColor(255, 255, 255, 255);
			for (int i = 0; i < p.size(); i++) {
				for (int j = 0; j < p.size(); j++) {
					float dist = ofDist(p[i].pos.x, p[i].pos.y, p[j].pos.x, p[j].pos.y);
					if (dist < 30) {
						ofDrawLine(p[i].pos.x, p[i].pos.y, p[j].pos.x, p[j].pos.y);
					}
				}
			}
		}

		fbo.end();
		fbo.draw(0, 0);

	// draw instructions
	ofSetColor(255, 255, 255);
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

void ofApp::exit()
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
