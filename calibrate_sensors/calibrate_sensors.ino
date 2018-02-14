const int one_pin = A1;
const int two_pin = A4;
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



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    
    one_val = analogRead(one_pin);
    Serial.println("ONE TWO THREE FOUR FIVE ENCODE");
    
    Serial.print(one_val);
    Serial.print("  ");

    two_val = analogRead(two_pin);
    Serial.print(two_val);
    Serial.print("  ");

    three_val = analogRead(three_pin);
    
    Serial.print(three_val);
    Serial.print("  ");


    four_val = analogRead(four_pin);
   
    Serial.print(four_val);
    Serial.print("  ");

  
    five_val = analogRead(five_pin);
    
    Serial.print(five_val);
    Serial.print("  ");

  
    encod_val = analogRead(encod_pin);
    
    Serial.println(encod_val);
    
    delay(1000);
    

}
