# Integration Debugging — Tail Servo Failure

## Symptom

개별 꼬리 또는 2-servo 구성에서는 동작했지만 전체 시스템 통합 후 4-servo 꼬리 구성에서 오류가 발생했습니다.

## Hypotheses

1. Mechanical overload
2. Overheating
3. Power supply
4. UART communication
5. Motor-specific fault
6. Communication / timing interference

## Isolation

| Hypothesis | Test | Observation |
|---|---|---|
| Mechanical overload | 링크 부하 없이 꼬리만 동작 | 오류 지속 |
| Overheating | 전원 인가 직후 오류 발생 여부 확인 | 즉시 오류 → 과열 가능성 낮음 |
| Power supply | Herkulex 4개에 별도 전원 공급 | 오류 지속 |
| Communication | Arduino Mega 직결, 2-servo와 4-servo 비교 | 2개 구성 동작 / 4개 구성 오류 |
| Motor fault | 충분히 검증하지 못함 | 미확인 |
| Timing / integration | 통합 코드 구조 재검토 | 가능성 남음 |

## Result

프로젝트 일정 안에 root cause를 확정하지 못했습니다.


## Post-Project Code Review

이후 팀 통합 코드를 다시 확인하면서 다음 요소를 발견했습니다.

- `torqueON()`이 ID 1·2에는 호출되지만 ID 3·4에는 호출되지 않음
- 수 초 단위의 blocking `delay()`
- Hardware Serial1 + SoftwareSerial + encoder interrupt 동시 사용

이 중 `torqueON()` 누락은 유력한 후보지만, 수정 후 실제 하드웨어에서 재시험하지 않았으므로 **검증된 원인으로 단정하지 않습니다.**

## Takeaway

원인 후보를 목록화한 것은 유효했지만, `2 servos work → 4 servos fail`이라는 관찰을 중심으로 ID/초기화/상태 차이를 더 빠르게 비교했어야 했습니다.
