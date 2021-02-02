#include "particle.h"

particle::particle() {

}

//-----------------------------------------------------------------------------------------------------------------
void particle::setup(ofVec3f intitialPos) {

	pos.set(intitialPos);
	initialVel.set(ofRandom(-0.01, 0.01), ofRandom(-0.01, 0.01), ofRandom(-0.01, 0.01));
	uniqueVal = ofRandom(0, 100);
	vel = initialVel;

}

void particle::reset()
{
	frc.set(0, 0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y) {
	// add in a force in X and Y for this frame.
	frc.x += x;
	frc.y += y;

}
void particle::addDampingForce() {


	vel *= 0.99;
	
}

//------------------------------------------------------------
void particle::addAttraction(ofVec3f attractPoint)
{
	
		ofVec3f attractPt = attractPoint;
		ofVec3f frcAttract = attractPt - pos; //attraction we get the attraction force/vector by looking at the mouse pos relative to our pos
	
			frcAttract.normalize();
			frc += frcAttract * 0.1; //apply force

}

void particle::addRepulsion( ofVec3f frcRepulsion,float dist)
{

	frcRepulsion.normalize();
		frc += frcRepulsion * 0.11*ofMap(dist,0,200,1.0,0); //apply force
	
}

void particle::addNoise(float noiseAmt)
{
	ofVec3f noiseVec;
	noiseVec.set(ofSignedNoise(ofGetElapsedTimef() + uniqueVal) * noiseAmt, ofSignedNoise(ofGetElapsedTimef() + 10 + uniqueVal) * noiseAmt);
	frc += noiseVec;
}

//-----------------------------------------------------------------------------------------------------------------
void particle::update() {



		vel += frc;
		pos += vel;

}

//-----------------------------------------------------------------------------------------------------------------
void particle::draw(float radius) {

	ofDrawSphere(pos, radius);
}

void particle::bounceWall()
{

	if (pos.x > ofGetWidth()) {
		pos.x = ofGetWidth();
		vel.x *= -1.0;

	}
	else if (pos.x < 0) {
		pos.x = 0;
		vel.x *= -1.0;

	}

	if (pos.y > ofGetHeight()) {
		pos.y = ofGetHeight();
		vel.y *= -1.0;

	}
	else if (pos.y < 0) {
		pos.y = 0;
		vel.y *= -1.0;

	}
}
