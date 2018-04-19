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
    HUDBar *motionBar = new HUDBar(10, 10, 80, 300, 0);
    components.push_back(motionBar);
    
    HUDBar *leftMotionBar = new HUDBar(100, 10, 80, 300, 1);
    components.push_back(leftMotionBar);
    
    HUDBar *rightMotionBar = new HUDBar(200, 10, 80, 300, 2);
    components.push_back(rightMotionBar);
    
    HUDBar *upMotionBar = new HUDBar(300, 10, 80, 300, 3);
    components.push_back(upMotionBar);
    
    HUDBar *downMotionBar = new HUDBar(400, 10, 80, 300, 4);
    components.push_back(downMotionBar);
    
    HUDGraph *graph = new HUDGraph(10, 320, 480, 300);
    components.push_back(graph);
}

//--------------------------------------------------------------
void HUD::draw(float values[]) {
    for(int i=0 ; i < components.size() ; i++) {
        components[i]->draw(values);
    }
}
