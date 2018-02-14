#include <Servo.h>

const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;

Servo myServo; //function connected to Servo

int angle = 0; //angle for servo to go to

void setup(){
  
  myServo.attach(9); //tells what pin servo is attached to
  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  
  
}

void loop(){
  /*for(angle = 90; angle > 0; angle-=1){
  
        myServo.write(angle);
        delay(15);
      }*/
  Drive_fwd();
  delay(6000);
  
  STOP();
  
      /*for(angle = 0; angle < 90; angle+=1){
    
         myServo.write(angle);
        delay(15);
      }*/
  Drive_bwd();
  delay(3000);
  WAIT();
}

void Drive_fwd(){
  digitalWrite(in1,LOW); //left wheel cw
  digitalWrite(in2,HIGH);
      
  digitalWrite(in3,LOW); //right wheel cw
  digitalWrite(in4,HIGH);
}

void Drive_bwd(){
  digitalWrite(in1,HIGH); //both counter ccw
  digitalWrite(in2,LOW);
      
  digitalWrite(in3,HIGH);
  digitalWrite(in4, LOW);
}

void Drive_right(){
  digitalWrite(in1,HIGH); // turns ccw for right
  digitalWrite(in2,LOW);
      
  digitalWrite(in3,LOW); 
  digitalWrite(in4, HIGH);
}

void Drive_left(){
  digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH);
      
  digitalWrite(in3,HIGH);// turns ccw for left
  digitalWrite(in4, LOW);
}

void STOP(){
  digitalWrite(in1,LOW);//turns both off
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void WAIT(){
  int i = 0;
  while(i==0){
    digitalWrite(in1,LOW);//turns both off
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
  }
}

