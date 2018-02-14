int left_pins[] = {7,4};
int right_pins[] = {3,2};

const int enable_2 = 6;
const int enable_1 = 5;

const int one_pin = A4;
const int two_pin = A1;

const int three_pin = A2;
const int four_pin = A3;

const int five_pin = A0;
const int encod_pin = A5;

int j;

int one_val;
int two_val;

int three_val;
int four_val;

int five_val;
int encod_val;

int one_black;
int two_black;

int three_black;
int four_black;

int five_black;
int encod_black;

float pi = 3.14;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  
  for(int i = 0; i < 2; i++)
  {
    pinMode(left_pins[i],OUTPUT);
    pinMode(right_pins[i],OUTPUT);
  }
  j = 0;
  analogWrite(enable_2,200);
  analogWrite(enable_1,200);
  callibrate();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(j < 3)
  {
    Drive_fwd();
    encoder(50);
  }
  
  
  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  five_val = analogRead(five_pin);
  
  //check();
  
  if(one_val < one_black && two_val > two_black)
  {
    Turn_left_off();
  }
  
  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  
  if(one_val > one_black && one_val < one_black)
  {
    Turn_right_off();
  }
  
  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  
  if(three_val < three_black || four_val < four_black)
  {
    encoder(50);
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    if(three_val > three_black && four_val > four_black)
    {
      j++;
      Serial.println("Crossed a line");
      Serial.println(j);
    }
    if(j >= 3)
    {
      STOP();
    }
  }
  
  /*Going_straight(3);
  j = 3;
  while(j==3)
  {
    STOP();
  }*/
  
}

void Drive_fwd()
{
  Serial.println("Driving Forward");
  analogWrite(enable_1,200);
  analogWrite(enable_2,200);
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
  //analogWrite(enable_1,100);
  
  Serial.println("Turning Left off");
  //change pwm instead of turning off motor completely
}

void Turn_right_off()
{
  digitalWrite(right_pins[0],LOW);
  digitalWrite(right_pins[1],LOW);
  //analogWrite(enable_2,100);
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
  analogWrite(enable_1,0);
  analogWrite(enable_2,0);
}

int average(int list[15])
{
  int avg = 0;
  for(int i = 0; i < 15; i++)
  {
    avg += list[i];
  }
  
  avg = avg/15;
  return avg;
}

void check()
{
  if(three_val < three_black)
  {
    Turn_left_off();
    four_val = analogRead(four_pin);
    while(four_val > four_black)
    {
      four_val = analogRead(four_pin);
    }
    Turn_right_off();
    j++;
    return;
  }
  
  else if(four_val < four_black)
  {
    Turn_right_off();
    three_val = analogRead(three_pin);
    while(three_val < three_black)
    {
      three_val = analogRead(three_pin);
    }
    
    Turn_left_off();
    j++;
    return;
  }
}

void callibrate()
{
  int test_left[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int test_right[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int test_three[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int test_four[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int test_five[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int test_encod[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for(int i = 0; i < 15; i++)
  {
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    test_left[i] = one_val;
    test_right[i] = two_val;
    delay(1000);
    Serial.println("left_val, right_val");
    Serial.println(one_val);
    Serial.println(two_val);
  }
  
  one_black = maxi(test_left);
  two_black = maxi(test_right);
  
  for(int i = 0; i < 15; i++)
  {
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    test_three[i] = three_val;
    test_four[i] = four_val;
    delay(1000);
    Serial.println("three_val, four_val");
    Serial.println(three_val);
    Serial.println(four_val);
  }
  
  three_black = maxi(test_three);
  four_black = maxi(test_four);
  
  for(int i = 0; i < 15; i++)
  {
    five_val = analogRead(five_pin);
    encod_val = analogRead(encod_pin);
    test_five[i] = five_val;
    test_encod[i] = encod_val;
    
    delay(1000);
    Serial.println("five_val");
    Serial.println(five_val);
    
  }
  
  five_black = maxi(test_five);
  encod_black = maxi(test_encod);
}

int maxi(int list[15])
{
  int maximum = 0;
  for(int i = 0; i < 15; i++)
  {
    if(maximum < list[i])
    {
      maximum = list[i];
    }
  }
  
  
  return maximum;
}

void Going_straight(int num_lines)
{
  Serial.println("Going Straight");
  int i = 0;
  while(i < num_lines)
  {
    delay(50);
    one_val = analogRead(one_pin);
    Serial.println("one value: ");
    Serial.println(one_val);
   
    two_val = analogRead(two_pin);
    Serial.println("two value: ");
    Serial.println(two_val);
    
    three_val = analogRead(three_pin);
    Serial.println("three value: ");
    Serial.println(three_val);
    
    four_val = analogRead(four_pin);
    Serial.println("four value: ");
    Serial.println(four_val);
    
    
    
    Drive_fwd();
    if(one_val < one_black && two_val > two_black)
    {
    
      Turn_left_off();
    }
  
    else if(two_val < two_black && one_val > one_black)
    {
    
      Turn_right_off();
    }
    
    Drive_fwd();
    
    if(three_val < three_black && four_val > four_black)
    {
      Turn_left_off();
      
      while(four_val > four_black)
      {
         four_val = analogRead(four_pin);
      }
        Turn_right_off();
      i++;
      Serial.println("Counting a line: ");
      Serial.println(i);
    }
    
    else if(four_val < four_black && three_val > three_black)
    {
      Turn_right_off();
      while(three_val > three_black)
      {
        three_val = analogRead(three_pin);
      }
      
      Turn_left_off();
      i++;
      Serial.println("Counting a line: ");
      Serial.println(i);
    }
    
  }
  
}

void encoder(float distance)
{
  int num_tri = 8;
  float diameter = 36;
  
  float dist_calc = 0;
  
  while(dist_calc < distance)
  {
    encod_val = analogRead(encod_pin);
    
    if(encod_val < encod_black)
    {
      dist_calc += (pi/num_tri)*(diameter/2);
    } 
  }
    return;
}

