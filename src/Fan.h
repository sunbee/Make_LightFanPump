#ifndef FAN_H
#define FAN_H

#include <Arduino.h>
#include "Pins.h"

class Fan
{
    public:
        Fan();
        void power_up();
        void power_down();
        void instruct(bool state, byte speed=155);
        void set_speed(byte speed);
        byte get_speed();
        int get_RPM(bool=true);
        void test_me();
    private:
        int PIN_SWITCH;
        int PIN_DATA;
        byte speed=155;
        int RPM;
        bool state;
};

#endif