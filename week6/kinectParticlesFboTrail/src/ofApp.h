#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxAzureKinect.h"
#include "ofxGui.h"
#include "particle.h"

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
		void exit();
		ofxCvColorImage colorImg;

		ofxCvGrayscaleImage grayImage; // grayscale depth image
		ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
		ofxCvGrayscaleImage grayThreshFar; // the far thresholded image

		ofxCvContourFinder contourFinder;

		ofxToggle bThreshWithOpenCV;
	
		//int nearThreshold;
		//int farThreshold;
		vector<particle>p;

		ofxPanel gui;
		ofxFloatSlider nearThreshold;
		ofxFloatSlider farThreshold;

		
		ofFbo fbo;

		ofxFloatSlider fadeAmount;

		ofxToggle useNoise;
		ofxToggle connectLines;
		ofxFloatSlider noiseAmount;
		ofxIntSlider pNum;

		int kWdith;
		int kHeight;

private:
	ofxAzureKinect::Device kinectDevice;
	ofFpsCounter kinectFps;

		
};
