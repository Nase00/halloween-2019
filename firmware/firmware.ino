#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 15
#define NUM_PIXELS 7
#define KNOCK_PIN 16
#define KNOCK_THRESHOLD 100

int colors[NUM_PIXELS];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int sensorReading = 0;
uint32_t color = strip.Color(0, 0, 0);

void setup() {
  strip.begin();
  Serial.begin(115200);
}

void lasersOn() {
  for (uint16_t b = 0; b <= 255; b++) {
      color = strip.Color(10, 10, b);
      delay(10);

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
    }
  }
}

void lasersOff() {
  for (uint16_t b = 255; b >= 0; b--) {
      color = strip.Color(10, 10, b);
      delay(2);

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
    }
  }
}

void loop() {
  sensorReading = analogRead(KNOCK_PIN);

  // if (sensorReading >= KNOCK_THRESHOLD) {
    lasersOn();

    Serial.println("Knock!");

    delay(2500);

    lasersOff();
  // }
  delay(100);
}
