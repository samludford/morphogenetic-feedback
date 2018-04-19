//
//  HUDWheel.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 19/04/2018.
//

#include "HUDWheel.h"

//--------------------------------------------------------------
HUDWheel::HUDWheel(float _x, float _y, float _width, float _height) : HUDComponent(_x, _y, _width, _height) {

}

//--------------------------------------------------------------
void HUDWheel::drawHUD(float values[]) {
    
    motionVals.push_front(values[0]);
    if(motionVals.size() > 100) {
        motionVals.pop_back();
    }
    
    float shade_dark = 80.0;
    
    ofPushMatrix();
    ofTranslate(width/2.0, height/2.0);
    ofSetColor(shade_dark);
    ofDrawCircle(0, 0, width/2.0);
    ofSetColor(SHADE_BOTTOM);
    ofDrawCircle(0, 0, width/2.0 - 5.0);
    
    float s1Rad = width/2.0 * 0.95;
    float s1Thick = width * 0.04;
    drawSegment(ofPoint(0,0), SHADE_TOP, s1Rad, s1Thick, -20.0, 20.0);
    drawSegment(ofPoint(0,0), SHADE_TOP, s1Rad, s1Thick, -20.0 + 90.0, 20.0 + 90.0);
    drawSegment(ofPoint(0,0), SHADE_TOP, s1Rad, s1Thick, -20.0 + 180.0, 20.0 + 180.0);
    drawSegment(ofPoint(0,0), SHADE_TOP, s1Rad, s1Thick, -20.0 + 270.0, 20.0 + 270.0);
    

    
    float shRad = width/2.0 * 0.7;
    float shThick = width * 0.01;
    drawSegment(ofPoint(0,0), shade_dark, shRad, shThick, -40.0 + 45.0, 40.0 + 45.0);
    drawSegment(ofPoint(0,0), shade_dark, shRad, shThick, -40.0 + 90.0 + 45.0, 40.0 + 90.0 + 45.0);
    drawSegment(ofPoint(0,0), shade_dark, shRad, shThick, -40.0 + 180.0 + 45.0, 40.0 + 180.0 + 45.0);
    drawSegment(ofPoint(0,0), shade_dark, shRad, shThick, -40.0 + 270.0 + 45.0, 40.0 + 270.0 + 45.0);
    
    
    ofPushStyle();
    ofSetColor(shade_dark);
    ofSetLineWidth(5);
    for(int i=0 ; i<4 ; i++) {
        ofPushMatrix();
        
        ofRotate(90 * i + 45);
        ofDrawLine(shRad, 0, width/2.0, 0);
        ofPopMatrix();
    }
    ofPopStyle();
    
    ofPushMatrix();
    ofRotate(ofGetFrameNum() * 0.4);
    float d1Rad = width/2.0 * 0.6;
    drawDotted(ofPoint(0,0), 200.0, d1Rad, 2);
    ofPopMatrix();
    
    ofColor c = ofColor(SHADE_TOP, 150);
    float s2Rad = width/2.0 * 0.58;
    float s2Thick = width * 0.04;
    drawSegment(ofPoint(0,0), c, s2Rad, s2Thick, 30.0, 120.0);
    drawSegment(ofPoint(0,0), c, s2Rad, s2Thick, 30.0 + 120.0, 120.0 + 120.0);
    drawSegment(ofPoint(0,0), c, s2Rad, s2Thick, 30.0 + 240.0, 120.0 + 240.0);
    
    drawSegment(ofPoint(0,0), c, s2Rad, s2Thick, 60.0, 90.0);
    drawSegment(ofPoint(0,0), c, s2Rad, s2Thick, 60.0 + 120.0, 90.0 + 120.0);
    drawSegment(ofPoint(0,0), c, s2Rad, s2Thick, 60.0 + 240.0, 90.0 + 240.0);
    
    drawSegment(ofPoint(0,0), 60.0, s2Rad - s2Thick/2.0, s2Thick/2.0, 30.0, 60.0);
    drawSegment(ofPoint(0,0), 60.0, s2Rad - s2Thick/2.0, s2Thick/2.0, 30.0 + 120.0, 60.0 + 120.0);
    drawSegment(ofPoint(0,0), 60.0, s2Rad - s2Thick/2.0, s2Thick/2.0, 30.0 + 240.0, 60.0 + 240.0);
    
    ofPushMatrix();
    ofRotate(ofGetFrameNum() * -0.2);
    float s3Rad = width/2.0 * 0.46;
    float s3Thick = width * 0.01;
    drawSegment(ofPoint(0,0), SHADE_TOP, s3Rad, s3Thick, 0.0, 90.0);
    drawSegment(ofPoint(0,0), SHADE_TOP, s3Rad, s3Thick, 0.0 + 180.0, 90.0 + 180.0);
    ofPopMatrix();
    
    float iRad = width/2.0 * 0.3;
    float iThick = width * 0.04;
    drawIris(ofPoint(0,0), iRad, iThick);
    ofPopMatrix();
}

//--------------------------------------------------------------
void HUDWheel::drawSegment(ofPoint loc, ofColor col, float radius, float thickness, float startAngle, float endAngle) {
    ofPushMatrix();
    ofPath path;
    path.setCircleResolution(100);
    path.arc(loc.x, loc.y, radius, radius, startAngle, endAngle);
    path.setFilled(true);
    path.setColor(col);
    path.draw();
    ofPath pathI;
    pathI.setCircleResolution(100);
    pathI.arc(0, 0, radius - thickness, radius - thickness, startAngle, endAngle);
    pathI.setFilled(true);
    pathI.setColor(SHADE_BOTTOM);
    pathI.draw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void HUDWheel::drawDotted(ofPoint loc, float dots, float radius, float thickness) {
    ofPushMatrix();
    ofTranslate(loc.x, loc.y);
    float ang_div = 360.0 / dots;
    for(int i=0; i < dots ; i+=2) {
        ofPath path;
        path.moveTo(radius * cos(ofDegToRad(i*ang_div)), radius * sin(ofDegToRad(i*ang_div)));
        path.setCircleResolution(100);
        path.arc(0, 0, radius, radius, i * ang_div, i * ang_div + ang_div);
        path.setFilled(false);
        path.setStrokeWidth(thickness);
        path.setColor(SHADE_TOP);
        path.draw();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void HUDWheel::drawIris(ofPoint loc, float radius, float thickness) {
    ofSetColor(SHADE_TOP);
    ofPushMatrix();
    ofRotate(90);
    ofTranslate(loc.x, loc.y);
    ofSetLineWidth(2);
    float count = 100.0;
    float ang_div = 360.0 / count;
    for(int i=0 ; i < count ; i++) {
        float l = ofMap(motionVals[i], 0, 50, 0, radius, radius);
        ofPushMatrix();
        ofRotate(i * ang_div);
        ofDrawLine(radius, 0, radius - l, 0);
        ofDrawLine(radius + 2, 0, radius + 3, 0);
        ofPopMatrix();
    }
    ofPopMatrix();
}
