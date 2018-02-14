#include <Event.h>
#include <Timer.h>
#include <Servo.h>


Timer t;
int pin = 13; //servo pin

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

int one_exp = 220;
int two_exp = 220;

int one_black = 370;
int two_black = 310;
int three_black = 500;
int four_black = 450;
int five_black = 330;
int encod_black;


Servo myServo; //function connected to Servo
Servo oneServo;
Servo twoServo;

int angle = 0; //angle for servo to go to
int up = 60;
int down = 170;

unsigned long time;
unsigned int time45;
unsigned long time1;
unsigned long time2;

unsigned int turn45;

long one_sec = 1000;

char state = 'A';
int hop_or1 = 1;
int A[4][5]= {{1,1,0,0,0},{2,2,1,0,0},{3,3,2,1,0},{4,2,3,2,1}};
int B[4][5] = {{1,2,0,0,0},{2,2,2,0,0},{3,3,3,1,0},{4,2,4,2,1}};
int C[4][5] = {{1,3,0,0,0},{2,2,3,0,0},{3,3,4,1,0},{4,2,5,2,1}};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  pinMode(pin, OUTPUT);
  t.every(6000, main_function);

  delay(1000);
  pick_up(up);
  calibrated_turn();
  Serial.println(time1);
  //chill(one_sec);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //t.update();
  //gtest();
}
void main_function()
{
  //Back_up();
  //calibrated_turn();
  //chill(one_sec);
  //Turning_right_45();
  /*plinetest(6);
  scan2();
  turning_right_5();
  scan2();
  plinetest(2);
  turning_left_5();
  scan2();*/
  
  plinetest(1);
  scan2();
  Turning_right_45();
  chill(one_sec);
  pick_up(down);
  Get_ball();
  pick_up(up);
  Back_up();
  scan2();
  scan3();
  plinetest(1);
  
  /*scan2();
  Turning_right_45();
  Get_ball();
  pick_up(up);
  Back_up();*/
  

  
  STOPFOREVER(1);
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
  
  time45 = millis() - time1;
  Serial.println(time45);
  turn45 = time45/4;
  Serial.println(turn45);
  
}

