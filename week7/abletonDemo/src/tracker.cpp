#include "tracker.h"

tracker::tracker()
{
}

void tracker::setup()
{
	attractionPt.set(1280 / 2, 720 / 2, 0);
	pos.set(1280/2,720/2, 0);
	vel.set(0, 0, 0);
	frc.set(0, 0, 0);
}

void tracker::update(vector<ofVec3f> pts)
{

	//reset force
	frc.set(0, 0);
	

	if (pts.size() > 0) {
		ofVec3f frcAttract = attractionPt - pos; //attraction we get the attraction force/vector by looking at the mouse pos relative to our pos
		//frc = pos - attractPt; //repulsion
		float dist = frcAttract.length();//lenght is the same as magnitude
		//frcAttract.normalize();
		frc += (frcAttract*0.01);// *0.4; //apply force

		ofVec3f sumAverage(0, 0, 0);
		for (int i = 0; i < pts.size(); i++) {

			sumAverage += pts[i];
		}

		attractionPt = sumAverage / pts.size();
	}

	//damping velocity
	vel *= 0.9;

	vel += frc;
	
	pos += vel;
}

void tracker::draw(string type)
{
	ofFill();
	ofSetColor(255, 0, 0);
	ofDrawCircle(pos,20);
	ofDrawBitmapStringHighlight(type, pos);
}

float tracker::getPan()
{
	return ofMap(pos.x, 0, 1280, -1.0, 1.0, true);
}

float tracker::getVol()
{
	//cout << abs(frc.x) << endl;
	return ofMap(abs(frc.x), 0.0,2.0, 0.0, 1.0, true);
}
