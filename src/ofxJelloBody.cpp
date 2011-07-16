#include "ofxJelloBody.h"
#include "ofxJello.h"

ofxJelloBody::ofxJelloBody()
{

}

ofxJelloBody::~ofxJelloBody()
{
	delete body;
}

void ofxJelloBody::createBody()
{
	body=new Body();
}

void ofxJelloBody::createBody(ofPolyline shape, float massPerPoint, ofPoint position, float rotation, ofPoint scale, bool kinematic)
{
	ClosedShape* sh=ofxJello::ofToShapePtr(shape);
	Vector2 p=ofxJello::ofToVec2(position);
	Vector2 s=ofxJello::ofToVec2(scale);
	body=new Body(sh, massPerPoint, p, rotation, s, kinematic);
}

Body* ofxJelloBody::getBody()
{
	return body;
}

void ofxJelloBody::draw()
{
	ofPushMatrix();
	ofTranslate(getPosition());

	ofPoint s=getScale();
	ofScale(s.x, s.y);
	Vector2* pts=getPoints();
	ofFill();
	ofSetColor(80);
	ofBeginShape();
	for(int i=0; i<getPointsAmount(); i++) {
		ofVertex(pts[i].X, pts[i].Y);
	}
	ofEndShape();
	ofPopMatrix();
}

ofPoint* ofxJelloBody::getOfPoints()
{
	ofPoint* ret=new ofPoint[getPointsAmount()];
	Vector2* pts=getPoints();
	for(int i=0; i<getPointsAmount(); i++) {
		ret[i]=ofxJello::vec2ToOf(pts[i]);
	}
	return ret;
}

Vector2* ofxJelloBody::getPoints()
{
	Vector2* ret=new Vector2[getPointsAmount()];
	for(int i=0; i<getPointsAmount(); i++) {
		ret[i]=body->mPointMasses[i]->Position;
	}
	return ret;
}

int ofxJelloBody::getPointsAmount()
{
	return body->mPointMasses.size();
}

ofPoint ofxJelloBody::getPosition()
{
	return ofxJello::vec2ToOf(body->mDerivedPos);
}

ofPoint ofxJelloBody::getScale()
{
	return ofxJello::vec2ToOf(body->mScale);
}
