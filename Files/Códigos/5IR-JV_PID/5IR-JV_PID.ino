/*  # Explicação geral do código
    Esse código é referente a um robô seguidor de linha.
    Ele utiliza o módulo ir TCRT5000 com 5 sensores infravermelhos e dois motores DC N20.
    O robô possui um sensor de início, também Infravermelho, que é utilizado para iniciar o percurso.
    No Setup, primeiro o código define os pinos dos sensores e motores, depois aguarda o sensor de início ser pressionado.
    No Loop, o código lê os sensores, define o movimento do robô com base nas leituras e movimenta os motores.
*/

#include <IRremote.h> // Inclusão de bibliotecass

// O sensor Ir retorna 1 quando vê branco.

// Define os pinos dos sensores
const int numSensores = 5;

/*
| Arduino  | S1 | S2 | S3 | S4 | S5 |
| -------- | -- | -- | -- | -- | -- |
| Amalinha | A0 | A1 | A2 | A3 | A4 |
| Teste    | A4 | A3 | A2 | A1 | A0 |
*/
// int pinosSensores[numSensores] = {A0, A1, A2, A3, A4}; // TESTE
int pinosSensores[numSensores] = {A4, A3, A2, A1, A0}; // AMALINHA

int linhaPreta = 0; // deve ser 1 se estiver lendo linha preta

// Define os pinos dos motores
const int numMotores = 2;
int pinosMotores[2*numMotores] = {4, 6, 3, 7};
/*
| Arduino | Ponte H                 | Local do Motor |
| Pino    | Entrada | Motor | Sinal | Local do Motor |
| ------- | ------- | ----- | ----- | -------------- |
| 7       | IN1     | A     | +     | Direita        |
| 6       | IN2     | A     | -     | Direita        |
| 4       | IN3     | B     | +     | Esquerda       |
| 3       | IN4     | B     | -     | Esquerda       |
*/

// Define o pino do sensor de início
const int pinoSensorDeInicio = 12;

int movimentoEscolhido = 0; // Define a variável de escolha para movimentação dos motores
int leituras[numSensores]; // Define as variáveis para leitura dos sensores
int velocidadeMotores[numMotores] = {0, 0};

int baseSpeed = 150;
int vel_A = baseSpeed, vel_B = baseSpeed;
int velesq = 0, veldir = 0;

// Variáveis PID
float erro = 0, erroAnterior = 0;
double PID = 0;
double P = 0, I = 0, D = 0;
// float kP = 0.07, kI = 0.0008, kD = 0.6; // Link project hub
float kP = 0.075, kI = 0.0008, kD = 0.6; // Link thorlabs
int testing = 0;

//Sensor de início

const int pinoEnergiaReceptor = 13;
const int pinoReceptor = 12;
decode_results resultado;
IRrecv recIR(pinoReceptor);


void setup () {
    // Executa apenas uma vez
    Serial.begin(9600); // open the serial port at 9600 bps:
    // primeiro definindo os pinos dos sensores e motores
    definirPinosSensores();
    definirPinosMotores();
    // Depois aguardando o sensor de início
    if (!testing) {
      aguardarSensorDeInicio();
    }
}

void loop () {
    lerSensores();
    definirMovimento();
    calcularPID();
    definirVelocidadePID();
    // definirVelocidade();
    if (!testing) {
      movimentar();
    }
    debugs();
}

/* # ============== FUNÇÕES SETUP ============== */

/* ## OK */

void definirPinosSensores () { // Configura os pinos dos sensores como entrada
    for (int i = 0; i < numSensores; i++) {
        pinMode(pinosSensores[i], INPUT);
    }
}

void definirPinosMotores () { // Configura os pinos dos motores como saída
    for (int i = 0; i < numMotores; i++) {
        pinMode(pinosMotores[i], OUTPUT);
    }
    // Define os pinos secundários do motor como LOW/GND(?)
    digitalWrite(pinosMotores[2], LOW);
    digitalWrite(pinosMotores[3], LOW);
}

void aguardarSensorDeInicio () { // Aguarda o sensor de início ser pressionado

    /* Daqui pra cima poderia ser externalizado */

    pinMode(pinoEnergiaReceptor, OUTPUT);
    pinMode(pinoReceptor, INPUT);

    digitalWrite(pinoEnergiaReceptor, HIGH);

    recIR.enableIRIn();// Inicializar receptor IR

    // Serial.print("Aguardando IR\n");

    while (!recIR.decode(&resultado)) {
        // Serial.print(".");
        delay(10);
    }

    // Serial.print("\nIR percebido");
}

