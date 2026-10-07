#include <Herkulex.h>

// Define the motor ID
#define MOTOR_ID 3

void setup() {
  // Initialize the hardware serial port for debugging
  Serial.begin(115200);
  // Initialize the Herkulex library with the hardware serial port
  Herkulex.beginSerial1(115200);

  // Initialize the Herkulex motor
  Herkulex.initialize();

  // Clear any previous errors
  Herkulex.clearError(MOTOR_ID);

  // Turn on the torque to enable the motor
  Herkulex.torqueON(MOTOR_ID);

  // Set the LED color to green to indicate the motor is ready
  Herkulex.setLed(MOTOR_ID, LED_GREEN);

  // Move the motor at a constant speed indefinitely
  int speed = 1000; // 모터 속도 세팅; adjust as needed
  int pTime = 0; // 실행시간(연속회전의 경우 0)
  int iLed = LED_GREEN; // 작동 중 LED 색상

  // Send the move command
  Herkulex.moveSpeedOne(MOTOR_ID, speed, pTime, iLed);

  // Check for errors
  delay(1000); // Wait for a moment to let the command execute
  int errorStatus = Herkulex.stat(MOTOR_ID);
  if (errorStatus != H_STATUS_OK) {
    Serial.print("Error: ");
    Serial.println(errorStatus, HEX);
    Herkulex.clearError(MOTOR_ID); // Clear error if any
  }
}

void loop() {
  // Nothing to do here, the motor will keep rotating indefinitely
}
