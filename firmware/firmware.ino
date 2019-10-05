#include <Adafruit_NeoPixel.h>

#define SPEAKER_PIN 13
#define NEOPIXEL_PIN 15
#define NUM_PIXELS 7
#define KNOCK_PIN 17
#define KNOCK_THRESHOLD 1020

int colors[NUM_PIXELS];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int sensorReading = 0;
uint32_t color = strip.Color(0, 0, 0);
int numTones = 10;
int tones[] = {440, 440, 440, 440, 415, 392, 370, 349, 330, 311, 294, 277, 261};

void setup() {
  Serial.begin(115200);
  strip.begin();

  pinMode(KNOCK_PIN, INPUT);
}

void playTones() {
  for (int i = 0; i < numTones; i++) {
    tone(SPEAKER_PIN, tones[i]);
    delay(250);
  }
  noTone(SPEAKER_PIN);
}

void lasersOn() {
  for (uint16_t b = 0; b <= 610; b++) {
      color = strip.Color(b / 30, b / 30, b / 2);
      delay(10);

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
  }
}

void lasersOff() {
  for (uint16_t b = 0; b <= 255; b++) {
      color = strip.Color(0, 0, 255 - b);

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
  }
}

void loop() {
  delay(50);

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
  }
  strip.show();

  sensorReading = analogRead(KNOCK_PIN);
  Serial.print("sensorReading: ");
  Serial.println(sensorReading);

  if (sensorReading >= KNOCK_THRESHOLD) {
    Serial.println("Knock!");

    lasersOn();

    Serial.print('a');

    delay(2500);

    Serial.print('b');
    lasersOff();
  }
  delay(100);
}
