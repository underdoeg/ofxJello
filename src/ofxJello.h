#ifndef OFXJELLO_H
#define OFXJELLO_H

#include "ClosedShape.h"
#include "ofMain.h"
#include "ofxJelloBody.h"
#include "World.h"

typedef std::vector<ofxJelloBody*> bodyList;

class ofxJello {

public:
	ofxJello();
	~ofxJello();
	void addBody(ofxJelloBody* body);
	void setGravity(ofPoint p);
	void update();
	void draw();

	static Vector2 ofToVec2(ofPoint p);
	static Vector3 ofToVec3(ofPoint p);
	static ofPoint vec2ToOf(Vector2 v);
	static ofPoint vec3ToOf(Vector3 v);
	static ClosedShape* ofToShapePtr(ofPolyline p);

private:
	/*
	static ofPtr<ofxJello> singleton;
	static bool hasSingleton;
	static ofxJello* get();
	*/
	bodyList bodies;
	World world;
	float lastTime;
};

#endif // OFXJELLO_H
