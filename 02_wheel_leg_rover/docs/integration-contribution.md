# 팀 통합 코드 중 본인 작성 부분

`final.ino`는 팀 공동 통합 코드임. 이 문서는 그중 본인이 작성한 명령만 정리함.

## 1. `k` — 꼬리 돌출·복귀


```cpp
else if (car == 'k') {
  setMotorAngle(MOTOR_ID_1, ANGLE_1_2, 300);
  setMotorAngle(MOTOR_ID_2, ANGLE_2_2, 500);
  setMotorAngle(MOTOR_ID_3, ANGLE_3_2, 300);
  setMotorAngle(MOTOR_ID_4, ANGLE_4_2, 500);

  delay(500);

  setMotorAngle(MOTOR_ID_1, ANGLE_1_1, 300);
  setMotorAngle(MOTOR_ID_2, ANGLE_2_1, 500);
  setMotorAngle(MOTOR_ID_3, ANGLE_3_1, 300);
  setMotorAngle(MOTOR_ID_4, ANGLE_4_1, 500);

  delay(500);
}
```

Herkulex ID 1–4로 좌우 꼬리의 두 축을 함께 이동시키는 명령.

## 2. `o` — 휠레그 펼침

Herkulex ID 5·6을 연속 회전시키면서 팀원이 작성한 DC 모터 함수를 호출하는 구조.

```cpp
else if (car == 'o') {
  int speed = 500;
  int pTime = 0;

  Herkulex.moveSpeedOne(MOTOR_ID, speed, pTime, LED_GREEN);
  Herkulex.moveSpeedOne(MOTOR_ID_0, speed, pTime, LED_GREEN);

  rot();          // team-authored DC motor helper
  delay(3000);
  Stop3();        // team-authored DC motor stop helper

  Herkulex.moveSpeedOne(MOTOR_ID, 0, pTime, LED_RED);
  Herkulex.moveSpeedOne(MOTOR_ID_0, 0, pTime, LED_RED);
}
```

## 3. 작성 범위

본인 작성:
- Herkulex 꼬리 동작
- Herkulex 연속 회전 제어
- `k` 명령
- `o` 명령 중 Herkulex 명령과 팀 함수 호출을 묶은 흐름

팀원 작성:
- `rot()` 내부의 DC 모터 구동
- `Stop3()` 내부의 DC 모터 정지
- Bluetooth 기본 제어
- 엔코더 P 제어
- 리니어 액추에이터 함수
