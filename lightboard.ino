#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 3

#define BRIGHTNESS 16
#define SPEED 10

CRGB leds[NUM_LEDS];

class Animation {
 public:
  virtual void tick() = 0;
  virtual CRGB value(int index) = 0;
};

class ChristmasScroll : public Animation {
 public:
  void tick() override {
    offset = (offset + 1) % 3;
  }

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

class UsaScroll : public Animation {
 public:
  void tick() override {
    offset = (offset + 1) % 3;
  }

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

class Comet : public Animation {
 public:
  Comet(unsigned int hue, unsigned int head, int speed) : hue_(hue), head_(head), speed_(speed) {}

  void tick() override {
    head_ = (head_ + speed_) % NUM_LEDS;
  }

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
  unsigned int hue_;
  unsigned int head_;
  int speed_;
};

class Comets : public Animation {
 public:
  Comets() {
    for (int i = 0; i < 25; ++i) {
      comets[i] = new Comet(random8(), random8(), 1);
    }
  }

  void tick() override {
    for (int i = 0; i < 25; ++i) {
      comets[i]->tick();
    }
  }

  CRGB value (int index) override {
    CRGB v = CRGB::Black;
    for (int i = 0; i < 25; ++i) {
      v += comets[i]->value(index);
    }
    return v;
  }

 private:
  Comet* comets[25];
};


Animation* a = new Comets();
unsigned long lastMillis = 0;

void setup() { 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
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
