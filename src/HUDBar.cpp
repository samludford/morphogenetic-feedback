//
//  HUDBar.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 19/04/2018.
//

#include "HUDBar.h"

//--------------------------------------------------------------
HUDBar::HUDBar(float _x, float _y, float _width, float _height, int _value) : HUDComponent(_x, _y, _width, _height) {
    value = _value;
}

//--------------------------------------------------------------
void HUDBar::drawHUD(float values[]) {
    // draw rectangle
    ofSetColor(SHADE_TOP);
    int v = values[value];
    ofNoFill();
    ofDrawRectRounded(0, 0, width, height, 3.0);
    float vNorm = ofMap(v, 0, 40, 0, 1);
    ofFill();
    ofDrawRectRounded(0, height - (height*vNorm), width, height*vNorm, 3.0);
}
