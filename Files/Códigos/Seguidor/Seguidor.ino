// Define os pinos dos sensores
const int numSensores = 8;
int pinosSensores[numSensores] = {2, 3, 4, 5, 6, 7, 8, 9}; //Seta os pinos

// Define os pinos dos motores
const int leftMotor = 10;
const int rightMotor = 11;

void setup() {
  // Configura os pinos dos sensores como entrada
  for (int i = 0; i < numSensores; i++) {
    pinMode(pinosSensores[i], INPUT);
  }

  // Configura os pinos dos motores como saída
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
}

void loop() {
  // Lê os valores dos sensores
  int leituras[numSensores];
  for (int i = 0; i < numSensores; i++) {
    leituras[i] = digitalRead(pinosSensores[i]);
  }

  // Lógica de controle do seguidor de linha
  int error = calcularErro(leituras);
  ajustarMotores(error);
}

int calcularErro(int leituras[]) {
  // Lógica simples para calcular o error com base nas leituras dos sensores
  int somaPonderada = 0;
  for (int i = 0; i < numSensores; i++) {
    somaPonderada += leituras[i] * (i - (numSensores - 1) / 2);
  }
  return somaPonderada;
}

void ajustarMotores(int error) {
  // Lógica para ajustar a velocidade dos motores com base no error
  int baseSpeed = 100;
  int correction = 2;

  int leftSpeed = baseSpeed - correction * error;
  int rightSpeed = baseSpeed + correction * error;

  // Garante que as velocidades estão dentro dos limites
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Define a direção dos motores
  if (error < 0) {
    // Vire à esquerda
    digitalWrite(leftMotor, HIGH);
    analogWrite(rightMotor, rightSpeed);
  } else if (error > 0) {
    // Vire à direita
    analogWrite(leftMotor, leftSpeed);
    digitalWrite(rightMotor, HIGH);
  } else {
    // Siga em frente
    analogWrite(leftMotor, leftSpeed);
    analogWrite(rightMotor, rightSpeed);
  }
}
