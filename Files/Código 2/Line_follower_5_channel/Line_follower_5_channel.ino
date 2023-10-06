// #include <Arduino.h>

#define m1 4  // Right Motor MA1
#define m2 5  // Right Motor MA2
#define m3 2  // Left Motor MB1
#define m4 3  // Left Motor MB2
#define e1 9  // Right Motor Enable Pin EA
#define e2 10 // Left Motor Enable Pin EB

bool middle_sensor;

//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
//*************************************************//

int motor_speed = 255;

void setup() {
    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
    pinMode(m4, OUTPUT);
    pinMode(e1, OUTPUT);
    pinMode(e2, OUTPUT);
    pinMode(ir1, INPUT);
    pinMode(ir2, INPUT);
    pinMode(ir3, INPUT);
    pinMode(ir4, INPUT);
    pinMode(ir5, INPUT);
}

void loop() {
    // Reading Sensor Values
    int s1 = digitalRead(ir1); // Left Most Sensor
    int s2 = digitalRead(ir2); // Left Sensor
    int s3 = digitalRead(ir3); // Middle Sensor
    int s4 = digitalRead(ir4); // Right Sensor
    int s5 = digitalRead(ir5); // Right Most Sensor

    int sum = s1 + s2 + s3 + s3 + s4 + s5;

    left_most           = (sum == 4) && (s1 == 0);
    left                = (sum == 4) && (s2 == 0);
    middle              = (sum == 4) && (s3 == 0);
    right               = (sum == 4) && (s4 == 0);
    right_most          = (sum == 4) && (s5 == 0);
    middle_left         = (sum == 3) && (s2 == 0) && (s3 == 0);
    middle_right        = (sum == 3) && (s3 == 0) && (s4 == 0);
    left_left_middle    = (sum == 2) && (s4 == 1) && (s5 == 1);
    middle_right_right  = (sum == 2) && (s1 == 1) && (s2 == 1);
    stop                = sum == 0;

    if (middle) { // if only middle sensor detects black line
        // going forward with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    if (left_sensor) { // if only left sensor detects black line
        // going right with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }

    if (left_most) { // if only left most sensor detects black line
        // going right with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, HIGH);
    }

    if (right) { // if only right sensor detects black line
        // going left with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    if (right_most) { // if only right most sensor detects black line
        // going left with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, HIGH);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    if (middle_right) { // if middle and right sensor detects black line
        // going left with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    if (middle_left) { // if middle and left sensor detects black line
        // going right with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }

    if (left_left_middle) { // if middle, left and left most sensor detects black line
        // going right with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }

    if (middle_right_right) { // if middle, right and right most sensor detects black line
        // going left with full speed
        analogWrite(e1, motor_speed); // you can adjust the speed of the motors from 0-255
        analogWrite(e2, motor_speed); // you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    if (stop) { // if all sensors are on a black line
        // stop
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }
}
