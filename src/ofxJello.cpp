#include "ofxJello.h"

/*
ofPtr<ofxJello> ofxJello::singleton;
bool ofxJello::hasSingleton=false;
*/
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
	bodyList::iterator it=bodies.begin();
	while(it!=bodies.end()){
		(*it)->draw();
		++it;
	}
}

void ofxJello::addBody(ofxJelloBody* body)
{
	bodies.push_back(body);
	world.addBody(body->getBody());
}

Vector2 ofxJello::ofToVec2(ofPoint p)
{
	return Vector2(p.x, p.y);
}

Vector3 ofxJello::ofToVec3(ofPoint p)
{
	return Vector3(p.x, p.y, p.z);
}

ofPoint ofxJello::vec2ToOf(Vector2 v)
{
	return ofPoint(v.X, v.Y);
}

ofPoint ofxJello::vec3ToOf(Vector3 v)
{
	return ofPoint(v.X, v.Y, v.Z);
}

ClosedShape* ofxJello::ofToShapePtr(ofPolyline p)
{
	ClosedShape* shape=new ClosedShape();
	shape->begin();
	std::vector<ofPoint>::iterator it=p.getVertices().begin();
	while(it!=p.getVertices().end()){
		shape->addVertex(ofToVec2(*it));
		++it;
	}
	shape->finish();
	return shape;
}

/*
ofxJello* ofxJello::get()
{
	if(!hasSingleton) {
		singleton=ofPtr<ofxJello>(new ofxJello());
		hasSingleton=true;
	}
	return singleton.get();
}
*/
