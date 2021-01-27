#include "particle.h"

particle::particle() {

}

//-----------------------------------------------------------------------------------------------------------------
void particle::setup() {

	pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
	uniqueVal = ofRandom(0, 100);

}

//-----------------------------------------------------------------------------------------------------------------
void particle::update() {


		ofVec3f newVel = vel;
		frc.set(ofSignedNoise(ofGetElapsedTimef()+uniqueVal) * 2, ofSignedNoise(ofGetElapsedTimef() + 10+uniqueVal) * 2, 0);

		newVel += frc;


		pos += newVel;

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


		trail.push_back(pos);

		if (trail.size() >20) {
			trail.erase(trail.begin());
		}
}

//-----------------------------------------------------------------------------------------------------------------
void particle::draw(float radius) {
	ofFill();
	ofDrawCircle(pos, radius);

}

void particle::drawTrail() {

	ofNoFill();
	ofBeginShape();

	for (int i = 0; i < trail.size(); i++) {
	
		ofVertex(trail[i]);
	}

	ofEndShape();

}