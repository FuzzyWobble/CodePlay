#ifndef GREG_H
#define GREG_H

#include "ofMain.h"

class greg{

public:
	
	//constructor
	greg();
	
	//variables
	ofImage gregImg;
	int gregHeight, gregWidth;
	
	//functions
	void xenoToPoint(float catchX, float catchY, float spd);
	void draw();
	
	//physics stuff
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f frc;
	float damping;
	void resetForce();
	void addForce(float x, float y);
	void addDampingForce();	
	void setInitialCondition(float px, float py, float vx, float vy);
	void update();
	void bounceOffWalls();
	
	float killBoxX,killBoxY,killBoxWidth,killBoxHeight;
	ofRectangle killBoxGreg;
	
	float xPrev;

};

#endif // 