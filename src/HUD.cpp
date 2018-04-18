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
}

//--------------------------------------------------------------
void HUD::draw(float values[]) {
    for(int i=0 ; i < components.size() ; i++) {
        components[i].draw(values);
    }
}
