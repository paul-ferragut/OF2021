#include "roadObject.h"

roadObject::roadObject()
{
}

//--------------------------------------------------------------
void roadObject::setup(ofVec3f intialPos, ofColor color) {
	pos = intialPos;
	col = color;
	//dimensions.set(ofRandom(10, 20), ofRandom(400, 500));
	dimensions.set(ofRandom(6, 12),0, ofRandom(400, 500));
	dimensions.y = dimensions.x;
	
}

void roadObject::scroll(float speed)
{
	pos.x += speed;
}

//--------------------------------------------------------------
void roadObject::draw() {
	ofSetColor(150, 60, 200);

	ofDrawBox(pos.x, pos.y,0, dimensions.x, dimensions.y, dimensions.z);

}

//--------------------------------------------------------------