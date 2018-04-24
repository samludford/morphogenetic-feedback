#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    
    // sets up the app to run on second display (a widescreen LG monitor)
    
    ofGLFWWindowSettings settingsMain;
    settingsMain.width = 2560;   // LG monitor resolution
    settingsMain.height = 1080;
    settingsMain.setPosition(ofVec2f(1280, 0));
    settingsMain.decorated = false;     // false = get rid of window border
    settingsMain.resizable = false; // false = fixed window
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settingsMain); // Draws window in ofApp.cpp
    shared_ptr<ofApp> mainApp(new ofApp);
    ofRunApp( mainWindow, mainApp );
    ofRunMainLoop();
    
}
