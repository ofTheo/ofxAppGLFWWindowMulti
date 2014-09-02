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
        ofPoint getWindowPosition(int windowNo);
        void setWindowPosition(int windowNo, int x, int y);
        ofPoint getWindowShape(int windowNo);
        void setWindowShape(int windowNo, int w, int h);
        ofPoint getScreenSize(int windowNo);
        void setFullscreen(int windowNo, bool fullscreen);
        void toggleFullscreen(int windowNo);
        void closeWindow(int which);
        void closeFocusedWindow();
        
        int getActiveWindowNo();
        int getFocusedWindowNo();

        ofxAppGLFWWindowMulti * getWindowPtr(); 
    
    protected:
        ofxAppGLFWWindowMulti * windowPtr;
        ofxXmlSettings windowPosXml;
        string machineString; 
};