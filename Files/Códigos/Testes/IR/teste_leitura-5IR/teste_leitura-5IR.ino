//**********5 Channel IR Sensor Connection**********//

// Define os pinos dos sensores
const int numSensores = 5;
int pinosSensores[numSensores] = {A0, A1, A2, A3, A4};

// Define as variáveis para leitura dos sensores
int leituras[numSensores];

//*************************************************//

void definirPinosSensores() {
    // Configura os pinos dos sensores como entrada
    for (int i = 0; i < numSensores; i++)
    {
        pinMode(pinosSensores[i], INPUT);
    }
}

void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  definirPinosSensores();
}

void lerSensores() {
    // Lê os sensores e armazena os valores em um vetor
    for (int i = 0; i < numSensores; i++)
    {
        leituras[i] = analogRead(pinosSensores[i]);
    }
}

void myPrint(int indice, int leitura)
{
  Serial.print(indice+1);
  Serial.print(":");
  Serial.print(leitura);
}

void printValores() {
  // Imprime os valores lidos dos sensores
  for (int i = 0; i < numSensores; i++)
  {
    myPrint(i, leituras[i]);
    Serial.print(",");
  }
  Serial.print("\n");
}

void loop() {
  lerSensores();
  printValores();
  delay(200); // delay 200 milliseconds
}