#ifndef HOOK_H
#define HOOK_H

#include "ofMain.h"

class hook{
	
public:
	
	//constructor
	hook();
	
	void draw();
	void lineDraw();
	void update(float bgStep, bool moving);
	
	ofImage *hookImgPointer;
	ofVec2f pos;
	int hookWidth, hookHeight;
	float posY_sin;
	float posY_range;
	float speed;
	
	float killBoxX,killBoxY,killBoxWidth,killBoxHeight;
	ofRectangle killBoxHook;
	
};

#endif // 