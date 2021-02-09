#include "building.h"


building::building()
{

}

//--------------------------------------------------------------
void building::setup(ofVec3f intialPos,ofColor color){
	pos = intialPos;
	col = color;
	dimensions.set(ofRandom(100, 500),0, ofRandom(300, 1800));
	dimensions.y = dimensions.x;
}

void building::scroll(float speed)
{
	pos.x += speed;
}

//--------------------------------------------------------------
void building::draw(){
	ofSetColor(10, 60, 200);
	ofDrawBox(pos.x,pos.y,0,dimensions.x,dimensions.y,dimensions.z);
}

//--------------------------------------------------------------
void building::drawWindows() {

	for (int x = 0; x < dimensions.x; x += dimensions.x / 10) {
		for (int z = 0; z < dimensions.z; z += dimensions.z / 12) {
			ofDrawBox(pos.x + x - (dimensions.x / 2), pos.y, z - (dimensions.z / 2), dimensions.x / 20, dimensions.y + 2, dimensions.z / 20);
		}
	}
}

//--------------------------------------------------------------