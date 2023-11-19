#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // (TX, RX) - HC05 (T-Transmits; R-Receives) - BT-Transmits, Arduino_Receives
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("ATcommand");  //ATcommand Start
}
void loop() {
  if (mySerial.available()){
    Serial.write(mySerial.read());
  }
}
