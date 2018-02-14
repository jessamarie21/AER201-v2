
//left motor black, red
//right motor red, black
//motor pins
const int left_pins[] = {7,4};
const int right_pins[] = {3,2};

const int enable_2 = 6;
const int enable_1 = 5;

//analog pins
const int one_pin = A1;
const int two_pin = A4;
const int three_pin = A2;
const int four_pin = A3;
const int five_pin = A0;
const int encod_pin = A5;

//servo
//Servo myServo;
int angle = 90;

//line following sensor values
int one_val;
int two_val;
int three_val;
int four_val;
int five_val;
int encod_val;

//line following calibration
int max_black_one = 1023;
int max_black_two = 1023;
int max_black_three = 1023;
int max_black_four = 1023;
int max_black_five = 1023;
int max_black_encod = 1023;

//number of lines


int cor_one = 6;
int cor_two = 3;

int initial = 3;

//number of times path run
int mid_hop = 7;
int cor_hop = 4;

int left = 0;
int right = 1;
int dist_val = 30;
float pi = 3.14;


//state mid hopper
char state = 'A';
int hop_or1 = 1;
int A[4][5]= {{1,1,0,0,0},{2,2,1,0,0},{3,3,2,1,0},{4,2,3,2,1}};
int B[4][5] = {{1,2,0,0,0},{2,2,2,0,0},{3,3,3,1,0},{4,2,4,2,1}};
int C[4][5] = {{1,3,0,0,0},{2,2,3,0,0},{3,3,4,1,0},{4,2,5,2,1}};

