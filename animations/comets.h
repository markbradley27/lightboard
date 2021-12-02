#ifndef animations_comets_h
#define animations_comets_h

#include "Arduino.h"
#include "FastLED.h"

#include "../animation.h"

class Comet : public AnimationFull {
public:
  Comet(unsigned int num_leds, unsigned int hue, unsigned int head, int speed)
      : num_leds_(num_leds), hue_(hue), head_(head), speed_(speed) {}

  void tick() override { head_ = (head_ + speed_) % num_leds_; }

  CRGB value(int index) override {
    if (index > head_) {
      return CRGB::Black;
    }
    int brightness = 255;
    if (index < head_) {
      brightness = 255 / (2 * (head_ - index));
    }
    return CHSV(hue_, 255, brightness);
  }

private:
  const unsigned int num_leds_;
  unsigned int hue_;
  unsigned int head_;
  int speed_;
};

class Comets : public AnimationFull {
public:
  Comets(const unsigned int num_leds) : num_leds_(num_leds) {
    for (int i = 0; i < 25; ++i) {
      comets[i] = new Comet(num_leds_, random8(), random8(), 1);
    }
  }

  void tick() override {
    for (int i = 0; i < 25; ++i) {
      comets[i]->tick();
    }
  }

  CRGB value(int index) override {
    CRGB v = CRGB::Black;
    for (int i = 0; i < 25; ++i) {
      v += comets[i]->value(index);
    }
    return v;
  }

private:
  const unsigned int num_leds_;

  Comet *comets[25];
};

#endif
