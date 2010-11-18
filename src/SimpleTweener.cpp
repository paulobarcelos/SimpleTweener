/*
 *  SimpleTweener
 *	A fat free tweening engine.
 *
 *  Created by Paulo Barcelos on 05/11/10.
 *  Copyleft. Don't be a jerk, share your code.
 *
 *	http://www.paulobarcelos.com
 */
#include "SimpleTweener.h"
////////////////////////////////////////////////////////////
// CONSTRUCTOR ---------------------------------------------
////////////////////////////////////////////////////////////
SimpleTweener::SimpleTweener(){
	easingFunc = NULL;
	backEasingFunc = NULL;
	duration = 0.f;
	delay = 0.f;
	repeat = NONE;
	repeatDelay = false;
	curTime = 0;
	started = false;
	complete = false;
	_firstTime = true;
}
////////////////////////////////////////////////////////////
// addTween ------------------------------------------------
////////////////////////////////////////////////////////////
//void SimpleTweener::addTween(float * var, float initValue, float finalValue, bool relative){
void SimpleTweener::addTween(float * var, float value){
	TweenObject * tweenObject = new TweenObject();
	tweenObject->var = var;
	tweenObject->offset = value;
	tweenObject->incrementMonitor = 0;
	tweenObject->negativeOffset = (value<0);
	tweenObjects.push_back(tweenObject);
}

////////////////////////////////////////////////////////////
// clearTweens ---------------------------------------------
////////////////////////////////////////////////////////////
void SimpleTweener::clearTweens(){
	int i = tweenObjects.size();
	while(--i>=0){
       delete tweenObjects[0];
       tweenObjects.erase(tweenObjects.begin());
	}
}
////////////////////////////////////////////////////////////
// setup ---------------------------------------------------
////////////////////////////////////////////////////////////
void SimpleTweener::setup(float duration, float delay, float(*easingFunc)(float t, float b, float c, float d),int repeat, bool repeatDelay, float(*backEasingFunc)(float t, float b, float c, float d)){
	this->duration = duration;
	this->delay = delay;
	this->easingFunc = easingFunc;
	this->backEasingFunc = backEasingFunc;
	this->repeat = repeat;
	this->repeatDelay = repeatDelay;
	this->started = false;
	this->complete = false;
	this->_firstTime = true;
}
////////////////////////////////////////////////////////////
// start -------------------------------------------------
////////////////////////////////////////////////////////////
void SimpleTweener::start(){
	started = true;
	complete = false;
	if(_firstTime) curTime = -delay;
	else curTime = repeatDelay ? -delay:0; 
	_firstTime = false;
	for(vector<TweenObject*>::iterator it = tweenObjects.begin(); it != tweenObjects.end(); it++) (*it)->lastIncrement = 0;
}
////////////////////////////////////////////////////////////
// update --------------------------------------------------
////////////////////////////////////////////////////////////
void SimpleTweener::update(float dt){
	if(started && !complete)
	{
		curTime += dt;
		curTime = (curTime>duration)?duration:curTime;
		complete = (curTime>=duration);
		if(curTime > 0) // we wanna make sure to don't do anything during the delay time
		{	
			for(vector<TweenObject*>::iterator it = tweenObjects.begin(); it != tweenObjects.end(); it++)
			{
				float curIncrement = (*easingFunc)(curTime,0.f,(*it)->offset,duration);
				float deltaIncrement = curIncrement - (*it)->lastIncrement;
				(*it)->lastIncrement = curIncrement;						
				// As the dt is not 100% precise, at the end of the tween need to make a tiny adjustment in the deltaIncrement...
				if(complete){	
					// This is far from being the most clean and optimized way to calculate the adjsutment... but my deadline is coming. TODO!
					float dAbsOffset = (fabs((*it)->offset)-(*it)->offset)*0.5f;
					float absIncrementMonitor = fabs((*it)->incrementMonitor);
					float absDeltaIncrement;
					if(!(*it)->negativeOffset) absDeltaIncrement = fabs((*it)->offset) - fabs(dAbsOffset - fabs(absIncrementMonitor));
					else absDeltaIncrement = fabs(dAbsOffset - fabs(absIncrementMonitor));
					
					deltaIncrement = ((*it)->offset < 0.f) ? - absDeltaIncrement: absDeltaIncrement;
				
				}						
				*((*it)->var) += deltaIncrement;
				(*it)->incrementMonitor += deltaIncrement;
			}
		}
			
	
		if(complete)
		{
			switch (repeat) {
				case LOOP:
					resetValues();
					start();
					break;
				case BACK_AND_FORTH:
					invertValues();
					start();
					break;
				default:
					clearTweens();
			}
		}
	}
}
////////////////////////////////////////////////////////////
// resetValues --------------------------------------------
////////////////////////////////////////////////////////////
void SimpleTweener::resetValues(){	
	for(vector<TweenObject*>::iterator it = tweenObjects.begin(); it != tweenObjects.end(); it++)
	{
		*((*it)->var) -= (*it)->offset;
		(*it)->incrementMonitor -= (*it)->offset;
	}
}
////////////////////////////////////////////////////////////
// invertValues --------------------------------------------
////////////////////////////////////////////////////////////
void SimpleTweener::invertValues(){	
	for(vector<TweenObject*>::iterator it = tweenObjects.begin(); it != tweenObjects.end(); it++) (*it)->offset = -(*it)->offset;
	if (backEasingFunc != NULL)
	{
		float(*tempEasingFunc)(float t, float b, float c, float d) = easingFunc;
		easingFunc = backEasingFunc;
		backEasingFunc = tempEasingFunc;
	}
}
////////////////////////////////////////////////////////////
// setProgress ---------------------------------------------
////////////////////////////////////////////////////////////
void SimpleTweener::setProgress(float progress){
	if(progress<0)progress = 0;
	else if(progress>1) progress = 1;
	
	curTime = progress * duration;
}
////////////////////////////////////////////////////////////
// getProgress ---------------------------------------------
////////////////////////////////////////////////////////////
float SimpleTweener::getProgress(){
	return ((curTime/duration)>1)?1:(curTime/duration);
}
////////////////////////////////////////////////////////////
// getDuration ---------------------------------------------
////////////////////////////////////////////////////////////
float SimpleTweener::getDuration(){
	return duration;
}
////////////////////////////////////////////////////////////
// isStarted ----------------------------------------------
////////////////////////////////////////////////////////////
bool SimpleTweener::isStarted(){
	return started;
}
////////////////////////////////////////////////////////////
// isComplete ----------------------------------------------
////////////////////////////////////////////////////////////
bool SimpleTweener::isComplete(){
	return complete;
}