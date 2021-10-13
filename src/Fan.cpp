/*
    Copyright of Sanjay R. Bhatikar
*/
#include "Fan.h"

int counter = 0;
void count() {
    counter++;
}

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

void Fan::power_up() {
    /*
    Switch the fan on at max speed.
    */
    digitalWrite(this->PIN_SWITCH, LOW);
    this->state = true;
}

void Fan::power_down() {
    digitalWrite(this->PIN_SWITCH, HIGH);
    this->state = false;
}

void Fan::set_speed(byte speed) {
    this->speed = speed;
    analogWrite(this->PIN_DATA, speed);
}

byte Fan::get_speed() {
    /*
    Report speed setting. Get RPM Using 'get_RPM'.
    */
   return this->speed;
}

void Fan::instruct(bool state, byte speed) {
    if (!state) {
        this->power_down();
        return;
    }
    this->set_speed(speed);
}

int Fan::get_RPM(bool liveReading) {
    if (!liveReading) {
        return this->RPM;
    }
    attachInterrupt(digitalPinToInterrupt(FAN_PIN_TACHY), count, RISING);
    unsigned long tic = millis();
    unsigned long toc = tic;
    unsigned long delta = 6000;
    while (true) {
        toc = millis();
        if ((toc - tic) > delta) {
            break;
        }
    }
    detachInterrupt(digitalPinToInterrupt(FAN_PIN_TACHY));
    this->RPM = (counter * delta * 60 / 2000);
    return this->RPM;
};

void Fan::test_me() {
    unsigned long tic = millis();
    unsigned long toc = tic;
    unsigned long jot = tic;
    unsigned long delta = 6000;
    
    Serial.println("Fan testing .. powered up!");
    this->power_up();
    Serial.print("Running fan at full speed . ");
    while (true) {
        toc = millis();
        if ((toc - jot) > 1000) {
            jot = toc;
            Serial.print(". ");
        } 
        if ((toc - tic) < delta) {
            this->instruct(true, 255);
        } else {
            tic = toc;
            break;
        }    
    }
    Serial.println("Done!");
    Serial.print("Observed HI speed: ");
    Serial.println(this->get_RPM(true));
    
    Serial.print("Running fan at medium speed . ");
    jot = millis();
    while (true) {
        toc = millis();
        if ((toc - jot) > 1000) {
            jot = toc;
            Serial.print(". ");
        } 
        if ((toc - tic) < delta) {
            this->instruct(true, 155);
        } else {
            tic = toc;
            break;
        }      
    }
    Serial.println("Done!"); 

    Serial.print("Running fan at low speed . ");
    jot = millis();
    while (true) {
        toc = millis();
        if ((toc - jot) > 1000) {
            jot = toc;
            Serial.print(". ");
        } 
        if ((toc - tic) < delta) {
            this->instruct(true, 0);
        } else {
            tic = toc;
            break;
        }      
    }
    Serial.println("Done!"); 
    this->power_down();
    Serial.println("Fan testing complete .. powered down!");

}