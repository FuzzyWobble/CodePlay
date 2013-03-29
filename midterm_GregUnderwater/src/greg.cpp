

#include "greg.h"

//------------------------------------------------------------------
greg::greg(){
	gregImg.loadImage("greg.png");
	setInitialCondition(100,100,0,0);
	gregWidth = 200;
	gregHeight = 145;
	damping = 0.15f;
}

//------------------------------------------------------------------
void greg::xenoToPoint(float catchX, float catchY, float spd){
	
	pos.x = spd * catchX + (1-spd) * pos.x; 
	pos.y = spd * catchY + (1-spd) * pos.y;
	
}

//------------------------------------------------------------------
void greg::draw(){

	if(xPrev>pos.x){ //greg switched directions
        ofPushMatrix();
        ofScale(-1,1);
        gregImg.draw(-pos.x-gregWidth,pos.y,gregWidth,gregWidth*0.70);
        ofPopMatrix(); 
    }else{
        gregImg.draw(pos.x,pos.y,gregWidth,gregWidth*0.70); 
    }
	
//	gregImg.draw(pos.x,pos.y,gregWidth,gregHeight);
//	ofNoFill();
//	ofSetColor(255,0,0);	
//	ofRect(killBoxX,killBoxY,killBoxWidth,killBoxHeight);
//	ofSetColor(255);
//	ofFill();
}	

//------------------------------------------------------------------
void greg::resetForce(){
    frc.set(0,0);
}

//------------------------------------------------------------------
void greg::addForce(float x, float y){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void greg::addDampingForce(){
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void greg::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void greg::update(){	
	vel = vel + frc;
	pos = pos + vel;
	
	if(xPrev>pos.x){ //greg switched directions
		killBoxX = pos.x+10;	
	}else{
		killBoxX = pos.x+60;	
	}
	
	killBoxY = pos.y+65;
	killBoxWidth = gregWidth-70;
	killBoxHeight = gregHeight-95;
	killBoxGreg.set(killBoxX,killBoxY,killBoxWidth,killBoxHeight);
}

//------------------------------------------------------------
void greg::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x+gregWidth > maxx){
		pos.x = maxx-gregWidth; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (pos.y+gregHeight > maxy){
		pos.y = maxy-gregHeight; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}
