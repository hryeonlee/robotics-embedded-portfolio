#include <Wire.h> 
#include <Adafruit_PWMServoDriver.h>

// Initialize the PCA9685 using the default address
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  123  // Min pulse width out of 4096
#define SERVOMAX  492  // Max pulse width out of 4096
#define SERVO_FREQ 50  // Servo frequency (50Hz)

// Servo numbers for one leg
#define HIP_SERVO 0
#define KNEE_SERVO 1
#define ANKLE_SERVO 2

// Pressure sensor pin
const int pressureSensorPin = A0; 

void setup() {
  Serial.begin(9600);
  Serial.println("Single Leg Test!");

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  

  pinMode(pressureSensorPin, INPUT);  // Set the sensor pin as input
  delay(10);
}

void loop() {
  // 처음에는 다리를 최대한 구부립니다
  moveJoint(HIP_SERVO, 150);  // Move HIP_SERVO to the middle position
  moveJoint(KNEE_SERVO, 0);
  moveJoint(ANKLE_SERVO, 0);
  delay(1000);

  // 압력 센서가 3개 이상 측정될 때까지 무릎과 발목을 천천히 펴십시오
  for (int angle = 0; angle <= 135; angle++) {
    moveJoint(KNEE_SERVO, angle);
    moveJoint(ANKLE_SERVO, angle);
    delay(100);  // 동작을 느리게 합니다

    int sensorValue = analogRead(pressureSensorPin);
    float pressure = sensorValue * (5.0 / 1023.0);  // 압력값으로 변환
    Serial.print("Pressure: ");
    Serial.println(pressure);

    if (pressure >= 3) {
      Serial.println("Pressure threshold reached, stopping.");
     break;  // Break out of the loop, stopping further movements
    }
  }

  // 선택사항: 서보를 중지한 후 필요한 경우 여기에 추가 코드를 추가합니다

  while (1) {
    // 이 무한 루프를 사용하면 루프 기능이 다시 실행되지 않습니다
    // 따라서 서보를 마지막 위치에 유지하는 것은
    delay(1000);  // 사용 중인 루프를 피하기 위해 지연되는 것뿐입니다
  }
}

void moveJoint(uint8_t servoNum, uint8_t angle) {
  uint16_t pulseLen = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(servoNum, 0, pulseLen);
}