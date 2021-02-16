#pragma once
#include "ofMain.h"


class particleShader {

	public:
		particleShader();
		~particleShader();
		
		void reset(ofRectangle posIn);
		void resetEnd();
		void update();
		void draw(float r);
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		

		ofRectangle bounds;

		float radius;
		int w;
};