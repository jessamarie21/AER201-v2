#include <Servo.h>

Servo myServo; //function connected to Servo

int angle = 0; //angle for servo to go to


void setup() {
  Serial.begin(9600);
  Serial.println("character? ");
  myServo.attach(9); //tells what pin servo is attached to
}

void loop(){
  if(Serial.available()){
    char chari = Serial.read();
    if(chari == '+'){
      for(angle = 0; angle < 90; angle+=1){
  
        myServo.write(angle);
        delay(15);
      }
    }
    else if(chari == '-'){
      for(angle = 90; angle > 0; angle-=1){
    
         myServo.write(angle);
        delay(15);
      }
    }
  }
    
    
}
  
