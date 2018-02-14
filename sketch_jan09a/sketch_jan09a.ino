const int switchPin = 2; //tells arduino what pin switch is connected to
const int motorPin = 9;
int switchState = 0;

void setup(){
  pinMode(motorPin, OUTPUT); //sets motor pin as output
  pinMode(switchPin, INPUT); //sets switch as input
}

void loop(){
  switchState = digitalRead(switchPin); //reads and stores state of switch pin
  
  if(switchState == HIGH)
  {
    digitalWrite(motorPin,HIGH); //makes motor move if switch is pressed
  }
  
  else
  {
    digitalWrite(motorPin,LOW);
  }
}

  
