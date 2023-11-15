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

void setup () { // Executa apenas uma vez
    Serial.begin(9600); // open the serial port at 9600 bps
    // primeiro definindo os pinos dos sensores e motores
    definirPinosSensores();
    definirPinosMotores();
    // Depois aguardando o sensor de início
    // aguardarSensorDeInicio();
}

void definirPinosSensores () { // Configura os pinos dos sensores como entrada
    for (int i = 0; i < numSensores; i++) {
        pinMode(pinosSensores[i], INPUT);
    }
}

void definirPinosMotores () { // Configura os pinos dos motores como saída
    for (int i = 0; i < numMotores; i++) {
        pinMode(pinosMotores[i], OUTPUT);
    }
}

void aguardarSensorDeInicio () {// Aguarda o sensor de início ser pressionado
    pinMode(pinoSensorDeInicio, INPUT);
    while (digitalRead(pinoSensorDeInicio) == LOW)
    {
        delay(10);
    }
}

void loop() {
    lerSensores();
    definirMovimento();
    definirVelocidade();
    movimentar();
}

void lerSensores() { // Lê os sensores e armazena os valores em um vetor
    for (int i = 0; i < numSensores; i++)
    {
        leituras[i] = digitalRead(pinosSensores[i]);
    }
}

void definirMovimento () { // Define o movimento do robô com base nas leituras dos sensores
    int s1 = leituras[0]; // Left Most Sensor
    int s2 = leituras[1]; // Left Sensor
    int s3 = leituras[2]; // Middle Sensor
    int s4 = leituras[3]; // Right Sensor
    int s5 = leituras[4]; // Right Most Sensor

    movimentoEscolhido = !s1 * 1 + !s2 * 2 + !s3 * 4 + !s4 * 8 + !s5 * 16;
    // debugLeituraLinha();
}

void definirPercentualVelocidadeMotores (float M1V1, float M1V2, float M2V1, float M2V2) { // M = Motor; V = Velocidade;
    int velocidadeBase = 255;
    float reducao = 0.15;
    velocidadeMotores[0] = velocidadeBase * M1V1 * (reducao + 0.0);
    velocidadeMotores[1] = velocidadeBase * M1V2 * (reducao + 0.0);
    velocidadeMotores[2] = velocidadeBase * M2V1 * (reducao + 0.0);
    velocidadeMotores[3] = velocidadeBase * M2V2 * (reducao + 0.0);
    // velocidadeMotores[0] = 0;  
    // velocidadeMotores[1] = 0; //29 foi
    // velocidadeMotores[2] = 0;
    // velocidadeMotores[3] = 0; //37 foi
    // debugImprimirVelocidades();
}

void definirVelocidade () { // Define as velocidades baseado no movimento escolhido
    switch (movimentoEscolhido) {
    case 1: // GirarDireitaCompleto
        definirPercentualVelocidadeMotores(0.0, 1.0, 1.0, 0.0);
        break;
    case 2: // GirarDireita
        definirPercentualVelocidadeMotores(0.0, 0.0, 1.0, 0.0);
        break;
    case 8: // GirarEsquerda
        definirPercentualVelocidadeMotores(1.0, 0.0, 0.0, 0.0);
        break;
    case 16: // GirarEsquerdaCompleto
        definirPercentualVelocidadeMotores(1.0, 0.0, 0.0, 1.0);
        break;
    case 4: // moverParaFrente
        definirPercentualVelocidadeMotores(0.0, 1.0, 0.0, 1.0);
        break;
    default: // parar
        definirPercentualVelocidadeMotores(0.0, 0.0, 0.0, 0.0);
        break;
    }
}

void movimentar () { // Movimenta os motores com base nas velocidades definidas
    for (int i = 0; i < 2*numMotores; i++) {
        analogWrite(pinosMotores[i], velocidadeMotores[i]);
    }
}


void debugLeituraLinha(){
    Serial.print("(s1, s2, s3, s4, s5, movimento): \t(");
    for (int i = 0; i < numSensores; i++) {
        Serial.print(!leituras[i]);
        Serial.print(", ");
    }
    Serial.print(movimentoEscolhido);
    Serial.print(")\n");
}

void debugMovimentoMotor(){
    Serial.print("(pino, velocidade): \t");
    for (int i = 0; i < 2*numMotores; i++){
        Serial.print("(");
        Serial.print(pinosMotores[i]);
        Serial.print(", ");
        Serial.print(velocidadeMotores[i]);
        Serial.print(")");
        Serial.print("\t");
    }
    Serial.print("\n");
}

void debugImprimirVelocidades (){
    for (int i = 0; i < 2*numMotores; i++){
        Serial.print(velocidadeMotores[i]);
        Serial.print("\t");
    }
    Serial.print("\n");
}
