# Integration Code Contribution

`final.ino`는 팀 공동 통합 코드였습니다. 이 문서에는 그중 직접 작성한 명령의 역할만 정리합니다.

## `k` — Tail deployment / return

본인이 작성한 영역:

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

Herkulex ID 1~4를 사용해 좌우 꼬리의 두 축을 함께 이동시키는 명령입니다.

## `o` — Wheel-leg gear actuation

본인이 작성한 통합 명령은 Herkulex ID 5·6을 연속 회전시키면서 팀원이 작성한 DC motor helper function을 호출하는 구조였습니다.

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

## Ownership Boundary

직접 작성:
- Herkulex tail motion
- Herkulex continuous rotation control
- `k` command
- `o` command에서 Herkulex 명령과 팀 함수 호출을 조합한 통합 흐름

팀원 작성:
- `rot()` 내부의 DC motor drive logic
- `Stop3()` 내부의 DC motor stop logic
- Bluetooth base control
- encoder P-control
- linear actuator functions


