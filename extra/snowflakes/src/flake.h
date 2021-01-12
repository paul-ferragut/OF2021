#pragma once

#include "ofMain.h"


class flake {



public:
	flake() {};
	~flake() {};
	void setup(ofVec3f originPos,float side,float lineThickness);
	void update(bool push,ofVec2f posMouse);
	void draw(bool debug);
	void reset();

	ofVec3f pt[4];
	ofVec3f centerPt[2];
	bool hover[6];
	bool activated[6];
	ofPolyline poly[6];
	float sideE;
	float height;
	float lThickness;
};