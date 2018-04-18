//
//  HUDComponent.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#pragma once
#include "ofMain.h"

class HUDComponent {
    
public:
    
    HUDComponent(float _x, float _y, float _width, float _height);
    void draw(float values[]);  // 0 - motion, 1 - leftMotion, 2 - rightMotion, 3 - upMotion, 4 - downMotion
    
protected:
    
    float x, y, width, height;
    void drawHUD(float values[]);
    
};
