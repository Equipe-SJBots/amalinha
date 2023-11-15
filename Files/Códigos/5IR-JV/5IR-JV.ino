/*
    Esse código é referente a um robô seguidor de linha.
    Ele utiliza o módulo ir TCRT5000 com 5 sensores infravermelhos e dois motores DC N20.
    O robô possui um sensor de início, também Infravermelho, que é utilizado para iniciar o percurso.
    No Setup, primeiro o código define os pinos dos sensores e motores, depois aguarda o sensor de início ser pressionado.
    No Loop, o código lê os sensores, define o movimento do robô com base nas leituras e movimenta os motores.
*/

// Define os pinos dos sensores
const int numSensores = 5;
// int pinosSensores[numSensores] = {A0, A1, A2, A3, A4}; // TESTE
int pinosSensores[numSensores] = {A4, A3, A2, A1, A0}; // AMALINHA


// Define os pinos dos motores
const int numMotores = 2;
int pinosMotores[2*numMotores] = {4, 3, 7, 6};
/*
IN1 | 7 | MTR A + | Direita
IN2 | 6 | MTR A - | Direita
IN3 | 4 | MTR B + | Esquerda
IN4 | 3 | MTR B - | Esquerda
*/

// Define o pino do sensor de início
const int pinoSensorDeInicio = 12;

// Define as variáveis para leitura dos sensores
int leituras[numSensores];

// Define a variável de escolha para movimentação dos motores
int movimentoEscolhido = 0;

int velocidadeMotores[2 * numMotores] = {0, 0, 0, 0};

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

void lerSensores()
{
    // Lê os sensores e armazena os valores em um vetor
    for (int i = 0; i < numSensores; i++)
    {
        leituras[i] = digitalRead(pinosSensores[i]);
    }
}

void loop()
{
    lerSensores();
    definirMovimento();
    definirVelocidade();
    movimentar();
}

void definirMovimento()
{
    // Define o movimento do robô com base nas leituras dos sensores
    int s1 = leituras[0]; // Left Most Sensor
    int s2 = leituras[1]; // Left Sensor
    int s3 = leituras[2]; // Middle Sensor
    int s4 = leituras[3]; // Right Sensor
    int s5 = leituras[4]; // Right Most Sensor

    int sum = s1 + s2 + s3 + s3 + s4 + s5;
    movimentoEscolhido = !s1 * 1 + !s2 * 2 + !s3 * 4 + !s4 * 8 + !s5 * 16;

    // int left_most = (sum == 4) && (s1 == 0);
    // int left = (sum == 4) && (s2 == 0);
    // int middle = (sum == 4) && (s3 == 0);
    // int right = (sum == 4) && (s4 == 0);
    // int right_most = (sum == 4) && (s5 == 0);

    // int middle_left = (sum == 3) && (s2 == 0) && (s3 == 0);
    // int middle_right = (sum == 3) && (s3 == 0) && (s4 == 0);

    // int left_left_middle = (sum == 2) && (s4 == 1) && (s5 == 1);
    // int middle_right_right = (sum == 2) && (s1 == 1) && (s2 == 1);

    // int stop = sum == 0;

    // int lm = left_most;
    // int lf = left;
    // int mf = middle;
    // int rt = right;
    // int rm = right_most;


    Serial.print(s1);
    Serial.print("\t");
    Serial.print(s2);
    Serial.print("\t");
    Serial.print(s3);
    Serial.print("\t");
    Serial.print(s4);
    Serial.print("\t");
    Serial.print(s5);
    Serial.print("\t");
    Serial.print("\t\t");
    Serial.print(sum);
    Serial.print("\t\t");
    Serial.print(movimentoEscolhido);
    Serial.println();
}

void definirVelocidadeMotores (int Motor1Velocidade1, int Motor1Velocidade2, int Motor2Velocidade1, int Motor2Velocidade2) { // Define a velocidade dos motores
    velocidadeMotores[0] = Motor1Velocidade1;
    velocidadeMotores[1] = Motor1Velocidade2;
    velocidadeMotores[2] = Motor2Velocidade1;
    velocidadeMotores[3] = Motor2Velocidade2;
}

void definirVelocidade()
{
    switch (movimentoEscolhido) {
    case 1: // GirarDireitaCompleto
        definirVelocidadeMotores(0, 255, 255, 0);
        break;
    case 2: // GirarDireita
        definirVelocidadeMotores(0, 0, 255, 0);
        break;
    case 4: // moverParaFrente
        definirVelocidadeMotores(255, 0, 255, 0);
        break;
    case 8: // GirarEsquerda
        definirVelocidadeMotores(255, 0, 0, 0);
        break;
    case 16: // GirarEsquerdaCompleto
        definirVelocidadeMotores(255, 0, 0, 255);
        break;
    default: // parar
        definirVelocidadeMotores(100, 0, 100, 0);
        break;
    }
}

void printMovimentoMotor(){
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
    printMovimentoMotor();
    // Movimenta os motores com base no movimento escolhido
    for (int i = 0; i < 2*numMotores; i++)
    {
        analogWrite(pinosMotores[i], velocidadeMotores[i]);
    }
}