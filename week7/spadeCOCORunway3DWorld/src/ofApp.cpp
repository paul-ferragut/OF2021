#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	widthRunway = 600;
	heightRunway = 400;

	surface.set(0, 0, 8000, 1000);
	ofEnableDepthTest();
	scrollSpeed = 5;

	colorRoad.setHex(ofHexToInt("aeaac8"));
	colorPavement.setHex(ofHexToInt("72ffff"));
	colorWindow.setHex(ofHexToInt("4b4101"));
	colorSky.setHex(ofHexToInt("5fdbff"));
	colorSign.setHex(ofHexToInt("4f2a00"));
	colorTrafficLight.setHex(ofHexToInt("857067"));
	colorBuildings.setHex(ofHexToInt("d6526e"));
	//
	runway.setup(this, "http://localhost:8000");
	runway.start();

	fbo.allocate(widthRunway,heightRunway);
	runwayImageData.allocate(widthRunway, heightRunway,OF_IMAGE_COLOR);
	runwayResult.allocate(widthRunway, heightRunway, OF_IMAGE_COLOR);


}

//--------------------------------------------------------------
void ofApp::update(){


	if (ofGetFrameNum() % 50 == 0) {
		building nBuild;
		buildings.push_back(nBuild);
		buildings.back().setup(ofVec3f(0, ofRandom(0, 200), 0), ofColor(255));

		buildings.push_back(nBuild);
		buildings.back().setup(ofVec3f(0, ofRandom(1200, 1400), 0), ofColor(255));
	}
	for (int i = 0; i < buildings.size(); i++) {
		buildings[i].scroll(scrollSpeed);
		if (buildings[i].pos.x > surface.width) {
			buildings.erase(buildings.begin() + i);
		}
	}

	if (ofGetFrameNum() % 120 == 0) {
		roadObject nBuild;
		roadObjects.push_back(nBuild);
		roadObjects.back().setup(ofVec3f(0, ofRandom(400, 600), 0), ofColor(255));

		roadObjects.push_back(nBuild);
		roadObjects.back().setup(ofVec3f(0, ofRandom(800, 1000), 0), ofColor(255));
	}


	for (int i = 0; i < roadObjects.size(); i++) {
		roadObjects[i].scroll(scrollSpeed);
		if (roadObjects[i].pos.x > surface.width) {
			roadObjects.erase(roadObjects.begin() + i);
		}
	}


	fbo.readToPixels(runwayImageData);
	runwayImageData.update();

	if (runwayImageData.isAllocated() && !runway.isBusy()) {
		ofxRunwayData data;
		data.setImage("semantic_map", runwayImageData, OFX_RUNWAY_JPG);
		runway.send(data);
	}

	runway.get("output", runwayResult);
}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	ofBackground(colorSky);
	cam.begin();
	ofSetColor(colorPavement);
	ofDrawRectangle(0, 0, surface.width, 600);
	ofSetColor(colorRoad);
	ofDrawRectangle(0, 600, surface.width, 200);
	ofSetColor(colorPavement);
	ofDrawRectangle(0, 800, surface.width, 600);


	ofDrawRectangle(0, 800, surface.width, 600);
	for (int i = 0; i < buildings.size(); i++) {
		ofSetColor(colorBuildings);
		buildings[i].draw();
		ofSetColor(colorWindow);
		buildings[i].drawWindows();
	}
	ofSetColor(colorSign);
	for (int i = 0; i < roadObjects.size(); i++) {
		roadObjects[i].draw();
	}

	cam.end();
	fbo.end();


	ofSetColor(255, 255);
	fbo.draw(0, 0);

	if (runwayImageData.isAllocated()) {
		runwayImageData.draw(0, 400);
	}
	if (runwayResult.isAllocated()) {
		runwayResult.draw(600, 400);
	}
	runway.drawStatus(20, 820, true);

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
// Runway sends information about the current model
//--------------------------------------------------------------
void ofApp::runwayInfoEvent(ofJson& info) {
	ofLogNotice("ofApp::runwayInfoEvent") << info.dump();
}
// if anything goes wrong
//--------------------------------------------------------------
void ofApp::runwayErrorEvent(string& message) {
	ofLogNotice("ofApp::runwayErrorEvent") << message;
}
