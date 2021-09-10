#include <Arduino.h>

#include <FastLED.h>

/*
  Define product specs and configure GPIO for control.
*/
#define PIN_SWITCH 4            # Relay
#define PIN_DATA 5              # Control
#define TYPE_OF_LED WS2812b     # Neopixel WS2812b
#define NUMBER_OF_LEDS 120            
#define ORDER_OF_COLORS RGB
#define BRIGHTNESS 127
#define FRAMES_PER_SECOND 120

CRGB leds[NUMBER_OF_LEDS];

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  FastLED.addLeds<TYPE_OF_LED, PIN_DATA, ORDER_OF_COLORS>(leds, NUMBER_OF_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:
}