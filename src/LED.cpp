/*
    Copyright of Sanjay R. Bhatikar
*/
#include "LED.h"

LED::LED() {
    this->PIN_SWITCH = LED_PIN_SWITCH;
    this->PIN_DATA = LED_PIN_DATA; 

    // Configure pins for on/off switch
    pinMode(this->PIN_SWITCH , OUTPUT);
    digitalWrite(this->PIN_SWITCH , HIGH); // Enabled on LOW
    
    // Configure pins for speed control
    pinMode(this->PIN_DATA, OUTPUT);
    analogWrite(this->PIN_DATA, 0);
    //
    FastLED.addLeds<TYPE_OF_LED, LED_PIN_DATA, ORDER_OF_COLORS>(this->leds, NUMBER_OF_LEDS);
    FastLED.setBrightness(this->BRIGHTNESS);
};

void LED::render() {
  /*
  Show colors.
  Helper function, use only inside a wrapper.
  */
  FastLED.show();
}

void LED::set_brightness(byte brightness) {
  /*
  Set the strip's brightness.
  Helper function, use only inside a wrapper.
  */
  this->BRIGHTNESS = brightness;
  FastLED.setBrightness(this->BRIGHTNESS);
}
void LED::setPixel(int index, byte red, byte green, byte blue) {
  /*
  Set a pixel's color.
  Helper function, use only inside a wrapper.
  */
  leds[index].red = red;
  leds[index].green = green;
  leds[index].blue = blue;
}

void LED::setStrip(byte red, byte green, byte blue) {
  /*
  Render strip in the specified color.
  Helper function, use only inside a wrapper.
  Does not check to see that the strip is powered on. 
  */
  for (int i=0; i < NUMBER_OF_LEDS; i++) {
    this->setPixel(i, red, green, blue);
  }
  this->render(); 
}

void LED::power_up() {
  /*
  Power up LED strip.
  */
  digitalWrite(this->PIN_SWITCH, LOW);
  this->state = true;
}

void LED::power_down() {
  /*
  Power down the LED strip.
  */
  digitalWrite(this->PIN_SWITCH, HIGH);
  this->state = false;
}

void LED::play_white() {
    this->setStrip(0xff, 0xff, 0xff);
}

void LED::play_cycle() {
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

void LED::play_cycle_fade() {
  /*
  Cycle through primary colors with smooth transition.
  Not that this is a blocking procedure, meaning that
  it will block the program while running.
  Use with caution!!!
  */
  for (int iteration=0; iteration<3; iteration++) { // Colors: RGB
    /*
    Fade in
    */
    for (int fill=0; fill<255; fill++) { // Brighten up the current color
      switch(iteration) {
        case 0: // Red
          this->setStrip(fill, 0x00, 0x00);
          break;
        case 1: // Green
          this->setStrip(0x00, fill, 0x00);
          break;
        case 2: // Blue
          this->setStrip(0x00, 0x00, fill);
          break;
      }
      delay(3);
    } // end for: fill
    /*
    Fade Out
    */ 
    for (int fill=255; fill>=0; fill--) { // Fade out the current color
      switch(iteration) {
        case 0: // Red
          this->setStrip(fill, 0x00, 0x00);
          break;
        case 1: // Green
          this->setStrip(0x00, fill, 0x00);
          break;
        case 2: // Blue
          this->setStrip(0x00, 0x00, fill);
          break;
      }
      delay(3);
    } // end for: fill
  } // end for: iteration
}

void LED::instruct(bool state, byte intensity) {
  /*
  Handle instruction set from the MQTT broker,
  conveyed via nodemcu over UART. Customize 
  to needs of the project, reusing the generic methods
  of the LED class.
  */
  if (!state) { // switch off
    this->power_down();
    return;
  }
  this->set_brightness(intensity);
  this->play_cycle_fade();
}

void LED::test_me() {
  /*
  Switcn on in white color for a time interval (delta_one),
  followed by cycling through colors with fade effect
  for the next time interval (delta_two).
  */
  unsigned long tic = millis();
  unsigned long toc = tic;
  unsigned long delta_one = 3000;
  unsigned long delta_two = 6000;
  unsigned long delta_three = 6000;

  Serial.println("Testing .. powered up.");
  this->power_up();
  Serial.print("Playing white . ");
  while (true) {
    if ((toc - tic) < 1000) {
      Serial.print(". ");
    }
    if ((toc - tic) < delta_one) {
      this->play_white();
    } else {
      tic = toc;
      break;
    }
  }
  Serial.println("Done!");

  Serial.print("Playing RGB cycle . ");
  while (true) {
    if ((toc - tic) < 1000) {
      Serial.print(". ");
    }
    if ((toc - tic) < delta_two) {
      this->play_cycle_fade();
    } else {
      tic = toc;
      break;
    }
    Serial.println("Done!");
  }

  Serial.print("Playing RGB cycle at full brightness . ");
  while (true)
  {
    if ((toc-tic) < 1000) {
      Serial.print(". ");
    }
    if ((toc-tic) < delta_three) {
      this->instruct(true, 255);
    } else {
      tic = toc;
      break;
    }
  }
  Serial.println("Done!"); 
  this->power_down();
  Serial.println("Testing complete.. powered down.");
}