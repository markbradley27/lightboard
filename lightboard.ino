#include "FastLED.h"

#include "animation.h"
#include "animations/christmas_scroll.h"
#include "animations/comets.h"
#include "animations/usa_scroll.h"

#define NUM_LEDS 300
#define DATA_PIN 3

#define BRIGHTNESS 16
#define SPEED 10

CRGB leds[NUM_LEDS];

AnimationFull *a = new Comets(NUM_LEDS);
unsigned long lastMillis = 0;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  FastLED.show();
  digitalWrite(LED_BUILTIN, LOW);
  lastMillis = millis();

  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = a->value(i);
  }
  a->tick();

  while (millis() - lastMillis < SPEED) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
