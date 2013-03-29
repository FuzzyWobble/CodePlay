
#include "seaparticle.h"

//------------------------------------------------------------
seaparticle::seaparticle(){
	setInitialCondition(0,0,0,0);
	damping = 0.13f;
}

//------------------------------------------------------------
void seaparticle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void seaparticle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void seaparticle::addRepulsionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void seaparticle::addAttractionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void seaparticle::addRepulsionForce(seaparticle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this seaparticle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void seaparticle::addAttractionForce(seaparticle & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this seaparticle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
		p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
	
}

//------------------------------------------------------------
void seaparticle::addDampingForce(){
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void seaparticle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void seaparticle::update(){	
	vel = vel + frc;
	pos = pos + vel;
}

//------------------------------------------------------------
void seaparticle::draw(){
	ofEnableAlphaBlending();
	
	//size ranges from 3-8
	
	int numCircles = int(size*1.2);
	float sz,opc;
	
	for(int i=0;i<numCircles;i++){
		sz = (size * (i+1))/3.0; 
		opc = 24-(i*3);
		if(opc<3){opc=3;}
		ofSetColor(50-(i*3),50-(i*3),80-(i*3),opc);
		ofCircle(pos.x, pos.y, sz);
	}	
	
	ofSetColor(255);
	ofDisableAlphaBlending();
}
