#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//ofSetBackgroundAuto(false);

	vidGrabber.setVerbose(true);
	vidGrabber.setup(320, 240);
	colorImg.allocate(320, 240);
	grayImage.allocate(320, 240);
	grayBg.allocate(320, 240);
	grayDiff.allocate(320, 240);

	ofBackground(0);

	particle nP;

	gui.setup();
	gui.add(debugDraw.setup("debugDraw", true));
	gui.add(useNoise.setup("particle useNoise", true));
	gui.add(noiseAmount.setup("particle noiseAmount", 0.4,0.01,2.0));
	gui.add(pNum.setup("particle number", 1000, 200, 20000));
	gui.add(threshold.setup("threshold", 65, 0, 255));

	gui.add(bLearnBakground.setup("bLearnBakground", false));
	gui.add(minBlob.setup("minBlob", 1000, 50, 10000));
	gui.add(maxBlob.setup("maxBlob", 30000, 100, 40000));
	gui.add(useHole.setup("useHole", false));

	p.assign(pNum,nP);

	for (int i = 0; i < p.size(); i++) {
		p[i].setup();
	}
	ofEnableAlphaBlending();

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle("Framerate:"+ofToString(ofGetFrameRate()));
	ofSetFrameRate(30);

	if (pNum != p.size()) {
		if (pNum > p.size()) {
			int newParticlesNum = pNum - p.size()  ;
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
		//p[i].addForce(0,0.1);
		//p[i].addRepulsion(ofVec3f(ofGetMouseX(), ofGetMouseY()));
		p[i].addAttraction(attractionPoints);
		p[i].addDampingForce();
		p[i].update();
		p[i].bounceWall();
	}

	bool bNewFrame = false;

	vidGrabber.update();
	bNewFrame = vidGrabber.isFrameNew();
	if (bNewFrame) {

		colorImg.setFromPixels(vidGrabber.getPixels());

		grayImage = colorImg;

		if (bLearnBakground == true) {
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, minBlob, maxBlob, 10, useHole);	// find holes
		
	}

	attractionPoints.clear();
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		ofVec3f centerBlob(contourFinder.blobs[i].boundingRect.getCenter().x,contourFinder.blobs[i].boundingRect.getCenter().y);
		centerBlob *= 6;//scale to resolution:320*6=1920
		attractionPoints.push_back(centerBlob);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(255,255);

	for (int i = 0; i < p.size(); i++) {
		p[i].draw(3);
	}

	if (debugDraw) {
		for (int i = 0; i < attractionPoints.size(); i++) {
			ofSetColor(255, 0, 0);
			ofDrawCircle(attractionPoints[i], 30);
		}

		ofSetHexColor(0xffffff);
		colorImg.draw(20, 20);
		grayImage.draw(360, 20);
		grayBg.draw(20, 280);
		grayDiff.draw(360, 280);
		grayDiff.draw(20, 540);
		contourFinder.draw(20, 540);
	}

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
