#include <AFMotor.h> // L293D motor driver shield library
int spin = 0; // spin; arbitrary
const int stepsPerRevolution = 400; // number of steps per revolution
AF_Stepper motor(stepsPerRevolution, 2); // motor on shield port #2

void setup() {
  Serial.begin(9600); // sets data communication rate
  motor.setSpeed(50); // 50 rpm

  motor.step(50, FORWARD, SINGLE); // turn 50 steps 
  delay(50);
  motor.step(50, BACKWARD, SINGLE); // turn 50 steps 
  delay(1500); //  end setup check
}

void loop() {
  spin = random(50, 400); // define random step count within range
  motor.step(spin, FORWARD, SINGLE); // turn 50 steps 
  delay(50); // 50 milliseconds between each spin
  spin = random(50, 400); // redefine new random step count
  motor.step(spin, BACKWARD, SINGLE); // turn 50 steps 
  delay(50); // 50 milliseconds between next loop
}
