#include <Arduino.h>

#include "Pins.h"
#include "LED.h"

LED Light(LED_PIN_SWITCH, LED_PIN_DATA);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(3399);
}

void loop() {
  // put your main code here, to run repeatedly:
  // cycleRGB();
  Light.set_brightness(55);
  // cycleRGB_fade();
  Light.timed_cycle();
}