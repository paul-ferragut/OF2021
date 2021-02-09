#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
/*Demo with arduino connected to Adafruit BNO055 Absolute Orientation Sensor sending through Serial

Arduino Sketch:

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  delay(500);
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Orientation Sensor Test"); Serial.println("");


if (!bno.begin())
{
	
	Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
	while (1);
}

delay(1000);


bno.setExtCrystalUse(true);


displaySensorDetails();
}

void loop(void)
{

	sensors_event_t event;
	bno.getEvent(&event);

	Serial.print(F("Orientation: "));
	Serial.print((float)event.orientation.x);
	Serial.print(F(" "));
	Serial.print((float)event.orientation.y);
	Serial.print(F(" "));
	Serial.print((float)event.orientation.z);
	Serial.println(F(""));

	uint8_t sys, gyro, accel, mag = 0;
	bno.getCalibration(&sys, &gyro, &accel, &mag);

	delay(BNO055_SAMPLERATE_DELAY_MS);
}

*/
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofSerial serial;

		string message;

		float roll;
		float pitch;
		float yaw;

		ofxAssimpModelLoader model;
		ofLight light;

};
