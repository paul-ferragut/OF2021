#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// print input ports to console
	midiIn.listInPorts();

	// open port by number (you may need to change this)
	midiIn.openPort(0);

	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);

	// add ofApp as a listener
	midiIn.addListener(this);

	// print received messages to the console
	midiIn.setVerbose(true);

}

//--------------------------------------------------------------
void ofApp::update(){
	midiReceive();

}

//--------------------------------------------------------------
void ofApp::draw(){

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
void ofApp::exit() {

	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}
void ofApp::midiReceive()
{

	for (unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];

		int control = message.control;

		if (message.status < MIDI_SYSEX && newMidiMessageB && i == (midiMessages.size() - 1)) {
			
			if (message.status == MIDI_CONTROL_CHANGE) {

				cout << message.control << " value" << message.value << endl;

				switch (control) {
				case 0:
					break;
				case 1:

					break;
				case 2://slider

					break;
				case 3:

					break;
				case 4:

					break;
				case 5:

					break;
				case 6:

					break;
				case 7:

					break;
				case 8:

					break;
				case 9:

					break;
				case 10:

					break;
				case 11:

					break;
				case 12:

					break;
				case 13://knob
					//range is 10 - 118
					doubleMidi = 0;
					break;
				case 14:
					doubleMidi = 0;
					break;
				case 15:
					doubleMidi = 0;
					break;
				case 16:
					doubleMidi = 0;
					break;
				case 17:
					doubleMidi = 0;
					break;
				case 18:
					doubleMidi = 0;
					break;
				case 19:
					doubleMidi = 0;
					break;
				case 20:

					break;
				case 21:

					break;
				case 22:

					break;
				case 23:

					break;
				case 24:

					break;
				case 25:

					break;
				case 26:

					break;
				case 27:

					break;
				case 28:

					break;
				case 29:

					break;
				case 30:

					break;
				case 31:

					break;
				case 32:

					break;
				case 33:

					break;
				case 34:

					break;
				case 35:

					break;
				case 36:

					break;
				case 37:

					break;
				case 38:

					break;
				case 39:

					break;
				case 40:

					break;
				case 41:

					break;
				case 42:

					break;
				case 43:

					break;
				case 44:

					break;
				case 45:

					break;
				case 46:

					break;
				case 47:

					break;
				case 48:

					break;
				case 49:

					break;
				case 50:

					break;
				case 51:

					break;
				case 52:

					break;
				case 53:

					break;
				case 54:

					break;
				case 55:

					break;
				case 56:
					if (message.value == 127) {
						doubleMidi++;
					}
					if (doubleMidi == 2) {
						doubleMidi = 0;
					}
					break;
				case 57:
					if (message.value == 127) {
						doubleMidi++;
					}
					if (doubleMidi == 2) {
						doubleMidi = 0;
					}
					break;
				case 58:

					break;
				case 59:

					break;
				case 60:

					break;
				case 61:

					break;
				case 62:

					break;
				case 63:

					break;
				case 64:

					break;
				case 65:

					break;
				case 66:

					break;
				case 67:

					break;
				case 68:

					break;
				case 69:

					break;
				case 70:

					break;
				case 71:

					break;
				case 72:

					break;
				case 73:

					break;
				case 74:

					break;
				case 75:

					break;
				case 76:

					break;
				case 77:

					break;
				case 78:

					break;
				case 79:

					break;
				case 80:

					break;
				case 81:

					break;
				case 82:

					break;
				case 83:

					break;
				case 84:

					break;
				case 85:

					break;
				case 86:
					//JOG WHEEL
					//cout << message.value << endl;
					break;
				case 87:

					break;
				case 88:

					break;
				case 89:
					break;

				}
				newMidiMessageB = false;
			}
		}
	}
}

void ofApp::newMidiMessage(ofxMidiMessage & msg)
{
	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while (midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}