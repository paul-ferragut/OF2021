#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
#include "ofxGui.h"
#include "particleShader.h"
#define P_NUM 10

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxAutoReloadedShader shader;
		ofVideoGrabber webcam;

		ofxPanel gui;
		ofxFloatSlider intensity;
		ofxFloatSlider radius;
		ofxFloatSlider rgb;
		ofxFloatSlider spread;

		ofVec2f arrayUniform[P_NUM];
		float arrayParticleSize[P_NUM];
		particleShader p[P_NUM];
		static const int arrayLength = 10;
};
