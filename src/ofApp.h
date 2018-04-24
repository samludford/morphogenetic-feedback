#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "MagnetManager.h"
#include "OpticalFlowManager.h"
#include "HUD.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {

public:
    
	void setup();
	void update();
	void draw();
    
    // video input
    ofVideoGrabber video;
    
    // ofxMaxim (used in the MagnetManager for handling the timing of pulse patterns)
    void audioOut(float * output, int bufferSize, int nChannels);
    int  bufferSize;
    int  sampleRate;
    
    // magnet manager (class handling communication with the arduino)
    MagnetManager *magnetManager;
    
    // optical flow manager (class handling CV related tasks)
    OpticalFlowManager *opticalFlowManager;
    
    // HUD (class for handling the graphical component displayed on the LG Monitor)
    HUD *hud;

    
};

