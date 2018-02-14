#include <Event.h>
#include <Timer.h>
#include <Servo.h>


Timer t;
int pin = 13; //servo pin

int left_pins[] = {7, 4};
int right_pins[] = {3, 2};

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

int one_exp = 590;
int two_exp = 590;
int one_black = 490;
int two_black = 480;
int three_black = 720;
int four_black = 600;
int five_black = 580;
int encod_black;

Servo myServo; //function connected to Servo

int angle = 0; //angle for servo to go to
int up = 10;
int down = 120;

unsigned long time;
long turn360 = 7540 + 200;
long turn180 = turn360 / 2 + 200; // 1/2
long turn90 = turn360 / 4; // 1/4
long turn270 = turn360 * 3 / 4; // 3/4

long one_sec = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  pinMode(pin, OUTPUT);
  t.every(7000, main_function);
  for (int i = 0; i < 2; i++)
  {
    pinMode(left_pins[i], OUTPUT);
    pinMode(right_pins[i], OUTPUT);
  }

  pick_up(up);

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  t.update();
  //gtest();

  //align();

  //Turn_left_off(75,75);
 
  //Turn_left_off2(100,100);
  
  //Turn_right_off(75,75);
  //Turn_right_off2(75,75);
  //Serial.println("straight");
}

void align()
{
  one_val = analogRead(one_pin); //right
  two_val = analogRead(two_pin); //left
  //Serial.print(one_val);
  //Serial.print(" ");
  //Serial.println(two_val);

  //these error values get larger the darker the sensor get because they get farther and farther from the expected value
  //50 is just a number to scale down the errors so they can be added to the pwms
  int r_error = (one_exp - one_val);
  int l_error = (two_exp - two_val);
  Serial.print(r_error);
  Serial.print(" ");
  Serial.println(l_error);
  do
  {
    if (l_error > r_error)
    {
      Turn_left_off2(85, 85);
      delay(500);
    }
    else
    {
      Turn_right_off2(85, 85);
      delay(500);
    }
    one_val = analogRead(one_pin); //right
    two_val = analogRead(two_pin); //left
    r_error = abs(one_exp - one_val);
    l_error = abs(two_exp - two_val);
    Serial.print(r_error);
    Serial.print(" ");
    Serial.println(l_error);
  } while (abs(l_error - r_error) >= 25);
}

void main_function()
{
  plinetest(1);
  chill(one_sec);

  turn(1, turn90);
  chill(one_sec);
  //align();

  plinetest(1);
  chill(one_sec);

  turn(1, turn180);
  chill(one_sec);
  //align();

  plinetest(1);
  chill(one_sec);

  turn(0, turn90);
  chill(one_sec);
  //align();

  plinetest(1);
  chill(one_sec);

  STOPFOREVER(1);
}

