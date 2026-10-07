# Debugging Case — Leg 6 PWM Channel Mapping

## Problem

PCA9685 두 번째 보드에 연결된 6번 다리가 움직이지 않았습니다.

18개의 서보를 한 보드에서 모두 구동할 수 없어 PCA9685를 두 개 사용했으며, 실제 배선 재구성 이후 코드의 번호 체계와 하드웨어 채널이 어긋난 상태였습니다.

## Mapping

최종 보행 코드에서는 다음 구조로 정리했습니다.

| Leg | Board | Hip | Knee | Ankle |
|---|---|---:|---:|---:|
| 1 | PCA9685 #1 (0x40) | 0 | 1 | 2 |
| 2 | PCA9685 #1 (0x40) | 3 | 4 | 5 |
| 3 | PCA9685 #1 (0x40) | 6 | 7 | 8 |
| 4 | PCA9685 #1 (0x40) | 9 | 10 | 11 |
| 5 | PCA9685 #1 (0x40) | 12 | 13 | 14 |
| 6 | PCA9685 #2 (0x41) | 0 | 1 | 2 |

## Debugging Approach

```text
No motion
  ↓
Servo fault?
  ↓
Wiring?
  ↓
PCA9685 board output?
  ↓
Logical servo ID ↔ physical PWM channel?
  ↓
Remap and retest
```

## Result

6번 다리의 세 관절을 두 번째 PCA9685의 0~2번 채널로 재지정한 뒤 전체 보행 코드에 반영했습니다.

## What I Learned

다중 액추에이터 시스템에서는 제어 알고리즘뿐 아니라

`logical ID ↔ driver channel ↔ physical actuator`

의 일치 여부가 시스템 동작에 직접 영향을 줍니다.
