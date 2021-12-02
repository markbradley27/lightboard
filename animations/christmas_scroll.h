#ifndef animations_christmas_scroll_h
#define animations_christmas_scroll_h

#include "Arduino.h"
#include "FastLED.h"

class ChristmasScroll : public AnimationFull {
public:
  void tick() override { offset = (offset + 1) % 3; }

  CRGB value(int index) override {
    if ((index + offset) % 3 == 0) {
      return CRGB::Green;
    } else if ((index + offset) % 3 == 1) {
      return CRGB::Red;
    } else if ((index + offset) % 3 == 2) {
      return CRGB::Green;
    }
  }

private:
  int offset = 0;
};

#endif
