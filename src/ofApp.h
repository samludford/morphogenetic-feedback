#pragma once
#include "ofMain.h"
//#include "ofxOpenCv.h"
#include "ofxMaxim.h"
#include "MagnetManager.h"
#include "OpticalFlowManager.h"

//using namespace cv;


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
    
    // video input
    ofVideoGrabber video;
    
    // ofxMaxim
    void audioOut(float * output, int bufferSize, int nChannels);
    int        bufferSize; /* buffer size */
    int        sampleRate;
    
    // magnet manager
    MagnetManager *magnetManager;
    
    // optical flow analysis
    OpticalFlowManager *opticalFlowManager;
    
};

