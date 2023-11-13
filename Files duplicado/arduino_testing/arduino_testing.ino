//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
// #define ir6 A5
// #define ir7 A6
// #define ir8 A7
// #define ir9 A8

//*************************************************//

int motor_speed = 255;
int static_variable = 500;

void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  // pinMode(ir6, INPUT);
  // pinMode(ir7, INPUT);
  // pinMode(ir8, INPUT);
  // pinMode(ir9, INPUT);
}

void myPrint(String label, int value)
{
  Serial.print(label);
  Serial.print(": ");
  Serial.print(value);
  Serial.print(",");
}

void printStringAndInt(String str, int num)
{
  Serial.print(str);
  Serial.print(": ");
  Serial.println(num);
}

void loop()
{
  
  int s1 = analogRead(ir1); // Left Most Sensor
  int s2 = analogRead(ir2); // Left Sensor
  int s3 = analogRead(ir3); // Middle Sensor
  int s4 = analogRead(ir4); // Right Sensor
  int s5 = analogRead(ir5); // Right Most Sensor
  // int s6 = digitalRead(ir6);
  // int s7 = digitalRead(ir7);
  // int s8 = digitalRead(ir8); 
  // int s9 = digitalRead(ir9); 

  // print labels
  myPrint("ir1", s1);
  myPrint("ir2", s2);
  myPrint("ir3", s3);
  myPrint("ir4", s4);
  myPrint("ir5", s5);
  // myPrint("ir6", ir6);
  // myPrint("ir7", ir7);
  // myPrint("ir8", ir8);
  // myPrint("ir9", ir9);
  Serial.print("\n");

  delay(200); // delay 200 milliseconds
}