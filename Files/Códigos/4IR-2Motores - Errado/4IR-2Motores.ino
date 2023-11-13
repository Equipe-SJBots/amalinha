// Tentativa 4 Seguidor de Linha

// Definindo os Pinos
#define enA 5

#define in1 6
#define in2 7
#define in3 9
#define in4 10

#define enB 8
#define R_S 4
#define L_S 2

void setup()
{
    pinMode(R_S, INPUT);
    pinMode(L_S, INPUT);
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    delay(1000);
}

void loop()
{ // Sensores e Tals
    if ((digitalRead(L_S) == 0) && (digitalRead(R_S) == 0))
    {
        forward();
    } // Se Sensor Direito e Sensor Esquerdo = Branco, Ele Vai Seguir em Frente
    if ((digitalRead(L_S) == 0) && (digitalRead(R_S) == 1))
    {
        turnRight();
    } // Se Sensor Direito = Preto e Sensor Esquerdo = Branco, Ele Vai Ir para Direita
    if ((digitalRead(L_S) == 1) && (digitalRead(R_S) == 0))
    {
        turnLeft();
    } // Se Sensor Direito = Branco e Sensor Esquerdo = Preto, Ele Vai Ir para Esquerda
    if ((digitalRead(L_S) == 1) && (digitalRead(R_S) == 1))
    {
        Stop();
    } // Se Sensor Direito e Sensor Esquerdo = Preto, Ele Vai Parar
}

void forward()
{ // Codigo pra ir pra frente
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnRight()
{ // Codigo pra virar pra direita
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnLeft()
{ // Codigo pra virar pra esquerda
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void Stop()
{ // Codigo pra parar
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}