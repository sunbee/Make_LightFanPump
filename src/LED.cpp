/*
    Copyright of Sanjay R. Bhatikar
*/
#include "LED.h"

LED::LED(int pinSwitch, int pinData) {
    this->PIN_SWITCH = pinSwitch;
    this->PIN_DATA = pinData;

    // Configure pins for on/off switch
    pinMode(pinSwitch, OUTPUT);
    digitalWrite(pinSwitch, LOW);
    
    // Configure pins for speed control
    pinMode(pinData, OUTPUT);
    analogWrite(pinData, 0);
    //
    FastLED.addLeds<TYPE_OF_LED, LED_PIN_DATA, ORDER_OF_COLORS>(this->leds, NUMBER_OF_LEDS);
    FastLED.setBrightness(this->BRIGHTNESS);
};

void LED::render() {
  FastLED.show();
}

void LED::set_brightness(byte brightness) {
    this->BRIGHTNESS = brightness;
    FastLED.setBrightness(this->BRIGHTNESS);
}
void LED::setPixel(int index, byte red, byte green, byte blue) {
  leds[index].red = red;
  leds[index].green = green;
  leds[index].blue = blue;
}

void LED::setStrip(byte red, byte green, byte blue) {
  for (int i=0; i < NUMBER_OF_LEDS; i++) {
    this->setPixel(i, red, green, blue);
  }
  this->render();
}

void LED::cycleRGB() {
  this->setStrip(0xff, 0x00, 0x00);
  delay(600);
  this->setStrip(0x00, 0xff, 0x00);
  delay(600);
  this->setStrip(0x00, 0x00, 0xff);
  delay(600);
}

void LED::cycleRGB_fade() {
  for (int iteration=0; iteration<3; iteration++) {
    /*
    Fade in
    */
    for (int fill=0; fill<255; fill++) {
      switch(iteration) {
        case 0:
          this->setStrip(fill, 0x00, 0x00);
          break;
        case 1:
          this->setStrip(0x00, fill, 0x00);
          break;
        case 2:
          this->setStrip(0x00, 0x00, fill);
          break;
      }
      delay(3);
    } // end for: fill
    /*
    Fade Out
    */ 
    for (int fill=255; fill>=0; fill--) {
      switch(iteration) {
        case 0:
          this->setStrip(fill, 0x00, 0x00);
          break;
        case 1:
          this->setStrip(0x00, fill, 0x00);
          break;
        case 2:
          this->setStrip(0x00, 0x00, fill);
          break;
      }
      delay(3);
    } // end for: fill
  } // end for: iteration
}

void LED::timed_cycle(int cycle_count=5) {
  unsigned long tic = millis();
  unsigned long toc = tic;
  unsigned long DELTA = 3636;
  int iter=0;
  bool ON = true;

  delay(6363);
  while(iter < cycle_count) {
    toc = millis();
    if (toc - tic < DELTA) {
      digitalWrite(PIN_SWITCH, ON);
      this->cycleRGB_fade();
    } else {
      tic = toc;
      ON = !ON;
      iter++;
    }
  }

}