int i = 0;
int j = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  
  for(int i = 0; i < 2; i++)
  {
    pinMode(left_pins[i],OUTPUT);
    pinMode(right_pins[i],OUTPUT);
  }
  
  //myServo.attach(9);
  int test[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  analogWrite(enable_1,255);
  analogWrite(enable_2,255);
  for(int i = 0; i < 15; i++)
  {
    
    one_val = analogRead(one_pin);
    Serial.println("ONE: ");
    Serial.println(one_val); 
    delay(500);
    test[i] = one_val;
  }
  
  max_black_one = average(test);
  
  for(int i = 0; i < 15; i++)
  {
    two_val = analogRead(two_pin);
    Serial.println("TWO: ");
    Serial.println(two_val);
    delay(1000);
    test[i] = two_val;
  }
  
  max_black_two = average(test);
  
  for(int i = 0; i < 15; i++)
  {
    three_val = analogRead(three_pin);
    Serial.println("THREE: ");
    Serial.println(three_val);
    delay(1000);
    test[i] = three_val;
    
  }
  
  max_black_three = average(test);
  
  for(int i = 0; i < 15; i++)
  {
    four_val = analogRead(four_pin);
    Serial.println("FOUR: ");
    Serial.println(four_val);
    delay(1000);
    test[i] = four_val;
  }
  
  max_black_four = average(test);
  
  for(int i = 0; i < 15; i++)
  {
    five_val = analogRead(five_pin);
    Serial.println("FIVE: ");
    Serial.println(five_val);
    delay(1000);
    test[i] = five_val;
  }
  
  max_black_five = average(test);
  
  for(int i = 0; i < 15; i++)
  {
    encod_val = analogRead(encod_pin);
    Serial.println("ENCODE: ");
    Serial.println(encod_val);
    delay(1000);
    test[i] = encod_val;
  }
  
  max_black_encod = average(test);
    
  //reveal(A);
  //reveal(B);
  //reveal(C);
  Going_straight(initial);
  STOP();
  //Turning_corner(left);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(i < cor_hop && j == 0)
  {
    
    Drive_fwd();
    encoder(130);
    Drive_bwd();
    encoder(130);
    Turning_around(right);
    Going_straight(cor_one);
    Turning_right();
    Going_straight(cor_two);

    i++;
    
    Turning_around(right);
    Going_straight(cor_two);
    Turning_left();
    Going_straight(cor_one);
    Turning_corner(right);
  }
  
  else if(j < mid_hop && i == cor_hop-1)
  {
    if(state == 'A')
    {
       state_machine(A);
    }
    
    else if(state == 'B')
    {
       state_machine(B);
    }
    
    else if(state == 'C')
    {
       state_machine(C);
    }
 
    j++;
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

void Going_straight(int num_lines)
{
  Serial.println("Going Straight");
  int i = 0;
  while(i < num_lines)
  {
    one_val = analogRead(one_pin);
    Serial.println("one value: ");
    Serial.println(one_val);
    delay(1000);
   
    two_val = analogRead(two_pin);
    Serial.println("two value: ");
    Serial.println(two_val);
    delay(1000);
    
    three_val = analogRead(three_pin);
    Serial.println("three value: ");
    Serial.println(three_val);
    delay(1000);
    
    four_val = analogRead(four_pin);
    Serial.println("four value: ");
    Serial.println(four_val);
    delay(1000);
    
    
    
    Drive_fwd();
    if(one_val < max_black_one && two_val > max_black_two)
    {
    
      Turn_left_off();
    }
  
    else if(two_val < max_black_two && one_val > max_black_one)
    {
    
      Turn_right_off();
    }
    
    Drive_fwd();
    
    if(three_val < max_black_three && four_val > max_black_four)
    {
      Turn_left_off();
      
      while(four_val > max_black_four)
      {
         four_val = analogRead(four_pin);
      }
        Turn_right_off();
      i++;
      Serial.println("Counting a line: ");
      Serial.println(i);
    }
    
    else if(four_val < max_black_four && three_val > max_black_three)
    {
      Turn_right_off();
      while(three_val > max_black_three)
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

void Turning_right()
{
  Serial.println("Turning Right");
  Drive_fwd();
  encoder(dist_val);
  STOP();
  five_val = analogRead(five_pin);
  while(five_val > max_black_five)
  {
    Drive_fwd();
    five_val = analogRead(five_pin);
  }
  
  if(five_val < max_black_five)
  {
    Turn_right_off();
    five_val = analogRead(five_pin);
    while (five_val > max_black_five)
    {
      five_val = analogRead(five_pin);
    }
  }
  
  
  return;
  
}

void Turning_left()
{
  Serial.println("Turning left");
  Drive_fwd();
  encoder(dist_val);
  STOP();
  five_val = analogRead(five_pin);
  while(five_val > max_black_five)
  {
    Drive_fwd();
    five_val = analogRead(five_pin);
  }
  
  if(five_val < max_black_five)
  {
    Turn_left_off();
    five_val = analogRead(five_pin);
    while (five_val > max_black_five)
    {
      five_val = analogRead(five_pin);
    }
  }
  
  
  return;
}

void Turning_corner(int direct)
{
  Serial.println("Turning 45");
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  if(direct == 1)
  {
    Turn_right_off();
    while(three_val > max_black_three || four_val > max_black_four)
    {
      three_val = analogRead(three_pin);
      four_val = analogRead(four_pin);
    }
  }
  
  else
  {
    Turn_left_off();
    while(three_val > max_black_three || four_val > max_black_four)
    {
      three_val = analogRead(three_pin);
      four_val = analogRead(four_pin);
    }
  }
  
  return;
}

void Turning_around(int direct)
{
  Serial.println("Turning 180");
  Drive_fwd();
  encoder(dist_val);
  STOP();
  five_val = analogRead(five_pin);
  while(five_val > max_black_five)
  {
    Drive_fwd();
    analogRead(five_pin);
  }
  
  if(direct == 1)
  {
    int i = 0;
    Turn_right_off();
    while(i < 2)
    {
      five_val = analogRead(five_pin);
      if(five_val < max_black_five)
      {
        i++;
      }
    }
  }
  
  else
  {
    int i = 0;
    Turn_left_off();
    while(i < 2)
    {
      five_val = analogRead(five_pin);
      if(five_val < max_black_five)
      {
        i++;
      }
    }
  }
  return;
}

void state_machine(int list[4][5])
{
  if(hop_or1 == list[0][0])
  {
     Going_straight(list[0][1]); //orientation one with hopper on red line and leg closest to board perpendicular to board
     Turning_corner(right);
     Drive_fwd();
     encoder(130);
     Drive_bwd();
     encoder(130);
     Turning_around(right);
     Going_straight(list[0][1]);
  }
      
  else if(hop_or1 == list[1][0])
  {  
     Turning_right();
     Going_straight(list[1][1]); //orientation two with hopper one space over from red line and leg closest to board perpendicular to board
     Turning_left();
     Going_straight(list[1][2]);
     Turning_corner(left);
     Drive_fwd();
     encoder(130);
     Drive_bwd();
     encoder(130);
     Turning_around(left);
     Going_straight(list[1][2]);
     Turning_right();
     Going_straight(list[1][1]);
  }
       
  else if(hop_or1 == list[2][0])
  { 
     Turning_right();
     Going_straight(list[2][1]); //orientation 3 with hopper flipped and one space over from red line
     Turning_left();
     Going_straight(list[2][2]);
     Turning_left();
     Going_straight(list[2][3]);
     Turning_corner(left);
     Drive_fwd();
     encoder(130);
     Drive_bwd();
     encoder(130);
     Turning_around(left);
     Going_straight(list[2][3]);
     Turning_right();
     Going_straight(list[2][2]);
     Turning_right();
     Going_straight(list[2][1]);
     Turning_left();
  }
       
  else if(hop_or1 == list[3][0])
  {
     Turning_right();
     Going_straight(list[3][1]); //orientation 4 with hopper flipped and right at redline
     Turning_left();
     Going_straight(list[3][2]);
     Turning_left();
     Going_straight(list[3][3]);
     Turning_left();
     Going_straight(list[3][4]);
     Turning_corner(left);
     Drive_fwd();
     encoder(130);
     Drive_bwd();
     encoder(130);
     Turning_around(left);
     Going_straight(list[3][4]);
     Turning_right();
     Going_straight(list[3][3]);
     Turning_right();
     Going_straight(list[3][2]);
     Turning_right();
     Going_straight(list[3][1]);
     Turning_left();
           
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
  if(encod_val < max_black_encod)
  {
    dist_calc += (pi/num_tri)*(diameter/2);
  } 
  }
  STOP();
  return;
}

/*void servo_change(int angle)
{
  if(angle == 90)
  {
    for(angle = 90; angle > 0; angle -= 1)
    {
      myServo.write(angle);
      delay(15);
    }
  }
  
  if(angle == 0)
  {
    for(angle = 0; angle < 90; angle += 1)
    {
      myServo.write(angle);
      delay(15);
    }
  }
}*/

void reveal(int list[4][5])
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      Serial.println(list[i][j]);
      delay(1000);
    }
  }
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


