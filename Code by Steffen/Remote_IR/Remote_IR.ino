#include <IRremote.h> //include the library
/// stepper motor
#include <Stepper.h>

#define CHminus   0xFFA25D
#define CH  0xFF629D
#define CHplus   0xFFE21D
#define FastFL  0xFF22DD
#define FastFR  0xFF02FD
#define PlayPause   0xFFC23D
#define Minus   0xFFE01F
#define Plus   0xFFA857
#define EQ  0xFF906F
#define Button_100+  0xFF9867
#define Button_200+  0xFFB04F
#define Button_0   0XFF6897
#define Button_1   0xFF30CF
#define Button_2   0xFF18E7
#define Button_3   0xFF7A85
#define Button_4   0xFF10EF
#define Button_5   0xFF38C7
#define Button_6   0xFF5AA5
#define Button_7   0xFF42BD
#define Button_8   0xFF4AB5
#define Button_9   0xFF52AD
#include <IRremote.h>

const int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;



// Define number of steps per revolution
#define STEPS 32
int steps2take;

// Define stepper motor control pins
#define I1  46
#define I2  47
#define I3  48
#define I4  49

////////////


// sensor line defines

#define LS 12 // left sensor
#define RS 13 // right sensor

//////////////////////////////////////// From Motor Main


/// relay control


#define relay 11
#define interval 1000



////relay  end

// Defines pins numbers
// Front Ultrasoic Sensor
const int trigPinFront = 4;
const int echoPinFront = 5;
// Left Ultrasonic Sensor
const int trigPinLeft = 6;
const int echoPinLeft = 7;
// Right Ultrasonic Sensor
const int trigPinRight = 8;
const int echoPinRight = 9;
// Defines variables
long durationFront;
long durationLeft;
long durationRight;
int distanceFront;
int distanceLeft;
int distanceRight;


int pathdistanceRight;

int pathdistanceLeftt;




// Motor A pin control
#define enA 2 // Control of the velocity
#define in1 50 // Control of the direction
#define in2 51 // Control of the direction

// Motor B pin control
#define enB 3 // Control of the velocity
#define in3 52 // Control of the direction
#define in4 53 // Control of the direction



//int motorSpeedA = 0;
//int motorSpeedB = 0;


// Initialize stepper library
Stepper stepper(STEPS, I4, I2, I3, I1);



//////////////////////////////////////// From ps2 main End
void setup() {

  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  // Sensor line
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);

  // Motor line
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // pinMode(enA, OUTPUT);
  // pinMode(enB, OUTPUT);

  // Relay line
  pinMode(relay, OUTPUT);

  // Ultrasonic Sensors
  // Front Sensor
  pinMode(trigPinFront, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinFront, INPUT); // Sets the echoPin as an Input
  // Left Sensor
  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
  // Right Sensor
  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an Input


}
void loop() {

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }

  if ( results.value == 0xFF629D) {
    Forward();
  }

  if ( results.value == 0xFF02FD) {
    Stop();
  }

  if ( results.value == 0xFFA857) {
    Backward();
  }

  if ( results.value == 0xFFB04F) {
    turnRight();
  }

  if ( results.value == 0XFF6897) {
    turnLeft();
  }

  if ( results.value == 0xFF22DD) {
    BreakLeft();
  }

  if ( results.value == 0xFFC23D) {
    BreakRight();
  }


  if ( results.value == 0xFFE01F) {
    ReverseLeft();
  }

  if ( results.value == 0xFF906F) {
    ReverseRight();
  }

  if ( results.value == 0xFFA25D) {
    LeftForward();
  }

  if ( results.value == 0xFFE21D) {
    RightForward();
  }


  if ( results.value == 0xFF18E7) {
    fire();
  }

  if ( results.value == 0xFF30CF) {
    platformup();
  }

  if ( results.value == 0xFF7A85) {
    platformdown();
  }





}


