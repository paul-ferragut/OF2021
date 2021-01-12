#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	worldImage.load("3840px-Blue_Marble_2002.png");//load image from bin/data

	ofDisableArbTex();//This is for mapping the image on the sphere for the 3D demo, here is why https://forum.openframeworks.cc/t/what-does-ofdisablearbtex-do/26377/3
	ofLoadImage(mTex, "3840px-Blue_Marble_2002.png");


	worldLatLongData.load("country-coordinates-world.csv");//load the latitude and longitude csv
	worldHealth.load("roadTrafficDeaths.csv");//load the road death csv, World Health Statistics 2020 | Complete | Geo - Analysis from kaggle.com https://www.kaggle.com/utkarshxy/who-worldhealth-statistics-2020-complete?select=cleanFuelAndTech.csv
	worldPopulationData.load("population_by_country_2020.csv");//load the population by country csv


	for (int i = 0; i < worldHealth.getNumRows()-1; i++) {//-1 because the first row doesn't count
		
		countryName[i] = worldHealth.getRow(i+1).getString(0);//We store all the country names //+1 because we want to ignore the first row
		countryVal[i] = worldHealth.getRow(i+1).getFloat(3);//We store all the traffice values

		countryLat[i] = 0;//We initiate all the latitude value to 0
		countryLong[i] = 0;//We initiate all the longitude value to 0

		//We Loop through the country names in the other spreadsheet 
		for (int j = 0; j < worldLatLongData.getNumRows()-1; j++) {
			string countryName2 = worldLatLongData.getRow(j+1).getString(2);
			if (countryName[i] == countryName2) {//We find matching country names between the 2 spreadsheets
				countryLat[i] = worldLatLongData.getRow(j+1).getFloat(0); //then we assign the corresponding latitude value
				countryLong[i]= worldLatLongData.getRow(j+1).getFloat(1);
			}
		}

		for (int j = 0; j < worldPopulationData.getNumRows()-1; j++) {
			string countryName2 = worldPopulationData.getRow(j+1).getString(0);
			if (countryName[i] == countryName2) {
				worldPopulation[i] = worldPopulationData.getRow(j+1).getInt(1);
			}
		}

	}

	maxPopulation= worldPopulationData.getRow(1).getInt(1);//The biggest population is the number in the row 1 ,column 1, this will give a us a population range, useful later
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofFill();
	ofSetColor(255, 255);
	worldImage.draw(0,0,ofGetWidth(),ofGetHeight());//draw the earth image

	for (int i = 0; i < worldHealth.getNumRows()-1; i++) {
		if (countryLat[i] != 0 && countryLong[i] != 0) {//we ignore the countries for which we don't know the latitude and longitude

			ofSetColor(ofMap(countryVal[i], 0.0, 40, 0, 255, true), ofMap(countryVal[i], 0.0, 40, 255, 0, true), 0, 200);//the circle color is green for low value and red for high value
			
			ofVec3f posCountry;
			posCountry.set(ofMap(countryLong[i], -180, 180, 0, ofGetWidth(), true), ofMap(countryLat[i], 90, -90, 0, ofGetHeight(), true),0);//We remap the longitude and latitude with our screen dimension https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.satsig.net%2Flat_long.htm&psig=AOvVaw0mTcOPsRGdU_s4bXiYEYiS&ust=1610557969053000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCJDIxY7ylu4CFQAAAAAdAAAAABAF
			
			ofDrawCircle(posCountry, ofMap(worldPopulation[i], 0, maxPopulation, 20, 200, true));//the circle radius is proportional to the country population

			ofSetColor(255, 255);
			ofDrawBitmapString(countryName[i], posCountry);//We draw the country name in white
		
		}
	}
	

	//If you want to test the example in 3D comment the beginning and uncomment the part below
	/*
	ofEnableDepthTest();//This is like enabling occlusion with 3D object https://docs.unity3d.com/uploads/Main/TransparentDiffuseZWrite.png
	cam.begin();//starting OF easyCam
	ofSetColor(255, 255);
	mTex.bind();//binding the earth image to a drawn sphere
	ofDrawSphere(0, 0, 0, 300);
	mTex.unbind();

	for (int i = 0; i < worldHealth.getNumRows() - 1; i++) {


		//Here we are using quaternions, this is fancy math for making calculations with 3d rotations easier
		//three rotations
		glm::quat latRot, longRot, spinQuat;
		latRot = glm::angleAxis(ofDegToRad(countryLat[i]), glm::vec3(-1, 0, 0));
		longRot = glm::angleAxis(ofDegToRad(countryLong[i]), glm::vec3(0, 1.0, 0));

		spinQuat = glm::angleAxis(ofDegToRad(180), glm::vec3(0, 1, 0));

		//our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
		glm::vec3 center = glm::vec3(0, 0, 300);
		//multiplying a quat with another quat combines their rotations into one quat
		//multiplying a quat to a vector applies the quat's rotation to that vector
		//so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
		glm::vec3 worldPoint = spinQuat * longRot * latRot * center;

		
		ofSetColor(ofMap(countryVal[i], 0.0, 40, 0, 255, true), ofMap(countryVal[i], 0.0, 40, 255, 0, true), 0, 130);
		ofDrawSphere(worldPoint, ofMap(worldPopulation[i], 0, maxPopulation, 4, 100, true));
		
	}
	cam.end();
	*/
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
