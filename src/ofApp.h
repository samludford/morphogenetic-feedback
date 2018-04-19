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
    
    // video processing
    
    // ofxMaxim
    void audioOut(float * output, int bufferSize, int nChannels);
    int  bufferSize;
    int  sampleRate;
    
    // magnet manager
    MagnetManager *magnetManager;
    
    // optical flow analysis
    OpticalFlowManager *opticalFlowManager;
    
    // HUD
    HUD *hud;
    
    // image for display
    ofxCvColorImage image;        //The current video frame
    ofxCvGrayscaleImage grayImage, grayImagePrev;
    
};

