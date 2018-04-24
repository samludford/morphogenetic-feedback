//
//  HUD.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#include "HUD.h"

//#define OUTER_MARGIN 40.0
//#define INNER_MARGIN 80.0

//--------------------------------------------------------------
HUD::HUD() {
    
    
    // initialise the HUD components
    // values are optimised for (but not dependent on) the dimensions of
    // the LG widescreen monitor intended for installation
    
    panelWidth = (ofGetWidth() - outerMargin*2.0) / 3.0;
    float panelOffset = outerMargin + panelWidth;
    float panelHeight = ofGetHeight() - outerMargin*2.0;
    float barHeight = panelHeight/2.0 - innerMargin * 1.5;
    float barSpacing = 20.0;
    float barWidth = (panelWidth - 2.0*innerMargin - 4.0*barSpacing) * 0.2;
    float graphWidth = panelWidth - 2.0 * innerMargin;
    float barY = outerMargin + innerMargin;

    HUDBar *motionBar = new HUDBar(panelOffset + innerMargin, barY, barWidth, barHeight, 0);
    components.push_back(motionBar);

    HUDBar *leftMotionBar = new HUDBar(panelOffset + innerMargin + barWidth + barSpacing, barY, barWidth, barHeight, 1);
    components.push_back(leftMotionBar);

    HUDBar *rightMotionBar = new HUDBar(panelOffset + innerMargin + barWidth*2.0 + barSpacing*2.0, barY, barWidth, barHeight, 2);
    components.push_back(rightMotionBar);

    HUDBar *upMotionBar = new HUDBar(panelOffset + innerMargin + barWidth*3.0 + barSpacing*3.0, barY, barWidth, barHeight, 3);
    components.push_back(upMotionBar);

    HUDBar *downMotionBar = new HUDBar(panelOffset + innerMargin + barWidth*4.0 + barSpacing*4.0, barY, barWidth, barHeight, 4);
    components.push_back(downMotionBar);

    HUDGraph *graph = new HUDGraph(panelOffset + innerMargin, barY + barHeight + innerMargin, graphWidth, barHeight);
    components.push_back(graph);

    float padding = 40.0;
    float wheelXOffset = outerMargin + panelWidth * 2.0 + innerMargin + padding;
    
    float wheelSize = panelWidth - innerMargin*2.0 - padding*2.0;
    
    HUDWheel *wheel = new HUDWheel(wheelXOffset, ofGetHeight()*0.5 - wheelSize*0.5, wheelSize, wheelSize);
    components.push_back(wheel);
    
}

//--------------------------------------------------------------
void HUD::draw(float values[]) {
    
    // draw the static HUD components
    drawFrame();

    // draw the dynamic HUD components
    for(int i=0 ; i < components.size() ; i++) {
        components[i]->draw(values);
    }
}

//--------------------------------------------------------------
void HUD::drawFrame() {
    
    ofPushStyle();
    
    ofSetColor(SHADE_TOP);
    
    ofNoFill();
    
    
    float section = (ofGetWidth() - outerMargin*2.0) / 3.0;
    float x1 = outerMargin + section;
    float x2 = outerMargin + 2.0 * section;
    
    float rWidth =  panelWidth - innerMargin*2.0;
    ofFill();
    float padding = 40.0;
    
    // frame for video feed
    ofDrawRectangle(outerMargin + innerMargin + padding, ofGetHeight()*0.5 - (rWidth-padding*2.0)*0.5, rWidth-padding*2.0, rWidth-padding*2.0);
    
    float cLength = 20.0;
    
    // draw the corners used to frame the video feed and HUDWheel
    ofDrawLine(outerMargin + innerMargin, outerMargin + innerMargin, outerMargin + innerMargin + cLength, outerMargin + innerMargin);
    ofDrawLine(outerMargin + innerMargin, outerMargin + innerMargin, outerMargin + innerMargin, outerMargin + innerMargin + cLength);
    
    ofDrawLine(outerMargin + innerMargin, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin + cLength, ofGetHeight()-outerMargin-innerMargin);
    ofDrawLine(outerMargin + innerMargin, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin, ofGetHeight()-outerMargin-innerMargin-cLength);
    
    ofDrawLine(outerMargin + innerMargin + rWidth, outerMargin + innerMargin, outerMargin + innerMargin + rWidth - cLength, outerMargin + innerMargin);
    ofDrawLine(outerMargin + innerMargin + rWidth, outerMargin + innerMargin, outerMargin + innerMargin + rWidth, outerMargin + innerMargin + cLength);
    
    ofDrawLine(outerMargin + innerMargin + rWidth, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin + rWidth - cLength, ofGetHeight()-outerMargin-innerMargin);
    ofDrawLine(outerMargin + innerMargin + rWidth, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin + rWidth, ofGetHeight()-outerMargin-innerMargin - cLength);
    
    ofPushMatrix();
    
    ofTranslate(panelWidth*2.0, 0);
    
    ofDrawLine(outerMargin + innerMargin, outerMargin + innerMargin, outerMargin + innerMargin + cLength, outerMargin + innerMargin);
    ofDrawLine(outerMargin + innerMargin, outerMargin + innerMargin, outerMargin + innerMargin, outerMargin + innerMargin + cLength);
    
    ofDrawLine(outerMargin + innerMargin, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin + cLength, ofGetHeight()-outerMargin-innerMargin);
    ofDrawLine(outerMargin + innerMargin, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin, ofGetHeight()-outerMargin-innerMargin-cLength);
    
    ofDrawLine(outerMargin + innerMargin + rWidth, outerMargin + innerMargin, outerMargin + innerMargin + rWidth - cLength, outerMargin + innerMargin);
    ofDrawLine(outerMargin + innerMargin + rWidth, outerMargin + innerMargin, outerMargin + innerMargin + rWidth, outerMargin + innerMargin + cLength);
    
    ofDrawLine(outerMargin + innerMargin + rWidth, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin + rWidth - cLength, ofGetHeight()-outerMargin-innerMargin);
    ofDrawLine(outerMargin + innerMargin + rWidth, ofGetHeight()-outerMargin-innerMargin, outerMargin + innerMargin + rWidth, ofGetHeight()-outerMargin-innerMargin - cLength);
    ofPopMatrix();
    
    ofPopStyle();

}


