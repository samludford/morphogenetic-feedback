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
    
    // clock
    clock.setTempo(30.0);
    clock.setTicksPerBeat(2);
}

//--------------------------------------------------------------
void MagnetManager::audioLoop() {
    clock.ticker();
    if(clock.tick) {
        
        // don't do anything until arduino setup complete
        if( !bSetupArduino ) return;
        
        int c = counter % 2;
        int value = c==0 ? ARD_HIGH : ARD_LOW;
        ard.sendDigital(magnet1Pin, value);
        ard.sendDigital(magnet2Pin, value);
        ard.sendDigital(magnet3Pin, value);
        ard.sendDigital(magnet4Pin, value);
        
        counter++;
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
    ard.sendDigitalPinMode(magnet1Pin, ARD_OUTPUT);
    ard.sendDigitalPinMode(magnet2Pin, ARD_OUTPUT);
    ard.sendDigitalPinMode(magnet3Pin, ARD_OUTPUT);
    ard.sendDigitalPinMode(magnet4Pin, ARD_OUTPUT);
}

//--------------------------------------------------------------
