#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(20,20,20);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofSetBackgroundAuto(false);

	background_game.loadImage("background_game.png");
	startScreenImg.loadImage("start_screen.png");
	h1.loadImage("hook1.png");
	h2.loadImage("hook2.png");
	h3.loadImage("hook3.png");
	h4.loadImage("hook4.png");
	
	//Arduino
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	serial.setup(5, 57600); //open the device - !change the first number to the correct serial port!
	firstContact = false;
	
	//Movie
	//ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_TEXTURE_ONLY; //no pixel access
	ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
	
	//gregMovie.setPixelFormat(OF_PIXELS_RGBA);
	//bg1.setPixelFormat(OF_PIXELS_RGB);
	//bg2.setPixelFormat(OF_PIXELS_RGB);
	//gregMovie.loadMovie("greg.mov", decodeMode);
	//bg1.loadMovie("background_mov_1_1800x720.mov", decodeMode);
	//bg2.loadMovie("background_mov_2_1800x720.mov", decodeMode);
	//gregMovie.play();
	//bg1.play();
	//bg2.play();
	//bg1.setLoopState(OF_LOOP_NORMAL);
	//bg2.setLoopState(OF_LOOP_NORMAL);

	bgTotal = 0.0;
	bgStep = 6.0;
	bgInc = 0.0035;

	gameDurationTotal = createdHookTime = 0;
	createdHookWait = 2000; //wait at least two seconds between hooks
	gameStartTime = ofGetElapsedTimeMillis();
	
	ofSetLineWidth(2);
	
	killedByHook = false;
	startScreen = true;

	//create sea particles
	for(int i=0;i<50;i++){
		seaparticle aSeaParticle;
		aSeaParticle.size = ofRandom(3,8);
		aSeaParticle.pos.x = ofRandom(-50,1380);
		aSeaParticle.pos.y = ofRandom(70,920);
		seaparticles.push_back(aSeaParticle);
	}
}

