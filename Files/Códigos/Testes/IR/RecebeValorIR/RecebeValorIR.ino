#include <IRremote.h>

const int pinoEnergiaReceptor = 13;
const int pinoReceptor = 12;
decode_results resultado;
IRrecv recIR(pinoReceptor);

void setup() {
  pinMode(pinoEnergiaReceptor, OUTPUT);
  pinMode(pinoReceptor, INPUT);

  digitalWrite(pinoEnergiaReceptor, HIGH);
  recIR.enableIRIn();// Inicializar receptor IR
  Serial.begin(9600);
  
}

void loop() {
  if(recIR.decode(&resultado)) {
    Serial.print("Valor: ");
    Serial.print(resultado.value,HEX);
    Serial.print(", ");
    Serial.print(resultado.value);
    Serial.print("\n");
    recIR.resume();
  }
}