#include "ofApp.h"
#include "ofxPS3EyeGrabber.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    // ps3EyeSetup
    video.setDesiredFrameRate(60);
//    video.setDeviceID(0);
    video.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    video.initGrabber(480, 480);
    
    // ofxMaxim setup (used in MagnetManager for clocking)
    sampleRate = 44100;
    bufferSize = 512;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    // setup input manager
    opticalFlowManager = new OpticalFlowManager();
    
    // setup output manager
    magnetManager = new MagnetManager();
    
    // setup hud
    hud = new HUD();
    
    ofSetCircleResolution(100);
    
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
    
    float values[] = {  opticalFlowManager->motion,
                        opticalFlowManager->leftMotion,
                        opticalFlowManager->rightMotion,
                        opticalFlowManager->upMotion,
                        opticalFlowManager->downMotion };
    
    magnetManager->incrementValues(values);
    hud->draw(values);
    
    // draw video
    if(opticalFlowManager->bufferFloat.bAllocated) {
        opticalFlowManager->bufferFloat.draw( 160.0 + 1.0, 246.667 + 1.0, 586.667 - 2.0, 586.667 - 2.0);
    }

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    for (int i = 0; i < bufferSize; i++){
        magnetManager->audioLoop();
    }
}


