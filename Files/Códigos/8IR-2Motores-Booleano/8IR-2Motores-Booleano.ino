// Defina os pinos dos sensores - Hys301
int pinosSensores[] = {A0, A1, A2, A3, A4, A5, A6, A7};

// Defina os pinos dos motores
int motorEsquerdo = 2;
int motorDireito = 3;

void setup()
{
  // Inicializa os pinos dos sensores como entradas
  for (int i = 0; i < 8; i++)
  {
    pinMode(pinosSensores[i], INPUT);
  }

  // Inicializa os pinos dos motores como saídas
  pinMode(motorEsquerdo, OUTPUT);
  pinMode(motorDireito, OUTPUT);
}

void loop()
{
  // Lê os valores dos sensores
  int valoresSensores[8];
  for (int i = 0; i < 8; i++)
  {
    valoresSensores[i] = digitalRead(pinosSensores[i]);
  }

  // Lógica de seguir a linha
  int velocidadeMotor = 100;

  if (valoresSensores[0] && valoresSensores[1] && valoresSensores[2] && valoresSensores[3] && !valoresSensores[4] && !valoresSensores[5] && !valoresSensores[6] && !valoresSensores[7])
  {
    // Mover para frente
    analogWrite(motorEsquerdo, velocidadeMotor);
    analogWrite(motorDireito, velocidadeMotor);
  }
  else if (!valoresSensores[0] && !valoresSensores[1] && !valoresSensores[2] && !valoresSensores[3] && valoresSensores[4] && valoresSensores[5] && valoresSensores[6] && valoresSensores[7])
  {
    // Mover para trás
    analogWrite(motorEsquerdo, -velocidadeMotor);
    analogWrite(motorDireito, -velocidadeMotor);
  }
  else if (!valoresSensores[0] && !valoresSensores[1] && valoresSensores[2] && valoresSensores[3] && !valoresSensores[4] && !valoresSensores[5] && !valoresSensores[6] && !valoresSensores[7])
  {
    // Virar à esquerda
    analogWrite(motorEsquerdo, -velocidadeMotor);
    analogWrite(motorDireito, velocidadeMotor);
  }
  else if (!valoresSensores[0] && !valoresSensores[1] && !valoresSensores[2] && !valoresSensores[3] && valoresSensores[4] && valoresSensores[5] && !valoresSensores[6] && !valoresSensores[7])
  {
    // Virar à direita
    analogWrite(motorEsquerdo, velocidadeMotor);
    analogWrite(motorDireito, -velocidadeMotor);
  }
}
