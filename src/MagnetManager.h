//
//  MagnetManager.hpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#pragma once
#include "ofMain.h"
#include "ofxMaxim.h"

//#define ARDUINO_UNO_TTY "/dev/tty.usbmodem1411"
#define ARDUINO_UNO_TTY "tty.usbmodem1411"

class MagnetManager {
    
public:
    
    MagnetManager();
    void audioLoop();
    void update();
    
protected:
    
    // Arduino
    ofArduino ard;
    bool bSetupArduino;
    void setupArduino(const int & version);
    bool motorState;
    
    const int magnet1Pin {4};
    const int magnet2Pin {5};
    const int magnet3Pin {6};
    const int magnet4Pin {7};
    
    bool magnet1State {false};
    bool magnet2State {false};
    bool magnet3State {false};
    bool magnet4State {false};
    
    // Maximilian
    maxiClock clock;
    int counter;
    
};
