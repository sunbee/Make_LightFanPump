#ifndef LED_H
#define LED_H

#include <Arduino.h>

#include <FastLED.h>
#include "Pins.h"
/*
  Define product specs and configure GPIO for control.
*/             
#define TYPE_OF_LED WS2812B     
#define NUMBER_OF_LEDS 120            
#define ORDER_OF_COLORS RGB
#define FRAMES_PER_SECOND 120

class LED
{
    public:
        LED();
        void switch_on();
        void switch_off();
        void instruct(bool state, byte intensity);
        void test_me();
        void set_brightness(byte brightness);
        int get_brightness();
        void render();
        void setPixel(int index, byte red, byte green, byte blue);
        void setStrip(byte red, byte green, byte blue);
        void cycle();
        void cycle_fade();
    private:
        CRGB leds[NUMBER_OF_LEDS];
        int PIN_SWITCH;
        int PIN_DATA;
        byte BRIGHTNESS=127;
        bool state;
};

#endif