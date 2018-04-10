#include "ofApp.h"
#include "ofxPS3EyeGrabber.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(125);
//    video.setDeviceID(0);
    video.setDesiredFrameRate(60);
    video.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    video.initGrabber(640, 480);
    debug = true;
    
    ard.connect("/dev/tty.usbmodem1421", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino    = false;
}

// Arduino
void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pin D3 as digital output
    ard.sendDigitalPinMode(3, ARD_OUTPUT);
    
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();
    
    // do not send anything until the arduino has been set up
    if (bSetupArduino) {
        // fade the led connected to pin D11
        
        // switch motor on / off every 120 seconds
        int frame = ofGetFrameNum();
        if(frame % 120 == 0) {
            motorState = !motorState;
            int value = motorState ? ARD_HIGH : ARD_LOW;
            ard.sendDigital(3, value);
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
}

//--------------------------------------------------------------
void ofApp::update(){
    
	video.update();		//Decode the new frame if needed
	//Do computing only if the new frame was obtained
	if ( video.isFrameNew() ) {
		//Store the previous frame, if it exists till now
		if ( grayImage.bAllocated ) {
			grayImagePrev = grayImage;
		}

		//Getting a new frame
		image.setFromPixels( video.getPixels() );
		image.mirror(false, true);
		grayImage = image; //Convert to grayscale image

		//Do processing if grayImagePrev is inited
		if ( grayImagePrev.bAllocated ) {
			//Get absolute difference
			diff.absDiff( grayImage, grayImagePrev );

			//We want to amplify the difference to obtain
			//better visibility of motion
			//We do it by multiplication. But to do it, we
			//need to convert diff to float image first
			diffFloat = diff;	//Convert to float image
			diffFloat *= 5.0;	//Amplify the pixel values (original = 5.0)

			//Update the accumulation buffer
			if ( !bufferFloat.bAllocated ) {
				//If the buffer is not initialized, then
				//just set it equal to diffFloat
				bufferFloat = diffFloat;
			}
			else {
				//Slow damping the buffer to zero
				bufferFloat *= 0.65; //original = 0.85
				//Add current difference image to the buffer

				bufferFloat += diffFloat;
				bufferFloat.erode(); //helps get rid of noise (remove if not needed)
			}
		}
	}
    
    updateArduino();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground( 255, 255, 255 );	//Set the background color

	//Draw only if diffFloat image is ready.
	//It happens when the second frame from the video is obtained
	if ( diffFloat.bAllocated ) {
		//Get image dimensions
		int w = grayImage.width;
		int h = grayImage.height;

        //Set color for images drawing
        ofSetColor( 255, 255, 255 );

        //Draw images grayImage,  diffFloat, bufferFloat
        if (debug)
        {
            grayImage.draw( 0, 0, w/2, h/2 );
            diffFloat.draw( w/2, 0, w/2, h/2 );
            bufferFloat.draw( 0, h/2, w/2, h/2 );
        }
        else image.draw( 0, 0, ofGetWidth(), ofGetHeight() );

        //Draw the image motion areas
        if (debug)
        {
            //Shift and scale the coordinate system
            ofPushMatrix();
            ofTranslate( w/2, h/2);
            ofScale( 0.5, 0.5 );
            //Draw bounding rectangle
            ofSetColor(0, 0, 0);
            ofNoFill();
        }

        //Get bufferFloat pixels
        float *pixels = bufferFloat.getPixelsAsFloats();

        //Scan all pixels
        for (int y=0; y<h; y+=1)
        {
            for (int x=0; x<w; x+=1)
            {
                //Get the pixel value
                float value = pixels[ x + w * y ];
                //If value exceed threshold, then draw pixel
                if ( value >= 1.4 ) {                           //original was 0.9
                   if (debug) ofDrawRectangle( x, y, 1, 1 );
                }
            }
        }
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    debug = !debug;
}
