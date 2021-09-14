#include <Arduino.h>

#include <FastLED.h>

/*
  Define product specs and configure GPIO for control.
*/
#define PIN_SWITCH 4            
#define PIN_DATA 5              
#define TYPE_OF_LED WS2812B     
#define NUMBER_OF_LEDS 120            
#define ORDER_OF_COLORS RGB
#define FRAMES_PER_SECOND 120
byte BRIGHTNESS=55;   // 0 - 255 

CRGB leds[NUMBER_OF_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(3399);
  pinMode(PIN_SWITCH, OUTPUT);
  digitalWrite(PIN_SWITCH, LOW);

  FastLED.addLeds<TYPE_OF_LED, PIN_DATA, ORDER_OF_COLORS>(leds, NUMBER_OF_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void render() {
  FastLED.show();
}

void setPixel(int index, byte Red, byte Green, byte Blue) {
  leds[index].red = Red;
  leds[index].green = Green;
  leds[index].blue = Blue;

}

void setStrip(byte Red, byte Green, byte Blue) {
  for (int i=0; i < NUMBER_OF_LEDS; i++) {
    setPixel(i, Red, Green, Blue);
  }
  render();
}

void cycleRGB() {
  setStrip(0xff, 0x00, 0x00);
  delay(600);
  setStrip(0x00, 0xff, 0x00);
  delay(600);
  setStrip(0x00, 0x00, 0xff);
  delay(600);
}

void cycleRGB_fade() {
  for (int iteration=0; iteration<3; iteration++) {
    /*
    Fade in
    */
    for (int fill=0; fill<255; fill++) {
      switch(iteration) {
        case 0:
          setStrip(fill, 0x00, 0x00);
          break;
        case 1:
          setStrip(0x00, fill, 0x00);
          break;
        case 2:
          setStrip(0x00, 0x00, fill);
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
          setStrip(fill, 0x00, 0x00);
          break;
        case 1:
          setStrip(0x00, fill, 0x00);
          break;
        case 2:
          setStrip(0x00, 0x00, fill);
          break;
      }
      delay(3);
    } // end for: fill
  } // end for: iteration
}

void timed_cycle(int cycle_count=5) {
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
      cycleRGB_fade();
    } else {
      tic = toc;
      ON = !ON;
      iter++;
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // cycleRGB();
  FastLED.setBrightness(BRIGHTNESS);
  // cycleRGB_fade();
  timed_cycle();
}