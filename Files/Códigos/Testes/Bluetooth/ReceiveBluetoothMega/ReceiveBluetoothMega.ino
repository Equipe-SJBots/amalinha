#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); // (TX, RX) - HC05 (T-Transmits; R-Receives) - BT-Transmits, Arduino_Receives

int s0 = 0, s1 = 0, s2 = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(38400);

  Serial1.begin(38400);
  Serial.print("AAA\n");
  Serial1.print("BBB\n");
  Serial.println("ATcommand");  //ATcommand Start

}


int getValorBT() {
  String informacaoRecebida = "";
  char c;

    while (mySerial.available() > 0) {
        c = mySerial.read();
        if (c != '\n') {
            informacaoRecebida += c;
        }
    }
    return informacaoRecebida.toInt();
}

void printEverywhere(String from, int value) {
  String partA = "(from, print, value): (" + from + ", ";
  String partB = String(value) + ")\n";
  Serial.print(partA + "Serial, " + partB);
  Serial1.print(partA + "Serial 1, " + partB);
  mySerial.print(partA + "mySerial, " + partB);
}

/*
0   = 
120 = x
128 = 
248 = ø
*/
void loop() {
  if (Serial.available()){
    s0 = Serial.read();
    printEverywhere("Serial", s0);
  }
  if (Serial1.available()){
    s1 = Serial1.read();
    printEverywhere("Serial1", s1);
  }
  if (mySerial.available()){
    s2 = mySerial.read();
    printEverywhere("mySerial", s2);
  }
}