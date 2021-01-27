#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	vidGrabber.setup(320,240);

	colorImg.allocate(320,240);
	grayImg.allocate(320, 240);
	grayBg.allocate(320, 240);
	grayDiff.allocate(320, 240);

	gui.setup();
	gui.add(bLearnBackground.setup("capture bg",false));
	gui.add(threshold.setup("threshold", 60, 0, 255));

	ofBackground(0);

}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
	bool bNewFrame = false;
	bNewFrame=vidGrabber.isFrameNew(); //30 images per second, 200 frames seconds
	if (bNewFrame==true) {
	
		colorImg.setFromPixels(vidGrabber.getPixels());

		grayImg = colorImg;

		if (bLearnBackground==true) {
			grayBg = grayImg;
			bLearnBackground = false;
		}

		grayDiff.absDiff(grayBg, grayImg);
		grayDiff.threshold(threshold);

		contourFinder.findContours(grayDiff, 300, (320 * 240) / 2, 10, false);
		

		for (int i = 0; i < contourFinder.nBlobs; i++) {
			cout << "blob nb:" << i << " center x:" << contourFinder.blobs[i].boundingRect.getCenter().x << " center y:" << contourFinder.blobs[i].boundingRect.getCenter().y << endl;
		
		}

	}


}

//--------------------------------------------------------------
void ofApp::draw(){
	colorImg.draw(20, 20);
	grayImg.draw(360, 20);
	grayBg.draw(20, 280);
	grayDiff.draw(360, 280);
	grayDiff.draw(360, 540);
	contourFinder.draw(360, 540);
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
