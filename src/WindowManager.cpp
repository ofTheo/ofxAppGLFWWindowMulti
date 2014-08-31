//
//  WindowManager.cpp
//
//  Created by Theodore Watson on 6/18/14.
//
//

#include "WindowManager.h"

WindowManager::WindowManager(){
    windowPtr = NULL; 
}

//--------------------------------------------------------------
void WindowManager::setup(ofxAppGLFWWindowMulti * ptr){
    windowPtr = ptr;
    machineString = "default";
    if( getenv("USER") != NULL ) {
        machineString = getenv("USER");
    }
}

//--------------------------------------------------------------
ofxAppGLFWWindowMulti * WindowManager::getWindowPtr(){
    return windowPtr;
}

//--------------------------------------------------------------
int WindowManager::getActiveWindowNo(){
    return windowPtr->getCurrentWindowNo();
}

//--------------------------------------------------------------
int WindowManager::getFocusedWindowNo(){
    return windowPtr->getFocusedWindowNo();
}
//--------------------------------------------------------------
void WindowManager::createWindow(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::createWindow") << " windowPtr needs to be set " << endl;
    }
    windowPtr->addWindow();
}

//--------------------------------------------------------------
void WindowManager::setWindowTitle(int windowNo, string title){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setWindowTitle") << " windowPtr needs to be set " << endl;
    }
    windowPtr->setWindowTitle(windowNo, title);
}

//--------------------------------------------------------------
void WindowManager::setWindowPosition(int windowNo, int x, int y){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setWindowPosition") << " windowPtr needs to be set " << endl;
    }
    windowPtr->setWindowPosition(windowNo, x, y);
}

//--------------------------------------------------------------
void WindowManager::setWindowShape(int windowNo, int w, int h){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setWindowShape") << " windowPtr needs to be set " << endl;
    }
    windowPtr->setWindowShape(windowNo, w, h);
}

//--------------------------------------------------------------
void WindowManager::setFullscreen(int windowNo, bool fullscreen){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::setFullscreen") << " windowPtr needs to be set " << endl;
    }
    windowPtr->setFullscreen(windowNo, fullscreen);
}

//--------------------------------------------------------------
void WindowManager::toggleFullscreen(int windowNo){
    if (windowPtr == NULL) {
        ofLogError("WindowManager::toggleFullscreen") << " windowPtr needs to be set " << endl;
    }
    windowPtr->toggleFullscreen(windowNo);
}

//--------------------------------------------------------------
void WindowManager::closeActiveWindow(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::closeActiveWindow") << " windowPtr needs to be set " << endl;
    }
    windowPtr->closeWindow(getActiveWindowNo());
}

//--------------------------------------------------------------
void WindowManager::closeWindow(int which){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::closeWindow") << " windowPtr needs to be set " << endl;
    }
    windowPtr->closeWindow(which);
}

//--------------------------------------------------------------
void WindowManager::loadWindowSettings(){
    if( windowPtr == NULL ){
        ofLogError("WindowManager::loadWindowSettings") << " windowPtr needs to be set " << endl;
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
        ofLogError("WindowManager::saveWindowSettings") << " windowPtr needs to be set " << endl;
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