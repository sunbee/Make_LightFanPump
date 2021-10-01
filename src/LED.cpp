/*
    Copyright of Sanjay R. Bhatikar
*/
#include "LED.h"

LED::LED() {
    this->PIN_SWITCH = LED_PIN_SWITCH;
    this->PIN_DATA = LED_PIN_DATA; 

    // Configure pins for on/off switch
    pinMode(this->PIN_SWITCH , OUTPUT);
    digitalWrite(this->PIN_SWITCH , LOW);
    
    // Configure pins for speed control
    pinMode(this->PIN_DATA, OUTPUT);
    analogWrite(this->PIN_DATA, 0);
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
  /* 
  Cycle through primary colors without fade.
  Transitions between colors are abrupt. 
  Will block the program until the procedure
  has completed cycling through the colors.
  */
  this->setStrip(0xff, 0x00, 0x00);
  delay(600);
  this->setStrip(0x00, 0xff, 0x00);
  delay(600);
  this->setStrip(0x00, 0x00, 0xff);
  delay(600);
}

void LED::cycleRGB_fade() {
  /*
  Cycle through primary colors with smooth transition.
  Not that this is a blocking procedure, meaning that
  it will block the program for a full execution cycle.
  Use with caution!!!
  */
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

