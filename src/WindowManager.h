//
//  WindowManager.h
//
//  Created by Theodore Watson on 6/18/14.
//
//

#pragma once

#include "ofxAppGLFWWindowMulti.h"
#include "ofxXmlSettings.h"

class WindowManager{
    public:
    
        WindowManager(); 
        void setup(ofxAppGLFWWindowMulti * ptr);
        void loadWindowSettings();
        void saveWindowSettings();
    
        void createWindow();
        void setWindowTitle(int windowNo, string title);
        void closeWindow(int which);
        void closeActiveWindow();
        
        int getActiveWindowNo();
        int getFocusedWindowNo();

        ofxAppGLFWWindowMulti * getWindowPtr(); 
    
    protected:
        ofxAppGLFWWindowMulti * windowPtr;
        ofxXmlSettings windowPosXml;
        string machineString; 
};