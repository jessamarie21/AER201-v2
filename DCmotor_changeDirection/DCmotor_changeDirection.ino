const int controlPin1 = 2; //set pins according to arduino connections
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin = 5;
const int potPin = A0;

int onOffSwitchState = 0; //set variable initial state, save current and previous state
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0; //set inital motor power, speed, direction
int motorSpeed = 0;
int motorDirection = 1;

void setup(){
  pinMode(directionSwitchPin, INPUT); //set pinmode as input or output
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  digitalWrite(enablePin, LOW); //so motor doesnt start immediately
}

void loop(){
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin); //determines state from pin, on or off
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin); //determines direction from pin
  motorSpeed = analogRead(potPin)/4; //speed is read from potentiometer
  if(onOffSwitchState != previousOnOffSwitchState)//if it wasn't on but now it's on, turns on motorpower
  {
    if(onOffSwitchState == HIGH)
    {
      motorEnabled = !motorEnabled;
    }
  }
  
  if(directionSwitchState != previousDirectionSwitchState)//if the direction was changed then the motor direction switches
  {
    if(directionSwitchState == HIGH)
    {
      motorDirection = !motorDirection;
    }
  }
  
  if(motorDirection == 1)//sets output pins
  {
    digitalWrite(controlPin1,HIGH);
    digitalWrite(controlPin2,LOW);
  }
  
  else//changes output pins based on direction
  {
    digitalWrite(controlPin1,LOW);
    digitalWrite(controlPin2,HIGH);
  }
  
  if(motorEnabled == 1)//if the motor power is on, the enable pin is given the motor speed
  {
    analogWrite(enablePin,motorSpeed);
  }
  
  else//if it's off the enable pin is given 0
  {
    analogWrite(enablePin,0);
  }
  //before ending loop, saves current states as previous states
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}
    
