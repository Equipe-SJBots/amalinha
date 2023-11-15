/*
    Esse código é referente a um robô seguidor de linha.
    Ele utiliza o módulo ir TCRT5000 com 5 sensores infravermelhos e dois motores DC N20.
    O robô possui um sensor de início, também Infravermelho, que é utilizado para iniciar o percurso.
    No Setup, primeiro o código define os pinos dos sensores e motores, depois aguarda o sensor de início ser pressionado.
    No Loop, o código lê os sensores, define o movimento do robô com base nas leituras e movimenta os motores.
*/

// Define os pinos dos sensores
const int numSensores = 5;
int pinosSensores[numSensores] = {A0, A1, A2, A3, A4};

// Define os pinos dos motores
const int numMotores = 2;
int pinosMotores[numMotores] = {10, 11};

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

    movimentoEscolhido = !s1 * 1 + !s2 * 2 + !s3 * 4 + !s4 * 8 + !s5 * 16;

    // Serial.print(s1);
    // Serial.print("\t");
    // Serial.print(s2);
    // Serial.print("\t");
    // Serial.print(s3);
    // Serial.print("\t");
    // Serial.print(s4);
    // Serial.print("\t");
    // Serial.print(s5);
    // Serial.print("\t");
    // Serial.print("\t\t");
    // Serial.print(sum);
    // Serial.print("\t\t");
    // Serial.print(movimentoFinal);
    // Serial.println();
}

void definirVelocidadeMotores (int velocidadeMotor1, int velocidadeMotor2) { // Define a velocidade dos motores
    velocidadeMotores[0] = velocidadeMotor1;
    velocidadeMotores[1] = velocidadeMotor2;
}

void definirVelocidade()
{
    switch (movimentoEscolhido) {
    case 1: // GirarDireitaCompleto
        definirVelocidadeMotores(0, 255);
        break;
    case 2: // GirarDireita
        definirVelocidadeMotores(0, 255);
        break;
    case 4: // moverParaFrente
        definirVelocidadeMotores(255, 255);
        break;
    case 8: // GirarEsquerda
        definirVelocidadeMotores(255, 0);
        break;
    case 16: // GirarEsquerdaCompleto
        definirVelocidadeMotores(255, 0);
        break;
    default: // parar
        definirVelocidadeMotores(127, 127);
        break;
    }
}

void testeMovimentoMotor(){
    Serial.print("pino:");
    Serial.print(pinosMotores[0]);
    Serial.print(", velocidade:");
    Serial.print(velocidadeMotores[0]);
    Serial.print("\tpino:");
    Serial.print(pinosMotores[1]);
    Serial.print(", velocidade:");
    Serial.print(velocidadeMotores[1]);
    Serial.print("\n");
}

void movimentar()
{
    testeMovimentoMotor();
    // Movimenta os motores com base no movimento escolhido
    analogWrite(pinosMotores[0], velocidadeMotores[0]);
    analogWrite(pinosMotores[1], velocidadeMotores[1]);
}