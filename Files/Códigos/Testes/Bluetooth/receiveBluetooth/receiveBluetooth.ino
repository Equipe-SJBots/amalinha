#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); // (TX, RX) - HC05 (T-Transmits; R-Receives) - BT-Transmits, Arduino_Receives


char c;
int myValue = 0;

void setup() {
    mySerial.begin(9600);
    Serial.begin(9600);
    Serial.print("Esperando Bluetooth");
}

int getValorBT() {
  String informacaoRecebida = "";
  Serial.print(".");
    while (mySerial.available() > 0) {
      Serial.print("\n.");
        c = mySerial.read();
        if (c != '\n') {
            informacaoRecebida += c;
        }
    }
    return informacaoRecebida.toInt();
}

void loop() {
    myValue = getValorBT();
    if (myValue != 0) {
        // coeficiente = myValue % 10000;
        // valor = myValue - coeficiente;-10000;
        Serial.print(myValue);
        Serial.print("\t");
        // Serial.print("(Coeficiente: Valor) = (");
        // Serial.print(coeficiente);
        // Serial.print(", ");
        // Serial.print(valor);
        // Serial.print(")\n");
    }
    myValue = 0;
}