const int led_pin = 10;
const int led_pin_green = 9;
const int photo_pin = 0;
const int photo_pin_2 = 1;
void setup()
{
 Serial.begin(9600); 
 pinMode(led_pin, OUTPUT);
 pinMode(led_pin_green, OUTPUT);
  
}

void loop()
{
  Serial.println(analogRead(photo_pin));
  Serial.println('\n');
  Serial.println(analogRead(photo_pin_2));
 
  int photo_val = analogRead(photo_pin);
  int photo_val2 = analogRead(photo_pin_2);
  if(photo_val <= 600)
  {
     analogWrite(led_pin,analogRead(photo_pin)/2);
  }
  
  else if(photo_val2 <= 600)
  {
    analogWrite(led_pin_green,analogRead(photo_pin_2)/2);
  }
  else
  {
    analogWrite(led_pin, 0);
    analogWrite(led_pin_green,0);
  }
  delay(50);
}

//general value is 840-850
//white value is 700-710-720-730
//black value 500-520
//red value 590-620
