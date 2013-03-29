#ifndef SEAPARTICLE_H
#define SEAPARTICLE_H

#include "ofMain.h"

class seaparticle{
public:
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f frc;   
	float lastAngle;
	
	seaparticle();
	virtual ~seaparticle(){};
	
	void resetForce();
	void addForce(float x, float y);
	void addRepulsionForce(float x, float y, float radius, float scale);
	void addAttractionForce(float x, float y, float radius, float scale);
	void addRepulsionForce(seaparticle &p, float radius, float scale);
	void addAttractionForce(seaparticle &p, float radius, float scale);
	void addDampingForce();
	void setInitialCondition(float px, float py, float vx, float vy);
	void update();
	void draw();
	void bounceOffWalls();
	
	float damping;
	
	float size;
	
protected:
private:
};

#endif // 