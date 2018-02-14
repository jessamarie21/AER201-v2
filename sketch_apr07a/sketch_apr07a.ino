#include <Servo.h>

Servo oneServo;
Servo twoServo;

void setup() {
  // put your setup code here, to run once:
  oneServo.attach(10);
  twoServo.attach(9);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  oneServo.write(0);
  twoServo.write(0);
  
}
