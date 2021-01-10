#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	void audioIn(ofSoundBuffer & input);//from the audioInputExample

	vector <float> left;//from the audioInputExample
	vector <float> right;//from the audioInputExample
	//vector <float> volHistory;//from the audioInputExample

	int 	bufferCounter;//from the audioInputExample
	//int 	drawCounter;//from the audioInputExample

	float smoothedVol;//from the audioInputExample
	float scaledVol;//from the audioInputExample

	ofSoundStream soundStream;//from the audioInputExample

	bool scene1;
	bool scene2;

	float maxVolume;
};