#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	webcam.setDeviceID(0);
	webcam.initGrabber(1920, 1080);

	gui.setup();
	gui.add(intensity.setup("intensity", 0.5, 0.0, 1.0));
	gui.add(radius.setup("radius", 0.5, 0.0, 1.0));
	gui.add(rgb.setup("rgb", 0.5, 0.0, 1.0));
	gui.add(spread.setup("spread", 1, 0, 5.0));

	shader.load("shader");

	ofRectangle distortRect(0, 0, ofGetWidth(), ofGetHeight());


	for (unsigned int i = 0; i < P_NUM; i++) {
		p[i].reset(distortRect);
	}

	//ofDisableArbTex();
}

//--------------------------------------------------------------
void ofApp::update(){

	webcam.update();


	for (unsigned int i = 0; i < P_NUM; i++) {
		p[i].update();
		arrayParticleSize[i] = p[i].radius;
		arrayUniform[i].x = p[i].pos.x;
		arrayUniform[i].y = p[i].pos.y;
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);

	shader.begin();
	shader.setUniform1f("elapsedTime", ofGetElapsedTimeMillis()*0.00003);
	shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	shader.setUniform1f("intensityUniform",intensity);
	shader.setUniform1f("radiusUniform", radius);
	shader.setUniform1f("rgbUniform", rgb);
	shader.setUniform2fv("posP", &arrayUniform[0].x, arrayLength);
	shader.setUniform1fv("radiusP", &arrayParticleSize[0], arrayLength);
	webcam.draw(0,0);

	shader.end();
	gui.draw();

	for (unsigned int i = 0; i < P_NUM; i++) {
		p[i].draw(radius);
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
