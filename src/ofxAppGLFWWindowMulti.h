//
//  ofxAppGLFWWindowMulti.h
//
//  Created by Theodore Watson on 1/28/14.
//
//

#pragma once

#include "ofConstants.h"

#define GLFW_INCLUDE_NONE

#if (_MSC_VER)
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif

#include "ofAppBaseWindow.h"
#include "ofEvents.h"
#include "ofPixels.h"
#include "ofRectangle.h"

class ofBaseApp;

class AppGLFWSingleWindow{

    public:
        AppGLFWSingleWindow(){
            bInFocus = false;
            bMainWindow = false;
            bFullscreen = false;
            bInitialized = false;
            windowPtr = NULL;
        }
    
        ofRectangle getCurrentBounds(){
            if( bFullscreen ){
                return fullScreenBounds;
            }else{
                return windowBounds;
            }
        }
    
        bool bFullscreen;
        bool bMainWindow;
        bool bInFocus;
        bool bInitialized;
        bool bClosed;
        int windowNo;
    
        string windowName; 
        GLFWwindow* windowPtr;
    
        ofRectangle windowBounds;
        ofRectangle fullScreenBounds;
    
        ofPoint mousePt; 
};

class ofxAppGLFWWindowMulti : public ofAppBaseWindow {

public:

	ofxAppGLFWWindowMulti();
	~ofxAppGLFWWindowMulti(){}


	// window settings, this functions can be called from main before calling ofSetupOpenGL
	void 		setNumSamples(int samples);
	void 		setDoubleBuffering(bool doubleBuff);
	void 		setColorBits(int r, int g, int b);
	void		setAlphaBits(int a);
	void		setDepthBits(int depth);
	void		setStencilBits(int stencil);
	void		listVideoModes();
	bool		isWindowIconified();
	bool		isWindowActive();
	bool		isWindowResizeable();
	void		iconify(bool bIconify);
    void        setMultiDisplayFullscreen(bool bMultiFullscreen); //note this just enables the mode, you have to toggle fullscreen to activate it.


    //begin multi window stuff
    int getCurrentWindowNo();
    int getFocusedWindowNo();
    bool isWindowInFocus(int winNo);
    
    int addWindow(string windowName = "", float x = 0, float y = 0, float w = 1024, float h = 768, bool bFullscreen = false);
    bool closeWindow(int windowNo);
    int getNumWindows();
    int getNumActiveWindows();
    
    //Note: push/pop window should always be used together.
    //sets active the window specified by windowNo - all OF window commands will now refer to this window.
    bool pushWindow(int windowNo);
    //restores the previously active window
    void popWindow();

    vector < shared_ptr <AppGLFWSingleWindow> > getWindows();
    //end multi window stuff

    
    // this functions are only meant to be called from inside OF don't call them from your code
	void setOpenGLVersion(int major, int minor);
	void setupOpenGL(int w, int h, int screenMode);
	void initializeWindow();
	void runAppViaInfiniteLoop(ofBaseApp * appPtr);


	void hideCursor();
	void showCursor();

	int getHeight();
	int getWidth();

	ofVec3f		getWindowSize();
    ofVec3f		getWindowSize(int winNo);
	ofVec3f		getScreenSize();
	ofVec3f 	getWindowPosition();

	void setWindowTitle(string title);
	void setWindowPosition(int x, int y);
	void setWindowShape(int w, int h);

	void			setOrientation(ofOrientation orientation);
	ofOrientation	getOrientation();

	int			getWindowMode();

	void		setFullscreen(bool fullscreen);
	void		toggleFullscreen();

	void		enableSetupScreen();
	void		disableSetupScreen();

	void		setVerticalSync(bool bSync);

#if defined(TARGET_LINUX) && !defined(TARGET_RASPBERRY_PI)
	Display* 	getX11Display();
	Window  	getX11Window();
#endif

#if defined(TARGET_LINUX) && !defined(TARGET_OPENGLES)
	GLXContext 	getGLXContext();
#endif

#if defined(TARGET_LINUX) && defined(TARGET_OPENGLES)
	EGLDisplay 	getEGLDisplay();
	EGLContext 	getEGLContext();
	EGLSurface 	getEGLSurface();
#endif

#if defined(TARGET_OSX)
	void *		getNSGLContext();
	void *		getCocoaWindow();
#endif

#if defined(TARGET_WIN32)
	HGLRC 		getWGLContext();
	HWND 		getWin32Window();
#endif

    //so we get set the correct window for events in key pressed mouse etc.
    void setFocusedWindow(GLFWwindow * windowP_);

private:
	// callbacks
	void			display(GLFWwindow* window);

	static void 	mouse_cb(GLFWwindow* windowP_, int button, int state, int mods);
	static void 	motion_cb(GLFWwindow* windowP_, double x, double y);
	static void 	keyboard_cb(GLFWwindow* windowP_, int keycode, int scancode, unsigned int codepoint, int action, int mods);
	static void 	resize_cb(GLFWwindow* windowP_, int w, int h);
	static void 	exit_cb(GLFWwindow* windowP_);
	static void 	close_cb(GLFWwindow* windowP_);
	static void		scroll_cb(GLFWwindow* windowP_, double x, double y);
	static void 	drop_cb(GLFWwindow* windowP_, int numFiles, const char** dropString);
	static void 	focus_cb(GLFWwindow* windowP_, int focus);

	static void 	exitApp();

#ifdef TARGET_LINUX
	void setWindowIcon(const string & path);
	void setWindowIcon(const ofPixels & iconPixels);
#endif

	//utils
	int				samples;
	int				rBits,gBits,bBits,aBits,depthBits,stencilBits;


	bool			bEnableSetupScreen;

	int				buttonInUse;
	bool			buttonPressed;

	int 			nFramesSinceWindowResized;
	bool			bDoubleBuffered;
    bool            bMultiWindowFullscreen;
    bool            isSetup; 

    ofPoint         updateWindowSize(int winNo);
	int				getCurrentMonitor();
	
	static ofxAppGLFWWindowMulti	* instance;
	static ofBaseApp *	ofAppPtr;

    int currentWindow;
    int focusedWindow;
    vector < shared_ptr <AppGLFWSingleWindow> > windows;
    vector <int> windowStack;

	ofOrientation orientation;

	int glVersionMinor, glVersionMajor;

	bool iconSet;

    #ifdef TARGET_WIN32
    LONG lExStyle, lStyle;
    #endif // TARGET_WIN32
};

