#include <Event.h>
#include <Timer.h>
#include <Servo.h>


Timer t;
int pin = 13;

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

int one_exp = 680;
int two_exp = 600;

int three_black = 750;
int four_black = 650;
int five_black = 580;
int encod_black;

char state = 'A';
int hop_or1 = 1;
int A[4][5]= {{1,1,0,0,0},{2,2,1,0,0},{3,3,2,1,0},{4,2,3,2,1}};
int B[4][5] = {{1,2,0,0,0},{2,2,2,0,0},{3,3,3,1,0},{4,2,4,2,1}};
int C[4][5] = {{1,3,0,0,0},{2,2,3,0,0},{3,3,4,1,0},{4,2,5,2,1}};


int j = 0; //encoder counter (increases everytime you go from white to black on the encoder)
int lc = 0; //lines crossed used in straighten
//int rlc = 0; //lines crossed used in plinetest

Servo myServo; //function connected to Servo

int angle = 0; //angle for servo to go to

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
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //gtest();
  /*
  plinetest(2);
  STOP();
  Serial.println("looped1");
  delay(5000);
  Serial.println("looped2");
  */

  t.update();

  //plinetest(2);
  //Turn_left_off(150,150); //right motor forwards / left motor backwards
}

//method is used to calibrate the lacalite
//currently you need to manually calibrate it
//right down the values for white and black
void main_function()
{
  Drive_fwd(100,100);
  
  /*plinetest(1);
  //slowdown();


  Turning_left();

  plinetest(1);
  Turning_left_180();
  plinetest(1);
  //five_to_black();
  /*five_to_black();
  plinetest(2);
  slowdown();
  Turning_right_45();
  Drive_fwd(100,100);
  delay(3000);*/
  
  
  //pick_up(120);
  /*Drive_fwd(100,100);
  delay(1500);
  STOP;
  delay(2000);
  //five_to_black();
  pick_up(10);
  Drive_bwd(100,100);
  delay(2000);*/
  //STOPFOREVER(1);
}
void five_to_black()
{
  Serial.println("five black");
  five_val = analogRead(five_pin);
  while (five_val > five_black)
  {
    five_val = analogRead(five_pin);
    Serial.println("five black while");
    
    one_val = analogRead(one_pin); //right
    two_val = analogRead(two_pin); //left
    //Serial.print(one_val);
    //Serial.print(" ");
    //Serial.println(two_val);

    int exp_val = (one_exp + two_exp) / 2; //this is a middle value found from gtest, both sensors are approx. 500 when the lacalite it facing straight

    //contasts that can be changed to increase the amount the robot tries to correct itself
    int kpr = 10; //make this higher usually because for some reason this side never turns enough
    int kpl = 10;

    int rpwm = 150;
    int lpwm = 150;

    //these error values get larger the darker the sensor get because they get farther and farther from the expected value
    //50 is just a number to scale down the errors so they can be added to the pwms
    int r_error = (one_exp - one_val) / 50;
    int l_error = (two_exp - two_val) / 50;

    //Serial.print(r_error);
    //Serial.print(" ");
    //Serial.println(l_error);

    //these are the corrected pwms
    int r_corr = rpwm + kpr * r_error;
    int l_corr = lpwm + kpl * l_error;
    //Serial.print(l_corr);
    //Serial.print(" ");
    //Serial.println(r_corr);

    Drive_fwd(l_corr, r_corr); //drives motors at the corrected pwm

    //check if you cross line perpendicularly
   
    five_val = analogRead(five_pin);
    if (five_val < five_black)
    {
      break;
    }
    delay(100);
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

void slowdown()
{
  Serial.println("slowwwwww");
  int exp5v = 660;
  int pwm5 = 100;
  Drive_fwd(0, 0);
  /*while(pwm5 >=0)
  {
    Drive_fwd(pwm5, pwm5);
    five_val = analogRead(five_pin);
    int err = abs(five_val - exp5v)*10;
    pwm5 -= err;
        Serial.println(pwm5);
    delay(50);
  }
  */
  five_val = analogRead(five_pin);
  while (five_val > five_black)
  {
    Drive_bwd(100, 100);
    five_val = analogRead(five_pin);
    Serial.println("five_val");
    if (five_val < five_black)
    {
      break;
    }

    delay(50);
  }



  //STOPFOREVER(1);
  //Drive_fwd(100,100);
}

void Turning_left()
{
  four_val = analogRead(four_pin);
  bool two_hit_black = false;
  while (four_val > four_black)
  {
    Serial.println("four_val");
    Turn_left_off2(100, 100);
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
    Serial.println("one_val || two_val");
    Turn_left_off2(100, 100);
    three_val = analogRead(three_pin);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    Serial.print(one_val);
    Serial.println(two_val);
    if (two_val < two_exp)
    {
      two_hit_black = true;
      if(two_hit_black && two_val < two_exp && one_val < one_exp)
      {
        Serial.println("done turning");
        break;
      }
      Serial.println("continuing");
      continue;
    }
    
    
    if(three_val < three_black)
    {
      Turn_right_off2(100, 100);
      one_val = analogRead(one_pin);
      two_val = analogRead(two_pin);
      while(one_val > one_exp || two_val > one_exp)
      {
        Turn_right_off2(100, 100);
        one_val = analogRead(one_pin);
        two_val = analogRead(two_pin);
        Serial.println("went into corrective while");
      }
    }
      

    delay(50);
  }


}

void Turning_left_45()
{
  three_val = analogRead(three_pin);
  bool go = false;

  while (three_val > three_black)
  {
    Serial.println("three_val");
    Turn_left_off2(100, 100);
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    if (four_val < four_black)
    {
      go = true;
    }

    Serial.println(three_val);
    if (three_val < three_black)
    {
      break;
    }

    delay(50);
  }

  if (go == true)
  {
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

    three_val = analogRead(three_pin);
    while (three_val > three_black)
    {
      Serial.println("three_val2");
      Turn_left_off(100, 0);
      three_val = analogRead(three_pin);
      Serial.println(three_val);
      if (three_val < three_black)
      {
        break;
      }

      delay(50);
    }
  }

  else
  {
    four_val = analogRead(four_pin);
    while (four_val > four_black)
    {
      Serial.println("four_val2");
      Turn_left_off2(100, 0);
      four_val = analogRead(four_pin);
      Serial.println(four_val);
      if (four_val < four_black)
      {
        break;
      }

      delay(50);
    }
  }
}

void Turning_left_180()
{
  four_val = analogRead(four_pin);
  bool two_hit_black = false;
  while (four_val > four_black)
  {
    Serial.println("four_val");
    Turn_left_off2(100, 100);
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
    Serial.println("three_val");
    Turn_left_off2(100, 100);
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
    Turn_left_off2(100, 100);
    four_val = analogRead(four_pin);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
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
    Turn_left_off(100, 100);
    three_val = analogRead(three_pin);
    one_val = analogRead(one_pin);
    two_val = analogRead(two_pin);
    Serial.println(three_val);
    if (two_val < two_exp)
    {
      two_hit_black = true;
      if(two_hit_black && two_val < two_exp && one_val < one_exp)
      {
        break;
      }
      continue;
    }

    delay(50);
  }

  /*four_val = analogRead(four_pin);
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
  
  unsigned long time = millis();
  while(millis() - time < 750)
  {
    Drive_fwd(100,100);
  }
  
  unsigned long time1 = millis();
  while(millis() - time1 < 300)
  {
    Turn_right_off2(100,100);
  }
  
  unsigned long time2 = millis();
  while(millis() - time2 < 250)
  {
    Turn_left_off2(100,100);
  }*/
  

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

void Turning_right_45()
{
  four_val = analogRead(four_pin);
  bool go = false;

  while (four_val > four_black)
  {
    Serial.println("four_val");
    Turn_right_off2(100, 100);
    four_val = analogRead(four_pin);
    three_val = analogRead(three_pin);
    if (three_val < three_black)
    {
      go = true;
    }

    Serial.println(four_val);
    if (four_val < four_black)
    {
      break;
    }

    delay(50);
  }

  if (go == true)
  {
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
      Turn_right_off(0, 100);
      four_val = analogRead(four_pin);
      Serial.println(four_val);
      if (four_val < four_black)
      {
        break;
      }

      delay(50);
    }
  }

  else
  {
    three_val = analogRead(three_pin);
    while (three_val > three_black)
    {
      Serial.println("three_val2");
      Turn_right_off2(0, 100);
      three_val = analogRead(three_pin);
      Serial.println(three_val);
      if (three_val < three_black)
      {
        break;
      }

      delay(50);
    }
  }


}

void Turning_right_180()
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
  Serial.println("Driving Backward");
  analogWrite(enable_1, rpwm);
  analogWrite(enable_2, lpwm);
  digitalWrite(left_pins[0], HIGH);
  digitalWrite(left_pins[1], LOW);
  digitalWrite(right_pins[0], HIGH);
  digitalWrite(right_pins[1], LOW);
}

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
/*
//increases everytime you go from white to black on the encoder
void enctest() {
  //found from gtest
  int white_v = 180; //typical white encoder value
  int black_v = 100; //typical black encoder value

  encod_val = analogRead(encod_pin);

  //if on white and change to black add 1 to j
  //if you change white_v a number in between white and black maybe you could add to j everytime colour switches
  if (abs(encod_val - white_v) > 40)
  {
    j++;
    //Serial.println(encod_val - white_v);
    //Serial.println("changed");
    //Serial.println(j);
  }
  Drive_fwd(100, 100);
  delay(350);
  //this delay value was calculated
  /*
    radius = 1.75 cm
    circumference = 2*pi*r = 11 cm
    8 wedges on encoder
    timed that it take 7.08 seconds to travel 28 cm at 100 pwm
    v = d/t = 28/7.08 = 3.955 cm/s
    t = d/v = 11/3.955 = 2.78 s for 1 wheel turn
    2.78/8 = 0.3475 s per wedge
  */
//}

//new line following method
void plinetest(int lines)
{
  int right_error[6] = {0,0,0,0,0,0};
  int left_error[6] = {0,0,0,0,0,0};
  int count = 0;
  int ipl_error = 0;
  int ipr_error = 0;
  while (count < lines)
  {
    one_val = analogRead(one_pin); //right
    two_val = analogRead(two_pin); //left
    //Serial.print(one_val);
    //Serial.print(" ");
    //Serial.println(two_val);

    int exp_val = (one_exp + two_exp) / 2; //this is a middle value found from gtest, both sensors are approx. 500 when the lacalite it facing straight

    //contasts that can be changed to increase the amount the robot tries to correct itself
    int kpr = 2; //make this higher usually because for some reason this side never turns enough
    int kpl = 2;
    int ipl = 1;
    int ipr = 1;
    int rpwm = 100;
    int lpwm = 100;

    //these error values get larger the darker the sensor get because they get farther and farther from the expected value
    //50 is just a number to scale down the errors so they can be added to the pwms
    int r_error = (one_exp - one_val) / 50;
    int l_error = (two_exp - two_val) / 50;
    right_error[0] = r_error;
    left_error[0] = l_error;
    for(int i = 5; i > 0; i -= 1)
    {
      right_error[i] = right_error[i-1];
      left_error[i] = left_error[i-1];
    }
    
    for(int i = 5; i > 0; i -= 1)
    {
      ipr_error += right_error[i];
      ipl_error += left_error[i];
    } 

    Serial.println("r_error || l_error");
    Serial.print(r_error);
    Serial.print(" ");
    Serial.println(l_error);

    //these are the corrected pwms
    int r_corr = rpwm + kpr * r_error + ipr_error*ipr;
    int l_corr = lpwm + kpl * l_error + ipl_error*ipl;
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
  Serial.println("out of while in line follow");
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

//method can be used to straighten the lacalite if it hits a perpendicular line at an angle
/*void straighten()
{
  three_val = analogRead(three_pin);
  four_val = analogRead(four_pin);
  //Serial.print(three_val);
  //Serial.print(" ");
  //Serial.println(four_val);

  while (three_val < 650 && four_val > 550) //if three is on black and four is on white (values from gtest)
  {
    //Serial.println("turn left");
    Drive_fwd(75, 0);
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    if (three_val < 650 && four_val < 550) //when both are black break
    {
      //Serial.println("stop turning");
      lc++;
      break;
    }
    delay(50);
  }
  while (three_val > 650 && four_val < 550) //if four in on black and three in on white (gtest)
  {
    //Serial.println("turn right");
    Drive_fwd(0, 75);
    three_val = analogRead(three_pin);
    four_val = analogRead(four_pin);
    if (three_val < 650 && four_val < 550) //when both are black break
    {
      //Serial.println("stop turning");
      lc++;
      break;
    }
    delay(50);
  }
  Drive_fwd(100, 100);
  delay(500);
}*/

/*bool receiver(char check)
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;
    // Message with a good checksum received, dump it.
    Serial.print("Got: '");

    for (i = 0; i < buflen; i++)
    {
      char c = (buf[i]);
      Serial.print(c);
      if (c == check)
      {
        return true;
      }
      else {
        return false;
      }
    }
  }

}*/

void pick_up(int angle)
{
  
  myServo.attach(9);
  if (angle == 120)
  {
    myServo.write(angle);
    return;
  }

  else if (angle == 10)
  {
    myServo.write(angle);
    return;
  }
}

void state_machine(int list[4][5])
{
  if(hop_or1 == list[0][0])
  {
     plinetest(list[0][1]); //orientation one with hopper on red line and leg closest to board perpendicular to board
     slowdown();
     Turning_right_45();
     Drive_fwd(100,100);
     delay(1500);
     Drive_bwd(100,100);
     delay(1500);
     Turning_right_180();
     five_to_black();
     plinetest(list[0][1]);
     slowdown();
  }
      
  else if(hop_or1 == list[1][0])
  {  
     Turning_right();
     five_to_black();
     plinetest(list[1][1]); //orientation two with hopper one space over from red line and leg closest to board perpendicular to board
     slowdown();
     Turning_left();
     five_to_black();
     plinetest(list[1][2]);
     slowdown();
     Turning_left_45();
     Drive_fwd(100,100);
     delay(1500);
     Drive_bwd(100,100);
     delay(1500);
     Turning_left_180();
     five_to_black();
     plinetest(list[1][2]);
     slowdown();
     Turning_right();
     five_to_black();
     plinetest(list[1][1]);
  }
       
  else if(hop_or1 == list[2][0])
  { 
     Turning_right();
     five_to_black();
     plinetest(list[2][1]); //orientation 3 with hopper flipped and one space over from red line
     slowdown();
     Turning_left();
     five_to_black();
     plinetest(list[2][2]);
     slowdown();
     Turning_left();
     five_to_black();
     plinetest(list[2][3]);
     slowdown();
     Turning_left_45();
     five_to_black();
     Drive_fwd(100,100);
     delay(1500);
     Drive_bwd(100,100);
     delay(1500);
     Turning_left_180();
     five_to_black();
     plinetest(list[2][3]);
     slowdown();
     Turning_right();
     five_to_black();
     plinetest(list[2][2]);
     slowdown;
     Turning_right();
     five_to_black();
     plinetest(list[2][1]);
     slowdown();
     Turning_left();
     five_to_black();
  }
       
  else if(hop_or1 == list[3][0])
  {
     Turning_right();
     five_to_black();
     plinetest(list[3][1]); //orientation 4 with hopper flipped and right at redline
     slowdown();
     Turning_left();
     five_to_black();
     plinetest(list[3][2]);
     slowdown();
     Turning_left();
     five_to_black();
     plinetest(list[3][3]);
     slowdown();
     Turning_left();
     five_to_black();
     plinetest(list[3][4]);
     slowdown();
     Turning_left_45();
     Drive_fwd(100,100);
     delay(1500);
     Drive_bwd(100,100);
     delay(1500);
     Turning_left_180();
     five_to_black();
     plinetest(list[3][4]);
     slowdown();
     Turning_right();
     five_to_black();
     plinetest(list[3][3]);
     slowdown();
     Turning_right();
     five_to_black();
     plinetest(list[3][2]);
     slowdown();
     Turning_right();
     five_to_black();
     plinetest(list[3][1]);
     slowdown();
     Turning_left();
     five_to_black();
           
  }
  
}
