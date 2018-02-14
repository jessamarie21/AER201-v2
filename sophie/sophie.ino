#include <Event.h>
#include <Timer.h>
#include <Servo.h>


Timer t;
int pin = 13; //servo pin

int left_pins[] = {7, 4};
int right_pins[] = {3, 2};
int five_list[5] = {0,0,0,0,0};

const int enable_2 = 6; //left motor
const int enable_1 = 5; //right motor

const int one_pin = A4; //this is actually what you think two pin is
const int two_pin = A1; //this is actually what you think one_pin is
const int three_pin = A2;
const int four_pin = A3;
const int five_pin = A0;
const int encod_pin = A5;

int one_val;
int two_val;
int three_val;
int four_val;
int five_val;
int encod_val;

int one_exp;
int two_exp;

int one_black;
int two_black;
int three_black;
int four_black;
int five_black;
int encod_black;

int r_corr;
int l_corr;

int red_one_exp = 570;
int red_two_exp = 570;
int one_red = 510;
int two_red = 460;
int three_red = 770;
int four_red = 450;

Servo myServo; //function connected to Servo

int angle = 0; //angle for servo to go to
int up = 60;
int down = 180;

unsigned long time;
unsigned int time45;
unsigned long time1;
unsigned long time2;

unsigned int turn45;

long one_sec = 1000;
long one_min = 60000;
char state = 'A';
int hop_or1 = 1;
int A[4][5]= {{1,1,0,0,0},{2,2,1,0,0},{3,3,2,1,0},{4,2,3,2,1}};
int B[4][5] = {{1,2,0,0,0},{2,2,2,0,0},{3,3,3,1,0},{4,2,4,2,1}};
int C[4][5] = {{1,3,0,0,0},{2,2,3,0,0},{3,3,4,1,0},{4,2,5,2,1}};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  pinMode(pin, OUTPUT);
  //t.every(6000, main_function);
  for (int i = 0; i < 2; i++)
  {
    pinMode(left_pins[i], OUTPUT);
    pinMode(right_pins[i], OUTPUT);
  }
  delay(1000);
  pick_up(up);
  calibrate_sensors();
  chill(5000);
  calibrated_turn();
  Serial.println(time1);
  chill(5000);
  //start();
  scan2();
  plinetest(3);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //t.update();
  //gtest();
  //main_function();
  STOPFOREVER(1);
}

