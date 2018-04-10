#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofVideoGrabber video;		//Declare the video player object
	ofxCvColorImage image;		//The current video frame

	//The current and the previous video frames as grayscale images
	ofxCvGrayscaleImage grayImage, grayImagePrev;
	ofxCvGrayscaleImage diff;		//Absolute difference of the frames
	ofxCvFloatImage diffFloat;		//Amplified difference images
	ofxCvFloatImage bufferFloat;	//Buffer image
    
    
    // arduino
    ofArduino ard;
    bool bSetupArduino;
    void setupArduino(const int & version);
    void updateArduino();
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
    bool motorState;

    void mousePressed(int x, int y, int button);
    bool debug;
    
};

