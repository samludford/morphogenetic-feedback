//
//  HUD.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#pragma once

#include "ofMain.h"
#include "HUDComponent.h"

class HUD {
    
public:
    
    HUD();
    void draw(float values[]);
    
protected:
    
    vector<HUDComponent> components;
    
    
};