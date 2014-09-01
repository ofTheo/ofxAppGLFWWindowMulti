#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    winManager.setup((ofxAppGLFWWindowMulti *)ofGetWindowPtr());
    winManager.loadWindowSettings();

    ofSetWindowTitle("main window");

    winManager.createWindow();
    winManager.setWindowTitle(1, "second window");
    winManager.setWindowShape(1, 300, 300);
    winManager.setWindowPosition(1, 0, 0);

    for (int i = 0; i < winManager.getWindowPtr()->getNumActiveWindows(); ++i) {
        mousePos.push_back(ofPoint(0, 0));
        windowSizes.push_back(ofPoint(0, 0));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    int activeWindow = winManager.getActiveWindowNo();

	ofSetColor(255, 255, 255);
    if( activeWindow == 0){
        ofBackground(0, 0, 0);
        ofDrawBitmapString("Window 1\n'f' to toggle fullscreen\nn to open new window", -130 + ofGetWidth()/2, ofGetHeight()/2);
    }else{
        ofBackground(60, 60, 60);
        ofDrawBitmapString("Window " + ofToString(winManager.getActiveWindowNo()), -50 + ofGetWidth()/2, ofGetHeight()/2);
    }

    ofCircle(mousePos[winManager.getActiveWindowNo()], 50);

    ofVec2f size = winManager.getWindowPtr()->getWindowSize(activeWindow);
    ofDrawBitmapString("size: " + ofToString(size), 30, 30);
    ofVec2f pos = winManager.getWindowPtr()->getWindowPosition(activeWindow);
    ofDrawBitmapString("position: " + ofToString(pos), 30, 50);
}

//--------------------------------------------------------------
void ofApp::exit(){
    winManager.saveWindowSettings();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'f' ){
        winManager.toggleFullscreen(winManager.getFocusedWindowNo());
    }else if( key == 'n'){
        winManager.createWindow();
    }else if( key == 'c'){
        winManager.closeFocusedWindow();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    mousePos[winManager.getFocusedWindowNo()].x = x;
    mousePos[winManager.getFocusedWindowNo()].y = y;
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