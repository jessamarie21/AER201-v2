const int in1 = 7;
const int in2 = 4;
const int in3 = 3;
const int in4 = 2;

const int enable1 = 6;
const int enable2 = 5;
const int encod_pin = A0;

float pi = 3.14;
int encod_val;
float dist_calc;

int max_black_encod = 483;

void setup(){
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  Serial.println("change direction +/-, turn %/&");
  analogWrite(enable1, 150);
  analogWrite(enable2, 150);
}

void loop(){
  if(Serial.available()){
    char chari = Serial.read();
    if(chari == '+'){
      digitalWrite(in1,LOW); //left wheel cw
      digitalWrite(in2,HIGH);
      
      digitalWrite(in3,LOW); //right wheel cw
      digitalWrite(in4,HIGH);
      //encoder(900);
      
    }
    
    else if(chari == '-'){
      digitalWrite(in1,HIGH); //both counter ccw
      digitalWrite(in2,LOW);
      
      digitalWrite(in3,HIGH);
      digitalWrite(in4, LOW);
      //encoder(90);
    }
    
    else if(chari == '%'){
      digitalWrite(in1,HIGH); // turns ccw for right
      digitalWrite(in2,LOW);
      
      digitalWrite(in3,LOW); 
      digitalWrite(in4, HIGH);
    }
    
    else if(chari == '&'){
      digitalWrite(in1,LOW); 
      digitalWrite(in2,HIGH);
      
      digitalWrite(in3,HIGH);// turns ccw for left
      digitalWrite(in4, LOW);
    }
    else
    {
      digitalWrite(in1,LOW);//turns both off
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
    }
  }
}

void encoder(float distance)
{
  int num_tri = 4;
  float diameter = 36;
  
  float dist_calc = 0;
  
  while(dist_calc < distance)
  {
  encod_val = analogRead(encod_pin);
  Serial.println("encoder value: ");
  Serial.println(encod_val);
  delay(1000);
  if(encod_val < max_black_encod)
  {
    dist_calc += (pi/num_tri)*(diameter/2);
    Serial.println(dist_calc);
  }
  }
  
  return;
}