void scan()
{
  time = millis();
  while (millis() - time < 1000)
  {
    Turn_left_off2(100, 100);
  }

  one_val = analogRead(one_pin);
  two_val = analogRead(two_pin);
  while(!(abs(one_val - two_val) <= 100 && two_val < two_exp && one_val < one_exp) || two_val < two_black)
  {
    time = millis();
    while (millis() - time < 80)
    {
      Turn_right_off2(100, 100);
    } 
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    chill(125);
  }
  /*
  Serial.print(one_val);
  Serial.print(" ");
  Serial.println(two_val);
  */
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
  oneServo.attach(10);
  twoServo.attach(11);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

void Drive_bwd(int rpwm, int lpwm)
{
  //Serial.println("Driving Backward");
  rpwm = rpwm+90;
  lpwm = lpwm+90;
  oneServo.attach(10);
  twoServo.attach(11);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//turns robot left
//right wheel is off
void Turn_left_off(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  rpwm = 90;
  lpwm = lpwm+90;
  oneServo.attach(10);
  twoServo.attach(11);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//turns robot left
//both wheels on
void Turn_left_off2(int rpwm, int lpwm)
{
  //Serial.println("Driving Forward");
  rpwm = rpwm;
  lpwm = lpwm+90;
  oneServo.attach(10);
  twoServo.attach(11);
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
  twoServo.attach(11);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//turns robot right
//both wheels on
void Turn_right_off2(int rpwm, int lpwm)
{
  rpwm = rpwm+90;
  lpwm = lpwm;
  oneServo.attach(10);
  twoServo.attach(11);
  oneServo.write(rpwm);
  twoServo.write(lpwm);
}

//stops both motors
void STOP()
{
  //Serial.println("STOPPING!");
  oneServo.attach(10);
  twoServo.attach(11);
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
  int right_error[3] = {0, 0, 0};
  int left_error[3] = {0, 0, 0};
  int count = 0;
  int count2 = 0;
  while (count < lines)
  {
    one_val = analogRead(one_pin); //right
    two_val = analogRead(two_pin); //left
    //Serial.print(one_val);
    //Serial.print(" ");
    //Serial.println(two_val);

    //contasts that can be changed to increase the amount the robot tries to correct itself
    int kpr = 1; //make this higher usually because for some reason this side never turns enough
    int kpl = 1;
    int ipr1 = 0;
    int ipr2 = 0;
    int ipl1 = 0;
    int ipl2 = 0;
    int rpwm = 30;
    int lpwm = 30;

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
    int r_corr = rpwm + kpr * r_error/2 + right_error[1] * ipr1 + right_error[2] * ipr2;
    //int r_corr = rpwm - kpl * l_error - left_error[1] * ipl1 - left_error[2] * ipl2;;
    
    int l_corr = lpwm + kpl * l_error + left_error[1] * ipl1 + left_error[2] * ipl2;
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
    if (three_val > three_black)
    {
      three_w = true;
    }
    if (four_val > four_black)
    {
      four_w = true;
    }
    delay(100);
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

void Turning_left_45()
{

  time2 = millis();
  while(millis() - time2 < turn45)
  {
    Turn_left_off2(30,30);
  }
}

void Turning_right_45()
{
  Serial.println("turn45");

  time2 = millis();
  while(millis() - time2 < turn45)
  {
    Serial.println("turn45 while");
    Turn_right_off2(30,30);
  }
}

void Get_ball()
{
  time = millis();
  while(millis() - time < 3300)
  {
    Serial.println("get");
    Drive_fwd(30,30);
  }
}

void Back_up()
{
  Serial.println("i wanna get back to the old days when the phone would ring and i knew it was you");
  //time = millis();
  for(int i = 0; i < 3; i++)
  {
      four_val = analogRead(four_pin);
      three_val = analogRead(three_pin);
      Turn_left_off(0,10);
      delay(500);
    
      Turn_right_off(10,0);
      delay(500);
  }
      
  four_val = analogRead(four_pin);
  three_val = analogRead(three_pin);
  

  while(four_val > four_black && three_val > three_black)
  {
    four_val = analogRead(four_pin);
    three_val = analogRead(three_pin);
    Drive_bwd(30,30);
    delay(50);
  }
  
  five_val = analogRead(five_pin);
  while(five_val > five_black)
  {
    Serial.println("doing five");
    five_val = analogRead(five_pin);
    Turn_right_off2(30,30);
  }
  
  four_val = analogRead(four_pin);
  while(four_val > four_black)
  {
    Serial.println("doing five");
    four_val = analogRead(four_pin);
    Turn_right_off2(30,30);
  }
  
  five_val = analogRead(five_pin);
  while(five_val > five_black)
  {
    Serial.println("doing five");
    five_val = analogRead(five_pin);
    Turn_right_off2(30,30);
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
    Turn_left_off2(30, 30);
    four_val = analogRead(four_pin);
  }
  
  three_val = analogRead(three_pin);
  
  while (three_val > three_black)
  {
    Serial.println("three");
    Turn_left_off2(30, 30);
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
    Turn_right_off2(30, 30);
    three_val = analogRead(three_pin);
  }

  four_val = analogRead(four_pin);
  while (four_val > four_black)
  {
    Serial.println("four");
    Turn_right_off2(30, 30);
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
    Turn_left_off2(45, 45);
  }

  five_val = analogRead(five_pin);

  while(five_val > five_black)
  {
    time = millis();
    while (millis() - time < 80)
    {
      Turn_right_off2(45, 45);
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
    Turn_right_off2(45, 45);
  }

  five_val = analogRead(five_pin);

  while(five_val > five_black)
  {
    time = millis();
    while (millis() - time < 80)
    {
      Turn_left_off2(20, 60);
    } 
    five_val = analogRead(five_pin);
    chill(125);
  }
}


