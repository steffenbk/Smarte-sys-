#include <Servo.h>

Servo servo;
Servo servo2;
Servo servo3;
const int buttonPin = 2;
const int volt = 5;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  servo.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo.write(0);
  servo2.write(0);
  servo3.write(0);
  delay(2000);
  pinMode(buttonPin, INPUT);
  pinMode(volt, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  digitalWrite(volt, HIGH);
  
  if(buttonState == LOW) {
    servo.write(90);
    servo2.write(90);
    servo3.write(90);
    
  } else {
    servo.write(0);
    servo2.write(0);
    servo3.write(0);
  }
  
  
}
