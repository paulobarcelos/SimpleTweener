
#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "SimpleTweener.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void keyPressed( int key );
	
	SimpleTweener	tweener_1;
	SimpleTweener	tweener_2;
	float			x;
	float			y;
	float			r;
};

#endif
