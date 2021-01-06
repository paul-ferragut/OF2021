#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	image.load("photo.jpg");
	image.setImageType(OF_IMAGE_GRAYSCALE);
	ofBackground(0);

	vector<ofDefaultVec3>points;

	for (int i = 0; i < 400000; i++) {
		int randomX = ofRandom(0, image.getWidth());
		int randomY = ofRandom(0, image.getHeight());

		if (image.getPixels().getColor(randomX, randomY).getBrightness() > ofRandom(1, 255)) {
			points.push_back(ofDefaultVec3(randomX, randomY, 0));
		}
	}

	ofRectangle bounds = ofRectangle(0, 0, image.getWidth(), image.getHeight());
	voronoi.setBounds(bounds);
	voronoi.setPoints(points);
	voronoi.generate();
}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){

	voronoi.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 

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

