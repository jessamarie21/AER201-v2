/*Tracking Rotary Movement
Using a Rotary Encoder


set encoder pins as constants to poll
connect encoder pins 1 and 2 to two I/O pins on arduino
set number of steps per revolution for encoder, i.e. 16
declare initial angle 

declare initial encoder position

save previous state of encoder pin one as boolean

setup
  set pinmode of encoder pins as INPUT
  digitalWrite to both pins as HIGH
  
loop
  convert the value of encoder pin one into a boolean variable
  
  if the last pin state and the current pin state are different for encoder pin one 
    if pin 2 state is LOW
      decrease encoder position by one
      
    else
      increase encoder position by one
      
    angle is equal to a function converting the encoder position using the number of steps per revolution
  
  save previous state of encoder pin one
*/
