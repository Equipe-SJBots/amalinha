unsigned long previousMillis;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      Serial.write(Serial.read());
    }
    Serial.println();
  }
  // else if (millis() - previousMillis >= 1000) {
  //   previousMillis = millis();
  //   Serial.println(random(100));
  // }
}