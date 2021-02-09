#pragma once

#include "ofMain.h"

class building{

	public:
		building();
		void setup(ofVec3f intialPos,ofColor color);
		void scroll(float speed);
		void draw();
		void drawWindows();

		ofVec3f pos;
		ofVec3f dimensions;
		ofColor col;

};
