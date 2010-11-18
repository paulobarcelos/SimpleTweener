/*
 *  SimpleTweener
 *	A fat free tweening engine.
 *
 *  Created by Paulo Barcelos on 05/11/10.
 *  Copyleft. Don't be a jerk, share your code.
 *
 *	http://www.paulobarcelos.com
 */


#ifndef _SIMPLE_TWEENER
#define _SIMPLE_TWEENER
#include <vector>
using namespace std;
#include "PennerEasing/PennerEasing.h"
////////////////////////////////////////////////////////////
// TYPDEFS -------------------------------------------------
////////////////////////////////////////////////////////////
struct TweenObject{
    float*	var;
	float	offset;
	float	lastIncrement;
	
	float	incrementMonitor;
	
	bool negativeOffset;
};
////////////////////////////////////////////////////////////
// CONSTANTS -------------------------------------------------
////////////////////////////////////////////////////////////
enum TweenRepeat {
	NONE = 0,
	LOOP,
	BACK_AND_FORTH,
};
////////////////////////////////////////////////////////////
// CLASS DECLARATION ---------------------------------------
////////////////////////////////////////////////////////////
class SimpleTweener{
public:
	SimpleTweener();
	void	addTween(float* var, float value);
	void	clearTweens();
	void	setup(float duration, float delay = 0.f, float(*easingFunc)(float t, float b, float c, float d) = &(Linear::easeNone), int repeat = 0, bool repeatDelay = true, float(*backEasingFunc)(float t, float b, float c, float d) = NULL);
	void	start();
	void	update(float dt);
	float	getDuration();
	void	setProgress(float progress);
	float	getProgress();
	bool	isStarted();
	bool	isComplete();
private:

	void	resetValues();
	void	invertValues();
	vector<TweenObject*> tweenObjects;
	float(*	easingFunc)(float t, float b, float c, float d);
	float(*	backEasingFunc)(float t, float b, float c, float d);
	float	duration;
	float	delay;
	int		repeat;
	bool	repeatDelay;
	float	curTime;
	bool	complete;
	bool	started;
	bool	_firstTime;
};
#endif
