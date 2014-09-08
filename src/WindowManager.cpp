//
//  WindowManager.cpp
//
//  Created by Theodore Watson on 6/18/14.
//
//

#define UNSET_ERR "windowPtr needs to be set";

#include "WindowManager.h"

WindowManager::WindowManager(){
    windowPtr = NULL;
}

//--------------------------------------------------------------
void WindowManager::setup(ofxAppGLFWWindowMulti * ptr){
    if (ptr == NULL) {
        ofLogError("WindowManager::setup") << UNSET_ERR;
    }
    windowPtr = ptr;
    machineString = "default";
    if( getenv("USER") != NULL ) {
        machineString = getenv("USER");
    }
}

//--------------------------------------------------------------
ofxAppGLFWWindowMulti * WindowManager::getWindowPtr(){
    if ( windowPtr == NULL) {
        ofLogError("WindowManager::getWindowPtr") << UNSET_ERR;
    }
    return windowPtr;
}

//--------------------------------------------------------------
int WindowManager::getActiveWindowNo(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::getActiveWindowNo") << UNSET_ERR;
        return -1;
    }
    return windowPtr->getCurrentWindowNo();
}

//--------------------------------------------------------------
int WindowManager::getFocusedWindowNo(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::getFocusedWindowNo") << UNSET_ERR;
        return -1;
    }
    return windowPtr->getFocusedWindowNo();
}
//--------------------------------------------------------------
void WindowManager::createWindow(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::createWindow") << UNSET_ERR;
        return;
    }
    windowPtr->addWindow();
}

//--------------------------------------------------------------
void WindowManager::setWindowTitle(int windowNo, string title){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setWindowTitle") << UNSET_ERR;
        return;
    }
    windowPtr->setWindowTitle(windowNo, title);
}

//--------------------------------------------------------------
void WindowManager::setWindowPosition(int windowNo, int x, int y){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setWindowPosition") << UNSET_ERR;
        return;
    }
    windowPtr->setWindowPosition(windowNo, x, y);
}

//--------------------------------------------------------------
void WindowManager::setWindowShape(int windowNo, int w, int h){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setWindowShape") << UNSET_ERR;
        return;
    }
    windowPtr->setWindowShape(windowNo, w, h);
}

//--------------------------------------------------------------
ofPoint WindowManager::getWindowPosition(int windowNo){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::getWindowPosition") << UNSET_ERR;
        return ofPoint(0, 0);
    }
    return windowPtr->getWindowPosition(windowNo);
}

//--------------------------------------------------------------
ofPoint WindowManager::getWindowShape(int windowNo){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::getWindowShape") << UNSET_ERR;
        return ofPoint(0, 0);
    }
    return windowPtr->getWindowSize(windowNo);
}
//--------------------------------------------------------------
ofPoint WindowManager::getScreenSize(int windowNo){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::getScreenSize") << UNSET_ERR;
        return ofPoint(0, 0);
    }
    return windowPtr->getScreenSize(windowNo);
}

//--------------------------------------------------------------
void WindowManager::setFullscreen(int windowNo, bool fullscreen){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setFullscreen") << UNSET_ERR;
        return;
    }
    windowPtr->setFullscreen(windowNo, fullscreen);
}

//--------------------------------------------------------------
void WindowManager::toggleFullscreen(int windowNo){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::toggleFullscreen") << UNSET_ERR;
        return;
    }
    windowPtr->toggleFullscreen(windowNo);
}

//--------------------------------------------------------------
int WindowManager::getWindowMode(int windowMode){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::getWindowMode") << UNSET_ERR;
        return OF_WINDOW;
    }

    return windowPtr->getWindowMode(windowMode);
}

//--------------------------------------------------------------
void WindowManager::closeFocusedWindow(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::closeFocusedWindow") << UNSET_ERR;
        return;
    }
    windowPtr->closeWindow(getFocusedWindowNo());
}

//--------------------------------------------------------------
void WindowManager::closeWindow(int which){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::closeWindow") << UNSET_ERR;
        return;
    }
    windowPtr->closeWindow(which);
}

