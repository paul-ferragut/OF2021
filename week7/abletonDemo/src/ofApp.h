#pragma once

#include "ofMain.h"

//#define USE_DARKNET

#ifdef USE_DARKNET
#include "ofxDarknet.h"
#endif 

#include "ofxAbletonLive.h"
#include "tracker.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void exit();

	//ofxDarknet darknet;
	ofVideoGrabber video;
	ofVideoPlayer player;

	ofxAbletonLive live;

	tracker trackPersons;
	tracker trackCar;
	tracker trackBike;
	tracker trackDogs;

	vector<ofVec3f>personsPts;
	vector<ofVec3f>carPts;
	vector<ofVec3f>bikePts;
	vector<ofVec3f>dogPts;
	
};
