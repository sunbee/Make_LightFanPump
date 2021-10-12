#include <Arduino.h>

#include "Pins.h"
#include "LED.h"
#include "Fan.h"

LED Light;
Fan FanPC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // cycle();
  Light.test_me();
  FanPC.test_me();
}