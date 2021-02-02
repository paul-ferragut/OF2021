#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){



	model.loadModel("skateboard.obj");
	//2 we load a 3D model

	mesh = model.getMesh(0);
	// 2 we copy the model to ofMesh
	

	ofEnableDepthTest();


	for (int i = 0; i < mesh.getNumVertices(); i++) {
		particle nP;
		p.push_back(nP);
	}

	for (int i = 0; i < p.size(); i++) {
		p[i].setup(mesh.getVertex(i));
		//3 we create a particle from each vertex of the mesh
	}

}

//--------------------------------------------------------------
void ofApp::update(){

	ofSetFrameRate(60);
	for (int i = 0; i < p.size(); i++) {
		p[i].reset();

		ofVec3f mouse(ofGetMouseX(), ofGetMouseY(), 0);
		ofVec3f cur = cam.worldToScreen(mesh.getVertex(i));
		float distance = ofDist(cur.x, cur.y, cur.z, mouse.x, mouse.y, mouse.z);

		if (distance < 200) {
			ofVec3f vecRepulsion = p[i].pos - cur;
			p[i].addRepulsion(vecRepulsion,distance);
			p[i].addNoise(0.2);//optional
		}
		
		p[i].addAttraction(mesh.getVertex(i));//each particles is attracted to a vertex position of the original mesh

		p[i].addDampingForce();
		p[i].update();
	
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(64), ofColor(0));
	ofFill();
	ofSetColor(255,255,255);
	cam.begin();

	//glPointSize(2);
	//model.drawVertices();
	
	for (int i = 0; i < p.size(); i++) {
		ofColor meshCol = mesh.getColor(i);
		ofSetColor(meshCol);
		p[i].draw(0.1);
	}
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
