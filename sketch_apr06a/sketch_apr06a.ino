#include <Event.h>
#include <Timer.h>
#include <Servo.h>

Timer t;

const int one_pin = A1; //this is actually what you think two pin is
const int two_pin = A3; //this is actually what you think one_pin is
const int three_pin = A2;
const int four_pin = A4;
const int five_pin = A0;
const int pin = A5;

int one_val;
int two_val;
int three_val;
int four_val;
int five_val;
int pin_val;

int one_exp = 630;
int two_exp = 630;
int one_black = 490;
int two_black = 390;
int three_black = 730;
int four_black = 570;
int five_black = 140;
int five_white = 600;
int black = 790;


Servo myservo; //function connected to Servo
Servo babyservo;

Servo oneServo;
Servo twoServo;

long one_sec = 1000;
unsigned long time;
unsigned long time_turn_left;
unsigned int time_90_left;
unsigned long time_turn_right;
unsigned int time_90_right;
unsigned long square_time;
unsigned int half_square;
unsigned int half_time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  //pinMode(pin, OUTPUT);
  //t.every(3000, main_function);
  
  myservo.attach(4);
  babyservo.attach(3);
  myservo.write(90);
  babyservo.write(175); //close 175 / open 0
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(90);
  twoServo.write(90);
  delay(1000);
  calibrate_sensors();
  //plinetest(3);
  chill(5000);
  calibration_turn_left();
  chill(5000);
  //turn_90_left();
  //chill(5000);
  calibration_turn_right();
  chill(5000);
  //turn_90();
  //chill(5000);
  //cal_square();
  chill(15000);
  //drive_half();
  start_right();
  //main_function();
}

void loop() {
  // put your main code here, to run repeatedly:
  five_val = analogRead(five_pin);
  if(five_val < five_black)
  {
    Serial.println("black");
    Serial.println(five_val);
    main_function();
  }

  else if(five_val > five_white)
  {
    Serial.println("white");
    Serial.println(five_val);
    main_function();
  }
  
  //chill(30000);
  //main_function();
  //gtest();
  //t.update();
  //main_function();
  
  //Drive_fwd(80,10);
  
  //gtest();
  
  oneServo.write(90);
  twoServo.write(90);
  
  
  //STOPFOREVER(1);
}

void main_function()
{
  Serial.println("happening");
  //moving_left(2);
  delay(3000);
  release_ball();
  delay(2000);
  close_hatch();

  //moving_right(2);
}

void cal_square()
{
  Serial.println("Here square");
  square_time = millis();
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  while(three_val > three_black && four_val > four_black)
  {
    Serial.println("Here");
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    Drive_fwd(70,20);
  }
  
  half_square = millis() - square_time;
  Serial.println(half_square);
  half_time = half_square/2;
  Serial.println(half_time);
}

void drive_half()
{
  unsigned long time = millis();
  while(millis() - time < 700)
  {
    Drive_fwd(70,20);
  }
}
  
void calibration_turn_left()
{
  time_turn_left = millis();
  four_val = analogRead(four_pin);
  while (four_val > four_black)
  {
    Serial.println("four");
    Turn_left_off2(80, 80);
    four_val = analogRead(four_pin);
  }

  one_val = analogRead(one_pin);
  while (one_val > one_black)
  {
    Serial.println("three");
    Turn_left_off2(80, 80);
    three_val = analogRead(three_pin);
    one_val = analogRead(one_pin);
    if (one_val < one_black)
    {
      Serial.println("break");
      break;
    }
  }

  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);

  while (one_val < one_black)
  {
    Turn_left_off2(80, 80);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    if (one_val == one_exp && two_val == two_exp)
    {
      Serial.println("align");
      break;
    }
  }
  
  time_90_left = millis() - time_turn_left;
}

void calibration_turn_right()
{
  time_turn_right = millis();
  three_val = analogRead(three_pin);
  while (three_val > three_black)
  {
    Serial.println("three");
    Turn_right_off2(10, 10);
    three_val = analogRead(three_pin);
  }

  two_val = analogRead(two_pin);
  while (two_val > two_black)
  {
    Serial.println("four");
    Turn_right_off2(10, 10);
    three_val = analogRead(three_pin);
    two_val = analogRead(two_pin);
    if (two_val < two_black)
    {
      Serial.println("break");
      break;
    }
  }

  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);

  while (two_val < two_black)
  {
    Turn_right_off2(10, 10);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    if (two_val == two_exp && one_val == one_exp)
    {
      Serial.println("align");
      break;
    }
  }
  time_90_right = millis() - time_turn_right;
}
  
