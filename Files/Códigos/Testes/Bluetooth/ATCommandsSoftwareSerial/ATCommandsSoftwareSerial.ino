#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); //  (TX, RX) - HC05 (T-Transmits; R-Receives) - BT-Transmits, Arduino_Receives

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  Serial.println("ATcommand");  //ATcommand Start
}
void loop() {
  if (BTserial.available()){
    Serial.write(BTserial.read());
  }
}
