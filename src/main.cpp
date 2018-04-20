#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    
//    ofGLFWWindowSettings settingsMain;
//    settingsMain.width = 2560;   // LG monitor resolution
//    settingsMain.height = 1080;
////    settingsMain.setPosition(ofVec2f(200, 20)); // Position of window
////    settingsMain.setPosition(ofVec2f(0, 0));
//    settingsMain.setPosition(ofVec2f(1280, 0));
//    settingsMain.decorated = false;     // false = get rid of window border
//    settingsMain.resizable = false; // false = fixed window
//
//    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settingsMain); // Draws window in ofApp.cpp
//
////    ofSetupOpenGL(1200,400, OF_FULLSCREEN);            // <-------- setup the GL context
//
//    // this kicks off the running of my app
//    // can be OF_WINDOW or OF_FULLSCREEN
//    // pass in width and height too:
//    shared_ptr<ofApp> mainApp(new ofApp);
//    ofRunApp( mainWindow, mainApp );
//    ofRunMainLoop();
    
    ofSetupOpenGL(1200,400, OF_WINDOW);
    ofRunApp( new ofApp());
}
