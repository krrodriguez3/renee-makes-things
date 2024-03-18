// UNTESTED CODE 

// colloration with local artist

#include <AFMotor.h> // L293D motor driver shield library

const int stepsPerRevolution = 400; // number of steps per revolution
const int targetHeight = 600; // target height in steps (adjust as needed)
const int maxExtendSteps = 400; // maximum steps to extend (adjust as needed)

AF_Stepper motor(stepsPerRevolution, 2); // motor on shield port #2

int totalStepsMoved = 0; // variable to keep track of total steps moved

void setup() {
  Serial.begin(9600); // sets data communication rate
  motor.setSpeed(20); // adjust speed (rpm) as needed

  // Move the motor to the starting position
  motor.step(50, FORWARD, SINGLE);
  delay(100);
  motor.step(50, BACKWARD, SINGLE);
  delay(1500); // end setup check
}

void loop() {
  // Generate a random step count within a reasonable range
  int spin = random(400, 800);

  // Check if the total steps moved would exceed the maximum extend limit
  if (totalStepsMoved + spin > maxExtendSteps) {
    // If exceeded, retract only up to the maximum limit
    int retractSteps = maxExtendSteps - totalStepsMoved;
    motor.step(retractSteps, BACKWARD, SINGLE);
    delay(100);

    // Reset the total steps moved
    totalStepsMoved = maxExtendSteps;
  } else {
    // Move the motor to a random height
    motor.step(spin, FORWARD, SINGLE);
    delay(100);

    // Add the steps to the total
    totalStepsMoved += spin;
  }

  // Lower the flag to the target height
  motor.step(targetHeight, BACKWARD, SINGLE);
  delay(100);
}
