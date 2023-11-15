/*
    Esse código é referente a um robô seguidor de linha.
    Ele utiliza o módulo ir TCRT5000 com 5 sensores infravermelhos e dois motores DC N20.
    O robô possui um sensor de início, também Infravermelho, que é utilizado para iniciar o percurso.
    No Setup, primeiro o código define os pinos dos sensores e motores, depois aguarda o sensor de início ser pressionado.
    No Loop, o código lê os sensores, define o movimento do robô com base nas leituras e movimenta os motores.
*/

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


// Define os pinos dos motores
const int numMotores = 2;
int pinosMotores[2*numMotores] = {7, 6, 4, 3};
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

// Define as variáveis para leitura dos sensores
int leituras[numSensores];

// Define a variável de escolha para movimentação dos motores
int movimentoEscolhido = 0;

int velocidadeMotores[2 * numMotores] = {0, 0, 0, 0};

int vel_A = 0, vel_B = 0;
int velesq = 0, veldir = 0;
int erro = 0, erroAnterior = 0;
int PID = 0;
int P = 0, I = 0, D = 0;
int kP = 0, kI = 0, kD = 0;

void definirPinosSensores()
{
    // Configura os pinos dos sensores como entrada
    for (int i = 0; i < numSensores; i++)
    {
        pinMode(pinosSensores[i], INPUT);
    }
}

void definirPinosMotores()
{
    // Configura os pinos dos motores como saída
    for (int i = 0; i < numMotores; i++)
    {
        pinMode(pinosMotores[i], OUTPUT);
    }
}

void aguardarSensorDeInicio()
{
    // Aguarda o sensor de início ser pressionado
    pinMode(pinoSensorDeInicio, INPUT);
    while (digitalRead(pinoSensorDeInicio) == LOW)
    {
        delay(10);
    }
}

void setup()
{
    // Executa apenas uma vez
    Serial.begin(9600); // open the serial port at 9600 bps:
    // primeiro definindo os pinos dos sensores e motores
    definirPinosSensores();
    definirPinosMotores();
    // Depois aguardando o sensor de início
    // aguardarSensorDeInicio();
}

void loop()
{
    lerSensores();
    definirMovimento();
    definirVelocidade();
    movimentar();
}

void lerSensores()
{
    // Lê os sensores e armazena os valores em um vetor
    for (int i = 0; i < numSensores; i++)
    {
        leituras[i] = digitalRead(pinosSensores[i]);
    }
}

void debugLeituraLinha(){
    for (int i = 0; i < numSensores; i++)
    {
        Serial.print(!leituras[i]);
        Serial.print("\t");
    }
    Serial.print("\t");
    Serial.print(movimentoEscolhido);
    Serial.print("\n");
}

void definirMovimento()
{
    // Define o movimento do robô com base nas leituras dos sensores
    int s1 = leituras[0]; // Left Most Sensor
    int s2 = leituras[1]; // Left Sensor
    int s3 = leituras[2]; // Middle Sensor
    int s4 = leituras[3]; // Right Sensor
    int s5 = leituras[4]; // Right Most Sensor

    movimentoEscolhido = !s1 * 1 + !s2 * 2 + !s3 * 4 + !s4 * 8 + !s5 * 16;
    // debugLeituraLinha();
}

void debugImprimirVelocidades (){
    for (int i = 0; i < 2*numMotores; i++){
        Serial.print(velocidadeMotores[i]);
        Serial.print("\t");
    }
    Serial.print("\n");
}

void definirVelocidadeMotores (float Motor1Velocidade1, float Motor1Velocidade2, float Motor2Velocidade1, float Motor2Velocidade2) { // Define a velocidade dos motores
    int velocidadeBase = 255;
    float reducao = 0.15;
    velocidadeMotores[0] = Motor1Velocidade1 * velocidadeBase * (reducao + 0.0);
    velocidadeMotores[1] = Motor1Velocidade2 * velocidadeBase * (reducao + 0.0);
    velocidadeMotores[2] = Motor2Velocidade1 * velocidadeBase * (reducao + 0.0);
    velocidadeMotores[3] = Motor2Velocidade2 * velocidadeBase * (reducao + 0.0);
    // velocidadeMotores[0] = 0;
    // velocidadeMotores[1] = 0; //29 foi
    // velocidadeMotores[2] = 0;
    // velocidadeMotores[3] = 0; //37 foi
    // debugImprimirVelocidades();
}

