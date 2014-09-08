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
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    int activeWindow = winManager.getActiveWindowNo();
    int focusedWindow = winManager.getFocusedWindowNo();
    /*
     draw() loops through all windows, changing the value of activeWindow
     so we can do a comparison, or switch statement
    */

	ofSetColor(255, 255, 255);
    if( activeWindow == 0){
        ofBackground(0, 0, 0);
        ofDrawBitmapString("Window 1\n'f' to toggle fullscreen\nn to open new window", -130 + ofGetWidth()/2, ofGetHeight()/2);
    }else{
        ofBackground(60, 60, 60);
        ofDrawBitmapString("Window " + ofToString(activeWindow), -50 + ofGetWidth()/2, ofGetHeight()/2);
    }

    // Drawing on all active windows.
    ofVec2f shape = winManager.getWindowShape(activeWindow);
    ofDrawBitmapString("size: " + ofToString(shape), 30, 30);
    ofVec2f pos = winManager.getWindowPosition(activeWindow);
    ofDrawBitmapString("position: " + ofToString(pos), 30, 50);

    // Only draw on the focused window
    if ( activeWindow == focusedWindow) {
        string x = ofToString(ofGetMouseX());
        string y = ofToString(ofGetMouseY());

        ofDrawBitmapString("mouse: " + x + ", " + y, 30, 80);
    }

}

//--------------------------------------------------------------
void ofApp::exit(){
    winManager.saveWindowSettings();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'f' ){
        // winManager provides direct access to many window functions
        winManager.toggleFullscreen(winManager.getFocusedWindowNo());
    }else if( key == 'n'){
        winManager.createWindow();
    }else if( key == 'c'){
        winManager.closeFocusedWindow();
    }else if( key == 't'){
        /*
         pushWindow(windowNo) and popWindow() can switch the active window,
         now standard oF methods will refer to that specific window
        */
        winManager.pushWindow(1);
        ofLog() << "window 1 size:" << ofGetWindowSize();
        winManager.popWindow();
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