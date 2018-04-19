//
//  HUDBar.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 19/04/2018.
//

#pragma once
#include "HUDComponent.h"

class HUDBar : public HUDComponent {
    
public:
    
    HUDBar(float _x, float _y, float _width, float _height, int _value);
    void drawHUD(float values[]);
    
protected:
    
    int value;
    
};
