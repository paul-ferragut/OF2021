#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);

	 kWdith= 640;
	 kHeight= 576;

	if (this->kinectDevice.open())
	{
		auto kinectSettings = ofxAzureKinect::DeviceSettings();

		kinectSettings.updateIr = true;
		kinectSettings.updateColor = true;
		kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_1080P;
		kinectSettings.depthMode = K4A_DEPTH_MODE_NFOV_UNBINNED;
		kinectSettings.updateVbo = false;
		this->kinectDevice.startCameras(kinectSettings);
	}

	colorImg.allocate(kWdith,kHeight);
	grayImage.allocate(kWdith, kHeight);
	grayThreshNear.allocate(kWdith, kHeight);
	grayThreshFar.allocate(kWdith, kHeight);

	bThreshWithOpenCV = true;

	ofSetFrameRate(60);

	gui.setup();
	gui.add(nearThreshold.setup("near threshold", 5, 0, 60));
	gui.add(farThreshold.setup("far threshold", 55, 0, 60));
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

		ofVec3f centerBlob;
		bool blobAvailable = false;
		float blobWidth = 0;
		for (int i = 0; i < contourFinder.nBlobs; i++) {
			centerBlob.set(contourFinder.blobs[i].boundingRect.getCenter().x, contourFinder.blobs[i].boundingRect.getCenter().y);
			centerBlob *= 3;//scale to resolution
			blobWidth = contourFinder.blobs[i].boundingRect.getWidth() * 1.5;
			blobAvailable = true;
		}

		if (blobAvailable) {
			p[i].addAttraction(centerBlob, blobWidth);
		}
		p[i].addDampingForce();
		p[i].update();
		p[i].bounceWall();
	}

	if (this->kinectDevice.isFrameNew())
	{
		this->kinectFps.newFrame();

		grayImage.setFromPixels(this->kinectDevice.getDepthPix());
		grayImage.convertToRange(0, 255*10);

		//grayImage.convertToRange(0,255);
		//grayImage.brightnessContrast(1, 1);
		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
		if (bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(farThreshold, true);
			grayThreshFar.threshold(nearThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		}
		else {

			// or we do it ourselves - show people how they can work with the pixels
			ofPixels & pix = grayImage.getPixels();
			int numPixels = pix.size();
			for (int i = 0; i < numPixels; i++) {
				if (pix[i] < farThreshold && pix[i] >nearThreshold ) {
					pix[i] = 255;
				}
				else {
					pix[i] = 0;
				}
			}
		}

		// update the cv images
		grayImage.flagImageChanged();

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		//  , find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayImage, 1000, (grayImage.width*grayImage.height) / 2, 1, false);
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
			ofSetColor(255, 255, 255, 100);
			for (int i = 0; i < p.size(); i++) {
				for (int j = 0; j < p.size(); j++) {
					float dist = ofDist(p[i].pos.x, p[i].pos.y, p[j].pos.x, p[j].pos.y);
					if (dist < 200) {
						ofDrawLine(p[i].pos.x, p[i].pos.y, p[j].pos.x, p[j].pos.y);
					}
				}
			}
		}

		fbo.end();
		fbo.draw(0, 0);

	// draw instructions
	ofSetColor(255, 255, 255);
	grayImage.setFromPixels(this->kinectDevice.getDepthPix());
	grayImage.convertToRange(0, 255 * 10);
	grayImage.draw(10, 10, kWdith, kHeight);
	contourFinder.draw(10, 10, kWdith, kHeight);
	gui.draw();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case ' ':
		bThreshWithOpenCV = !bThreshWithOpenCV;
		break;
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

void ofApp::exit()
{
	this->kinectDevice.close();

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
