#include "Sine.h"

float Sine::easeIn (float t,float b , float c, float d) {
	return float(-c * cosf(t/d * (PI/2)) + c + b);
}
float Sine::easeOut(float t,float b , float c, float d) {	
	return float(c * sinf(t/d * (PI/2)) + b);	
}

float Sine::easeInOut(float t,float b , float c, float d) {
	return float(-c/2 * (cosf(PI*t/d) - 1) + b);
}