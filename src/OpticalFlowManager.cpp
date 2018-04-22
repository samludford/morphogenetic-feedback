//
//  OpticalFlowManager.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#include "OpticalFlowManager.h"

//--------------------------------------------------------------
OpticalFlowManager::OpticalFlowManager() {
    
}


//--------------------------------------------------------------
void OpticalFlowManager::calculate(ofPixels & pixels) {
    computeVectors(pixels);
    analyseVectors();
    processForDisplay();
}

//--------------------------------------------------------------
void OpticalFlowManager::computeVectors(ofPixels & pixels) {
    if ( gray1.bAllocated ) {
        gray2 = gray1;
        calculatedFlow = true;
    }
    
    //Convert to ofxCv images
    currentColor.setFromPixels( pixels );
    
    float decimate = 0.25;              //Decimate images to 25% (makes calculations faster + works like a blurr too)
    ofxCvColorImage imageDecimated1;
    imageDecimated1.allocate( currentColor.width * decimate, currentColor.height * decimate );
    imageDecimated1.scaleIntoMe( currentColor, CV_INTER_AREA );             //High-quality resize
    gray1 = imageDecimated1;
    
    if ( gray2.bAllocated ) {
        
        // optical flow stuff
        Mat img1( gray1.getCvImage() );  //Create OpenCV images
        Mat img2( gray2.getCvImage() );
        Mat flow;                        //Image for flow
        //Computing optical flow (visit https://goo.gl/jm1Vfr for explanation of parameters)
        calcOpticalFlowFarneback( img1, img2, flow, 0.7, 3, 11, 5, 5, 1.1, 0 );
        //Split flow into separate images
        vector<Mat> flowPlanes;
        split( flow, flowPlanes );
        //Copy float planes to ofxCv images flowX and flowY
        //we call this to convert back from native openCV to ofxOpenCV data types
        IplImage iplX( flowPlanes[0] );
        flowX = &iplX;
        IplImage iplY( flowPlanes[1] );
        flowY = &iplY;
    }
}

//--------------------------------------------------------------
void OpticalFlowManager::analyseVectors() {
    
        if(!calculatedFlow) return;
    
        // analysis e.g.
        int w = gray1.width;
        int h = gray1.height;
        float *flowXPixels = flowX.getPixelsAsFloats();
        float *flowYPixels = flowY.getPixelsAsFloats();
//        ofSetColor( 0, 0, 255 );
        for (int y=0; y<h; y+=5) {
            for (int x=0; x<w; x+=5) {
                
                motion = 0;
                leftMotion = 0;
                rightMotion = 0;
                upMotion = 0;
                downMotion = 0;
                
                float fx = flowXPixels[ x + w * y ];
                float fy = flowYPixels[ x + w * y ];
                
                motion += fabs( fx ) + fabs( fy );
                if(fx > 0) {
                    rightMotion += fabs( fx );
                } else {
                    leftMotion += fabs ( fx );
                }
                
                if(fy > 0) {
                    downMotion += fabs( fy );
                } else {
                    upMotion += fabs ( fy );
                }

            }
        }
}

//--------------------------------------------------------------
void OpticalFlowManager::processForDisplay() {
    if ( gray2.bAllocated ) {
        // frame differing for display
        diff.absDiff( gray1, gray2 );
        diffFloat = diff;    //Convert to float image
        diffFloat *= 5.0;    //Amplify the pixel values (original = 5.0)
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
