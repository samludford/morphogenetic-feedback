//
//  HUD.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#include "HUD.h"

//--------------------------------------------------------------
HUD::HUD() {
    
    // setup HUD
    float panelOffset = ofGetWidth() / 3.0;
    float spacing = 10.0;
    float panelWidth = ofGetWidth() / 3.0;
    float panelHeight = ofGetHeight() / 2.0;
    float componentHeight = panelHeight - 2.0 * spacing;
    float barWidth = (panelWidth - 6.0 * spacing) * 0.2;
    float graphWidth = panelWidth - 2.0 * spacing;
    float barY = spacing;
    
    HUDBar *motionBar = new HUDBar(spacing + panelOffset, barY, barWidth, componentHeight, 0);
    components.push_back(motionBar);
    
    HUDBar *leftMotionBar = new HUDBar(spacing*2.0 + barWidth + panelOffset, barY, barWidth, componentHeight, 1);
    components.push_back(leftMotionBar);

    HUDBar *rightMotionBar = new HUDBar(spacing*3.0 + barWidth*2.0 + panelOffset, barY, barWidth, componentHeight, 2);
    components.push_back(rightMotionBar);

    HUDBar *upMotionBar = new HUDBar(spacing*4.0 + barWidth*3.0 + panelOffset, barY, barWidth, componentHeight, 3);
    components.push_back(upMotionBar);

    HUDBar *downMotionBar = new HUDBar(spacing*5.0 + barWidth*4.0 + panelOffset, barY, barWidth, componentHeight, 4);
    components.push_back(downMotionBar);
    
    HUDGraph *graph = new HUDGraph(spacing + panelOffset, panelHeight + spacing, graphWidth, componentHeight);
    components.push_back(graph);
    
    float wheelXOffset = panelWidth * 2.0 + spacing;
    
    HUDWheel *wheel = new HUDWheel(wheelXOffset, spacing, panelWidth - spacing*2.0, ofGetHeight() - spacing * 2.0);
    components.push_back(wheel);
}

//--------------------------------------------------------------
void HUD::draw(float values[]) {
    for(int i=0 ; i < components.size() ; i++) {
        components[i]->draw(values);
    }
}
