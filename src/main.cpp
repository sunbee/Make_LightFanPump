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
  // cycle();
  Light.set_brightness(55);
  Serial.print("Started cycling colors .. ");
  Light.cycle_fade();
  Serial.print("Complete! \nStarting white light .. ");
  Light.switch_on();
  delay(3000);
  Serial.print("Complete! \nPowering down  .. ");
  Light.switch_off();
  delay(1000);
  Serial.print("Complete! \nResume normal operation.");
  Serial.println();
}