void turn_90()
{
  unsigned long time = millis();
  while(millis() - time < time_90_right)
  {
    Turn_right_off2(10,10);
  }
}

void turn_90_left()
{
  unsigned long time = millis();
  while(millis() - time < time_90_left)
  {
    Turn_left_off2(80,80);
  }
}

void calibrate_sensors()
{
  int test[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 15; i++)
  {

    one_val = analogRead(one_pin);
    Serial.println("ONE: ");
    Serial.println(one_val);
    delay(500);
    test[i] = one_val;
  }

  one_exp = average(test) + 20;

  for (int i = 0; i < 15; i++)
  {
    two_val = analogRead(two_pin);
    Serial.println("TWO: ");
    Serial.println(two_val);
    delay(500);
    test[i] = two_val;
  }

  two_exp = average(test) + 20;
  one_exp = (one_exp + two_exp) / 2;
  two_exp = one_exp;
  chill(5000);
  for (int i = 0; i < 15; i++)
  {

    one_val = analogRead(one_pin);
    Serial.println("ONE: ");
    Serial.println(one_val);
    delay(500);
    test[i] = one_val;
  }

  one_black = average(test) + 100;

  for (int i = 0; i < 15; i++)
  {
    two_val = analogRead(two_pin);
    Serial.println("TWO: ");
    Serial.println(two_val);
    delay(500);
    test[i] = two_val;
  }

  two_black = average(test) + 100;

  chill(5000);
  for (int i = 0; i < 15; i++)
  {
    three_val = analogRead(three_pin);
    Serial.println("THREE: ");
    Serial.println(three_val);
    delay(500);
    test[i] = three_val;

  }

  three_black = average(test) + 100;

  for (int i = 0; i < 15; i++)
  {
    four_val = analogRead(four_pin);
    Serial.println("FOUR: ");
    Serial.println(four_val);
    delay(500);
    test[i] = four_val;
  }

  four_black = average(test) + 100;

  chill(5000);
}

int average(int list[15])
{
  int avg = list[0];
  for (int i = 1; i < 15; i++)
  {
    if (list[i] < list[i - 1])
    {
      avg = list[i];
    }
  }

  return avg;
}

void start_right()
{
  
   chill(5000);
  
  /*chill(one_sec);
  plinetest(1);
  chill(one_sec);
  Turning_left();
  chill(one_sec);
  drive_half();
  chill(one_sec);
  turn_90();
  chill(one_sec);
  drive_half();
  chill(one_sec);
  turn_90_left();
  chill(one_sec);
  plinetest(1);
  chill(one_sec);
  turn_90();
  chill(one_sec);
  plinetest(1);
  chill(one_sec);
  Turning_left();
  chill(one_sec);*/
  
  Drive_fwd(70,20);
  delay(3600);
  /*three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  while(three_val > three_black && four_val > four_black)
  {
    three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
    Drive_fwd(70, 20);
  }*/
  chill(one_sec);
  turn_90_left();
  chill(one_sec);
  //plinetest(3);
  Drive_fwd(70,20);
  delay(9000);

  chill(one_sec);
  
  
  turn_90_left();
  chill(one_sec);
  Drive_fwd(70,20);
  delay(3600);
  
  chill(one_sec);
  turn_90();
  chill(one_sec);
  Drive_fwd(70,20);
  delay(900);
  chill(one_sec);
  Drive_fwd(70,20);
  delay(3000);
  
  
  
  
 /* chill(5000);
  plinetest(1);
  chill(one_sec);
  Drive_fwd(45,45);
  delay(150);
  chill(one_sec);
  Turning_right();
  chill(one_sec);
  plinetest(2);
  chill(one_sec);
  Turning_left();
  chill(one_sec);
  drive_half();
  chill(one_sec);
  turn_90();
  chill(one_sec);
  drive_half();
  chill(one_sec);
  turn_90_left();
  chill(one_sec);
  plinetest(1);
  chill(one_sec);
  turn_90();
  chill(one_sec);
  plinetest(1);
  chill(one_sec);
  Turning_left();
  chill(one_sec);
 
  //plinetest(3);
  
  plinetest(5);
  chill(one_sec);
  
  
  Turning_left();
  chill(one_sec);
  plinetest(2);
  chill(one_sec);
  Turning_right();
  chill(one_sec);
  drive_half();
  turn_90_left();
  chill(one_sec);
  plinetest(1);
  turn_90();
  chill(one_sec);
  plinetest(1);
  chill(one_sec);
  Drive_fwd(45,45);
  delay(3000);*/
}

