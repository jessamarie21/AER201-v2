const int rec_pin = A5;
const int led_pin = 11;

unsigned int rec_data = 0;
const unsigned int upper_limit = 370;
const unsigned int lower_limit = 370;

void setup()
{
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
}

void loop()
{
  rec_data = analogRead(rec_pin);
  Serial.println(rec_data);
  Serial.println('\n');
  
  if(rec_data > upper_limit)
  {
    digitalWrite(led_pin,HIGH);
  }
  
  delay(1000);
  
  if(rec_data < lower_limit)
  {
    digitalWrite(led_pin,LOW);
  }
}
