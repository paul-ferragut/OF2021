#include "particle.h"

particle::particle() {

}

//-----------------------------------------------------------------------------------------------------------------
void particle::setup() {

	pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	initialVel.set(ofRandom(-1, 1), ofRandom(-1, 1));
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

	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	vel *= 0.99;
	
}

//------------------------------------------------------------
void particle::addAttraction(ofVec3f attractPoint, float blobSize)
{
	//for (int i = 0; i < attractPoint.size(); i++) {
		ofVec3f attractPt = attractPoint;
		ofVec3f frcAttract = attractPt - pos; //attraction we get the attraction force/vector by looking at the mouse pos relative to our pos
		//frc = pos - attractPt; //repulsion
		float dist = frcAttract.length();//lenght is the same as magnitude
		if (dist < blobSize) {
			frcAttract.normalize();
			frc += frcAttract * 0.18; //apply force
		}
	//}
}

void particle::addRepulsion(ofVec3f repulsionPoint)
{
	ofVec3f repulsionPt = repulsionPoint;
	//frc = attractPt - pos; //attraction we get the attraction force/vector by looking at the mouse pos relative to our pos
	ofVec3f frcRepulsion = pos - repulsionPt; //repulsion
	float dist = frcRepulsion.length();
	if (dist < 300) {
		frcRepulsion.normalize();
		frc += frcRepulsion * 0.1; //apply force
	}
}

void particle::addNoise(float noiseAmt)
{
	ofVec3f noiseVec;
	noiseVec.set(ofSignedNoise(ofGetElapsedTimef() + uniqueVal) * noiseAmt, ofSignedNoise(ofGetElapsedTimef() + 10 + uniqueVal) * noiseAmt);
	frc += noiseVec;
}

//-----------------------------------------------------------------------------------------------------------------
void particle::update() {


		//ofVec3f newVel = vel;
		//frc.set(ofSignedNoise(ofGetElapsedTimef()+uniqueVal) * 2, ofSignedNoise(ofGetElapsedTimef() + 10+uniqueVal) * 2, 0);

		//vel += frc;
		vel += frc;
		pos += vel;

}

//-----------------------------------------------------------------------------------------------------------------
void particle::draw(float radius) {

	ofDrawCircle(pos, radius);
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
