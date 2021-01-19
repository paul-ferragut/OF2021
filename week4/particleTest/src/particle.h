#pragma once
#include "ofMain.h"

class particle {

public:
	particle();//constructor

	void setup();
	void update();
	void draw(float radius);

	ofVec3f pos;
	ofVec3f vel;
	ofVec3f frc;
	float uniqueVal;

};