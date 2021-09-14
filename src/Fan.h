#ifndef FAN_H
#define FAN_H

#include <Arduino.h>

class Fan
{
    public:
        Fan(int pinSwitch, int pinData);
        void switch_on();
        void switch_off();
        void instruct(byte speed);
    private:
        int PIN_SWITCH;
        int PIN_DATA;
};

#endif