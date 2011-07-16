#ifndef OFXJELLOSPRINGBODY_H
#define OFXJELLOSPRINGBODY_H

#include "SpringBody.h"
#include "ofxJelloBody.h" // Base class: ofxJelloBody

class ofxJelloSpringBody : public ofxJelloBody
{

public:
	void createBody();
	void createBody(ofPolyline shape, float massPerPoint = 1, ofPoint position = ofPoint(0,0), float rotation = 0, ofPoint scale = ofPoint(1,1), bool kinematic = false);

	SpringBody* getBody();

private:
	SpringBody body;
};

#endif // OFXJELLOSPRINGBODY_H
