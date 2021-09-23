#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

		int loadSettingFile();
		string getCurrentDate();
		string getCurrentTime();

		ofxOscReceiver rcv;
		int chk;
		int PORT_TO_FW_APP;
		string FW_APP_IP;
		
};
