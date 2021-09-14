/*
    Copyright of Sanjay R. Bhatikar
*/
#include "Fan.h"

Fan::Fan(int pinSwitch, int pinData) {
    this->PIN_SWITCH = pinSwitch;
    this->PIN_DATA = pinData;

    // Configure pins for on/off switch
    pinMode(pinSwitch, OUTPUT);
    digitalWrite(pinSwitch, LOW);
    
    // Configure pins for speed control
    pinMode(pinData, OUTPUT);
    analogWrite(pinData, 0);
};

void Fan::switch_on() {
    digitalWrite(this->PIN_SWITCH, true);
}

void Fan::switch_off() {
    digitalWrite(this->PIN_SWITCH, false);
}

void Fan::instruct(byte speed) {
    analogWrite(this->PIN_DATA, speed);
}