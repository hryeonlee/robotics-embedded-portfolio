/*
  Portfolio-reviewed version of the 2024 tail_movement_1 sketch.

  Original project intent:
  - Control two Herkulex DRS-0101 servos in one 2-link tail.
  - Move between two configured poses with different move times.

  Post-project cleanup:
  - Fixed the original MOTOR_ID_ typo.
  - Removed an unused angle-to-position conversion.
  - Clarified comments.

  IMPORTANT:
  This reviewed version was not revalidated on the original hardware after
  the project. It is included to show the control structure more clearly.
*/

#include <Herkulex.h>

#define MOTOR_ID_3 3
#define MOTOR_ID_4 4

#define ANGLE_3_A 150
#define ANGLE_3_B -50
#define ANGLE_4_A -150
#define ANGLE_4_B -60

void setMotorAngle(int motorID, int angle, int moveTime) {
  Herkulex.moveOneAngle(motorID, angle, moveTime, LED_BLUE);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  Herkulex.beginSerial1(115200);
  Herkulex.initialize();

  Herkulex.clearError(MOTOR_ID_3);
  Herkulex.clearError(MOTOR_ID_4);
  Herkulex.torqueON(MOTOR_ID_3);
  Herkulex.torqueON(MOTOR_ID_4);
}

void loop() {
  setMotorAngle(MOTOR_ID_3, ANGLE_3_A, 300);
  setMotorAngle(MOTOR_ID_4, ANGLE_4_A, 500);
  delay(500);

  setMotorAngle(MOTOR_ID_3, ANGLE_3_B, 300);
  setMotorAngle(MOTOR_ID_4, ANGLE_4_B, 500);
  delay(500);
}
