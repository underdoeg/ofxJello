#include "ofxJelloSpringBody.h"

void ofxJelloSpringBody::createBody()
{
	body=new SpringBody();
}
void ofxJelloSpringBody::createBody(ofPolyline shape, float massPerPoint, ofPoint position, float rotation, ofPoint scale, bool kinematic)
{
}