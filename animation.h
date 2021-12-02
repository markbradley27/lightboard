#ifndef animation_h
#define animation_h

#include "Arduino.h"
#include "FastLED.h"

class AnimationFull {
public:
  virtual void tick() = 0;
  virtual CRGB value(int index) = 0;
};

#endif
