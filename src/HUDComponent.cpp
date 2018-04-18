//
//  HUDComponent.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#include "HUDComponent.h"

//--------------------------------------------------------------
HUDComponent::HUDComponent(float _x, float _y, float _width, float _height) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}

//--------------------------------------------------------------
void HUDComponent::draw(float values[]) {
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x, y);
    drawHUD(values);
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void HUDComponent::drawHUD(float values[]) {
    // override in subclass
}

