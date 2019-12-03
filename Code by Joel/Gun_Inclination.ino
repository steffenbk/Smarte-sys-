// Gun Elevation Code
// Author: Joel Soto Escoda
// Autum 2019
// The following code is used in the angle setting for the gun platform. With the code we can control with one joystick the 
// motor turn and speed to set the shotting angle.

// Include stepper motor library
#include <Stepper.h>
 
// Define number of steps per revolution
#define STEPS 32
 
// Define stepper motor control pins
#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
 
// Initialize stepper library
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
 
// Joystick pot output is connected to Arduino A0
#define joystick  A0
 
void setup()
{ 
}
 
void loop()
{
  // Read analog value from the potentiometer
  int val = analogRead(joystick);
 
  // If the joystic is in the middle stop the motor
  if(  (val > 500) && (val < 523) )
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
 
  else
  {
    // Move the motor in the first direction
    while (val >= 523)
    {
      // Map the speed between 5 and 500 rpm
      int speed_ = map(val, 523, 1023, 5, 500);
      // Set motor speed
      stepper.setSpeed(speed_);
 
      // Move the motor (1 step)
      stepper.step(1);
 
      val = analogRead(joystick);
    }
 
    // Move the motor in the other direction
    while (val <= 500)
    {
      // Map the speed between 5 and 500 rpm
      int speed_ = map(val, 500, 0, 5, 500);
      // Set motor speed
      stepper.setSpeed(speed_);
 
      // Move the motor (1 step)
      stepper.step(-1);
 
      val = analogRead(joystick);
    }
   }
 }
