#pragma once

#include "ofMain.h"
#include "roadObject.h"
#include "building.h"

#include "ofxRunway.h"
// make sure you make your ofApp or class to inherit from ofxRunwayListener
class ofApp : public ofBaseApp, public ofxRunwayListener{

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
		
		ofEasyCam cam;

		ofColor colorRoad;
		ofColor colorPavement;
		ofColor colorWindow;
		ofColor colorSky;
		ofColor colorSign;
		ofColor colorTrafficLight;
		ofColor colorBuildings;

		ofRectangle surface;

		vector<building>buildings;
		vector < roadObject>roadObjects;

		float scrollSpeed;

		ofxRunway runway;
		ofImage runwayImageData;
		ofImage runwayResult;

		ofFbo fbo;

		int widthRunway;
		int heightRunway;


		void runwayInfoEvent(ofJson& info);
		void runwayErrorEvent(string& message);
};