void start_left()
{
  plinetest(1);
  
  Turning_right();
  chill(one_sec);
  Drive_fwd(230,230);
  delay(800);
  turn_90_left();
  Drive_fwd(230,230);
  delay(800);
  turn_90();
  chill(one_sec);
  plinetest(1);
  turn_90_left();
  plinetest(1);
  Turning_right();
  chill(one_sec);
  plinetest(5);
  chill(one_sec);
  Turning_right();
  chill(one_sec);
  plinetest(2);
  chill(one_sec);
  Turning_left();
  chill(one_sec);
  Drive_fwd(230, 230);
  delay(800);
  turn_90();
  chill(one_sec);
  plinetest(1);
  turn_90_left();
  chill(one_sec);
  plinetest(1);
  chill(one_sec);
  Drive_fwd(230, 230);
  delay(1000);
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
  Serial.println("    ");
  delay(1000);
}

void Drive_fwd(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  lpwm = lpwm+90;
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

void Drive_bwd(int rpwm, int lpwm)
{
  //Serial.println("Driving Backward");
  rpwm = rpwm+90;
  lpwm = lpwm;
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//turns robot left
//right wheel is off
void Turn_left_off(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  rpwm = 90;
  lpwm = lpwm;
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//turns robot left
//both wheels on
void Turn_left_off2(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  rpwm = rpwm;
  lpwm = lpwm;
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//turns robot right
//left wheel is off
void Turn_right_off(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  rpwm = rpwm+90;
  lpwm = 90;
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//turns robot right
//both wheels on
void Turn_right_off2(int rpwm, int lpwm)
{
  rpwm = rpwm+90;
  lpwm = lpwm+90;
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//stops both motors
void STOP()
{
  Serial.println("STOPPING!");
  oneServo.attach(10);
  twoServo.attach(9);
  oneServo.write(90);
  twoServo.write(90);
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
  int right_error[4] = {0, 0, 0, 0};
  int d_right_error[3] = {0, 0, 0};
  int left_error[4] = {0, 0, 0, 0};
  int d_left_error[3] = {0, 0, 0};
  int count = 0;
  int count2 = 0;
  unsigned long derivative = millis();
  while (count < lines)
  {
    one_val = analogRead(one_pin); //right
    two_val = analogRead(two_pin); //left
    //Serial.print(one_val);
    //Serial.print(" ");
    //Serial.println(two_val);

    //contasts that can be changed to increase the amount the robot tries to correct itself
    int kpr = 3; //make this higher usually because for some reason this side never turns enough
    int kpl = -3;
    int ipr1 = 2;
    int ipr2 = 2;
    int ipr3 = 2;
    int dpr1 = 3;
    int dpr2 = 3;
    int dpr3 = 3;
    int ipl1 = -2;
    int ipl2 = -2;
    int ipl3 = -2;
    int dpl1 = -3;
    int dpl2 = -3;
    int dpl3 = -3;
    int rpwm = 35;
    int lpwm = 55;

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
    right_error[3] = right_error[2];
    right_error[2] = right_error[1];
    right_error[1] = right_error[0];
    right_error[0] = r_error;

    left_error[3] = left_error[2];
    left_error[2] = left_error[1];
    left_error[1] = left_error[0];
    left_error[0] = l_error;

    //    Serial.println("r_error || l_error");
    //    Serial.print(r_error);
    //    Serial.print(" ");
    //    Serial.println(l_error);

    //derivative
    if(derivative == 100)
    {
      d_right_error[0] = (right_error[2] - right_error[3])/derivative;
      d_right_error[1] = (right_error[1] - right_error[2])/derivative;
      d_right_error[2] = (right_error[0] - right_error[1])/derivative;
      d_left_error[0] = (left_error[2] - left_error[3])/derivative;
      d_left_error[1] = (left_error[1] - left_error[2])/derivative;
      d_left_error[2] = (left_error[0] - left_error[1])/derivative;
      derivative = millis();
    }
    //these are the corrected pwms
    int r_corr = rpwm + kpr * r_error + right_error[1] * ipr1 + right_error[2] * ipr2 + right_error[3] * ipr3 + d_right_error[0] * dpr1 + d_right_error[1] * dpr2 + d_right_error[2] * dpr3;
    //int r_corr = rpwm - kpl * l_error - left_error[1] * ipl1 - left_error[2] * ipl2;;
    
    int l_corr = lpwm + kpl * l_error + left_error[1] * ipl1 + left_error[2] * ipl2 + left_error[3] * ipl3 + d_left_error[0] * dpl1 + d_left_error[1] * dpl2 + d_left_error[2] * dpl3;
    //int l_corr = lpwm - kpr * r_error/2 - right_error[1] * ipr1 - right_error[2] * ipr2;
    
    Serial.println("right motor");
    Serial.println(l_corr);
    Serial.println("left motor");
    Serial.println(r_corr);
    

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
      Serial.println(count);
    }
    
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
    if (three_val > three_black)
    {
      three_w = true;
    }
    if (four_val > four_black)
    {
      four_w = true;
    }
    delay(105);
  }
  Serial.println("out of while");
}

void Turning_left()
{
  four_val = analogRead(four_pin);
  while (four_val > four_black)
  {
    Serial.println("four");
    Turn_left_off2(80, 80);
    four_val = analogRead(four_pin);
  }

  one_val = analogRead(one_pin);
  while (one_val > one_black)
  {
    Serial.println("three");
    Turn_left_off2(80, 80);
    three_val = analogRead(three_pin);
    one_val = analogRead(one_pin);
    if (one_val < one_black)
    {
      Serial.println("break");
      break;
    }
  }

  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);

  while (one_val < one_black)
  {
    Turn_left_off2(80, 80);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    if (one_val == one_exp && two_val == two_exp)
    {
      Serial.println("align");
      break;
    }
  }
}

void Turning_right()
{
  three_val = analogRead(three_pin);
  while (three_val > three_black)
  {
    Serial.println("three");
    Turn_right_off2(10, 10);
    three_val = analogRead(three_pin);
  }

  two_val = analogRead(two_pin);
  while (two_val > two_black)
  {
    Serial.println("four");
    Turn_right_off2(10, 10);
    three_val = analogRead(three_pin);
    two_val = analogRead(two_pin);
    if (two_val < two_black)
    {
      Serial.println("break");
      break;
    }
  }

  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);

  while (two_val < two_black)
  {
    Turn_right_off2(10, 10);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    if (two_val == two_exp && one_val == one_exp)
    {
      Serial.println("align");
      break;
    }
  }
}

void moving_left(int num)
{
  myservo.attach(4);
  int count = 0;
  while (count < num)
  {
    pin_val = analogRead(pin);
    myservo.write(70);

    if (pin_val < black)
    {
      counting_stickers();
      count++;
      Serial.println(count);
    }
    delay(100);
  }

  myservo.write(90);


}

void moving_right(int num)
{
  myservo.attach(4);
  int count = 0;
  Serial.println("printing");
  while (count < num)
  {
    pin_val = analogRead(pin);
    Serial.println(pin_val);
    myservo.write(110);
    Serial.println("again");
    if (pin_val < black)
    {
      counting_stickers();
      count++;
      Serial.println(count);
    }
    delay(100);
  }

  myservo.write(90);

}

void counting_stickers()
{
  bool track_w = false; //set to true only when sensor three hits white again
  //set to true only when sensor four hits black again

  //you can only escape this while loop when both sensors hit white again
  //this takes care of the lacalite hitting a perpendicular line at an angle
  while (track_w == false)
  {
    pin_val = analogRead(pin);

    if (pin_val > black)
    {
      track_w = true;
    }
    delay(100);
  }
  Serial.println("out of while");
}

void release_ball()
{
  Serial.println("open");
  babyservo.attach(3);
  for (int i = 155; i > 0; i--)
  {
    babyservo.write(i);
    delay(15);
  }
}

void close_hatch()
{
  Serial.println("close");
  babyservo.attach(3);
  for (int i = 0; i < 155; i++)
  {
    babyservo.write(i);
    delay(15);
  }
}

