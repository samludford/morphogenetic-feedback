//
//  HUD.h
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#pragma once

#include "ofMain.h"
#include "HUDComponent.h"
#include "HUDBar.h"
#include "HUDGraph.h"
#include "HUDWheel.h"

class HUD {
    
public:
    
    HUD();
    void draw(float values[]);
    
protected:
    
    vector<HUDComponent*> components;
    void drawFrame();
    float innerMargin { 80.0 };
    float outerMargin { 40.0 };
    float panelWidth;
    
};
