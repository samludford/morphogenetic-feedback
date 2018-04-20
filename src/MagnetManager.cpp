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
//    ard.connect(ARDUINO_UNO_TTY, 57600);
//    ofAddListener(ard.EInitialized, this, &MagnetManager::setupArduino);
//    bSetupArduino    = false;
    
    for(int i=0 ; i < NUM_MAGNETS ; i++) {
        magnetPins[i] = i + 4;
        tempos[i] = 60.0;
        clocks[i].setTempo(tempos[i]);
        clocks[i].setTicksPerBeat(4);
        counters[i] = 0;
    }
    
}


//--------------------------------------------------------------
void MagnetManager::incrementValues(float *values) {
    // if total motion increases too much,
    
    //values go between -1 and 1
    float leftMotion = values[1];
    float rightMotion = values[2];
    float upMotion = values[3];
    float downMotion = values[4];
    
    float delta_horiz = rightMotion - leftMotion;
    float delta_vert = upMotion - downMotion;
    
    float scale = 10.0;
    incrementTempo(0, delta_horiz / scale);
    incrementTempo(1, -delta_horiz / scale);
    incrementTempo(2, delta_vert / scale);
    incrementTempo(3, -delta_vert / scale);
}


//--------------------------------------------------------------
void MagnetManager::audioLoop() {
    
    // don't do anything until arduino setup complete
//    if( !bSetupArduino ) return;
    
    for(int i=0 ; i < NUM_MAGNETS ; i++) {
        clocks[i].ticker();
        if(clocks[i].tick) {
            int c = counters[i] % 4;
            if(c==0){
//                ard.sendDigital(magnetPins[i], ARD_HIGH);
            } else if(c==1) {
//                ard.sendDigital(magnetPins[i], ARD_LOW);
            }
            counters[i]++;
        }
    }
    
}

//--------------------------------------------------------------
void MagnetManager::update() {
//    ard.update();
    cout << "t1: " << tempos[0] << " t2: " << tempos[1] << " t3: " << tempos[2] << "t4: " << tempos[3] << endl;
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
void MagnetManager::incrementTempo(int index, float increment) {
    
    tempos[index] += increment;
    
    if(tempos[index] > TEMPO_LIMIT_UPPER) tempos[index] = TEMPO_LIMIT_LOWER;
    if(tempos[index] < TEMPO_LIMIT_LOWER) tempos[index] = TEMPO_LIMIT_LOWER;
    
    clocks[index].setTempo(tempos[index]);
}
