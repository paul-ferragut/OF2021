#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(0, 0, 0);
	ofSetRectMode(OF_RECTMODE_CENTER);//using this function we draw rectangle from the center instead of the top left corner, thus centering a square is easier


	soundStream.printDeviceList();//from the audioInputExample

	int bufferSize = 256;//from the audioInputExample

	left.assign(bufferSize, 0.0);//from the audioInputExample
	right.assign(bufferSize, 0.0);//from the audioInputExample

	bufferCounter = 0;//from the audioInputExample
	smoothedVol = 0.0;//from the audioInputExample
	scaledVol = 0.0;//from the audioInputExample

	ofSoundStreamSettings settings;

	// if you want to set the device id to be different than the default
	// auto devices = soundStream.getDeviceList();
	// settings.device = devices[4];

	// you can also get devices for an specific api
	// auto devices = soundStream.getDevicesByApi(ofSoundDevice::Api::PULSE);
	// settings.device = devices[0];

	// or get the default device for an specific api:
	// settings.api = ofSoundDevice::Api::PULSE;

	// or by name
	auto devices = soundStream.getMatchingDevices("default");//from the audioInputExample
	if (!devices.empty()) {//from the audioInputExample
		settings.setInDevice(devices[0]);//from the audioInputExample
	}//from the audioInputExample

	settings.setInListener(this);//from the audioInputExample
	settings.sampleRate = 44100;//from the audioInputExample
	settings.numOutputChannels = 0;//from the audioInputExample
	settings.numInputChannels = 2;//from the audioInputExample
	settings.bufferSize = bufferSize;//from the audioInputExample
	soundStream.setup(settings);//from the audioInputExample

	scene1 = true;
	scene2 = false;

}

//--------------------------------------------------------------
void ofApp::update() {

	float microphoneSensitivity = 0.10;//Make this value slightly bigger or smaller depending on your mic sensitivity
	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, microphoneSensitivity, 0.0, 1.0, true);
	//cout<<"microphone volume; scaledVol:"<<scaledVol<<endl; //uncomment this line if you want to debug your microphone in the console

}

//--------------------------------------------------------------
void ofApp::draw() {


	if (scene1 == true) {
		//in this scene more concentric circles are drawn as the volume increase
		ofSetColor(255, 255, 255, 200);
		ofNoFill();//Draw shapes outlines
		ofSetLineWidth(1.0);

		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);//centering
		for (int i = 0; i < ofMap(scaledVol, 0.0, 1.0, 0, 400); i++) {
			ofDrawCircle(0, 0, 5 * i, 5 * i);
		}
		ofPopMatrix();

	}

	if (scene2 == true) {
		//in this scene we will draw a grid of square increasing their size with the sound volume
		ofSetColor(255, 255, 255, 150);
		ofFill();//fill the shapes

		//here we define paramaters for our grid of rectangles
		int rows = 10;//number of rows
		int columns = 10;//number of columns
		int gap = 100;//the gap in between each square

		ofPushMatrix();
		ofTranslate((ofGetWidth() / 2), ofGetHeight() / 2);//first we center our grid in the middle of our top left square
		ofTranslate(-((gap * (rows - 1)) / 2), -((gap * (columns - 1)) / 2));//second we offset back to the middle of our grid 
		//This is a nested loop!! A LOOP INSIDE A LOOP 
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				ofDrawRectangle(gap*i, gap*j, ofMap(scaledVol, 0.0, 1.0, 0, 200), ofMap(scaledVol, 0.0, 1.0, 0, 200));
			}
		}
		ofPopMatrix();
	}

	ofSetColor(255, 255, 255);
	ofDrawBitmapString("press 1 or 2 to activate scenes", 20, 35);//ofDrawBitmapString() is to draw text
	ofDrawBitmapString("scene1:" + ofToString(scene1), 20, 50);//ofToString() convert an int or a float or a bool into a string
	ofDrawBitmapString("scene2:" + ofToString(scene2), 20, 65);
	ofDrawBitmapString("volume:" + ofToString(scaledVol), 20, 20);

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	//by pressing the key '1' we activate or deactivate the scene1
	if (key == '1') {
		if (scene1 == true) {
			scene1 = false;
		}
		else if (scene1 == false) {
			scene1 = true;
		}
	}

	//by pressing the key '2' we activate or deactivate the scene2
	if (key == '2') {
		scene2 = !scene2; //this is actually the same as above, =! assign the bool to its contrary. Less code to write ;)
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input) {
	//from the audioInputExample
	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (size_t i = 0; i < input.getNumFrames(); i++) {
		left[i] = input[i * 2] * 0.5;
		right[i] = input[i * 2 + 1] * 0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted += 2;
	}

	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;

	// this is how we get the root of rms :) 
	curVol = sqrt(curVol);

	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;

	bufferCounter++;

}