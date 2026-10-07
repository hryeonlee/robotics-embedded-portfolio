#include <Herkulex.h>

// 허큘렉스 모터 ID 정의
#define MOTOR_ID_3 3
#define MOTOR_ID_4 4

// 목표 각도 정의
#define ANGLE_3_1 150
#define ANGLE_3_2 -50
#define ANGLE_4_1 -150
#define ANGLE_4_2 -60

void setup() {
  // 시리얼 통신 초기화그
  Serial.begin(115200); // 아두이노와 컴퓨터 간의 시리얼 통신
  Serial1.begin(115200); // 아두이노와 허큘렉스 모터 간의 시리얼 통신 

  // 허큘렉스 초기화
  Herkulex.beginSerial1(115200);
  Herkulex.initialize();

  // 모터 초기화
  Herkulex.torqueON(MOTOR_ID_3);
  Herkulex.torqueON(MOTOR_ID_);

  
}

void loop() {
  // 첫 번째 위치로 이동
  setMotorAngle(MOTOR_ID_3, ANGLE_3_1, 300);
  setMotorAngle(MOTOR_ID_4, ANGLE_4_1, 500);

  // 1초 대기
  delay(500);

  // 두 번째 위치로 이동
  setMotorAngle(MOTOR_ID_3, ANGLE_3_2, 300);
  setMotorAngle(MOTOR_ID_4, ANGLE_4_2, 500);

  // 1초 대기
  delay(500);

  // 세 번째 위치로 이동 (첫 번째 위치로 돌아감)
  setMotorAngle(MOTOR_ID_3, ANGLE_3_1, 300);
  setMotorAngle(MOTOR_ID_4, ANGLE_4_1, 500);
  
  delay(500);// loop는 비워둡니다. 모터는 setup에서 한번만 움직입니다.
}

void setMotorAngle(int motorID, int angle, int moveTime) {
  int position = map(angle, -150, 150, 0, 1023); // 각도를 허큘렉스 포지션 값으로 변환
  Herkulex.moveOneAngle(motorID, angle, moveTime, LED_BLUE); // 모터를 해당 위치로 이동 (moveTime 동안)
}
