//
//  HUDWheel.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 19/04/2018.
//

#pragma once

#include "HUDComponent.h"

class HUDWheel : public HUDComponent {
    
public:
    
    HUDWheel(float _x, float _y, float _width, float _height);
    void drawHUD(float values[]);
    
protected:
    
    void drawHUD(ofPoint loc, float size);
    void drawSegment(ofPoint loc, ofColor col, float radius, float thickness, float startAngle, float endAngle);
    void drawDotted(ofPoint loc, float dots, float radius, float thickness);
    void drawIris(ofPoint loc, float radius, float thickness);
    
    
    
};
