//
//  MagnetManager.cpp
//  morphogenetic-feedback
//
//  Created by Sam Ludford on 18/04/2018.
//

#include "MagnetManager.h"


//--------------------------------------------------------------
MagnetManager::MagnetManager() {
    
    // arduino
    ard.connect(ARDUINO_UNO_TTY, 57600);
    ofAddListener(ard.EInitialized, this, &MagnetManager::setupArduino);
    bSetupArduino    = false;
    
    for(int i=0 ; i < NUM_MAGNETS ; i++) {
        magnetPins[i] = i + 4;
        clocks[i].setTempo(60.0 + i);
        clocks[i].setTicksPerBeat(4);
        counters[i] = 0;
    }
    
}

//--------------------------------------------------------------
void MagnetManager::audioLoop() {
    
    // don't do anything until arduino setup complete
    if( !bSetupArduino ) return;
    
    for(int i=0 ; i < NUM_MAGNETS ; i++) {
        clocks[i].ticker();
        if(clocks[i].tick) {
            int c = counters[i] % 4;
            if(c==0){
                ard.sendDigital(magnetPins[i], ARD_HIGH);
            } else if(c==1) {
                ard.sendDigital(magnetPins[i], ARD_LOW);
            }
            counters[i]++;
        }
    }
    
}

//--------------------------------------------------------------
void MagnetManager::update() {
    ard.update();
}

//--------------------------------------------------------------
void MagnetManager::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &MagnetManager::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // set magnet pins as outputs
    for(int i=0 ; i < NUM_MAGNETS ; i++) {
        ard.sendDigitalPinMode(magnetPins[i], ARD_OUTPUT);
    }
}

//--------------------------------------------------------------
