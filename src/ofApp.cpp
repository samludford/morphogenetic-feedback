#include "ofApp.h"
#include "ofxPS3EyeGrabber.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	ofBackground(125);
    
    // ps3EyeSetup
    video.setDesiredFrameRate(60);
    video.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    video.initGrabber(480, 480);
    
    // ofxMaxim setup
    sampleRate = 44100;
    bufferSize = 512;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    // setup input and output managers
    magnetManager = new MagnetManager();
    opticalFlowManager = new OpticalFlowManager();
}


//--------------------------------------------------------------
void ofApp::update(){
    
    video.update();
    
    if ( video.isFrameNew() )
    {
        ofPixels & pixels = video.getPixels();
        opticalFlowManager->calculate(pixels);
    }
    
    magnetManager->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255);
    video.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    for (int i = 0; i < bufferSize; i++){
        magnetManager->audioLoop();
    }
}

