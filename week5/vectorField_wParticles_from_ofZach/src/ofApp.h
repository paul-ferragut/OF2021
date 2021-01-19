#pragma once

//Vector fields example based on example from https://github.com/ofZach/algo2012

#include "ofMain.h"
#include "particle.h"
#include "vectorField.h"

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased (int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		// let's make a vector of them
		vector <particle> particles;
		vectorField VF;
	
		int drawingStyle;
		bool bFade;
    
        bool bSavePdf;
    
	
};

