#include <NewPing.h>

// Motor Control Pins
const int MOTOR_A1 = 5;
const int MOTOR_A2 = 10;
const int MOTOR_B1 = 6;
const int MOTOR_B2 = 9;

// HC-SR04 Pins for front and right sensors
const int TRIGGER_PIN_FRONT = 7;
const int ECHO_PIN_FRONT = 4;
const int TRIGGER_PIN_RIGHT = 11;
const int ECHO_PIN_RIGHT = 12;
const int MAX_DISTANCE = 200;

NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE);
NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);

void setup() {
  // Set motor control pins as output
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);

  Serial.begin(9600);
}

// distance sensors to navigate the robot around.
void loop() {   
  int frontDistance = getDistance(sonarFront);
  if (frontDistance < 15) {
    int rightDistance = getDistance(sonarRight);
   
    //Right turn distance 
    if (rightDistance > 18) {
      goRight(200);
      delay(400); 
    // left turn 
    } else if (rightDistance < 17) {
      goLeft(240);
      delay(400); 
    
    // Comparison of distances to turn
    } else {
      int leftDistance = getDistance(sonarRight);
      if (rightDistance > leftDistance) {
        goRight(350);
        delay(400);
      } else {
        goLeft(200);
        delay(400);  
      }
    }    
  } else {
    goForward(150);
  }
}

int getDistance(NewPing &sonar) {
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void goBack(int speed) {
  analogWrite(MOTOR_A1, speed);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, speed);
  analogWrite(MOTOR_B2, 0);
}

void goForward(int speed) {
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, speed);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, speed);
}

void goRight(int speed) {
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, speed);
  analogWrite(MOTOR_B1, speed);
  analogWrite(MOTOR_B2, 0);
}

void goLeft(int speed) {
  analogWrite(MOTOR_A1, speed);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, speed);
}

void stop() {
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, 0);
}