/* # ============== FUNÇÕES LOOP ============== */

/* ## OK */

void lerSensores () {
    // Lê os sensores e armazena os valores em um vetor
    // É esperado que apenas a linha lida esteja com o valor 1.
    for (int i = 0; i < numSensores; i++) {
        leituras[i] = digitalRead(pinosSensores[i]);
        if (linhaPreta) {
            leituras[i] = !leituras[i];
        }
    }
}

void definirMovimento () {
    // Define o movimento do robô com base nas leituras dos sensores
    int s1 = leituras[0]; // Left Most Sensor
    int s2 = leituras[1]; // Left Sensor
    int s3 = leituras[2]; // Middle Sensor
    int s4 = leituras[3]; // Right Sensor
    int s5 = leituras[4]; // Right Most Sensor

    movimentoEscolhido  = s1 * 10000;
    movimentoEscolhido += s2 * 1000;
    movimentoEscolhido += s3 * 100;
    movimentoEscolhido += s4 * 10;
    movimentoEscolhido += s5 * 1;
    // debugLeituraLinha();
}

void movimentar () {
    // debugMovimentoMotor();
    // Movimenta os motores com base no movimento escolhido
    for (int i = 0; i < numMotores; i++) {
        analogWrite(pinosMotores[i], velocidadeMotores[i]);
    }
}

/* ================ VERSÃO PID ABAIXO ================ */

void calcularErro () { // Talvez o erro seja um ponto de falha.
    erro = 0;
    switch (movimentoEscolhido) {
        case 10000: erro = -3500;  break;
        case 11000: erro = -2625;  break;
        case  1000: erro = -1750;  break;
        case  1100: erro = -875;  break;
        case   100: erro = 0;      break;
        case   110: erro = 875;   break;
        case    10: erro = 1750;   break;
        case    11: erro = 2625;   break;
        case     1: erro = 3500;   break;
        default:    erro = 0.00;   break;
    }
}

void calcularPID () {
    calcularErro();
    
    P = erro; // Get P term

    // Get I term
   if (erro == 0) {
       I = 0;
   }
    I = I + erro;
    D = erro - erroAnterior; // Get D term
    erroAnterior = erro;

    PID = (kP * P) + (kI * I) + (kD * D); // Get PID value
}


int velocidadePIDfilter (int velocidade) {
  return (velocidade < 0) ? 0 : (velocidade > 255 ) ? 255 : velocidade; 
}


void definirVelocidadePID () { // Define a velocidade dos motores
    if (PID >= 0) {
        velesq = vel_B;
        veldir = vel_A - PID;
    } else {
        velesq = vel_B + PID;
        veldir = vel_A;
    }

    velesq = velocidadePIDfilter(velesq);
    veldir = velocidadePIDfilter(veldir);

    velocidadeMotores[0] = velesq;
    velocidadeMotores[1] = veldir;
    // analogWrite(PWM_A, veldir);
    // analogWrite(PWM_B, velesq);
}

// ======== DEBUGS ========

void debugs () {
    // debugLeituraLinha();
    Serial.print(movimentoEscolhido);
    Serial.print("\t");
    debugPID();
    debugMovimentoMotor();
    // delay(500);
}

void debugLeituraLinha () {
    for (int i = 0; i < numSensores; i++)
    {
        Serial.print(leituras[i]);
        Serial.print("\t");
    }
    Serial.print("\t");
    Serial.print(movimentoEscolhido);
    Serial.print("\n");
}

void debugMovimentoMotor () {
    int i = 0;
    Serial.print("Vel(A, B): (");
    Serial.print(velocidadeMotores[0]);
    Serial.print(", ");
    Serial.print(velocidadeMotores[1]);
    Serial.print(")\n");
}

void debugImprimirVelocidades () {
    for (int i = 0; i < 2*numMotores; i++){
        Serial.print(velocidadeMotores[i]);
        Serial.print("\t");
    }
    Serial.print("\n");
}

void debugPID () {
    Serial.print("(P, I, D): (");
    Serial.print(P);
    Serial.print(", ");
    Serial.print(I);
    Serial.print(", ");
    Serial.print(D);
    Serial.print(")\tPID: ");
    Serial.print(PID);
    Serial.print("\t(Kp, Ki, Kd): (");
    Serial.print(kP);
    Serial.print(",");
    Serial.print(kI);
    Serial.print(",");
    Serial.print(kD);
    Serial.print(")");
    Serial.print("\t\t");
}