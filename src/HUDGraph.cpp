//
//  HUDGraph.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 19/04/2018.
//

#include "HUDGraph.h"

//--------------------------------------------------------------
HUDGraph::HUDGraph(float _x, float _y, float _width, float _height) : HUDComponent(_x, _y, _width, _height) {
    valueHistory.resize(5);
}

//--------------------------------------------------------------
void HUDGraph::drawHUD(float values[]) {
    
    // update history deques
    for(int i=0 ; i < 5 ; i++) {
        valueHistory[i].push_front(values[i]);
        if(valueHistory[i].size() > buffer_size) valueHistory[i].pop_back();
    }
    
    // draw axis
    ofDrawLine(0, 0, 0, height);
    ofDrawLine(0, height, width, height);
    
    // draw lines
    for(int i = 0 ; i < 5 ; i++) {
        ofPolyline graphLine;
        float delta_x = width / (float) (buffer_size-1);
        for(int j = 0 ; j < valueHistory[i].size() ; j++) {
            float x = j * delta_x;
            float y = ofMap(valueHistory[i][j], 0 , 40, height-20, 0, height-40);
            if(j==0) {
                graphLine.curveTo(x, y);
            }
            graphLine.curveTo(x, y);
            if(j==valueHistory[i].size()-1) {
                graphLine.curveTo(x, y);
            }
        }
        graphLine.draw();
    }
    
    ofPushStyle();
    ofSetColor(255,0,0);
//    ofDrawRectangle(0, 0, width, height);
    ofPopStyle();

}