// Motor move functions
// Motor moves FORWARD
void Forward() {
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
// Motor moves BACK
void Backward() {
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
// Motors STOP
void Stop() {
  // Set Motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // Set Motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

// Motor moves RIGHT
void turnRight() {
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
// Motor moves LEFT
void turnLeft() {
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}



void BreakLeft() {
  // Set Motor A Stop
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}


void BreakRight() {
  // Set Motor B Stop
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}




void ReverseLeft() {
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //stop motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void ReverseRight() {
  // Stop motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //Move motor B back
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}




void LeftForward() {
  // Set Motor A Stop
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void RightForward() {

  // Set Motor B Stop

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}


void sensorline() {

  if (digitalRead(LS) && digitalRead(RS)) // Move Forward on line
  {
    Forward();
  }
  if (digitalRead(LS) && !(digitalRead(RS))) // turn RIGHT by rotationg left motors in forward and right ones in backward direction
  {
    turnRight();
  }
  if (!(digitalRead(LS)) && digitalRead(RS)) // Turn LEFT by rotating right motors in forward and left ones in backward direction
  {
    turnLeft();
  }

  if (!(digitalRead(LS)) && !(digitalRead(RS))) // Finish line, stop both the motors
  {
    Stop();
  }


}


void fire() {

  digitalWrite(relay, LOW);
  delay(100);
  digitalWrite(relay, HIGH);
  delay(5000);
}



void platformdown() {
  stepper.setSpeed(500);
  steps2take = 300;
  stepper.step(steps2take);
  delay(1000);


}

void platformup() {

  stepper.setSpeed(500);
  steps2take = -300;
  stepper.step(steps2take);
  delay(1000);


}

void autodrive() {

  // Calling the sensors functions
  Front_Sensor();
  Left_Sensor();
  Right_Sensor();
  /*
    // Setting the speed
    motorSpeedA = 50;
    motorSpeedB = 50;
  */

  if (distanceFront < 15) { // We need to know that we don't have sensor in the lab...
    Stop();
    delay(2000);
    Backward();
    delay(500);
    Stop();
    delay(1000);
  }

  else if (distanceRight < 15) {
    Stop();
    delay(2000);
    Backward();
    delay(750);
    Stop();
    delay(1000);
    turnLeft();
    delay(500);
    Stop();
    delay(1000);
  }

  else if (distanceRight < 30) {
    Stop();
    delay(2000);
    turnLeft();
    delay(00);
    Stop();
    delay(1000);
  }

  else if (distanceLeft < 15) {
    Stop();
    delay(2000);
    Backward();
    delay(750);
    Stop();
    delay(1000);
    turnRight();
    delay(500);
    Stop();
    delay(1000);
  }

  else if (distanceRight < 30) {
    Stop();
    delay(2000);
    turnRight();
    delay(500);
    Stop();
    delay(1000);
  }

  else {
    Forward();
  }

  /*
    // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
    if (motorSpeedA < 40) {
    motorSpeedA = 0;
    }
    if (motorSpeedB < 40) {
    motorSpeedB = 0;
    }
    // Send the PWN signal to the motor
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  */

}

// Front Sensor
void Front_Sensor() {
  // Clears the trigPin
  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationFront = pulseIn(echoPinFront, HIGH);
  // Calculating the distance
  distanceFront = durationFront * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceFront: ");
  Serial.println(distanceFront);
}


// Left Sensor
void Left_Sensor() {
  // Clears the trigPin
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationLeft = pulseIn(echoPinLeft, HIGH);
  // Calculating the distance
  distanceLeft = durationLeft * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceLeft: ");
  Serial.println(distanceLeft);
}

// Right Sensor
void Right_Sensor() {
  // Clears the trigPin
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationRight = pulseIn(echoPinRight, HIGH);
  // Calculating the distance
  distanceRight = durationRight * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceRight: ");
  Serial.println(distanceRight);
}

/////////////////////////////Functions end
