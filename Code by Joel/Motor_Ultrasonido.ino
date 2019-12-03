// ULtrasonic part
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

// Motor part
// Motor A pin control
#define enA 2 // Control of the velocity
#define in1 50 // Control of the direction
#define in2 51 // Control of the direction

// Motor B pin control
#define enB 3 // Control of the velocity
#define in3 52 // Control of the direction
#define in4 53 // Control of the direction

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  // Motor pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Sensors pins
  // Front Sensor
  pinMode(trigPinFront, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinFront, INPUT); // Sets the echoPin as an Input
  // Left Sensor
  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
  // Right Sensor
  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an Input
  
  // Be careful because in the comander we are not going to need....
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  
  // Front Sensor
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
  distanceFront = durationFront*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceFront: ");
  Serial.println(distanceFront);
  
  // Left Sensor
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
  distanceLeft = durationLeft*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceLeft: ");
  Serial.println(distanceLeft);
  
  // Right Sensor
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
  distanceRight = durationRight*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceRight: ");
  Serial.println(distanceRight);

  if (distanceFront < 10) { // We need to know that we don't have sensor in the lab...
    // Stop the motors
    // Set Motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // Set Motor B
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
    delay(2000);
    
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Fix the speed (slow)
    motorSpeedA = 125;
    motorSpeedB = 125;

    delay(2000);
  }
  
  else if (distanceRight < 10) {
    // Stop the motors
    // Set Motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // Set Motor B
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
    delay(2000);
    
    // Motor moves RIGHT?
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // We need to fix a speed (slow)
    motorSpeedA = 125;
    motorSpeedB = 125; 

    delay(2000);
  }

  else if (distanceLeft < 10) {
    // Stop the motors
    // Set Motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // Set Motor B
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
    delay(2000);
    
    // Motor moves LEFT?
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
    // We need to fix a speed (slow)
    motorSpeedA = 125;
    motorSpeedB = 125;

    delay(2000);
  }

  else {
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // Fix the speed (Medium-fast)
  motorSpeedA = 200;
  motorSpeedB = 200;
  }
  
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  // Send the PWN signal to the motor
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
 }
