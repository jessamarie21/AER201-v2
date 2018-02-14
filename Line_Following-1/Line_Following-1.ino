/*Using Photo Sensors to Control Differential Steering

white left range: 420-430
white right range: 420-430
left black range: 330-350
right black range: 340-360
red left range: 390-400
red right range: 370-390
*/

int left_pins[] = {7,4};
int right_pins[] = {3,2};

const int enable_2 = 6;
const int enable_1 = 5;


const int min_PWM = 64;
const int max_PWM = 128;

const int left_pin = A1;
const int right_pin = A4;

int j = 0;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  
  for(int i = 0; i < 2; i++)
  {
    pinMode(left_pins[i],OUTPUT);
    pinMode(right_pins[i],OUTPUT);
  }
  
  analogWrite(enable_2,255);
  analogWrite(enable_1,255);
  
  
}

void loop()
{
 
  int left_val = analogRead(left_pin);
  int right_val = analogRead(right_pin);
  
  Serial.println("left value: ");
  Serial.println(left_val);
  Serial.println(' ');
  
  Serial.println("right value: ");
  Serial.println(right_val);
  Serial.println(' ');
  delay(1000);
  
  if(left_val < 510 && right_val > 540)
  {
    
    Turn_left_off();
  }
  
  else if(right_val < 540 && left_val > 510)
  {
    
    Turn_right_off();
  }
  
  else if(right_val < 540 && left_val < 510)
  {
    j++;
    
    Serial.print("You have now passed ");
    Serial.print(j);
    Serial.println(" lines");
    Drive_fwd();
  }
  
  else
  {
    Drive_fwd();
  }
  
  /*while(j==6)
    {
      
      STOP();
    }*/
    
  
  
  
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
  //analogWrite(enable_1,30);
  Serial.println("Turning Left off");
  //change pwm instead of turning off motor completely
}

void Turn_right_off()
{
  digitalWrite(right_pins[0],LOW);
  digitalWrite(right_pins[1],LOW);
  Serial.println("Turning Right off");
  //analogWrite(enable_2,30);
}
  
void STOP()
{
  digitalWrite(left_pins[0],LOW);
  digitalWrite(left_pins[1],LOW);
  digitalWrite(right_pins[0],LOW);
  digitalWrite(right_pins[1],LOW);
  Serial.println("STOPPING!");
}
  
