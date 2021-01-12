#pragma once

#include "ofMain.h"
#include "ofxCsv.h"

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
		
		ofImage worldImage;

		ofxCsv worldLatLongData;
		ofxCsv worldHealth;// World Health Statistics 2020 | Complete | Geo - Analysis from kaggle.com
		ofxCsv worldPopulationData;// World Health Statistics 2020 | Complete | Geo - Analysis from kaggle.com
		
		string countryName[175];
		int countryLat[175];
		int countryLong[175];
		float countryVal[175];
		int worldPopulation[175];

		int maxPopulation;

		ofEasyCam cam;
		ofTexture mTex;
		ofLight light;
};
