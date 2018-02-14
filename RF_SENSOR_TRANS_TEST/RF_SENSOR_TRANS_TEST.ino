const int rf_trans = A0;

const int led_pin = 9;

void setup()
{
  Serial.begin(9600)
  pinMode(rf_trans,OUTPUT);
  pinMode(led_pin,OUTPUT);
}

void loop()
{
  for(int i = 4000; i > 5; i - (i/3))
  {
    digitalWrite(led_pin,HIGH);
    analogWrite(rf_trans,0);
    
    if(digitalRead(led_pin)==HIGH)
    {
      analogWrite(rf_trans, 390);
      
    }
    
    delay(2000);
    
    if(analogRead(rf_trans)==390)
    {
      Serial.println(analogRead(rf_trans));
      digitalWrite(led_pin, LOW);
    }
      

    delay(i);
  }
}
