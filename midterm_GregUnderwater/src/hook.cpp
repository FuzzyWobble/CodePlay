#include "hook.h"

//------------------------------------------------------------------
hook::hook(){
	hookWidth = 70;
	hookHeight = 100;
	pos.x = 1400;
	pos.y = ofRandom(70,760-hookHeight);
	//speed and posY_range defined in testApp.cpp
}

//------------------------------------------------------------------
void hook::draw(){
	hookImgPointer->draw(pos.x,posY_sin,hookWidth,hookHeight);
//	ofNoFill();
//	ofSetColor(255,0,0);
//	ofRect(killBoxX,killBoxY,killBoxWidth,killBoxHeight);
//	ofSetColor(255);
//	ofFill();
}

//------------------------------------------------------------------
void hook::lineDraw(){
	ofLine(pos.x+(hookWidth/2.0)-1, 65, pos.x+(hookWidth/2.0)-1, posY_sin+10);
}

//------------------------------------------------------------------
void hook::update(float bgStep, bool moving){
	pos.x -= bgStep; //move hook at the same speed as the background
	posY_sin = pos.y + sin(ofGetElapsedTimeMillis()*speed)*posY_range;
	
	if(posY_sin<65){ //prevent from being drawn above the water
		posY_sin=65;
	}
	
	killBoxX = pos.x+10;
	killBoxY = posY_sin+25;
	killBoxWidth = hookWidth-20;
	killBoxHeight = hookHeight-25;
	killBoxHook.set(killBoxX,killBoxY,killBoxWidth,killBoxHeight);
}