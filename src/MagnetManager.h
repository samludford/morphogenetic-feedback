//
//  MagnetManager.hpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#pragma once
#include "ofMain.h"
#include "ofxMaxim.h"

#define ARDUINO_UNO_TTY "tty.usbmodem1411"
#define NUM_MAGNETS 4
#define TEMPO_LIMIT_LOWER 30
#define TEMPO_LIMIT_UPPER 120

class MagnetManager {
    
public:
    
    MagnetManager();
    void audioLoop();
    void update();
    void incrementValues(float *values);
    
protected:
    
    // Arduino
    ofArduino ard;
    bool bSetupArduino;
    void setupArduino(const int & version);
    bool motorState;
    int magnetPins[NUM_MAGNETS];
    
    // Maximilian
    float tempos[NUM_MAGNETS];
    maxiClock clocks[NUM_MAGNETS];
    int counters[NUM_MAGNETS];
    
    void incrementTempo(int index, float increment);
    
};
