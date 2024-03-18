#include <AFMotor.h>
#include <ezButton.h>

#define DIRECTION_CCW -1
#define DIRECTION_CW 1

AF_DCMotor motor(1, MOTOR12_64KHZ);
ezButton limitSwitchExtend(A4);  
ezButton limitSwitchRetract(A5);  

int direction = DIRECTION_CW;
int prev_direction = DIRECTION_CW;

void setup() {
  Serial.begin(9600);
  motor.setSpeed(155); // max speed=255

  limitSwitchExtend.setDebounceTime(100);  
  limitSwitchRetract.setDebounceTime(100);  

  delay(30000); // wait 30 sec after plugin to begin moving, in milliseconds
  motor.run(BACKWARD);
}

void loop() {
  limitSwitchExtend.loop();  
  limitSwitchRetract.loop();  

  if (limitSwitchExtend.isPressed()) {
    direction *= -1;  // change direction
    Serial.println(F("The limit switch 1: TOUCHED"));
    Serial.println(F("Flag fully extended."));
  }

  if (limitSwitchRetract.isPressed()) {
    direction *= -1;  // change direction
    Serial.println(F("The limit switch 2: TOUCHED"));
    Serial.println(F("Flag fully retracted."));
  }

  if (prev_direction != direction) {
    Serial.print(F("The direction -> "));
    if (direction == DIRECTION_CW) {
      Serial.println(F("CLOCKWISE"));
      motor.run(RELEASE);
      delay(30000); // wait 30 seconds between each direction change, in milliseconds
      motor.run(BACKWARD);
    } else {
      Serial.println(F("ANTI-CLOCKWISE"));
      motor.run(RELEASE);
      delay(30000); // wait 30 sec between each direction change, in milliseconds
      motor.run(FORWARD);  
    }

    prev_direction = direction;
  }
}
