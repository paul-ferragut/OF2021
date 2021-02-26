#include "ofApp.h"

void ofApp::setup() 
{

#ifdef USE_DARKNET
	std::string cfgfile = ofToDataPath("cfg/yolov2-tiny-voc.cfg");
	std::string weightfile = ofToDataPath("yolov2-tiny-voc.weights");
	std::string namesfile = ofToDataPath("cfg/voc.names");
	darknet.init( cfgfile, weightfile, namesfile );

	player.load("record.mov");
	player.setLoopState(OF_LOOP_NORMAL);
	player.play();
#endif 

	live.setup();


	trackPersons.setup();
	trackCar.setup();
	trackBike.setup();
	trackDogs.setup();

}

void ofApp::update()
{
#ifdef USE_DARKNET
	player.update();
#endif 
	ofSetWindowTitle("FPS:" + ofToString(ofGetFrameRate()));

	live.update();




}

void ofApp::draw(){	

#ifdef USE_DARKNET	
	ofSetColor( 255 );
	player.draw( 0, 0 );

	float thresh = 0.3;
    float maxOverlap = 0.25;

	if(player.isFrameNew() &&darknet.isLoaded()) {

		std::vector< detected_object > detections = darknet.yolo(player.getPixels(), 0.6, maxOverlap);
		ofNoFill();	
		
		personsPts.clear();
		carPts.clear();
		bikePts.clear();
		dogPts.clear();
		for (int i = 0; i < detections.size(); i++) {
		
			ofSetColor(detections[i].color);
			glLineWidth(ofMap(detections[i].probability, 0, 1, 0, 8));
			ofNoFill();
			ofDrawRectangle(detections[i].rect);
			ofDrawBitmapStringHighlight(detections[i].label + ": " + ofToString(detections[i].probability), detections[i].rect.x, detections[i].rect.y + 20);
		
			if (detections[i].label == "person" || detections[i].label == "traveler" || detections[i].label == "athlete" || detections[i].label == "traffic-cop") {
				personsPts.push_back(detections[i].rect.getCenter());
			}
			if (detections[i].label == "car" || detections[i].label == "truck") {
				carPts.push_back(detections[i].rect.getCenter());
			}
			if (detections[i].label == "bike" || detections[i].label == "push-bike") {
				bikePts.push_back(detections[i].rect.getCenter());
			}
			if (detections[i].label == "dog") {
				dogPts.push_back(detections[i].rect.getCenter());
			}
		}

		trackPersons.update(personsPts);
		trackPersons.draw("PERSON");
		trackCar.update(carPts);
		trackCar.draw("CAR");
		trackBike.update(bikePts);
		trackBike.draw("BIKE");
		trackDogs.update(dogPts);
		trackDogs.draw("DOGS");

		if (live.isLoaded()) {
			ofxAbletonLiveTrack *track1 = live.getTrack(0);
			track1->setVolume(trackPersons.getVol());
			track1->setPan(trackPersons.getPan());

			ofxAbletonLiveTrack *track2 = live.getTrack(1);
			track2->setVolume(trackCar.getVol());
			track2->setPan(trackCar.getPan());

			ofxAbletonLiveTrack *track3 = live.getTrack(2);
			track3->setVolume(trackBike.getVol());
			track3->setPan(trackBike.getPan());

			ofxAbletonLiveTrack *track4 = live.getTrack(3);
			track4->setVolume(trackDogs.getVol());
			track4->setPan(trackDogs.getPan());
		}
	}
	#else

	if (ofGetFrameNum() % 30 == 0) {

		personsPts.clear();

		personsPts.push_back(ofVec2f(ofRandom(0, 1280), ofRandom(0, 800)));

	}


	if (ofGetFrameNum() % 100 == 0) {
		carPts.clear();
		carPts.push_back(ofVec2f(ofRandom(0, 1280), ofRandom(0, 800)));
	}

	if (ofGetFrameNum() % 200 == 0) {

		bikePts.clear();
		dogPts.clear();

		bikePts.push_back(ofVec2f(ofRandom(0, 1280), ofRandom(0, 800)));

		dogPts.push_back(ofVec2f(ofRandom(0, 1280), ofRandom(0, 800)));

	}



	trackPersons.update(personsPts);
	trackPersons.draw("PERSON");
	trackCar.update(carPts);
	trackCar.draw("CAR");
	trackBike.update(bikePts);
	trackBike.draw("BIKE");
	trackDogs.update(dogPts);
	trackDogs.draw("DOGS");

	if (live.isLoaded()) {
		ofxAbletonLiveTrack *track1 = live.getTrack(0);
		track1->setVolume(trackPersons.getVol());
		track1->setPan(trackPersons.getPan());

		ofxAbletonLiveTrack *track2 = live.getTrack(1);
		track2->setVolume(trackCar.getVol());
		track2->setPan(trackCar.getPan());

		ofxAbletonLiveTrack *track3 = live.getTrack(2);
		track3->setVolume(trackBike.getVol());
		track3->setPan(trackBike.getPan());

		ofxAbletonLiveTrack *track4 = live.getTrack(3);
		track4->setVolume(trackDogs.getVol());
		track4->setPan(trackDogs.getPan());
	}

	#endif


	if (!live.isLoaded()) {
		ofDrawBitmapString("ofxAbletonLive has not loaded yet!", 100, 100);
		return;
	}

	// now that live is fully loaded, we can print all the parameters to the screen

	ofDrawBitmapString(live.getTrackString(), 10, 15);
	int x = 200;

	map<int, ofxAbletonLiveTrack*>::iterator it = live.getTracks().begin();
	for (; it != live.getTracks().end(); ++it)
	{
		string trackString = "Track " + ofToString(it->first) + ": \"" + it->second->getName() + "\"\n";
		trackString += it->second->getDevicesInfo();
		trackString += it->second->getClipsInfo();

		map<int, ofxAbletonLiveDevice*>::iterator itd = it->second->getDevices().begin();
		for (; itd != it->second->getDevices().end(); ++itd) {
			trackString += itd->second->getParametersInfo();
		}

		ofDrawBitmapString(trackString, x, 15);
		x += 300;
	}


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	// get info
	if (key == '1')
	{
		// you can print all the available parameters to the console
		live.printAll();

		// or just the tracks
		live.printTracks();
	}

	// live's global properties
	else if (key == '2')
	{
		live.setTempo(88);
		live.setTime(20);
		live.setOverdub(true);
		live.setPan(-0.2);
		live.setVolume(0.8);
		live.setQuantization(4); // 0 = 8 bars, 1 = 4 bars ... 13 = 1/32nd bar
		live.setCrossFader(0.5);
	}

	// global playback controls
	else if (key == '3')
	{
		live.play();
		live.playContinue();
		live.playSelection();
		live.stop();

		live.prevCue();
		live.nextCue();

		live.selectScene(2);    // select 3rd row of clips
	}

	// working with track properties
	else if (key == '4')
	{
		// can get a handle to a track by index or by name.
		// the name and index correspond to what's in live.printTracks().
		// careful! returns NULL if track doesn't exist
		ofxAbletonLiveTrack *trackByIndex = live.getTrack(0);
		ofxAbletonLiveTrack *trackByName = live.getTrack("My Track");

		// tracks have a number of features with getters/setters
		trackByIndex->setVolume(ofRandom(1));
		trackByIndex->setPan(ofRandom(-1, 1));
		trackByIndex->setArmed(false);
		trackByIndex->setMute(false);
		trackByIndex->setSolo(false);
	}

	// get a track's clips
	else if (key == '5')
	{
		ofxAbletonLiveTrack *track = live.getTrack(1);

		// print all the clips we have (index, name)
		track->printClips();

		// grab a reference to a clip, either by index or by name
		ofxAbletonLiveClip *clipByIndex = track->getClip(0);
		ofxAbletonLiveClip *clipByName = track->getClip("Name of my clip");

		// clip actions
		clipByIndex->play();
		clipByIndex->setDetune(-25);  // -50 to 50
		clipByIndex->setTranspose(36);  // -48 to 48
		clipByIndex->setLooping(true);
		clipByIndex->setLoopStart(25.0);
		clipByIndex->setLoopEnd(100.0);
		clipByIndex->setWarp(true);
	}

	// get a track's devices
	else if (key == '6')
	{
		ofxAbletonLiveTrack *track = live.getTrack(0);

		// print all the devices we have (index, name)
		track->printDevices();

		// grab a reference to a device, either by index or by name
		ofxAbletonLiveDevice *deviceByIndex = track->getDevice(0);
		ofxAbletonLiveDevice *deviceByName = track->getDevice("Name of my clip");

		// you can enable/disable devices
		deviceByIndex->setEnabled(false);
	}

	// work with device parameters
	else if (key == '7')
	{
		ofxAbletonLiveTrack *track = live.getTrack(0);
		ofxAbletonLiveDevice *device = track->getDevice(0);

		// get all the parameters belonging to the device
		device->printParameters();

		// get a handle to a parameter by index (note: parameters start at 1, not 0) not name
		ofxAbletonLiveParameter *parameterByIndex = device->getParameter(1);
		ofxAbletonLiveParameter *parameterByName = device->getParameter("Attack");

		// set value of parameter by hand
		parameterByIndex->setValue(0.5);
	}

	// get a track's clips
	else if (key == '8')
	{
		ofxAbletonLiveTrack *track = live.getTrack(0);

		// print all the clips we have (index, name)
		track->printClips();

		// get clip by index or name
		ofxAbletonLiveClip *clipByIndex = track->getClip(0);
		ofxAbletonLiveClip *clipByName = track->getClip("my clip");

		// playback options for clips
		clipByIndex->play();
		clipByIndex->stop();
		clipByIndex->setLoopStart(1.0);
		clipByIndex->setLoopEnd(4.0);
		clipByIndex->setLooping(true);
		clipByIndex->setWarp(false);
		clipByIndex->setTranspose(10); // -48 to 48
		clipByIndex->setDetune(-20);  // -50 to 50
	}

	// refreshing ofxAbletonLive
	else if (key == '9')
	{
		// if you have made changes to your live set, refresh!
		live.refresh();
	}
}

void ofApp::exit()
{
	
	//delete &live;
}
