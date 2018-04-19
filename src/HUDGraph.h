//
//  HUDGraph.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 19/04/2018.
//

#pragma once

#include "HUDComponent.h"
#include "ofMain.h"

class HUDGraph : public HUDComponent {
    
public:
    
    HUDGraph(float _x, float _y, float _width, float _height);
    void drawHUD(float values[]);
    
protected:
    
    int buffer_size {30};
    vector<deque<float>> valueHistory;
    
};
