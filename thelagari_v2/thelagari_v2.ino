#include <Arduino.h>

#define NUM_IR 15
#define THRESHOLD 500
#define BASE_SPEED 150        
#define MAX_SPEED 255         

int motorPins[7] = {
  4,  // A1
  2,  // A2
  15, // PWMA
  18, // B1
  19, // B2
  21, // PWMB
  5   // STBY
};

int IR[NUM_IR] = {};

//------------------------------------------------------FUNCTIONS-----------------------------------------------------------------------

//speed_constrainer
int speed(int input) {
  return constrain(input, 0, 255); // Constrain the speed to a range of 0 to 255                     
}


//motor functions
void beginMotor(int motorPins[]) {
  digitalWrite(motorPins[6], HIGH); // STBY on
}

void idleMotor(int motorPins[]) {
  digitalWrite(motorPins[6], LOW); // STBY off
}

// ---- Motor A ----

void forwardA(int s)
{
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  analogWrite(motorPins[2], speed(s));
}

void reverseA(int s)
{
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  analogWrite(motorPins[2], speed(s));
}

void softBrakeA()
{
  analogWrite(motorPins[2], 0);
}

void hardBrakeA()
{
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], LOW);
  analogWrite(motorPins[2], 0);
}
// ---- Motor B ----
void forwardB(int s)
{
  digitalWrite(motorPins[3], LOW);
  digitalWrite(motorPins[4], HIGH);
  analogWrite(motorPins[5], speed(s));
}

void reverseB(int s)
{
  digitalWrite(motorPins[3], HIGH);
  digitalWrite(motorPins[4], LOW);
  analogWrite(motorPins[5], speed(s));
}

void softBrakeB()
{
  analogWrite(motorPins[5], 0);
}

void hardBrakeB()
{
  digitalWrite(motorPins[3], LOW);
  digitalWrite(motorPins[4], LOW);
  analogWrite(motorPins[5], 0);
}



//----------Both---------------------
void stop()
{
  hardBrakeA();
  hardBrakeB();
}

void FORWARD(int speed)
{
  forwardA(speed);
  forwardB(speed);
}
void REVERSE(int speed)
{
  reverseA(speed);
  reverseB(speed);
}


//******************************************PID Control Functions******************************************//

// Placeholder for PID control functions
float kp = 1.0; // Proportional gain
float ki = 0.0; // Integral gain
float kd = 0.0; // Derivative gain
float previousError = 0.0;
float integral = 0.0;
float pidControl(float setpoint, float measuredValue) {
  float error = setpoint - measuredValue;
  integral += error;
  float derivative = error - previousError;
  previousError = error;

  // PID output calculation
  return kp * error + ki * integral + kd * derivative;
}

//------------------------------------------------------Setup and loop functions------------------------------------------------------------------------

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(motorPins[i], OUTPUT); // Set motor pins as output
  }
  
  for (int i = 0; i < 15; i++) {
    pinMode(IR[i], INPUT); // Set IR pins as input
  }
  
  beginMotor(motorPins);
}



void loop() {
  // Example usage of motor functions
  FORWARD(200); // Move forward at speed 200
  delay(2000); // Wait for 2 seconds
  REVERSE(200); // Move backward at speed 200
  delay(2000); // Wait for 2 seconds
  stop(); // Stop the motors
  delay(1000); // Wait for 1 second before repeating



}