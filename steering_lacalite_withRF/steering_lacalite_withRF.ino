/*Using Photo Sensors to Control Differential Steering

white left range: 420-430
white right range: 420-430
left black range: 330-350
right black range: 340-360
red left range: 390-400
red right range: 370-390
*/

//motor pins
int left_pins[] = {7,4};
int right_pins[] = {3,2};

const int enable_2 = 6;
const int enable_1 = 5;

//analog pins
const int left_pin = A0;
const int right_pin = A1;
const int mid_pin = A3;
const int side_pin = A2;
const int rec_pin = A4;

//line following calibration
int loc = 1;
int j = 0;
int max_black_left;
int max_black_mid;
int max_black_side;
int max_black_right = 360;
int max_red_left = 400;
int max_red_right = 390;
int min_white = 420;

//rf calibration
unsigned int rec_data = 0;
const unsigned int upper_limit = 370;
const unsigned int lower_limit = 370;

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
  //rf_receiving
  /*rec_data = analogRead(rec_pin);
  Serial.println(rec_data);
  Serial.println('\n');*/
  
  //line_following readings
  int left_val = analogRead(left_pin);
  int right_val = analogRead(right_pin);
  int mid_val = analogRead(mid_pin);
  int side_val = analogRead(side_pin);
  
  Serial.println("left value: ");
  Serial.println(left_val);
  Serial.println(' ');
  
  delay(1000);
  
  Serial.println("right value: ");
  Serial.println(right_val);
  Serial.println(' ');
  
  delay(1000);
   
  Serial.println("middle value: ");
  Serial.println(mid_val);
  Serial.println(' ');
  
  delay(1000);
   
  Serial.println("side value: ");
  Serial.println(side_val);
  Serial.println(' ');
  
  delay(2000);
  
  /*if(left_val < max_black_left && right_val > max_black_right)
  {
    
    Turn_left_off();
  }
  
  else if(right_val < max_black_right && left_val > max_black_left)
  {
    
    Turn_right_off();
  }
  
  else if(right_val < max_black_right && left_val < max_black_left)
  {
    j++;
    
    Serial.print("You have now passed ");
    Serial.print(j);
    Serial.println(" lines");
    Drive_fwd();
  }
  
  else if(j == 4)
  {
    if(loc == 1)
    {
      while(mid_val > max_black_mid && side_val > max_black_side)
      {
        Turn_right_off();
        mid_val = analogRead(mid_pin);
        side_val = analogRead(side_pin);
      }
      
      j = 0;
      
    }
    
    else
    {
      Turn_left_off();
      while(mid_val > max_black_mid && side_val > max_black_side)
      {
        Turn_left_off();
        mid_val = analogRead(mid_pin);
        side_val = analogRead(side_pin);
      }
      
      j = 0;
      
    }
  }
     
  
  else
  {
    Drive_fwd();
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
  
