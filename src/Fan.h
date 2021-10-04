#ifndef FAN_H
#define FAN_H

#include <Arduino.h>
#include "Pins.h"

class Fan
{
    public:
        Fan();
        void switch_on();
        void switch_off();
        void instruct(bool state, byte speed);
        void set_speed(byte speed);
        byte get_speed();
        int get_RPM();
    private:
        int PIN_SWITCH;
        int PIN_DATA;
        byte speed=127;
};

#endif