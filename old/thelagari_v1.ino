#include"Motor.h"

MOTOR motor(8,10,11,9,18,19,1);

void setup() 
  {
  motor.begin(); // Start motor
  motor.setConstrain(255);  // Setting up limit of mototr speed or, speed constrain
  }

void loop() 
  {
  motor.forwardA(255); // Motor A forward at full speed
  motor.forwardB(128); // Motor B forward at half speed
  delay(2000);         // Run for 2 seconds
  motor.softBrakeA();  // Soft brake motor A
  motor.softBrakeB();  // Soft brake motor B
  delay(2000);         // Wait for 2 seconds
  motor.reverseA(255);
  motor.reverseB(128); // Motor B reverse at half speed
  delay(2000);         // Wait for 2 seconds
  motor.hardBrakeA();
  motor.hardBrakeB();  // Hard brake motor B
  delay(2000);         // Run for 2 seconds
  
  }

