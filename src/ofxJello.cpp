#include "ofxJello.h"

ofPtr<ofxJello> ofxJello::singleton;
bool ofxJello::hasSingleton=false;

ofxJello::ofxJello()
{
}

ofxJello::~ofxJello()
{
}

void ofxJello::setGravity(ofPoint p)
{
}

void ofxJello::update()
{
	float time=ofGetElapsedTimef();
	world.update(time-lastTime);
	lastTime=time;
}

void ofxJello::draw()
{

}

ofxJello* ofxJello::get()
{
	if(!hasSingleton) {
		singleton=ofPtr<ofxJello>(new ofxJello());
		hasSingleton=true;
	}
	return singleton.get();
}

