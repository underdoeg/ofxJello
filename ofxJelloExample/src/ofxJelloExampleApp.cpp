#include "ofxJelloExampleApp.h"

//--------------------------------------------------------------
void ofxJelloExampleApp::setup(){
	ofSetWindowTitle("ofxJelloExampleApp");
	ofBackground(0,0,0);
}

//--------------------------------------------------------------
void ofxJelloExampleApp::update(){
	jello.update();
}

//--------------------------------------------------------------
void ofxJelloExampleApp::draw(){
	jello.draw();
}

//--------------------------------------------------------------
void ofxJelloExampleApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofxJelloExampleApp::dragEvent(ofDragInfo dragInfo){ 

}
