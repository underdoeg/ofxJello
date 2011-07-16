#ifndef OFXJELLOBODY_H
#define OFXJELLOBODY_H

#include "ofMain.h"
#include "Body.h"

class ofxJelloBody {

public:
	ofxJelloBody();
	~ofxJelloBody();
	virtual void createBody();
	virtual void createBody(ofPolyline shape, float massPerPoint=1, ofPoint position=ofPoint(0,0), float rotation=0, ofPoint scale=ofPoint(1,1), bool kinematic=false);

	int getPointsAmount();
	Vector2* getPoints();
	ofPoint* getOfPoints();//this is actually slower
	ofPoint getPosition();
	ofPoint getScale();

	Body* getBody();

	virtual void draw();
private:
	Body* body;
};

#endif // OFXJELLOBODY_H
