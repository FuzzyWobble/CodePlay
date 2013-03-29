#pragma once

#include "ofMain.h"
#include "greg.h"
#include "hook.h"
#include "seaparticle.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		//game stuff
		ofImage background; //7868 ~ 1280x6=7680 (shrunk it a bit)
		ofImage background_game; //repeating bg for game
		float posTest;
		float mx,my;
		greg gregObj;
		float bgTotal, bgStep, bgInc;
		void restartGame();
	
		//trackball stuff
		ofSerial serial;
		unsigned char bytesReturned[5]; //reads bytes from arduino: |x1|y1|
		bool firstContact; //write first byte to Arduino	
		int mCount; //message count
		bool bogus_data;
		int x1;
		int y1;	
	
		ofQTKitPlayer gregMovie;
		ofQTKitPlayer bg1, bg2;

		long gameDurationTotal, createdHookTime, gameStartTime, endTimer;
		float createdHookWait;
	
		//fish images and pointers...
		ofImage h1,h2,h3,h4;		
		// let's make a vector of them
		vector <hook> hooks;
	
		bool killedByHook, startScreen;
	
		vector <seaparticle> seaparticles;
	
		int finalScore;
	
		ofImage startScreenImg;
	
};
