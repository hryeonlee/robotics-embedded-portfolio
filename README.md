# Robotics & Embedded Systems Portfolio

로봇·임베디드 시스템에서 **센서 입력 → 제어 판단 → 액추에이터 출력 → 실제 기구 동작**이 연결되는 과정을 구현하고 검증한 프로젝트를 정리한 포트폴리오입니다.

주요 경험은 다중 서보모터 제어, 센서 기반 조건 제어, UART 기반 스마트 서보 구동, 실제 하드웨어 통합 테스트와 디버깅입니다.

> Target Roles: Robotics Test / Embedded Control / System Integration / Verification & Validation

---

## Featured Projects

| 6족 랜딩기어 — Tripod gait | Wheel-leg — Herkulex tail control |
|---|---|
| ![Hexapod](01_hexapod_drone/media/tripod_gait_bench_test.gif) | ![Tail](02_wheel_leg_rover/media/tail_control_test.gif) |

| Project | Role | Technical Focus | Evidence |
|---|---|---|---|
| [Hexapod Drone Landing Gear](01_hexapod_drone/) | 5인 팀 · 팀장 · 제어 코드 및 센서 연동 | Arduino Mega, PCA9685 ×2, 18-Servo Control, FSR-406, Tripod Gait | 보행·착지 GIF, Arduino 코드, PWM 채널 매핑 디버깅 |
| [Wheel-leg Rover](02_wheel_leg_rover/) | 5인 팀 · Herkulex 구동 및 통합 테스트 | Herkulex DRS-0101, UART 115200 bps, 4-axis Tail, Integration Debugging | 꼬리 구동 GIF, 직접 작성 코드, 통합 오류 원인 분리 기록 |

### Additional Experience

- **i-HARBOR** — Raspberry Pi OS / SSH / VNC 환경 구성, Flask + gpiozero 기반 단일 서보모터·LED 웹 제어 프로토타입 구현
- **Vibration Energy Harvesting** — 회로 구성 및 측정 코드 작성, 오실로스코프로 정류 전 원신호 측정, 무부하 상태 약 14.1 V 개방전압 확인

---

## Engineering Focus

### 1. Multi-Servo Control

6족 드론 프로젝트에서 Arduino Mega와 PCA9685 보드 2개를 사용해 18개의 MG90S 계열 서보모터를 구동했습니다.

각 액추에이터를 단순히 개별 제어하는 데 그치지 않고,

`Leg → Joint → Servo ID → PCA9685 Board → PWM Channel`

매핑을 관리하며 실제 배선과 제어 코드가 일치하는지 검증했습니다.

### 2. Sensor-Based Conditional Control

FSR-406 압력센서 입력을 이용해 접지를 판단하고, 임계값 도달 시 해당 다리의 하강 동작을 멈추는 조건 제어 로직을 구현했습니다.

### 3. Hardware–Software Integration

실제 프로젝트에서는 코드만 정상이라고 해서 시스템이 정상적으로 동작하지 않았습니다.

문제가 발생하면 다음 범주를 분리해 확인했습니다.

`Power → Wiring → Communication → Control Code → Channel Mapping → Mechanical Coupling`

### 4. Root-Cause Isolation

- 6족 드론: 6번 다리 미동작 → 실제 PWM 채널과 코드 매핑 불일치 확인 → 재매핑
- Wheel-leg: 통합 후 꼬리 오류 → 과부하·과열·전원·통신·모터·코드 타이밍을 원인 후보로 분리해 테스트

---

## Skills Used in Projects

| Area | Verified Experience |
|---|---|
| Programming | Arduino C/C++, Python, basic C++ |
| MCU / SBC | Arduino Mega, Raspberry Pi |
| Motor Control | MG90S-class Servo, Herkulex DRS-0101 |
| Driver / I/O | PCA9685, PWM, GPIO |
| Communication | I2C, UART in Herkulex control system |
| Sensor | FSR-406, HC-SR04, IR line sensor |
| Test / Debug | Channel mapping, wiring check, integration test, root-cause isolation |
| Tools | Arduino IDE, Fritzing, Oscilloscope, Git/GitHub |


---

## Repository Structure

```text
.
├── 01_hexapod_drone/
│   ├── README.md
│   ├── src/
│   ├── docs/
│   └── media/
├── 02_wheel_leg_rover/
│   ├── README.md
│   ├── src/
│   ├── docs/
│   └── media/
└── NOTICE.md
```

---

## Collaboration & Scope

이 저장소의 대표 프로젝트는 팀 프로젝트입니다.

각 프로젝트 README에서 **My Contribution**과 **Team Scope**를 구분해 정리했습니다.

공개된 코드는 직접 작성한 코드 또는 직접 작성한 부분을 기준으로 정리한 포트폴리오용 자료입니다.
