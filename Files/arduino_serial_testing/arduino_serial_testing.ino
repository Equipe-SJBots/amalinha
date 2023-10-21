unsigned long previousMillis;
int variable1 = 0;
float variable2 = 0.0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  variable1++;
  variable2 += 0.1;
  Serial.print("Herick:");
  Serial.print(variable1);
  Serial.print(",");
  Serial.print("juau:");
  Serial.println(variable2);
  delay(1000);
}