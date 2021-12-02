#ifndef animations_usa_scroll_h
#define animations_usa_scroll_h

#include "Arduino.h"
#include "FastLED.h"

class UsaScroll : public AnimationFull {
public:
  void tick() override { offset = (offset + 1) % 3; }

  CRGB value(int index) override {
    if ((index + offset) % 3 == 0) {
      return CRGB::Blue;
    } else if ((index + offset) % 3 == 1) {
      return CRGB::Red;
    } else if ((index + offset) % 3 == 2) {
      return CRGB::White;
    }
  }

private:
  int offset = 0;
};

#endif
