//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A3
#define ir4 A4
#define ir5 A5
#define ir6 A6

//*************************************************//

int motor_speed = 255;

void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}

void myPrint(String label, int value)
{
  Serial.print(label);
  Serial.print("\t");
  Serial.print(value);
  Serial.print("\n");
}

void printStringAndInt(String str, int num)
{
  Serial.print(str);
  Serial.print(": ");
  Serial.println(num);
}

void loop()
{

  int s1 = digitalRead(ir1); // Left Most Sensor
  int s2 = digitalRead(ir2); // Left Sensor
  int s3 = digitalRead(ir3); // Middle Sensor
  int s4 = digitalRead(ir4); // Right Sensor
  int s5 = digitalRead(ir5); // Right Most Sensor

  // print labels
  printStringAndInt("ir1", ir1);
  printStringAndInt("ir2", ir2);
  printStringAndInt("ir3", ir3);
  printStringAndInt("ir4", ir4);
  printStringAndInt("ir5", ir5);
  delay(200); // delay 200 milliseconds
}