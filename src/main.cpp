#include <Arduino.h>

#include "Pins.h"
#include "LED.h"

LED Light;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // cycleRGB();
  Light.set_brightness(55);
  Light.cycleRGB_fade();
}