void turn(int dir, long angle) //1 left, 0 right
{
  time = millis();
  bool one_hit_black = false;
  bool two_hit_black = false;
  Serial.println("Turning");
  while(millis() - time < 500)
  {
    if(dir)
    {
      Turn_left_off2(100, 100);
    }
    
    else
    {
      Turn_right_off2(100, 100);
    }
  }
  
  int time1 = millis();
  while (millis() - time1 < angle)
  {
    if (dir)
    {
      Turn_left_off2(100, 100);
      two_val = analogRead(two_pin);
      one_val = analogRead(one_pin);
      Serial.println(two_val);
      if (two_val < two_black)
      {
        long time2 = millis();
        if(angle == turn180)
        {
          while(millis() - time2 < 150)
          {
            angle = turn90;
            Turn_left_off2(100, 100);
            two_val = analogRead(two_pin);
            one_val = analogRead(one_pin);
            
          }
          continue;
        }
        two_hit_black = true;
        
      }
      
      else if (one_val < one_exp && two_hit_black)
      {
         Serial.println("not timer two");
         Serial.println(two_hit_black);
         break;
      }
    }
    else
    {
      Turn_right_off2(100, 100);
      one_val = analogRead(one_pin);
      two_val = analogRead(two_pin);
      Serial.println(one_val);
      if (one_val < one_black)
      {
        if(angle == turn180)
        {
          long time2 = millis();
          while(millis() - time2 < 150)
          {
            angle = turn90;
            Turn_right_off2(100, 100);
            two_val = analogRead(two_pin);
            one_val = analogRead(one_pin);
          }
          continue;
        }
        one_hit_black = true;

      }
      
      else if (two_val < two_exp && one_hit_black)
      {
        Serial.println("not timer one");
        break;
      }
    }
  }
  
  two_val = analogRead(two_pin);
  while(two_val < two_black)
  {
    Turn_right_off2(85,85);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    if(one_val == one_exp && two_val == two_exp)
    {
      Serial.println("aligned two");
      break;
    }
  }
  
  one_val = analogRead(one_pin);
  while(one_val < one_black)
  {
    Turn_left_off2(85,85);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    if(one_val == one_exp && two_val == two_exp)
    {
      Serial.println("aligned one");
      break;
    }
  }
  Serial.println("Stopping");
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
  delay(5000);
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
  int right_error[3] = {0,0,0};
  int left_error[3] = {0,0,0};
  int count = 0;
  while (count < lines)
  {
    one_val = analogRead(one_pin); //right
    two_val = analogRead(two_pin); //left
    //Serial.print(one_val);
    //Serial.print(" ");
    //Serial.println(two_val);

    //contasts that can be changed to increase the amount the robot tries to correct itself
    int kpr = 2; //make this higher usually because for some reason this side never turns enough
    int kpl = 1;
    int ipr1 = 4;
    int ipr2 = 4;
    int ipl1 = 2;
    int ipl2 = 2;
    int rpwm = 100;
    int lpwm = 100;

    //these error values get larger the darker the sensor get because they get farther and farther from the expected value
    //50 is just a number to scale down the errors so they can be added to the pwms
    int r_error = (one_exp - one_val) / 50;
    int l_error = (two_exp - two_val) / 50;
    right_error[2] = right_error[1];
    right_error[1] = right_error[0]; 
    right_error[0] = r_error;
    
    left_error[2] = left_error[1];
    left_error[1] = left_error[0]; 
    left_error[0] = l_error;
    
    Serial.println("r_error || l_error");
    Serial.print(r_error);
    Serial.print(" ");
    Serial.println(l_error);

    //these are the corrected pwms
    int r_corr = rpwm + kpr * r_error + right_error[1]*ipr1 + right_error[2]*ipr2;
    int l_corr = lpwm + kpl * l_error + left_error[1]*ipl1 + left_error[2]*ipl2;
    //Serial.print(l_corr);
    //Serial.print(" ");
    //Serial.println(r_corr);

    Serial.println("r_corr");
    Serial.println(r_corr);
    Serial.println("l_corr");
    Serial.println(l_corr);
    Drive_fwd(l_corr, r_corr); //drives motors at the corrected pwm

    //check if you cross line perpendicularly
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    if (four_val < four_black || three_val < three_black) //if either sensor four or three hit black (values from gtest)
    {
      Serial.print("Crossed line: ");
      counting();
      count++;
    }
    delay(100);
  }
}
//method is used to count how many perpendicular lines we crossed
void counting()
{
  int rlc = 0;
  bool three_w = false; //set to true only when sensor three hits white again
  bool four_w = false; //set to true only when sensor four hits black again

  //you can only escape this while loop when both sensors hit white again
  //this takes care of the lacalite hitting a perpendicular line at an angle
  while (three_w == false || four_w == false)
  {
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    //Serial.print(three_val);
    //Serial.print(" ");
    //Serial.println(four_val);
    if (three_val > three_black)
    {
      three_w = true;
    }
    if (four_val > four_black)
    {
      four_w = true;
    }

    delay(50);
  }
  Serial.println("out of while");
  //add 1 to line counter
  rlc++;
  //Serial.println(rlc);
}

void pick_up(int angle)
{

  myServo.attach(9);
  myServo.write(angle);
  return;
}

void Turning_right()
{
  three_val = analogRead(three_pin);

  while (three_val > three_black)
  {
    Serial.println("three_val");
    Turn_right_off2(100, 100);
    three_val = analogRead(three_pin);
    Serial.println(three_val);
    if (three_val < three_black)
    {
      break;
    }

    delay(50);
  }

  four_val = analogRead(four_pin);

  while (four_val > four_black)
  {
    Serial.println("four_val");
    Turn_right_off2(100, 100);
    four_val = analogRead(four_pin);
    Serial.println(four_val);
    if (four_val < four_black)
    {
      break;
    }

    delay(50);
  }

  three_val = analogRead(three_pin);
  while (three_val > three_black)
  {
    Serial.println("three_val2");
    Turn_left_off(0, 100);
    three_val = analogRead(three_pin);
    Serial.println(three_val);
    if (three_val < three_black)
    {
      break;
    }

    delay(50);
  }

  four_val = analogRead(four_pin);
  while (four_val > four_black)
  {
    Serial.println("four_val2");
    Turn_right_off(100, 0);
    four_val = analogRead(four_pin);
    Serial.println(four_val);
    if (four_val < four_black)
    {
      break;
    }

    delay(50);
  }

}