//--------------------------------------------------------------
void testApp::update(){
	
	gameDurationTotal = ofGetElapsedTimeMillis()-gameStartTime;
	
	if(killedByHook){
		
	}else if(startScreen){
		
	}else{

		//read trackball from arduino/serial ---------------------------------------------------------
		if(firstContact==false){
			ofSleepMillis(1000); //we need this delay while Arduino gets reads		
			bool byteWasWritten = serial.writeByte('a'); //request data
			if(byteWasWritten){
				firstContact = true;
				cout << "first contact made" << endl;
				ofSleepMillis(2000); 
				bogus_data = false;
			}
		}
		
		if((firstContact==true)&&(serial.available())){
		
			//cout << "serial data available" << endl;
			int bytesNeeded = 5;
			int arrayOffset = 0;
			unsigned char tempArray[5];
			while(bytesNeeded){
				int i;
				int bytesRead = serial.readBytes(tempArray, 5 - arrayOffset);
				for(i = 0; i< bytesRead; i++){
					bytesReturned[arrayOffset] = tempArray[i];
					arrayOffset++;
					bytesNeeded--;
				}
			}
			
			for(int i=0;i<5;i=i+2){
				if(int(bytesReturned[i]) != 124){ //124='|'
					bogus_data = true;	
					cout << "bogus data @ " << i << " -> " << int(bytesReturned[i]) << endl;
					serial.flush(1,1);//flush input
					ofSleepMillis(10);
					break;
				}	
			}
			
			if(bogus_data==false){ //we have good data
				
				//read x1
				if(bytesReturned[1] != 0){
					x1 = int(bytesReturned[1]);
					if(x1>127){
						x1 = x1-256;
					}
				}
				//read, y1
				if(bytesReturned[3] != 0){
					y1 = int(bytesReturned[3]);
					if(y1>127){
						y1 = y1-256;
					}	
				}
				
			} //end bogus data
			
			if(abs(x1)>256){
				x1 = 0;
			}
			if(abs(y1)>256){
				y1 = 0;
			}
			
			bool byteWasWritten = serial.writeByte('a'); //request more data
			if(byteWasWritten){
				bogus_data = false;
			}
			
		} //end serial available
		// end read trackball ----------------------------------------------------
		
		
		// forces on greg -----------------------------
		float scaleForce = 0.25;
		gregObj.resetForce();
		gregObj.addForce(x1*scaleForce,-y1*scaleForce);
		gregObj.addDampingForce();
		gregObj.bounceOffWalls();
		gregObj.update();
		x1=y1=0;
		
		//background move -----------------------------
		bgStep += bgInc;
		if(bgStep >= 16){
			bgStep = 16;
		}
		bgTotal += bgStep;
		
		//hook timer -----------------------------
		createdHookWait -= (bgInc*100);
		if(createdHookWait <= 400){
			createdHookWait = 400;
		}
		
		//create hook -----------------------------
		if( (gameDurationTotal-createdHookTime) > createdHookWait ){ 

			hook aHook;
			int randInt = (int)ofRandom(1,5);
			if(randInt==1){
				aHook.hookImgPointer = &h1;
			}
			if(randInt==2){
				aHook.hookImgPointer = &h2;
			}
			if(randInt==3){
				aHook.hookImgPointer = &h3;
			}
			if(randInt==4){
				aHook.hookImgPointer = &h4;
			}
			aHook.posY_range = ofRandom(0.6,1.4)*(sqrt(gameDurationTotal)/5.0);
			aHook.speed = ofRandom(0.8,1.2)*(sqrt(gameDurationTotal)/250000.0);
			hooks.push_back(aHook);
			createdHookTime = gameDurationTotal;
		}
		
		//never have more than 10 hooks -----------------------------
		if(hooks.size()>10){
			hooks.erase(hooks.begin());
		}
		
		//hooks update -----------------------------
		for (int i = 0; i < hooks.size(); i++){
			hooks[i].update(bgStep,false);
		}
		
		//check if killed by a hook -----------------------------
		for (int i = 0; i < hooks.size(); i++){
			if(gregObj.killBoxGreg.intersects(hooks[i].killBoxHook)){
				killedByHook = true;
				finalScore = int(gameDurationTotal/100.0);
				endTimer = gameDurationTotal;
			}
		}
		
		//sea particle forces -----------------------------
		for (int i = 0; i < seaparticles.size(); i++){
			seaparticles[i].resetForce();
		}
		for (int i = 0; i < seaparticles.size(); i++){
			seaparticles[i].addAttractionForce(-2000, 360, 6000, 2.0*(bgStep/10.0));
		}
		for (int i = 0; i < seaparticles.size(); i++){
			seaparticles[i].addDampingForce();
			seaparticles[i].update();
			
			if(seaparticles[i].pos.x<-100){ //if particle is off screen, delete and create another
				seaparticles.erase(seaparticles.begin()+i);
				seaparticle aSeaParticle;
				aSeaParticle.size = ofRandom(3,8);
				aSeaParticle.pos.x = 1480;
				aSeaParticle.pos.y = ofRandom(70,920);
				seaparticles.push_back(aSeaParticle);
			}
		}
		
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	ofSetColor(255);
	
	if(killedByHook){
		ofBackground(0,0,30);
		ofSetColor(0,0,255);
		ofDrawBitmapString("GAME OVER, FINAL SCORE: "+ofToString(finalScore),530,360);
		if(gameDurationTotal-endTimer > 4000){
			restartGame();
		}
	}else if(startScreen){
		
		ofBackground(0);
		startScreenImg.draw(0,0,1280,720);
		
	}else{

		/*
		// old game stuff
		if(posTest < 7680-ofGetWidth()){
			background.draw(0-posTest,0,7680,720);
			ofDrawBitmapString("----- BACKGROUND: "+ofToString(posTest),10,ofGetHeight()-10);
		}else if( (posTest<7680) && (posTest>=(7680-1280)) ){
			background.draw(0-posTest,0,7680,720);
			background_game.draw(7680-posTest,0,1280,720);
			ofDrawBitmapString("----- GAME START: "+ofToString(posTest),10,ofGetHeight()-10);
		}else{
			int posStep = int(posTest)%1280;
			background_game.draw(1280-posStep,0,1280,720);
			background_game.draw(-posStep,0,1280,720);
			ofDrawBitmapString("----- GAME PLAY: "+ofToString(posTest),10,ofGetHeight()-10);
		}
		*/
		
		ofSetColor(255);
		
		//draw moving background -----------------------------
		int posStep = int(bgTotal)%1280;
		background_game.draw(1280-posStep,0,1280,720);
		background_game.draw(-posStep,0,1280,720);

		ofSetColor(200);
		
		//draw hook line -----------------------------
		for (int i = 0; i < hooks.size(); i++){
			hooks[i].lineDraw();
		}
		
		ofSetColor(255);
		
		ofEnableAlphaBlending();
		
		//draw greg -----------------------------
		gregObj.draw();
		gregObj.xPrev = gregObj.pos.x;
		
		//draw hook -----------------------------
		for (int i = 0; i < hooks.size(); i++){
			hooks[i].draw();
		}
		
		//draw sea particles -----------------------------
		for (int i = 0; i < seaparticles.size(); i++){
			seaparticles[i].draw();
		}
		
		ofDisableAlphaBlending();
			
		ofSetColor(160);
		
		//print on screen -----------------------------
		//ofDrawBitmapString("HOOK WAIT: "+ofToString(createdHookWait),10,ofGetHeight()-70);
		//ofDrawBitmapString("BG STEP: "+ofToString(bgStep),10,ofGetHeight()-55);
		//ofDrawBitmapString("HOOK SPEED: "+ofToString((sqrt(gameDurationTotal)/250000.0)*1000),10,ofGetHeight()-40);
		//ofDrawBitmapString("HOOK RANGE: "+ofToString(sqrt(gameDurationTotal)/5.0),10,ofGetHeight()-25);
		int difficulty = int( (bgStep * (sqrt(gameDurationTotal)/5.0) * (10000/createdHookWait)) / 1000 ) + 1;
		ofDrawBitmapString("DIFFICULTY: "+ofToString(difficulty)+"/25",10,ofGetHeight()-25);
		ofDrawBitmapString("SCORE: "+ofToString(int(gameDurationTotal/100.0)),10,ofGetHeight()-10);
		
	}
}

//--------------------------------------------------------------
void testApp::restartGame(){
	bgStep = 6.0;
	bgTotal = 0;
	gameDurationTotal = createdHookTime = 0;
	createdHookWait = 2000; 
	killedByHook = false;
	startScreen = true;
	seaparticles.clear();
	for(int i=0;i<50;i++){
		seaparticle aSeaParticle;
		aSeaParticle.size = ofRandom(3,8);
		aSeaParticle.pos.x = ofRandom(-50,1380);
		aSeaParticle.pos.y = ofRandom(70,920);
		seaparticles.push_back(aSeaParticle);
	}
	hooks.clear();
	gregObj.pos.x = 100;
	gregObj.pos.y = 100;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(startScreen==true){
		gameStartTime = ofGetElapsedTimeMillis();
		startScreen = false;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

