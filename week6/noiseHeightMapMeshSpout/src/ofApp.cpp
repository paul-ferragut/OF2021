#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// Initialise the Spout sender with a channel name
	sender.init("oFVisual");

	gui.setup();
	gui.add(maxHeight.setup("maxHeight",50.0,0.1,200));

	fbo.allocate(ofGetHeight(), ofGetHeight());
	
	ofBackground(0);
	
}

//--------------------------------------------------------------
void ofApp::update(){



}

//--------------------------------------------------------------
void ofApp::draw(){

	ofMesh mesh;
	int resMesh = fbo.getWidth() / 5;
	for (int x = 0; x < resMesh; x++) {
		for (int y = 0; y < resMesh; y++) {
			
			float brightness = ofNoise(x*0.01, y*0.01, ofGetElapsedTimef()*0.1);
			//brightness=glm::perlin(glm::vec3(x*0.01, y*0.01, ofGetElapsedTimef()*0.1)); //other type of noise
			//brightness = glm::simplex(glm::vec3(x*0.01, y*0.01, ofGetElapsedTimef()*0.1));//other type of noise
			mesh.addVertex(ofVec3f(x, y, brightness*maxHeight));
			mesh.addColor(brightness);
		}
	}


	for (int x = 0; x < resMesh -1; x++) {
		for (int y = 0; y < resMesh -1; y++) {
			mesh.addIndex(x + y * resMesh); // 0 
			mesh.addIndex((x + 1) + y * resMesh); // 1 
			mesh.addIndex(x + (y + 1)*resMesh); // 10 

			mesh.addIndex((x + 1) + y * resMesh); // 1 
			mesh.addIndex((x + 1) + (y + 1)*resMesh); // 11 
			mesh.addIndex(x + (y + 1)*resMesh); // 10 


		}
	}
	ofEnableDepthTest();
	fbo.begin();
	ofBackground(0);
	
	cam.begin();
	//mesh.draw();
	mesh.drawWireframe();
	cam.end();
	ofDisableDepthTest();
	fbo.end();
	fbo.draw(0,0);

	sender.send(fbo.getTexture());
	
	gui.draw();
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
