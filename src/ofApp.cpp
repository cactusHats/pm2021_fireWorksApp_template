#include "ofApp.h"
#include "define.h"
#include "confReader.hpp"

//--------------------------------------------------------------
void ofApp::setup(){

	// Load setting file
	chk = loadSettingFile();
	if (chk == int(PROCESS_RESULT::LOAD_SETTINGFILE_ERROR)) {
		printf("Setting file load error\n");
		exit();
	}

	// Set osc port
	chk = rcv.setup(PORT_TO_FW_APP);
	if (chk == false) {
		printf("Osc setting error\n");
		exit();
	}

	printf("Settings complete!\n");
}

//--------------------------------------------------------------
void ofApp::update(){

	while (rcv.hasWaitingMessages()) {

		ofxOscMessage m;
		rcv.getNextMessage(&m);

		// for fireworks control
		if (m.getAddress() == "/fireWorks/launchData") {
			
			// Get fireworks type 0~6
			int type = m.getArgAsInt(0);

			switch (type) {
			case 0:
				cout << "Type0 launched" << endl;
				break;
			case 1:
				cout << "Type1 launched" << endl;
				break;
			case 2:
				cout << "Type2 launched" << endl;
				break;
			case 3:
				cout << "Type3 launched" << endl;
				break;
			case 4:
				cout << "Type4 launched" << endl;
				break;
			case 5:
				cout << "Type5 launched" << endl;
				break;
			case 6:
				cout << "Type6 launched" << endl;
				break;
			default:
				cout << "Default" << endl;
				break;
			}
		}
		// for connection test msg
		else if (m.getAddress() == "/fireWorks/testMessage") {
			printf("%s %s Receive connection test msg\n", 
				getCurrentDate().c_str(), 
				getCurrentTime().c_str());
		}
	}
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
int ofApp::loadSettingFile() {

	//-- Load setting file --
	ifstream infile("./data/setting.conf"); //.exe‚©‚ç‹N“®‚·‚é‚Æ‚«
	string separator = conf::setSeparetor(",", "=", "\\s");

	if (infile) {
		conf::setMap(conf::config_map, infile, separator);
	}
	else {
		return int(PROCESS_RESULT::LOAD_SETTINGFILE_ERROR);
	}
	//-- Load setting value --
	PORT_TO_FW_APP = conf::readMap("PORT_TO_FW_APP");
	string fwAppIp = conf::readMap("FW_APP_IP"); 
	FW_APP_IP = fwAppIp;

	//-- Show setting value --
	printf("------ SETTING VALUES ------\n");
	printf("PORT_TO_FW_APP = %d\n", PORT_TO_FW_APP);
	printf("FW_APP_IP = %s\n", FW_APP_IP);
	printf("---------------------------\n");

	return int(PROCESS_RESULT::PROCESS_SUCCESS);
}

//--------------------------------------------------------------
string ofApp::getCurrentDate() {
	time_t timeValue;
	struct tm *timeObject;
	stringstream currentTime;

	time(&timeValue);
	timeObject = localtime(&timeValue);

	int Y = timeObject->tm_year - 100; //20XX”N >> XX
	int M = timeObject->tm_mon + 1;
	int D = timeObject->tm_mday;

	// setw(),setfill()‚Å0‹l‚ß
	currentTime << setw(2) << setfill('0') << Y << "/";
	currentTime << setw(2) << setfill('0') << M << "/";
	currentTime << setw(2) << setfill('0') << D;

	return currentTime.str();
}

//--------------------------------------------------------------
string ofApp::getCurrentTime() {
	time_t timeValue;
	struct tm *timeObject;
	stringstream currentTime;

	time(&timeValue);
	timeObject = localtime(&timeValue);

	int h = timeObject->tm_hour;
	int m = timeObject->tm_min;
	int s = timeObject->tm_sec;

	// setw(),setfill()‚Å0‹l‚ß
	currentTime << setw(2) << setfill('0') << h << ":";
	currentTime << setw(2) << setfill('0') << m << ":";
	currentTime << setw(2) << setfill('0') << s;

	return currentTime.str();
}