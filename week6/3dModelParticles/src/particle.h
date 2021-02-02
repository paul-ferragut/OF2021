#pragma once
#include "ofMain.h"

class particle {

public:
	particle();//constructor

	void setup(ofVec3f intitialPos);
	void reset();
	void addAttraction(ofVec3f attractPoint);
	void addRepulsion( ofVec3f frcRepulsion, float dist);
	void addNoise(float noiseAmt);
	void addForce(float x, float y);
	void addDampingForce();
	void update();
	void draw(float radius);
	void bounceWall();

	ofVec3f pos;
	ofVec3f vel;
	ofVec3f initialVel;
	ofVec3f frc;
	float uniqueVal;

};