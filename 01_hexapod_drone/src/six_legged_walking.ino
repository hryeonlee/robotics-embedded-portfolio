#include <Wire.h> 
#include <Adafruit_PWMServoDriver.h>

// Initialize two PCA9685 boards
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40); // Default address
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  123  // Min pulse width out of 4096
#define SERVOMAX  492  // Max pulse width out of 4096
#define SERVO_FREQ 50  // Servo frequency (50Hz)

// Servo numbers for leg 1
#define LEG1_HIP_SERVO 0
#define LEG1_KNEE_SERVO 1
#define LEG1_ANKLE_SERVO 2

// Servo numbers for leg 2
#define LEG2_HIP_SERVO 3
#define LEG2_KNEE_SERVO 4
#define LEG2_ANKLE_SERVO 5

// Servo numbers for leg 3
#define LEG3_HIP_SERVO 6
#define LEG3_KNEE_SERVO 7
#define LEG3_ANKLE_SERVO 8

// Servo numbers for leg 4
#define LEG4_HIP_SERVO 9
#define LEG4_KNEE_SERVO 10
#define LEG4_ANKLE_SERVO 11

// Servo numbers for leg 5
#define LEG5_HIP_SERVO 12
#define LEG5_KNEE_SERVO 13
#define LEG5_ANKLE_SERVO 14

// Servo numbers for leg 6
#define LEG6_HIP_SERVO 0
#define LEG6_KNEE_SERVO 1  // This is on the second board (pwm2)
#define LEG6_ANKLE_SERVO 2 // This is also on the second board (pwm2)

// Define optimal hip angles for forward and backward movement for each leg
int forwardHipAngles[6] = {80, 40, 90, 130, 130, 150}; // Replace with actual forward angles for each leg
int backwardHipAngles[6] = {150, 90, 130, 90, 70, 120}; // Replace with actual backward angles for each leg

void setup() {
  Serial.begin(9600);
  Serial.println("Single Leg Test!");

  pwm1.begin();
  pwm1.setPWMFreq(SERVO_FREQ);
  pwm2.begin();
  pwm2.setPWMFreq(SERVO_FREQ);
}

// Function to control a specific servo on a specific board
void setServo(Adafruit_PWMServoDriver &driver, uint8_t servoNum, int angle) {
  int pulseWidth = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  driver.setPWM(servoNum, 0, pulseWidth);
}

// Function to move a single leg
void moveLeg(int leg, int hipAngle, int kneeAngle, int ankleAngle) {
  switch (leg) {
    case 1:
      setServo(pwm1, LEG1_HIP_SERVO, hipAngle);
      setServo(pwm1, LEG1_KNEE_SERVO, kneeAngle);
      setServo(pwm1, LEG1_ANKLE_SERVO, ankleAngle);
      break;
    case 2:
      setServo(pwm1, LEG2_HIP_SERVO, hipAngle);
      setServo(pwm1, LEG2_KNEE_SERVO, kneeAngle);
      setServo(pwm1, LEG2_ANKLE_SERVO, ankleAngle);
      break;
    case 3:
      setServo(pwm1, LEG3_HIP_SERVO, hipAngle);
      setServo(pwm1, LEG3_KNEE_SERVO, kneeAngle);
      setServo(pwm1, LEG3_ANKLE_SERVO, ankleAngle);
      break;
    case 4:
      setServo(pwm1, LEG4_HIP_SERVO, hipAngle);
      setServo(pwm1, LEG4_KNEE_SERVO, kneeAngle);
      setServo(pwm1, LEG4_ANKLE_SERVO, ankleAngle);
      break;
    case 5:
      setServo(pwm1, LEG5_HIP_SERVO, hipAngle);
      setServo(pwm1, LEG5_KNEE_SERVO, kneeAngle);
      setServo(pwm1, LEG5_ANKLE_SERVO, ankleAngle);
      break;
    case 6:
      setServo(pwm2, LEG6_HIP_SERVO, hipAngle);
      setServo(pwm2, LEG6_KNEE_SERVO, kneeAngle);
      setServo(pwm2, LEG6_ANKLE_SERVO, ankleAngle);
      break;
  }
}

// Define the new groups of legs
int groupA[3] = {1, 3, 5}; // Legs 1, 3, 5
int groupB[3] = {2, 4, 6}; // Legs 2, 4, 6

// Function to move a group of legs
void moveGroupWithCustomHips(int *group, int *hipAngles, int kneeAngle, int ankleAngle) {
  for (int i = 0; i < 3; i++) {
    int leg = group[i] - 1; // Adjust for array indexing
    moveLeg(group[i], hipAngles[leg], kneeAngle, ankleAngle);
  }
}

void loop() {
  // Phase 1: Spread Group A legs forward, Group B supports
  moveGroupWithCustomHips(groupA, forwardHipAngles, 135, 135);
  moveGroupWithCustomHips(groupB, backwardHipAngles, 20, 20);
  delay(1000); // Adjust timing as needed

  // Phase 2: Lift Group A legs, move HIP_SERVO to backward position
  moveGroupWithCustomHips(groupA, backwardHipAngles, 135, 135);
  delay(500); // Short delay for lifting the legs

  // Phase 3: Lower Group A legs
  moveGroupWithCustomHips(groupA, backwardHipAngles, 20, 20);
  delay(500); // Short delay for lowering the legs

  // Phase 4: Spread Group B legs forward, Group A supports
  moveGroupWithCustomHips(groupB, forwardHipAngles, 135, 135);
  moveGroupWithCustomHips(groupA, backwardHipAngles, 20, 20);
  delay(1000); // Adjust timing as needed

  // Phase 5: Lift Group B legs, move HIP_SERVO to backward position
  moveGroupWithCustomHips(groupB, backwardHipAngles, 135, 135);
  delay(500); // Short delay for lifting the legs

  // Phase 6: Lower Group B legs
  moveGroupWithCustomHips(groupB, backwardHipAngles, 20, 20);
  delay(500); // Short delay for lowering the legs
}