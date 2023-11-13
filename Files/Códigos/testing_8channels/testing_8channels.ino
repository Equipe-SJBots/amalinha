//**********5 Channel IR Sensor Connection**********//
#define ir1 A8
#define ir2 A9
#define ir3 A10
#define ir4 A11
#define ir5 A12
#define ir6 A13
#define ir7 A14
#define ir8 A15

//*************************************************//

int motor_speed = 255;

void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(ir6, INPUT);
  pinMode(ir7, INPUT);
  pinMode(ir8, INPUT);
  digitalWrite(11, HIGH);
}

void myPrint(String label, int value)
{
  Serial.print(label);
  Serial.print(":");
  Serial.print(value);
  Serial.print(",");
}

void loop()
{

  int s1 = analogRead(ir1);
  int s2 = analogRead(ir2);
  int s3 = analogRead(ir3);
  int s4 = analogRead(ir4);
  int s5 = analogRead(ir5);
  int s6 = analogRead(ir6);
  int s7 = analogRead(ir7);
  int s8 = analogRead(ir8);

  // print labels
  myPrint("s100", 100);
  myPrint("s1", s1);
  myPrint("s2", s2);
  myPrint("s3", s3);
  myPrint("s4", s4);
  myPrint("s5", s5);
  myPrint("s6", s6);
  // myPrint("s7", s7);
  // myPrint("s8", s8);
  myPrint("s300", 300);
  Serial.print("\n");

  // delay(200); // delay 200 milliseconds
}