//
//  HUDComponent.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#pragma once
#include "ofMain.h"
#include "OpticalFlowManager.h"

#define SHADE_TOP 255.0
#define SHADE_BOTTOM 0.0

class HUDComponent {
    
public:
    
    HUDComponent(float _x, float _y, float _width, float _height);
    void draw(float values[]);
    virtual void drawHUD(float values[]);
    
protected:
    
    float x, y, width, height;
    
};
