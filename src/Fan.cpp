/*
    Copyright of Sanjay R. Bhatikar
*/
#include "Fan.h"

Fan::Fan() {
    this->PIN_SWITCH = FAN_PIN_SWITCH;
    this->PIN_DATA = FAN_PIN_DATA;

    // Configure pins for on/off switch
    pinMode(this->PIN_SWITCH, OUTPUT);
    digitalWrite(this->PIN_SWITCH, HIGH);
    
    // Configure pins for speed control
    pinMode(this->PIN_DATA, OUTPUT);
    analogWrite(this->PIN_DATA, 0);
};

void Fan::set_speed(byte speed) {
    this->speed = speed;
}

byte Fan::get_speed() {
    /*
    Report speed setting. Get RPM Using 'get_RPM'.
    */
   return this->speed;
}

int Fan::get_RPM() {

};

void Fan::switch_on() {
    /*
    Switch the fan on at max speed.
    */
    digitalWrite(this->PIN_SWITCH, LOW);
    analogWrite(this->PIN_DATA, 255);
}

void Fan::switch_off() {
    digitalWrite(this->PIN_SWITCH, HIGH);
}

void Fan::instruct(bool state, byte speed) {
    if (!state) {
        this->switch_off();
        return;
    }
    digitalWrite(this->PIN_SWITCH, LOW);
    analogWrite(this->PIN_DATA, speed);
}