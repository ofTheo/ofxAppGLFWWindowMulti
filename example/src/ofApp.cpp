#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //NOTE IF THIS DOESN'T COMPILE FOR YOU ON OS X
    //YOU NEED TO SET THE FILE TYPE OF ofxAppGLFWWindowMulti.cpp to Objective C++ Source
    //OR RENAME THE FILE ofxAppGLFWWindowMulti.mm

    winManager.setup((ofxAppGLFWWindowMulti *)ofGetWindowPtr());
    winManager.loadWindowSettings();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
    if( winManager.getActiveWindowNo() == 0){
        ofBackground(0, 0, 0);
        ofDrawBitmapString("Window 1\n'f' to toggle fullscreen\nn to open new window", -130 + ofGetWidth()/2, ofGetHeight()/2);
    }else{
        ofBackground(60, 60, 60);
        ofDrawBitmapString("Window " + ofToString(winManager.getActiveWindowNo()), -50 + ofGetWidth()/2, ofGetHeight()/2);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    winManager.saveWindowSettings();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'f' ){
        ofToggleFullscreen();
    }else if( key == 'n'){
        winManager.createWindow();
    }else if( key == 'c'){
        winManager.closeActiveWindow();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}