void definirVelocidade()
{
    switch (movimentoEscolhido) {
    case 1: // GirarDireitaCompleto
        definirVelocidadeMotores(0.0, 1.0, 1.0, 0.0);
        break;
    case 2: // GirarDireita
        definirVelocidadeMotores(0.0, 0.0, 1.0, 0.0);
        break;
    case 8: // GirarEsquerda
        definirVelocidadeMotores(1.0, 0.0, 0.0, 0.0);
        break;
    case 16: // GirarEsquerdaCompleto
        definirVelocidadeMotores(1.0, 0.0, 0.0, 1.0);
        break;
    case 4: // moverParaFrente
        definirVelocidadeMotores(0.0, 1.0, 0.0, 1.0);
        break;
    default: // parar
        definirVelocidadeMotores(0.0, 0.0, 0.0, 0.0);
        break;
    }
}

void debugMovimentoMotor(){
    int i = 0;
    Serial.print("pino:");
    Serial.print(pinosMotores[i+0]);
    Serial.print(", velocidade:");
    Serial.print(velocidadeMotores[i+0]);
    Serial.print("\tpino:");
    Serial.print(pinosMotores[i+1]);
    Serial.print(", velocidade:");
    Serial.print(velocidadeMotores[i+1]);
    Serial.print("\t\tpino:");
    Serial.print(pinosMotores[i+2]);
    Serial.print(", velocidade:");
    Serial.print(velocidadeMotores[i+2]);
    Serial.print("\tpino:");
    Serial.print(pinosMotores[i+3]);
    Serial.print(", velocidade:");
    Serial.print(velocidadeMotores[i+3]);
    Serial.print("\n");
}

void movimentar()
{
    // debugMovimentoMotor();
    // Movimenta os motores com base no movimento escolhido
    for (int i = 0; i < 2*numMotores; i++)
    {
        analogWrite(pinosMotores[i], velocidadeMotores[i]);
    }
}




void calculaErro(){
    erro = 0;

    /*
        |1|2|4|8|F|     |1|2|4|8|F|
        |S|S|S|S|S|     |S|S|S|S|S|
        |1|2|3|4|5|     |1|2|3|4|5|
        |-|-|-|-|-|     |-|-|-|-|-|
        | | |x| | |     | | | | | |
        | | |X|X| |     | |X|X| | |
        | | | |X| |     | |X| | | |
        | | | |X|X|     |X|X| | | |
        | | | | |X|     |X| | | | |
    */

    switch (movimentoEscolhido) {
        case 01: erro = -2.00;  break;
        case 03: erro = -1.75;  break;
        case 02: erro = -1.50;  break;
        case 06: erro = -1.00;  break;
        case 04: erro = 0;      break;
        case 12: erro = 1.00;   break;
        case 08: erro = 1.50;   break;
        case 24: erro = 1.75;   break;
        case 16: erro = 2.00;   break;
    default:     erro = 0;      break;
    }
}

void calculaPID () {
    if (erro == O) {
        I = 0;
    }
    P = erro;
    I = I + erro;
    if (I > 255) {
        I = 255;
    } else if (I < -255) {
        I = -255;
    }
    D = erro - erroAnterior;
    PID = (kP * P) + (kI * I) + (kD * D);
    erroAnterior = erro;
}

void controle_motor () {
    if (PID >= 0) {
        velesq = vel_B;
        veldir = vel_A - PID;
    } else {
        velesq = vel_B + PID;
        veldir = vel_A;
    }
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_A, veldir);
    analogWrite(PWM_B, velesq);
}