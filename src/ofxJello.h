#ifndef OFXJELLO_H
#define OFXJELLO_H

#include "ofMain.h"
#include "ofxJelloBody.h"
#include "World.h"

class ofxJello {

public:
	ofxJello();
	~ofxJello();
	void addBody(ofxJelloBody* body);
	void setGravity(ofPoint p);
	void update();
	void draw();

	static ofxJello* get();

private:
	static ofPtr<ofxJello> singleton;
	static bool hasSingleton;
	World world;
	float lastTime;
};

#endif // OFXJELLO_H