void hand_off()
{
  plinetest(3);
  turning_left_5();
  scan2();
  chill(one_sec);
  pick_up(down);
  Drive_fwd(150,150);
  delay(4000);
  
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  while(three_val > three_black && four_val > four_black)
  {
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    Drive_bwd(100,100);
  }
  pick_up(up);
  scan2();
  turning_left_5();
}
void calibrate_sensors()
{
  int test[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for(int i = 0; i < 15; i++)
  {
    
    one_val = analogRead(one_pin);
    Serial.println("ONE: ");
    Serial.println(one_val); 
    delay(500);
    test[i] = one_val;
  }
  
  one_exp = average(test)+25;
  
  for(int i = 0; i < 15; i++)
  {
    two_val = analogRead(two_pin);
    Serial.println("TWO: ");
    Serial.println(two_val);
    delay(500);
    test[i] = two_val;
  }
  
  two_exp = average(test)+25;
  
  one_exp = (one_exp + two_exp)/2;
  two_exp = one_exp;
  
  for(int i = 0; i < 15; i++)
  {
    three_val = analogRead(three_pin);
    Serial.println("THREE: ");
    Serial.println(three_val);
    delay(500);
    test[i] = three_val;
    
  }
  
  three_black = average(test) + 80;
  
  for(int i = 0; i < 15; i++)
  {
    four_val = analogRead(four_pin);
    Serial.println("FOUR: ");
    Serial.println(four_val);
    delay(500);
    test[i] = four_val;
  }
  
  four_black = average(test) + 80;
  
  for(int i = 0; i < 15; i++)
  {
    five_val = analogRead(five_pin);
    Serial.println("FIVE: ");
    Serial.println(five_val);
    delay(500);
    test[i] = five_val;
  }
  
  five_black = average(test) + 80;
}

int average(int list[15])
{
  int avg = list[0];
  for(int i = 1; i < 15; i++)
  {
    if(list[i] < list[i-1])
    {
      avg = list[i];
    }
  }
  
  return avg;
}

void start()
{
  scan2();
  plinetest(2);
  Turning_left_45();
  chill(one_sec);
  pick_up(down);
  Get_ball();
  pick_up(up);
  //Turn_left_off2(255,255);
  //delay(7000);
  Back_up();
  scan2();
  scan3();
  plinetest(6);
  turning_right_5();
  scan2();
  hand_off();
}
  
void main_function()
{
  
  scan2();
  plinetest(3);
  scan2();
  turning_left_5();
  scan2();
  plinetest(6);
  Turning_right_45();
  chill(one_sec);
  pick_up(down);
  Get_ball();
  pick_up(up);
  Back_up();
  scan2();
  scan3();
  
  plinetest(6);
  turning_right_5();
  scan2();
  hand_off();
   
  //STOPFOREVER(1);
}


void calibrated_turn()
{
  time1 = millis();
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  five_val = analogRead(five_pin);
  while(four_val > four_black)
  {
    Serial.println("four");
    Turn_left_off2(85,85);
    four_val = analogRead(four_pin);
  }
  
  three_val = analogRead(three_pin);
  while(three_val > three_black)
  {
    Serial.println("three");
    Turn_left_off2(85,85);
    three_val = analogRead(three_pin);
    five_val = analogRead(five_pin);
    Serial.println(five_val);
    if(five_val < five_black)
    {
      Serial.println("five");
      break;
    }
  }
  
  four_val = analogRead(four_pin);
  while(four_val > four_black)
  {
    Serial.println("four2");
    Turn_left_off2(85,85);
    four_val = analogRead(four_pin);
  }
  
  three_val = analogRead(three_pin);
  five_val = analogRead(five_pin);
  while(three_val > three_black)
  {
    Serial.println("three2");
    Turn_left_off2(85,85);
    three_val = analogRead(three_pin);
    five_val = analogRead(five_pin);
    Serial.println(five_val);
    if(five_val < five_black)
    {
      Serial.println("five");
      break;
    }
  }
  Turn_right_off2(85,85);
  time45 = millis() - time1;
  Serial.println(time45);
  turn45 = time45/4;
  Serial.println(turn45);
  
}

void chill(long len)
{ time = millis();
  while (millis() - time < len)
  {
    STOP();
  }
}


void gtest() {
  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  five_val = analogRead(five_pin);
  encod_val = analogRead(encod_pin);
  Serial.println("|ONE   |TWO   |THREE |FOUR  |FIVE  |ENC   |");
  Serial.print(" ");
  Serial.print(one_val);
  Serial.print("    ");
  Serial.print(two_val);
  Serial.print("    ");
  Serial.print(three_val);
  Serial.print("    ");
  Serial.print(four_val);
  Serial.print("    ");
  Serial.print(five_val);
  Serial.print("    ");
  Serial.println(encod_val);
  delay(1000);
}

//drives both motors forwards at different pwm
//lower number is the direction it will turn in
//rpwm = right motor
//lpwm = left motor
void Drive_fwd(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  analogWrite(enable_1, rpwm);
  analogWrite(enable_2, lpwm);
  digitalWrite(left_pins[0], LOW);
  digitalWrite(left_pins[1], HIGH);
  digitalWrite(right_pins[0], LOW);
  digitalWrite(right_pins[1], HIGH);
}

void Drive_bwd(int rpwm, int lpwm)
{
  //Serial.println("Driving Backward");
  analogWrite(enable_1, rpwm);
  analogWrite(enable_2, lpwm);
  digitalWrite(left_pins[0], HIGH);
  digitalWrite(left_pins[1], LOW);
  digitalWrite(right_pins[0], HIGH);
  digitalWrite(right_pins[1], LOW);
}

//turns robot left
//right wheel is off
void Turn_left_off(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  analogWrite(enable_1, rpwm);
  analogWrite(enable_2, lpwm);
  digitalWrite(left_pins[0], LOW);
  digitalWrite(left_pins[1], LOW);
  digitalWrite(right_pins[0], HIGH);
  digitalWrite(right_pins[1], LOW);
}

//turns robot left
//both wheels on
void Turn_left_off2(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  analogWrite(enable_1, rpwm);
  analogWrite(enable_2, lpwm);
  digitalWrite(left_pins[0], LOW);
  digitalWrite(left_pins[1], HIGH);
  digitalWrite(right_pins[0], HIGH);
  digitalWrite(right_pins[1], LOW);
}

//turns robot right
//left wheel is off
void Turn_right_off(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  analogWrite(enable_1, rpwm);
  analogWrite(enable_2, lpwm);
  digitalWrite(left_pins[0], HIGH);
  digitalWrite(left_pins[1], LOW);
  digitalWrite(right_pins[0], LOW);
  digitalWrite(right_pins[1], LOW);
}

//turns robot right
//both wheels on
void Turn_right_off2(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  analogWrite(enable_1, rpwm);
  analogWrite(enable_2, lpwm);
  digitalWrite(left_pins[0], HIGH);
  digitalWrite(left_pins[1], LOW);
  digitalWrite(right_pins[0], LOW);
  digitalWrite(right_pins[1], HIGH);
}

//stops both motors
void STOP()
{
  //Serial.println("STOPPING!");
  analogWrite(enable_1, 0);
  analogWrite(enable_2, 0);
  digitalWrite(left_pins[0], LOW);
  digitalWrite(left_pins[1], LOW);
  digitalWrite(right_pins[0], LOW);
  digitalWrite(right_pins[1], LOW);
}

//stops both motors forever
void STOPFOREVER(int cond)
{
  //infinite loop
  while (cond)
    STOP();
}

//new line following method
void plinetest(int lines)
{
  int right_error[3] = {0, 0, 0};
  int left_error[3] = {0, 0, 0};
  int count = 0;
  int count2 = 0;
  unsigned long error = millis();
  while (count < lines)
  {
    /*if(error - millis() == 1000)
    {
      if(r_corr > l_corr + 10)
      {
        one_val = analogRead(one_pin);
        
        while(one_val > (one_exp-30))
        {
          one_val = analogRead(one_pin);
          Drive_fwd(l_corr + 20, r_corr);
        }
      }
      
      else if(l_corr > r_corr + 10)
      {
        two_val = analogRead(two_pin);
        
        while(two_val > (two_exp-30))
        {
          two_val = analogRead(two_pin);
          Drive_fwd(l_corr, r_corr+20);
        }
      }
      
      error = millis();
    }*/
    one_val = analogRead(one_pin); //right
    two_val = analogRead(two_pin); //left
    //Serial.print(one_val);
    //Serial.print(" ");
    //Serial.println(two_val);

    //contasts that can be changed to increase the amount the robot tries to correct itself
    int kpr = 6; //make this higher usually because for some reason this side never turns enough
    int kpl = 2;
    int ipr1 = 5;
    int ipr2 = 4;
    int ipl1 = 2;
    int ipl2 = 2;
    int rpwm = 125;
    int lpwm = 125;

    //2 1 4 4 2 2

    //these error values get larger the darker the sensor get because they get farther and farther from the expected value
    //50 is just a number to scale down the errors so they can be added to the pwms
    int r_error = (one_exp - one_val) / 50;
    int l_error = (two_exp - two_val) / 50;
    /*if(one_val <= one_red && one_val >= (one_red - 10))
    {
      int r_error = (red_one_exp - one_val) / 50;
      int l_error = (red_two_exp - two_val) / 50;
    }*/
    right_error[2] = right_error[1];
    right_error[1] = right_error[0];
    right_error[0] = r_error;

    left_error[2] = left_error[1];
    left_error[1] = left_error[0];
    left_error[0] = l_error;

    //    Serial.println("r_error || l_error");
    //    Serial.print(r_error);
    //    Serial.print(" ");
    //    Serial.println(l_error);

    //these are the corrected pwms
    r_corr = rpwm + kpr * r_error/2 + right_error[1] * ipr1 + right_error[2] * ipr2;
    //int r_corr = rpwm - kpl * l_error - left_error[1] * ipl1 - left_error[2] * ipl2;;
    
    l_corr = lpwm + kpl * l_error + left_error[1] * ipl1 + left_error[2] * ipl2;
    //int l_corr = lpwm - kpr * r_error/2 - right_error[1] * ipr1 - right_error[2] * ipr2;
    

    

    Drive_fwd(l_corr, r_corr); //drives motors at the corrected pwm

    //check if you cross line perpendicularly
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    //Serial.println("three_val");
    //Serial.println(three_val);
    //Serial.println("four val");
    //Serial.println(four_val);
    if (four_val < four_black || three_val < three_black) //if either sensor four or three hit black (values from gtest)
    {
      Serial.println("Crossed line: ");
      counting();
      count++;
      count2++;
    }
    
    if(count2 == 2)
    {
      scan2();
      count2 = 0;
    }
    
    /*if ((four_val <= (four_red) && four_val >= (four_red - 10)) || (three_val <= (three_red) && three_val >= (three_red - 10))) //if either sensor four or three hit black (values from gtest)
    {
      Serial.println("Crossed line: ");
      Serial.println("Crossed red ");
      counting();
      count++;
    }*/
    
    delay(100);
  }
}
//method is used to count how many perpendicular lines we crossed
void counting()
{
  bool three_w = false; //set to true only when sensor three hits white again
  bool four_w = false; //set to true only when sensor four hits black again

  //you can only escape this while loop when both sensors hit white again
  //this takes care of the lacalite hitting a perpendicular line at an angle
  while (three_w == false || four_w == false)
  {
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    if (three_val > three_black || (three_val <= (three_red + 5) && three_val >= (three_red - 10)))
    {
      three_w = true;
    }
    if (four_val > four_black || (four_val <= (four_red + 5) && four_val >= (four_red - 10)))
    {
      four_w = true;
    }
    delay(170);
  }
  Serial.println("out of while");
}

void pick_up(int newangle) //up 10 down 120
{

  myServo.attach(9);
  if( newangle == down)
  {
    for(int i = up; i <= down; i++)
    {
      myServo.write(i);
      delay(15);
    }
  }
  
  else if(newangle == up)
  {
    for(int i = down; i >= up; i -= 1)
    {
      myServo.write(i);
      delay(15);
    }
  }
  return;
}


/*void Turning_left_red()
{
  four_val = analogRead(four_pin);
  while (four_val > four_red)
  {
    Serial.println("four");
    Serial.println(four_val);
    Turn_left_off2(85, 85);
    four_val = analogRead(four_pin);
  }

  three_val = analogRead(three_pin);
  while (three_val > three_red)
  {
    Serial.println("three");
    Serial.println(three_val);
    Turn_left_off2(85, 85);
    three_val = analogRead(three_pin);
    two_val = analogRead(two_pin);
    Serial.println(two_val);
    if (two_val < two_red)
    {
      Serial.println("break");
      break;
    }
  }
}

void Turning_right_red()
{
  three_val = analogRead(three_pin);
  while (three_val > three_red)
  {
    Serial.println("three");
    Turn_right_off2(85, 85);
    three_val = analogRead(three_pin);
  }

  four_val = analogRead(four_pin);
  while (four_val > four_red)
  {
    Serial.println("four");
    Turn_right_off2(85, 85);
    four_val = analogRead(four_pin);
    one_val = analogRead(one_pin);
    Serial.println(one_val);
    if (one_val < one_red)
    {
      Serial.println("break");
      break;
    }
  }
}

void Turning_red_180()
{
  four_val = analogRead(four_pin);
  while (four_val > four_red)
  {
    Turn_left_off2(85, 85);
    four_val = analogRead(four_pin);
  }

  three_val = analogRead(three_pin);
  while (three_val > three_red)
  {
    Turn_left_off2(85, 85);
    three_val = analogRead(three_pin);
  }

  four_val = analogRead(four_pin);
  while (four_val > four_red)
  {
    Turn_left_off2(85, 85);
    four_val = analogRead(four_pin);
  }
  three_val = analogRead(three_pin);
  while (three_val > three_red)
  {
    Turn_left_off2(85, 85);
    three_val = analogRead(three_pin);
    two_val = analogRead(two_pin);
    if (two_val < two_red)
    {
      break;
    }
  }
}*/

void Turning_left_45()
{

  time2 = millis();
  while(millis() - time2 < turn45 + 200)
  {
    Turn_left_off2(85,85);
  }
}

void Turning_right_45()
{
  Serial.println("turn45");

  time2 = millis();
  while(millis() - time2 < turn45+200)
  {
    Serial.println("turn45 while");
    Turn_right_off2(85,85);
  }
}

void Get_ball()
{
  time = millis();
  while(millis() - time < 3300)
  {
    Serial.println("get");
    Drive_fwd(120,120);
  }
}

void Back_up()
{
  Serial.println("i wanna get back to the old days when the phone would ring and i knew it was you");
  //time = millis();
  for(int i = 0; i < 2; i++)
  {
      four_val = analogRead(four_pin);
      three_val = analogRead(three_pin);
      Turn_left_off(0,250);
      delay(1000);
    
      Turn_right_off(250,0);
      delay(1000);
  }
  
  //Drive_bwd(255,255);
  //delay(3000);
  four_val = analogRead(four_pin);
  three_val = analogRead(three_pin);
  

  while(four_val > four_black && three_val > three_black)
  {
    four_val = analogRead(four_pin);
    three_val = analogRead(three_pin);
    Drive_bwd(85,85);
    delay(50);
  }
  
  five_val = analogRead(five_pin);
  while(five_val > five_black)
  {
    Serial.println("doing five");
    five_val = analogRead(five_pin);
    Turn_right_off2(85,85);
  }
  
  four_val = analogRead(four_pin);
  while(four_val > four_black)
  {
    Serial.println("doing five");
    four_val = analogRead(four_pin);
    Turn_right_off2(85,85);
  }
  
  five_val = analogRead(five_pin);
  while(five_val > five_black)
  {
    Serial.println("doing five");
    five_val = analogRead(five_pin);
    Turn_right_off2(85,85);
  }
  
  
}

/*void state_machine(int list[4][5])
{
  if(hop_or1 == list[0][0])
  {
     plinetest(list[0][1]); //orientation one with hopper on red line and leg closest to board perpendicular to board
     scan();
     Turning_right_45();
     Get_ball();
     Back_up();
     Turning_right_180();
     scan();
     plinetest(list[0][1]);
     scan();
  }
      
  else if(hop_or1 == list[1][0])
  {  
     Turning_right();
     scan();
     plinetest(list[1][1]); //orientation two with hopper one space over from red line and leg closest to board perpendicular to board
     scan();
     Turning_left();
     scan();
     plinetest(list[1][2]);
     scan();
     Turning_left_45();
     Get_ball();
     Back_up();
     Turning_left_180();
     scan();
     plinetest(list[1][2]);
     scan();
     Turning_right();
     scan();
     plinetest(list[1][1]);
     scan();
  }
       
  else if(hop_or1 == list[2][0])
  { 
     Turning_right();
     scan();
     plinetest(list[2][1]); //orientation 3 with hopper flipped and one space over from red line
     scan();
     Turning_left();
     scan();
     plinetest(list[2][2]);
     scan();
     Turning_left();
     scan();
     plinetest(list[2][3]);
     scan();
     Turning_left_45();
     Get_ball;
     Back_up();
     Turning_left_180();
     scan();
     plinetest(list[2][3]);
     scan();
     Turning_right();
     scan();
     plinetest(list[2][2]);
     scan();
     Turning_right();
     scan();
     plinetest(list[2][1]);
     scan();
     Turning_left();
     scan();
  }
       
  else if(hop_or1 == list[3][0])
  {
     Turning_right();
     scan();
     plinetest(list[3][1]); //orientation 4 with hopper flipped and right at redline
     scan();
     Turning_left();
     scan();
     plinetest(list[3][2]);
     scan();
     Turning_left();
     scan();
     plinetest(list[3][3]);
     scan();
     Turning_left();
     scan();
     plinetest(list[3][4]);
     scan();
     Turning_left_45();
     Get_ball();
     Back_up();
     Turning_left_180();
     scan();
     plinetest(list[3][4]);
     scan();
     Turning_right();
     scan();
     plinetest(list[3][3]);
     scan();
     Turning_right();
     scan();
     plinetest(list[3][2]);
     scan();
     Turning_right();
     scan();
     plinetest(list[3][1]);
     scan();
     Turning_left();
     scan();
           
  }
  
}*/

void turning_left_5()
{
  four_val = analogRead(four_pin);
  while (four_val > four_black)
  {
    Serial.println("four");
    Serial.println(four_val);
    Turn_left_off2(85, 85);
    four_val = analogRead(four_pin);
  }
  
  three_val = analogRead(three_pin);
  
  while (three_val > three_black)
  {
    Serial.println("three");
    Turn_left_off2(85, 85);
    three_val = analogRead(three_pin);
    five_val = analogRead(five_pin);
      
    Serial.println(five_val);
    if (five_val < five_black)
    {
      Serial.println("break");
      break;
    }
  }
}

void turning_right_5()
{
  three_val = analogRead(three_pin);
  while (three_val > three_black)
  {
    Serial.println("three");
    Turn_right_off2(85, 85);
    three_val = analogRead(three_pin);
  }

  four_val = analogRead(four_pin);
  while (four_val > four_black)
  {
    Serial.println("four");
    Turn_right_off2(85, 85);
    four_val = analogRead(four_pin);
    five_val = analogRead(five_pin);
    Serial.println(five_val);
    if (five_val < five_black)
    {
      Serial.println("break");
      break;
    }
  }
}

void scan2()
{
  time = millis();
  while (millis() - time < 900)
  {
    Turn_left_off2(100, 100);
  }

  five_val = analogRead(five_pin);

  while(five_val > five_black)
  {
    time = millis();
    while (millis() - time < 80)
    {
      Turn_right_off2(100, 100);
    } 
    five_val = analogRead(five_pin);
    chill(125);
  }
}

void scan3()
{
  time = millis();
  while (millis() - time < 900)
  {
    Turn_right_off2(100, 100);
  }

  five_val = analogRead(five_pin);

  while(five_val > five_black)
  {
    time = millis();
    while (millis() - time < 80)
    {
      Turn_left_off2(200, 90);
    } 
    five_val = analogRead(five_pin);
    chill(125);
  }
}
