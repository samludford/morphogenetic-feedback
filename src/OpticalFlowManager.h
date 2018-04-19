//
//  OpticalFlowManager.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxMaxim.h"

using namespace cv;

class OpticalFlowManager {
    
public:
    
    OpticalFlowManager();
    void calculate(ofPixels & pixels);
    float motion;
    float leftMotion;
    float rightMotion;
    float upMotion;
    float downMotion;
    ofxCvFloatImage diffFloat;  //Amplified difference images
    ofxCvFloatImage bufferFloat;    //Buffer image
    
protected:
    
    bool calculatedFlow {false};
    ofxCvColorImage currentColor;        //First and second original images
    ofxCvGrayscaleImage gray1, gray2;    //Decimated grayscaled images
    ofxCvFloatImage flowX, flowY;        //Resulted optical flow in x and y axes
    
    ofxCvGrayscaleImage diff;        //Absolute difference of the frames
    
    void computeVectors(ofPixels & pixels);
    void analyseVectors();
    void processForDisplay();
    
};