//--------------------------------------------------------------
void WindowManager::loadWindowSettings(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::loadWindowSettings") << UNSET_ERR;
        return;
    }

    vector < shared_ptr<AppGLFWSingleWindow> > windows = windowPtr->getWindows();

    windowPosXml.clear();
    if(windowPosXml.loadFile("settings/Window/windowSettings-"+machineString+".xml")){
        int numTags = windowPosXml.getNumTags("window");

        for(int i = windows.size(); i < numTags; i++){
            windowPtr->addWindow("Window "+ofToString(i,0), 100, 100, 400, 400, false);
        }

        windows = windowPtr->getWindows();

        int numToLoad = MIN(windows.size(), numTags);

        ofRectangle winBounds;
        ofRectangle fsBounds;

        for(int i = 0; i < numToLoad; i++){
            if( windowPosXml.pushTag("window", i) ){

                fsBounds.x           = windowPosXml.getAttribute("fullscreen-rect", "x", (int)windows[i]->fullScreenBounds.x);
                fsBounds.y           = windowPosXml.getAttribute("fullscreen-rect", "y", (int)windows[i]->fullScreenBounds.y);
                fsBounds.width       = windowPosXml.getAttribute("fullscreen-rect", "width", (int)windows[i]->fullScreenBounds.width);
                fsBounds.height      = windowPosXml.getAttribute("fullscreen-rect", "height", (int)windows[i]->fullScreenBounds.height);

                winBounds.x          = windowPosXml.getAttribute("window-rect", "x", (int)windows[i]->windowBounds.x);
                winBounds.y          = windowPosXml.getAttribute("window-rect", "y", (int)windows[i]->windowBounds.y);
                winBounds.width      = windowPosXml.getAttribute("window-rect", "width", (int)windows[i]->windowBounds.width);
                winBounds.height     = windowPosXml.getAttribute("window-rect", "height", (int)windows[i]->windowBounds.height);

                windowPosXml.popTag();

                if( windowPtr->pushWindow(i) ){

                    if( windowPosXml.getAttribute("window", "fullscreen", 0, i) ){
                        ofSetFullscreen(false);
                        ofSetWindowPosition(fsBounds.x+1, fsBounds.y);
                        ofSetFullscreen(true);

                        windows[i]->windowBounds = winBounds;
                    }else{
                        ofSetFullscreen(false);
                        ofSetWindowShape(winBounds.width, winBounds.height);
                        ofSetWindowPosition(winBounds.x, winBounds.y);
                        windows[i]->fullScreenBounds = fsBounds;
                    }

                    windowPtr->popWindow();
                }
            }

        }
    }

}

//--------------------------------------------------------------
void WindowManager::saveWindowSettings(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::saveWindowSettings") << UNSET_ERR;
        return;
    }

    if( ofDirectory::doesDirectoryExist("settings") == false){
        ofDirectory::createDirectory("settings");
    }
    if( ofDirectory::doesDirectoryExist("settings/Window") == false){
        ofDirectory::createDirectory("settings/Window");
    }

    vector < shared_ptr <AppGLFWSingleWindow> > windows = windowPtr->getWindows();

    windowPosXml.loadFile("settings/Window/windowSettings-"+machineString+".xml");
    windowPosXml.clear();
    for(int i = 0; i < windows.size(); i++){

        if( windows[i]->windowPtr == NULL )continue;

        windowPosXml.addTag("window");
        if( windowPosXml.pushTag("window", i) ){

            //force update of pos info
            if( windowPtr->pushWindow(i) ){
                windowPtr->getWindowSize();
                windowPtr->getWindowPosition();
                windowPtr->popWindow();
            }

            windowPosXml.addTag("fullscreen-rect");
            windowPosXml.addTag("window-rect");

            windowPosXml.addAttribute("fullscreen-rect", "x", (int)windows[i]->fullScreenBounds.x, 0);
            windowPosXml.addAttribute("fullscreen-rect", "y", (int)windows[i]->fullScreenBounds.y, 0);
            windowPosXml.addAttribute("fullscreen-rect", "width", (int)windows[i]->fullScreenBounds.width, 0);
            windowPosXml.addAttribute("fullscreen-rect", "height", (int)windows[i]->fullScreenBounds.height, 0);

            windowPosXml.addAttribute("window-rect", "x", (int)windows[i]->windowBounds.x, 0);
            windowPosXml.addAttribute("window-rect", "y", (int)windows[i]->windowBounds.y, 0);
            windowPosXml.addAttribute("window-rect", "width", (int)windows[i]->windowBounds.width, 0);
            windowPosXml.addAttribute("window-rect", "height", (int)windows[i]->windowBounds.height, 0);

            windowPosXml.popTag();
            windowPosXml.addAttribute("window", "fullscreen", windows[i]->bFullscreen, i);
        }
    }

    windowPosXml.saveFile("settings/Window/windowSettings-"+machineString+".xml");
}