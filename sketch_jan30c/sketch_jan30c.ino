/* Using photo sensors to control direction and speed of D.C. motors

declare variables of left and right pins as arrays of 3 --> one pin for PWM, two pins for motor direction
declare constants for minimum and maximum PWM
declare constants for left and right sensor pins, analog pins as 0 and 1
declare variable sensor Threshold, this decides whether the robot will move or not

setup

  use a for loop to set all pinmodes to output
  
loop

  use analogRead() to read and store left and right sensor pins
  check if sensors have been calibrated, sensoThreshold == 0, calibrate sensors to something above ambient average
    check if there is enough light to move
      call setSpeed for right and left pins, get speed using map(val,0,1023,min_PWM,max_PWM)
      
setSpeed - takes pins and speed

  check if speed given is a negative number
    set pins[1], HIGH, pins[2], LOW
    speed = -speed
    
  else
    analogWrite(pins[0], speed
    
*/
