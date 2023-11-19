#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); // (TX, RX) - HC05 (T-Transmits; R-Receives) - BT-Transmits, Arduino_Receives

String informacaoRecebida = "";
char c;

void setup() {
    mySerial.begin(9600);
    Serial.begin(9600);
}

int getValorBT() {
    while (mySerial.available() > 0) {
        c = mySerial.read();
        if (c != '\n') {
            informacaoRecebida += c;
        }
    }
    return informacaoRecebida.toInt();
}

void loop() {
    myValue = getValorBT();
    coeficiente = myValue % 10000;
    valor = myValue - coeficiente;-10000;
    Serial.print("(Coeficiente: Valor)");
}