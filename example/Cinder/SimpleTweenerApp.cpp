#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "SimpleTweener.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SimpleTweenerApp : public AppBasic {
  public:
	void setup();
	void update();
	void draw();
	
	SimpleTweener	tweener_1;
	SimpleTweener	tweener_2;
	float			x;
	float			y;
	float			r;
};

void SimpleTweenerApp::setup()
{
	x=0.f;
	y=500.f;
	r=20.f;
	tweener_1.setup(1.f,				// @duration: tween duration in seconds  - @default: 1.f
					0.5f,				// @delay: delay to start the tween (will also apply to repat BACK_AND_FORTH and LOOP) - @default: 0.f
					&(Sine::easeOut),	// @easingFunc: tween equasion (All PennerEasing equasions are available)  - @default: &(Linear::easeNone)
					BACK_AND_FORTH,		// @repeat: NONE, LOOP or BACK_AND_FORTH - @default: NONE
					&(Sine::easeIn));	// @backEasingFunc: if specified, will be used on the way back (only for repeat BACK_AND_FORTH) - @default: NULL
	
	tweener_1.addTween(&x,				// @var: pointer to the variable we want to tween
					   500);			// @value: value we want to tween to, RELATIVE to the variable initial-value	
	
	tweener_1.addTween(&r, 100.f);		// you can add multiple tweens per tweener
	
	tweener_1.start();
	
	tweener_2.setup(0.5f,				// @duration: tween duration in seconds  - @default: 1.f
					0.f,				// @delay: delay to start the tween (will also apply to repat BACK_AND_FORTH and LOOP) - @default: 0.f
					&(Expo::easeIn),	// @easingFunc: tween equasion (All PennerEasing equasions are available)  - @default: &(Linear::easeNone)
					BACK_AND_FORTH,		// @repeat: NONE, LOOP or BACK_AND_FORTH - @default: NONE
					&(Expo::easeOut));	// @backEasingFunc: if specified, will be used on the way back (only for repeat BACK_AND_FORTH) - @default: NULL
	
	tweener_2.addTween(&y,				// @var: pointer to the variable we want to tween
					   -500.f);			// @value: value we want to tween to, RELATIVE to the variable initial-value
	tweener_2.addTween(&r,				// @var: pointer to the variable we want to tween
					   150.f);			// @value: value we want to tween to, RELATIVE to the variable initial-value	
	
	
	tweener_2.start();
}


void SimpleTweenerApp::update()
{
	// you need to update the tweeners with the delta time of the current frame
	float dt = 1.f / getFrameRate();
	tweener_1.update(dt);
	tweener_2.update(dt);
}

void SimpleTweenerApp::draw()
{
	gl::clear();
	gl::drawSolidCircle(Vec2f(x,y), r);
}


CINDER_APP_BASIC( SimpleTweenerApp, RendererGl )
