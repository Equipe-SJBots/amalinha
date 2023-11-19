
// Define os pinos dos motores
int const quantidadeMotores = 4;
int pinosMotores[quantidadeMotores] = {4, 6, 3, 7};

void setup() {
    // Inicializa os pinos dos motores como saída
    Serial.begin(9600);
    for (int i = 0; i < quantidadeMotores; i++) {
        pinMode(pinosMotores[i], OUTPUT);
    }
    // analogWrite(motor1Pin1, velocidade);
    analogWrite(pinosMotores[2], 0);
    analogWrite(pinosMotores[3], 0);
    // analogWrite(motor1Pin2, -velocidade);

}

void motorVelocidade(int motor, int velocidade){
    Serial.print("(motor, velocidade) = (");
    Serial.print(motor);
    Serial.print(", ");
    Serial.print(velocidade);
    Serial.print(")\t");

    analogWrite(motor, velocidade);
}

void loop() {
    // Varia a velocidade dos motores de 0 a 255

    for (int velocidade = 0; velocidade <= 255; velocidade++) {
        motorVelocidade(pinosMotores[0], velocidade);
        motorVelocidade(pinosMotores[1], velocidade);
        Serial.print("\n");
        delay(100);
    }
    for (int velocidade = 255; velocidade >= 0; velocidade--) {
        motorVelocidade(pinosMotores[0], velocidade);
        motorVelocidade(pinosMotores[1], velocidade);
        Serial.print("\n");
        delay(100);
    }
}
