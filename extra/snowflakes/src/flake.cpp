#include "flake.h"


void flake::setup(ofVec3f originPos, float side, float lineThickness)
{

	lThickness = lineThickness;
	sideE = side;
	height= sideE * sqrt(3.0) / 2.0;
	pt[0].set(originPos);//left
	pt[1].set(originPos.x + sideE/2, originPos.y-height);// top
	pt[2].set(originPos.x + sideE, originPos.y);//right
	pt[3].set(originPos.x + sideE / 2, originPos.y+height);//bottom

	centerPt[0].set(originPos.x + sideE/2, originPos.y - (height / 2));//top
	centerPt[1].set(originPos.x + sideE/2, originPos.y + (height / 2));//bottom


	
	poly[0].addVertex(centerPt[0]);
	poly[0].addVertex(pt[0]);
	poly[0].addVertex(pt[1]);
	poly[0].addVertex(centerPt[0]);


	poly[1].addVertex(centerPt[0]);
	poly[1].addVertex(pt[0]);
	poly[1].addVertex(pt[2]);
	poly[1].addVertex(centerPt[0]);

	poly[2].addVertex(centerPt[0]);
	poly[2].addVertex(pt[1]);
	poly[2].addVertex(pt[2]);
	poly[2].addVertex(centerPt[0]);
	//
	poly[3].addVertex(centerPt[1]);
	poly[3].addVertex(pt[0]);
	poly[3].addVertex(pt[3]);
	poly[3].addVertex(centerPt[1]);

	poly[4].addVertex(centerPt[1]);
	poly[4].addVertex(pt[0]);
	poly[4].addVertex(pt[2]);
	poly[4].addVertex(centerPt[1]);

	poly[5].addVertex(centerPt[1]);
	poly[5].addVertex(pt[3]);
	poly[5].addVertex(pt[2]);
	poly[5].addVertex(centerPt[1]);

	for (int i = 0; i < 6; i++) {

		activated[i]=false;
		hover[i] = false;
	}

}

void flake::update(bool push, ofVec2f posMouse)
{
	if (activated[1]) {
		activated[4] = true;
	}
	if (activated[4]) {
		activated[1] = true;
	}

	for (int i = 0; i < 6; i++) {
		hover[i] = false;
		hover[i]=poly[i].inside(posMouse.x,posMouse.y);


		if (hover[i]&&push) {
			activated[i] = !activated[i];
		}
	}

}

void flake::draw(bool debug)
{

	for (int i = 0; i < 6; i++) {
		if (debug) {
			ofSetColor(255, 255, 255,20);
			ofNoFill();
			poly[i].draw();
		}
	
		if (activated[i]) {
			ofFill();
			if (debug) {
				ofSetColor(255, 255, 255, 100);
				ofBeginShape();
				ofVertices(poly[i].getVertices());
				ofEndShape();
			}
			ofSetLineWidth(lThickness);
			ofSetColor(255, 255, 255,255);
			switch (i) {
			case 0:
				ofDrawLine(pt[0],pt[1]);
				break;
			case 1:
				ofDrawLine(pt[0], pt[2]);
				break;
			case 2:
				ofDrawLine(pt[1], pt[2]);
				break;
			case 3:
				ofDrawLine(pt[0], pt[3]);
				break;
			case 4:
				ofDrawLine(pt[0], pt[2]);
				break;
			case 5:
				ofDrawLine(pt[3], pt[2]);
				break;
		}
			
			
		

			//poly[i].draw();
		}
		if (hover[i]) {
			if (debug) {
				ofFill();
				ofSetColor(0, 255, 0);
				ofBeginShape();
				ofVertices(poly[i].getVertices());
				ofEndShape();
			}
		}
	}
}

void flake::reset()
{

	for (int i = 0; i < 6; i++) {

		activated[i] = false;
		hover[i] = false;
	}
}
