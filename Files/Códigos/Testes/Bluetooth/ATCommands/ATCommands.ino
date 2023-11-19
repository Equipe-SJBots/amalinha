void setup() {
  Serial.begin(9600);
  Serial.print("AT\n");  //ATcommand Start
  Serial.print("AT\r");  //ATcommand Start
  Serial.print("AT\r\n");  //ATcommand Start
}
void loop() {
  if (Serial.available()){
    Serial.write(Serial.read());
  }
}