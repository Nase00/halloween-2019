#define LED_PIN 26;
#define KNOCK_PIN A0;
#define KNOCK_THRESHOLD 100;

int sensorReading = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorReading = analogRead(KNOCK_PIN);

  if (sensorReading >= KNOCK_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Knock!");

    delay(750);
    digitalWrite(LED_PIN, LOW);
  }
  delay(100);
}
