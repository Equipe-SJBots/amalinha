//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
#define ir6 A5
#define ir7 A6
#define ir8 A7

//*************************************************//

int motor_speed = 255;

void setup()
{
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(ir6, INPUT);
  pinMode(ir7, INPUT);
  pinMode(ir8, INPUT);
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