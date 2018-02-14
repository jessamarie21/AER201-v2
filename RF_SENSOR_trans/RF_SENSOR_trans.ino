/*#include <VirtualWire.h>

const int receiver_pin = 8;
const int trans_pin = 12;
const int led_pin = 7;

void setup()
{
  vw_set_tx_pin(trans_pin);
  vw_set_rx_pin(receiver_pin);
  pinMode(led_pin, OUTPUT);
  vw_setup(2000);
  
}

void loop()
{
  char mess[1] = {'j');
  digitalWrite(led_pin,HIGH);
  vw_send(mess,1);
  vw_wait_tx();
  
  if(vw_tx_active() == true)
  {
    digitalWrite(led_pin,LOW);
  }
  
  delay(1000);
  
  digitalWrite(led_pin,HIGH);
  vw_rx_start();
  vw_wait_rx();
  
  if(vw_have_message() == true)
  {
    digitalWrite(led_pin,LOW);
  }
  
  
}*/

const int rf_trans = 4;

const int led_pin = 9;

void setup()
{
  pinMode(rf_trans,OUTPUT);
  pinMode(led_pin,OUTPUT);
}

void loop()
{
  for(int i = 4000; i > 5; i - (i/3))
  {
    digitalWrite(led_pin,HIGH);
    digitalWrite(rf_trans,LOW);
    
    if(digitalRead(led_pin)==true)
    {
      digitalWrite(rf_trans, HIGH);
      
    }
    
    delay(2000);
    
    if(digitalRead(rf_trans)==true)
    {
      digitalWrite(led_pin, LOW);
    }
      

    delay(i);
  }
}


  
