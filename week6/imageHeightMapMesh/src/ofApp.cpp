#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	image.load("heightMap.png");
	image.resize(image.getWidth() / 4, image.getHeight() / 4);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	

	ofMesh mesh;
	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); y++) {
			float brightness = image.getPixels().getColor(x, y).getBrightness();
			mesh.addVertex(ofVec3f(x,y, brightness/3));
			mesh.addColor(brightness/255);
		}
	}

	for (int x = 0; x < image.getWidth() -1; x++) {
		for (int y = 0; y < image.getHeight() -1; y++) {
			mesh.addIndex(x + y * image.getWidth());//0
			mesh.addIndex((x + 1) + y * image.getWidth());//1
			mesh.addIndex(x + (y + 1)*image.getWidth());//5

			mesh.addIndex((x + 1)+y* image.getWidth());//1
			mesh.addIndex((x + 1) + (y + 1)*image.getWidth());//6
			mesh.addIndex(x + (y + 1)*image.getWidth());//5
		}
	}

	cam.begin();
	mesh.drawFaces();
	cam.end();
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
