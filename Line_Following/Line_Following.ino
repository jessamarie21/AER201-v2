/*Using Photo Sensors to Control Differential Steering

white left range: 230-260
white right range: 230-260
left black range: 150-180
right black range: 160-190
red range: 590-620
*/

int left_pins[] = {5,4};
int right_pins[] = {3,2};

int led_red = 10;
int led_green = 9;

const int min_PWM = 64;
const int max_PWM = 128;

const int left_pin = A0;
const int right_pin = A1;
int j = 0;

int threshold = 0;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  
  for(int i = 0; i < 2; i++)
  {
    pinMode(left_pins[i],OUTPUT);
    pinMode(right_pins[i],OUTPUT);
  }
  pinMode(led_red,OUTPUT);
  pinMode(led_green,OUTPUT);
}

void loop()
{
 
  int left_val = analogRead(left_pin);
  int right_val = analogRead(right_pin);
  
  Serial.println("left value: ");
  Serial.println(left_val);
  Serial.println(' ');
  delay(1000);
  
  Serial.println("right value: ");
  Serial.println(right_val);
  Serial.println(' ');
  delay(1000);
  
  if(left_val < 150 && right_val > 150)
  {
    digitalWrite(led_red,HIGH);
    Turn_left_off();
  }
  
  else if(right_val < 150 && left_val > 150)
  {
    digitalWrite(led_green,HIGH);
    Turn_right_off();
  }
  
  else if(right_val < 150 && left_val < 150)
  {
    j++;
    Serial.print(right_val<150);
    Serial.print(left_val<150);
    Serial.print("I;m gere");
    Serial.print("You have now passed ");
    Serial.print(j);
    Serial.println(" lines");
  }
  
  else 
  {
    Drive_fwd();
  }
  
  
}

void Drive_fwd()
{
  Serial.println("Driving Forward");
  digitalWrite(left_pins[0],LOW);
  digitalWrite(left_pins[1],HIGH);
  digitalWrite(right_pins[0],LOW);
  digitalWrite(right_pins[1],HIGH);
}

void Drive_bwd()
{
  
  digitalWrite(left_pins[0],HIGH);
  digitalWrite(left_pins[1],LOW);
  digitalWrite(right_pins[0],HIGH);
  digitalWrite(right_pins[1],LOW);
  Serial.println("Driving Backward");
}

void Turn_left_off()
{
  
  digitalWrite(left_pins[0],LOW);
  digitalWrite(left_pins[1],LOW);
  Serial.println("Turning Left off");
}

void Turn_right_off()
{
  digitalWrite(right_pins[0],LOW);
  digitalWrite(right_pins[1],LOW);
  Serial.println("Turning Right off");
}
  
void STOP()
{
  digitalWrite(left_pins[0],LOW);
  digitalWrite(left_pins[1],LOW);
  digitalWrite(right_pins[0],LOW);
  digitalWrite(right_pins[1],LOW);
  Serial.println("STOPPING!");
}
  
