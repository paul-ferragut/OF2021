#pragma once

#include "ofMain.h"


class roadObject{

	public:
		roadObject();

		void setup(ofVec3f intialPos, ofColor color);
		void scroll(float speed);
		void draw();

		ofVec3f pos;
		ofVec3f dimensions;
		ofColor col;
	
		
};
