const int led_pin = 10;

const int photo_pin = 0;

void setup()
{
 Serial.begin(9600); 
 pinMode(led_pin, OUTPUT);
}

void loop()
{
  Serial.println(analogRead(photo_pin));
  Serial.println('\n');
 
  int photo_val = analogRead(photo_pin);
  
  if(photo_val <= 600)
  {
     analogWrite(led_pin,analogRead(photo_pin)/2);
  }
  
  else
  {
    analogWrite(led_pin, 0);
  }
  delay(50);
}

//general value is 840-850
//white value is 700-710-720-730
//black value 500-520
//red value 590-620
