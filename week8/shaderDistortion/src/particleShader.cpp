#include "particleShader.h"

//------------------------------------------------------------------
particleShader::particleShader(){
	//attractPoints = NULL;
}
particleShader::~particleShader() {
	//attractPoints = NULL;
}

//------------------------------------------------------------------
void particleShader::reset(ofRectangle posIn){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	bounds = posIn;


	pos.x = ofRandom(bounds.x, bounds.x + bounds.width);//ofRandomWidth();
	pos.y = ofRandom(bounds.y, bounds.y + bounds.height);//ofRandomHeight();

	//if (ofRandomf() > 0.6) {
	//	pos.x = ofRandom(posIn2.x, posIn2.x + posIn2.width);//ofRandomWidth();
	//	pos.y = ofRandom(posIn2.x, posIn2.x + posIn2.width);//ofRandomHeight();
	//}
	
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	
	frc   = ofPoint(0,0,0);
	
	radius = ofRandom(4.0, ofRandom(400, 800));
	w = posIn.width;
	//scale = ofRandom(0.5, 1.0);
//	mode = PARTICLE_MODE_NOISE;
//	if( mode == PARTICLE_MODE_NOISE ){
		drag  = ofRandom(0.97, 0.97);
	//	vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
	//}else{
	//	drag  = ofRandom(0.95, 0.998);	
//	}
}

void particleShader::resetEnd()
{
	radius = ofRandom(4.0, ofRandom(400, 800));

//	pos.x = ofRandom(posIn1.x, posIn1.x + posIn1.width);//ofRandomWidth();
//	pos.y = -(radius * 2);// ofRandom(posIn1.x, posIn1.x + posIn1.width);//ofRandomHeight();

	//if (ofRandomf() > 0.6) {
	pos.x = ofRandom(0, w);//posIn2.x, posIn2.x + posIn2.width);//ofRandomWidth();
		pos.y = -(radius*2);//ofRandom(posIn2.x, posIn2.x + posIn2.width);//ofRandomHeight();
	//}

	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);

	frc = ofPoint(0, 0, 0);

	
	drag = ofRandom(0.97, 0.97);

}

//------------------------------------------------------------------
void particleShader::update(){


	float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
		
		frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
		frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
	
		vel *= drag; 
		vel += frc * 0.4;
		
	//2 - UPDATE OUR POSITION
	
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}else if( pos.x < bounds.x){
		pos.x = bounds.x;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight()+(radius*2) ){
		//pos.y = ofGetHeight();
		//vel.y *= -1.0;
		resetEnd();
	}
	else if( pos.y < -(radius*2) ){
		pos.y = -(radius*2);
		vel.y *= -1.0;
	}	
		
}

//------------------------------------------------------------------
void particleShader::draw(float r){

	ofSetColor(100, 100, 100);
	ofNoFill();
	ofDrawCircle(pos.x, pos.y, radius*r);
	ofFill();
}

