#pragma once

#include "ofMain.h"

class tracker
{
public:
	tracker();
	void setup();
	void update(vector<ofVec3f>pts);
	void draw(string type);
	float getPan();
	float getVol();
	ofVec3f attractionPt;
	ofVec3f pos;
	ofVec3f frc;
	ofVec3f vel;
};
