# Chapter 02: 변수, 데이터 타입, 연산자와 제어문

## 학습 목표
- C++의 기본 데이터 타입과 변수 선언 방법 습득
- 다양한 연산자의 사용법과 우선순위 이해
- 조건문과 반복문을 활용한 프로그램 제어 구조 학습
- 상수와 리터럴의 올바른 사용법 이해
- 안전한 형변환 기법 습득
- 레퍼런스와 포인터의 개념 및 차이점 이해
- 동적 메모리 할당과 해제 방법 학습
- 스마트 포인터를 통한 안전한 메모리 관리 기법 습득

---

## 1. 예제 01: 기본 데이터 타입 (01_basic_datatypes.cpp)

### 예제 정의
C++의 기본 데이터 타입의 크기와 범위를 확인합니다.

```cpp
/*
주제: 데이터 타입 (Data Types)
정의: 프로그램에서 사용할 수 있는 값의 종류와 그 값들이 메모리에서 차지하는 공간을 정의하는 분류 체계

핵심 개념: sizeof 연산자, 기본 데이터 타입
정의: 
- sizeof: 데이터 타입이나 변수가 메모리에서 차지하는 바이트 수를 반환하는 연산자
- 기본 데이터 타입: C++에서 미리 정의된 데이터 종류 (char, int, float, double, bool 등)
*/

#include <iostream>
using namespace std;

int main() {
    // 기본 데이터 타입들
    char ch = 'A';
    int num = 42;
    float f = 3.14f;
    double d = 3.14159;
    bool flag = true;
    
    cout << "=== 데이터 타입 크기 ===" << endl;
    cout << "char: " << sizeof(char) << "바이트, 값: " << ch << endl;
    cout << "int: " << sizeof(int) << "바이트, 값: " << num << endl;
    cout << "float: " << sizeof(float) << "바이트, 값: " << f << endl;
    cout << "double: " << sizeof(double) << "바이트, 값: " << d << endl;
    cout << "bool: " << sizeof(bool) << "바이트, 값: " << flag << endl;
    
    return 0;
}
```

---

## 2. 예제 02: 변수 초기화 방법 (02_variable_initialization.cpp)

### 예제 정의
C++의 다양한 변수 초기화 방법을 비교합니다.

```cpp
/*
주제: 변수 초기화 (Variable Initialization)
정의: 변수를 선언할 때 초기값을 설정하는 과정으로, 메모리에 의미 있는 값을 저장하는 것

핵심 개념: 직접 초기화, 생성자 초기화, 유니폼 초기화, const 키워드
정의:
- 직접 초기화: = 연산자를 사용하여 변수에 값을 할당하는 방식
- 생성자 초기화: 괄호를 사용하여 변수를 초기화하는 C++ 스타일
- 유니폼 초기화: 중괄호 {}를 사용하는 C++11의 통일된 초기화 방법
- const: 값을 변경할 수 없는 상수를 선언하는 키워드
*/

#include <iostream>
using namespace std;

int main() {
    // 다양한 초기화 방법
    int a = 10;        // 직접 초기화
    int b(20);         // 생성자 초기화
    int c{30};         // 유니폼 초기화 (C++11)
    
    const int MAX = 100;  // 상수
    
    cout << "직접 초기화: " << a << endl;
    cout << "생성자 초기화: " << b << endl;
    cout << "유니폼 초기화: " << c << endl;
    cout << "상수: " << MAX << endl;
    
    return 0;
}
```

---

## 3. 예제 03: 산술 연산자 (03_arithmetic_operators.cpp)

### 예제 정의
기본 산술 연산자의 사용법을 학습합니다.

```cpp
/*
주제: 산술 연산자 (Arithmetic Operators)
정의: 수학적 계산을 수행하는 연산자로, 피연산자들 사이의 기본적인 수치 연산을 담당

핵심 개념: +, -, *, /, %, static_cast
정의:
- + (덧셈): 두 값을 더하는 연산자
- - (뺄셈): 왼쪽 값에서 오른쪽 값을 빼는 연산자  
- * (곱셈): 두 값을 곱하는 연산자
- / (나눗셈): 왼쪽 값을 오른쪽 값으로 나누는 연산자
- % (나머지): 정수 나눗셈의 나머지를 구하는 연산자
- static_cast: 명시적 타입 변환을 수행하는 C++ 캐스팅 연산자
*/

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;
    
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << (a + b) << endl;
    cout << "a - b = " << (a - b) << endl;
    cout << "a * b = " << (a * b) << endl;
    cout << "a / b = " << (a / b) << " (정수 나눗셈)" << endl;
    cout << "a % b = " << (a % b) << " (나머지)" << endl;
    
    // 실수 나눗셈
    double result = static_cast<double>(a) / b;
    cout << "실수 나눗셈: " << result << endl;
    
    return 0;
}
```

---

## 4. 예제 04: 증감 연산자 (04_increment_operators.cpp)

### 예제 정의
전위/후위 증감 연산자의 차이점을 이해합니다.

```cpp
/*
주제: 증감 연산자 (Increment/Decrement Operators)  
정의: 변수의 값을 1씩 증가시키거나 감소시키는 단항 연산자

핵심 개념: ++, --, 전위 연산자, 후위 연산자
정의:
- ++ (증가 연산자): 변수의 값을 1 증가시키는 연산자
- -- (감소 연산자): 변수의 값을 1 감소시키는 연산자
- 전위 연산자: 변수 앞에 위치하여 먼저 증감 후 값을 반환 (++x, --x)
- 후위 연산자: 변수 뒤에 위치하여 현재 값을 반환한 후 증감 (x++, x--)
*/

#include <iostream>
using namespace std;

int main() {
    int x = 5;
    
    cout << "초기 x = " << x << endl;
    cout << "++x = " << (++x) << ", x = " << x << endl;  // 전위: 먼저 증가
    
    x = 5;  // 초기화
    cout << "x++ = " << (x++) << ", x = " << x << endl;  // 후위: 나중에 증가
    
    cout << "--x = " << (--x) << ", x = " << x << endl;  // 전위 감소
    
    return 0;
}
```

---

## 5. 예제 05: 비교 연산자 (05_comparison_operators.cpp)

### 예제 정의
비교 연산자를 사용한 조건 판별을 학습합니다.

```cpp
/*
주제: 비교 연산자 (Comparison Operators)
정의: 두 값의 크기나 동등성을 비교하여 참(true) 또는 거짓(false)을 반환하는 이항 연산자

핵심 개념: ==, !=, >, <, >=, <=, bool 타입
정의:
- == (같음): 두 값이 같은지 비교하는 연산자
- != (다름): 두 값이 다른지 비교하는 연산자
- > (큼): 왼쪽 값이 오른쪽 값보다 큰지 비교
- < (작음): 왼쪽 값이 오른쪽 값보다 작은지 비교
- >= (크거나 같음): 왼쪽 값이 오른쪽 값보다 크거나 같은지 비교
- <= (작거나 같음): 왼쪽 값이 오른쪽 값보다 작거나 같은지 비교
- bool: 참(true) 또는 거짓(false) 값만 저장할 수 있는 논리 데이터 타입
*/

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a > b: " << (a > b) << endl;
    cout << "a < b: " << (a < b) << endl;
    cout << "a >= b: " << (a >= b) << endl;
    cout << "a <= b: " << (a <= b) << endl;
    
    return 0;
}
```

---

## 6. 예제 06: 논리 연산자 (06_logical_operators.cpp)

### 예제 정의
논리 연산자의 사용법과 단락 평가를 학습합니다.

```cpp
/*
주제: 논리 연산자 (Logical Operators)
정의: 논리값(true/false)들을 조합하여 복합적인 조건을 만드는 연산자

핵심 개념: &&, ||, !, 단락 평가
정의:
- && (논리 AND): 두 조건이 모두 참일 때만 참을 반환하는 연산자
- || (논리 OR): 두 조건 중 하나라도 참이면 참을 반환하는 연산자  
- ! (논리 NOT): 논리값을 반대로 바꾸는 단항 연산자
- 단락 평가: 결과가 확정되면 나머지 조건을 평가하지 않는 최적화 기법
*/

#include <iostream>
using namespace std;

int main() {
    bool a = true, b = false;
    
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a && b: " << (a && b) << endl;  // AND
    cout << "a || b: " << (a || b) << endl;  // OR
    cout << "!a: " << (!a) << endl;          // NOT
    
    // 실용적 예제
    int age = 25;
    bool hasLicense = true;
    
    if (age >= 18 && hasLicense) {
        cout << "운전 가능" << endl;
    } else {
        cout << "운전 불가능" << endl;
    }
    
    return 0;
}
```

---

## 7. 예제 07: if 조건문 (07_if_statement.cpp)

### 예제 정의
기본적인 if-else 조건문을 학습합니다.

```cpp
/*
주제: 조건문 (Conditional Statements)
정의: 주어진 조건의 참/거짓에 따라 프로그램의 실행 흐름을 분기하는 제어 구조

핵심 개념: if, else, 조건 판별, 삼항 연산자
정의:
- if: 조건이 참일 때 특정 코드 블록을 실행하는 키워드
- else: if 조건이 거짓일 때 실행할 대안 코드 블록을 지정하는 키워드
- 조건 판별: 표현식이 참인지 거짓인지 평가하는 과정
- 삼항 연산자 (?:): 조건에 따라 두 값 중 하나를 선택하는 간단한 조건 연산자
*/

#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "점수를 입력하세요: ";
    cin >> score;
    
    // 단순 if-else
    if (score >= 60) {
        cout << "합격!" << endl;
    } else {
        cout << "불합격..." << endl;
    }
    
    // 삼항 연산자
    string result = (score >= 60) ? "합격" : "불합격";
    cout << "결과: " << result << endl;
    
    return 0;
}
```

---

## 8. 예제 08: else if 다중 조건 (08_else_if.cpp)

### 예제 정의
else if를 사용한 다중 조건 처리를 학습합니다.

```cpp
/*
주제: 다중 조건문 (Multiple Conditional Statements)
정의: 여러 개의 조건을 순차적으로 검사하여 해당하는 조건에 맞는 코드를 실행하는 제어 구조

핵심 개념: else if, 다중 분기, 조건 연쇄
정의:
- else if: 이전 조건이 거짓일 때 추가 조건을 검사하는 키워드 조합
- 다중 분기: 여러 경우의 수에 따라 프로그램 흐름을 나누는 것
- 조건 연쇄: 여러 조건을 순서대로 연결하여 검사하는 구조
*/

#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "점수를 입력하세요: ";
    cin >> score;
    
    if (score >= 90) {
        cout << "A학점" << endl;
    } else if (score >= 80) {
        cout << "B학점" << endl;
    } else if (score >= 70) {
        cout << "C학점" << endl;
    } else if (score >= 60) {
        cout << "D학점" << endl;
    } else {
        cout << "F학점" << endl;
    }
    
    return 0;
}
```

---

## 9. 예제 09: switch 문 (09_switch_statement.cpp)

### 예제 정의
switch 문을 사용한 메뉴 선택 처리를 학습합니다.

```cpp
/*
주제: switch 문 (Switch Statement)
정의: 하나의 변수 값에 따라 여러 경우 중 하나를 선택하여 실행하는 다중 분기 제어 구조

핵심 개념: switch, case, break, default
정의:
- switch: 변수의 값에 따라 분기를 결정하는 키워드
- case: switch 변수의 특정 값에 대응하는 실행 블록을 정의하는 라벨
- break: 현재 case 실행 후 switch 문을 종료하는 키워드
- default: 모든 case에 해당하지 않을 때 실행되는 기본 케이스
*/

#include <iostream>
using namespace std;

int main() {
    int choice;
    cout << "메뉴 선택 (1-3): ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "메뉴 1 선택" << endl;
            break;
        case 2:
            cout << "메뉴 2 선택" << endl;
            break;
        case 3:
            cout << "메뉴 3 선택" << endl;
            break;
        default:
            cout << "잘못된 선택" << endl;
            break;
    }
    
    return 0;
}
```

---

## 10. 예제 10: for 반복문 (10_for_loop.cpp)

### 예제 정의
for 반복문의 기본 사용법을 학습합니다.

```cpp
/*
주제: 반복문 (Loop Statements)
정의: 특정 조건이 만족되는 동안 코드 블록을 반복적으로 실행하는 제어 구조

핵심 개념: for 루프, 초기화, 조건, 증감
정의:
- for 루프: 초기화, 조건, 증감을 한 곳에 모아 정의하는 반복문
- 초기화: 반복문 시작 전 변수를 설정하는 부분
- 조건: 반복을 계속할지 결정하는 논리 표현식
- 증감: 각 반복 후 제어 변수를 변경하는 부분
*/

#include <iostream>
using namespace std;

int main() {
    // 기본 for 문
    cout << "1부터 5까지:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // 구구단
    int dan = 3;
    cout << dan << "단:" << endl;
    for (int i = 1; i <= 9; i++) {
        cout << dan << " x " << i << " = " << (dan * i) << endl;
    }
    
    return 0;
}
```

---

## 11. 예제 11: while 반복문 (11_while_loop.cpp)

### 예제 정의
while 반복문과 사용자 입력 처리를 학습합니다.

```cpp
/*
주제: while 반복문 (While Loop)
정의: 주어진 조건이 참인 동안 코드 블록을 반복 실행하는 제어 구조

핵심 개념: while, 조건 기반 반복, 무한 루프
정의:
- while: 조건이 참인 동안 반복을 수행하는 키워드
- 조건 기반 반복: 반복 횟수가 미리 정해지지 않고 조건에 의존하는 반복
- 무한 루프: 조건이 항상 참이어서 끝나지 않는 반복문 (while(true))
*/

#include <iostream>
using namespace std;

int main() {
    int num;
    int sum = 0;
    
    cout << "숫자를 입력하세요 (0 입력시 종료):" << endl;
    
    while (true) {
        cout << "숫자: ";
        cin >> num;
        
        if (num == 0) {
            break;
        }
        
        sum += num;
        cout << "현재 합계: " << sum << endl;
    }
    
    cout << "최종 합계: " << sum << endl;
    
    return 0;
}
```

---

## 12. 예제 12: do-while 반복문 (12_do_while.cpp)

### 예제 정의
do-while 반복문으로 메뉴 시스템을 구현합니다.

```cpp
/*
주제: do-while 반복문 (Do-While Loop)
정의: 코드 블록을 먼저 실행한 후 조건을 검사하여 반복을 결정하는 후검사 반복문

핵심 개념: do-while, 후검사 반복, 최소 1회 실행
정의:
- do-while: 코드를 먼저 실행하고 나중에 조건을 검사하는 반복문
- 후검사 반복: 반복 조건을 코드 실행 후에 검사하는 반복 방식
- 최소 1회 실행: 조건에 관계없이 적어도 한 번은 코드가 실행되는 특성
*/

#include <iostream>
using namespace std;

int main() {
    int choice;
    
    do {
        cout << "\n=== 메뉴 ===" << endl;
        cout << "1. 인사말" << endl;
        cout << "2. 현재 시간" << endl;
        cout << "3. 종료" << endl;
        cout << "선택: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "안녕하세요!" << endl;
                break;
            case 2:
                cout << "현재는 수업 시간입니다." << endl;
                break;
            case 3:
                cout << "프로그램을 종료합니다." << endl;
                break;
            default:
                cout << "잘못된 선택입니다." << endl;
        }
    } while (choice != 3);
    
    return 0;
}
```

---

## 13. 예제 13: break와 continue (13_break_continue.cpp)

### 예제 정의
break와 continue를 사용한 반복문 제어를 학습합니다.

```cpp
/*
주제: 반복문 제어 (Loop Control)
정의: 반복문의 정상적인 흐름을 변경하여 반복을 중단하거나 다음 반복으로 건너뛰는 제어 기법

핵심 개념: break, continue, 반복문 제어
정의:
- break: 현재 반복문을 즉시 종료하고 반복문 다음 문장으로 이동하는 키워드
- continue: 현재 반복의 나머지 부분을 건너뛰고 다음 반복으로 이동하는 키워드
- 반복문 제어: 특정 조건에서 반복의 흐름을 변경하는 프로그래밍 기법
*/

#include <iostream>
using namespace std;

int main() {
    // continue 예제 - 홀수만 출력
    cout << "1부터 10까지 홀수만:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 짝수면 건너뛰기
        }
        cout << i << " ";
    }
    cout << endl;
    
    // break 예제 - 5에서 중단
    cout << "1부터 시작해서 5에서 중단:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            break;  // 5에서 중단
        }
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
```

---

## 14. 예제 14: 레퍼런스 기초 (14_reference_basic.cpp)

### 예제 정의
레퍼런스의 기본 개념과 사용법을 학습합니다.

```cpp
/*
주제: 레퍼런스 (Reference)
정의: 기존 변수에 대한 별명(alias)으로, 같은 메모리 위치를 참조하는 또 다른 이름

핵심 개념: 레퍼런스(&), 별명, 초기화 필수
정의:
- 레퍼런스(&): 변수 선언 시 &를 붙여 다른 변수의 별명을 만드는 문법
- 별명: 같은 메모리 위치를 가리키는 다른 이름
- 초기화 필수: 레퍼런스는 선언과 동시에 반드시 초기화되어야 하는 특성
*/

#include <iostream>
using namespace std;

int main() {
    int original = 100;
    int& ref = original;  // 레퍼런스 생성
    
    cout << "원본: " << original << endl;
    cout << "레퍼런스: " << ref << endl;
    cout << "같은 주소? " << (&original == &ref) << endl;
    
    // 레퍼런스로 값 변경
    ref = 200;
    cout << "레퍼런스로 변경 후 원본: " << original << endl;
    
    return 0;
}
```

---

## 15. 예제 15: 포인터 기초 (15_pointer_basic.cpp)

### 예제 정의
포인터의 기본 사용법을 학습합니다.

```cpp
/*
주제: 포인터 (Pointer)
정의: 다른 변수의 메모리 주소를 저장하는 변수로, 간접적으로 메모리에 접근할 수 있게 해주는 도구

핵심 개념: 포인터(*), 주소 연산자(&), 역참조
정의:
- 포인터(*): 메모리 주소를 저장하는 변수 타입 (int* ptr)
- 주소 연산자(&): 변수의 메모리 주소를 얻는 연산자
- 역참조(*): 포인터가 가리키는 메모리 위치의 값에 접근하는 연산자
*/

#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;  // 포인터 생성
    
    cout << "변수 값: " << value << endl;
    cout << "변수 주소: " << &value << endl;
    cout << "포인터 값(주소): " << ptr << endl;
    cout << "포인터가 가리키는 값: " << *ptr << endl;
    
    // 포인터로 값 변경
    *ptr = 100;
    cout << "포인터로 변경 후: " << value << endl;
    
    return 0;
}
```

---

## 16. 예제 16: 포인터와 레퍼런스 비교 (16_pointer_vs_reference.cpp)

### 예제 정의
포인터와 레퍼런스의 차이점을 비교합니다.

```cpp
/*
주제: 포인터 vs 레퍼런스 (Pointer vs Reference)
정의: 간접 접근을 제공하는 두 가지 방법의 특성과 사용법 차이점 비교

핵심 개념: 재할당 가능성, 초기화 요구사항, 문법 차이
정의:
- 재할당 가능성: 포인터는 다른 변수를 가리킬 수 있지만 레퍼런스는 불가능
- 초기화 요구사항: 레퍼런스는 선언 시 반드시 초기화, 포인터는 나중에 가능
- 문법 차이: 포인터는 *로 역참조 필요, 레퍼런스는 직접 사용
*/

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    
    // 레퍼런스
    int& ref = a;
    cout << "레퍼런스: " << ref << endl;
    
    // 포인터
    int* ptr = &a;
    cout << "포인터가 가리키는 값: " << *ptr << endl;
    
    // 포인터는 재할당 가능
    ptr = &b;
    cout << "포인터 재할당 후: " << *ptr << endl;
    
    // 레퍼런스는 재할당 불가능 (다른 변수 참조 불가)
    // ref = b;  // 이것은 b의 값을 a에 복사하는 것
    
    return 0;
}
```

---

## 17. 예제 17: 동적 메모리 할당 (17_dynamic_memory.cpp)

### 예제 정의
new와 delete를 사용한 동적 메모리 관리를 학습합니다.

```cpp
/*
주제: 동적 메모리 할당 (Dynamic Memory Allocation)
정의: 프로그램 실행 중에 필요에 따라 힙(heap) 메모리 영역에서 메모리를 할당하고 해제하는 기법

핵심 개념: new, delete, 힙 메모리, 동적 배열
정의:
- new: 힙 메모리에 새로운 객체나 배열을 할당하는 연산자
- delete: new로 할당된 메모리를 해제하는 연산자
- 힙 메모리: 동적 할당이 이루어지는 메모리 영역
- 동적 배열: 실행 시간에 크기가 결정되는 배열 (new[], delete[])
- nullptr: null 포인터 리터럴 포인터가 아무것도 가리키지 않는다는 것을 명시적으로 나타냄
*/

#include <iostream>
using namespace std;

int main() {
    // 단일 변수 동적 할당
    int* ptr = new int(42);
    cout << "동적 할당된 값: " << *ptr << endl;
    
    delete ptr;  // 메모리 해제
    ptr = nullptr;  // 안전을 위해 nullptr 설정
    
    // 배열 동적 할당
    int size = 5;
    int* arr = new int[size];
    
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;  // 배열 메모리 해제
    
    return 0;
}
```

---

## 18. 예제 18: 상수와 리터럴 (18_constants_literals.cpp)

### 예제 정의
다양한 상수 선언 방법과 리터럴 사용법을 학습합니다.

```cpp
/*
주제: 상수와 리터럴 (Constants and Literals)
정의: 프로그램 실행 중 값이 변경되지 않는 데이터와 코드에 직접 기술되는 고정값

핵심 개념: const, constexpr, 리터럴 접미사, 매크로
정의:
- const: 런타임에 값이 결정되고 이후 변경할 수 없는 상수
- constexpr: 컴파일 타임에 값이 결정되는 상수 표현식
- 리터럴 접미사: 리터럴의 타입을 명시하는 접미사 (f, L, u 등)
- 매크로: 전처리기에 의해 텍스트 치환되는 기호 상수
*/

#include <iostream>
using namespace std;

// 매크로 상수 정의 (전처리기 지시문)
#define MAX_BUFFER_SIZE 1024
#define VERSION "2.1.0"
#define SQUARE(x) ((x) * (x))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    // const 상수
    const int MAX_STUDENTS = 30;
    const double PI = 3.14159;
    const string SCHOOL_NAME = "C++ 학원";
    
    // constexpr 상수 (컴파일 타임)
    constexpr int ARRAY_SIZE = 10;
    constexpr double GRAVITY = 9.8;
    
    cout << "=== 상수 활용 ===" << endl;
    cout << "최대 학생 수: " << MAX_STUDENTS << endl;
    cout << "원주율: " << PI << endl;
    cout << "학교명: " << SCHOOL_NAME << endl;
    cout << "중력가속도: " << GRAVITY << endl;
    
    // 매크로 상수 사용
    cout << "\n=== 매크로 상수 ===" << endl;
    cout << "버퍼 크기: " << MAX_BUFFER_SIZE << endl;
    cout << "프로그램 버전: " << VERSION << endl;
    cout << "5의 제곱: " << SQUARE(5) << endl;
    cout << "10과 15 중 작은 값: " << MIN(10, 15) << endl;
    
    // 리터럴과 접미사
    cout << "\n=== 리터럴 종류 ===" << endl;
    cout << "정수 리터럴: " << 42 << endl;
    cout << "실수 리터럴: " << 3.14 << endl;
    cout << "float 리터럴: " << 3.14f << endl;
    cout << "long 리터럴: " << 1000000L << endl;
    cout << "unsigned 리터럴: " << 100u << endl;
    cout << "16진수 리터럴: " << 0xFF << " (10진수: " << 0xFF << ")" << endl;
    cout << "8진수 리터럴: " << 077 << " (10진수: " << 077 << ")" << endl;
    cout << "2진수 리터럴: " << 0b1010 << " (10진수: " << 0b1010 << ")" << endl;
    
    // 배열에서 constexpr 사용
    int numbers[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    
    // 매크로를 이용한 배열
    char buffer[MAX_BUFFER_SIZE];
    cout << "\n매크로로 정의된 버퍼 크기: " << sizeof(buffer) << " 바이트" << endl;
    
    // const vs constexpr vs 매크로 비교
    cout << "\n=== 상수 타입 비교 ===" << endl;
    cout << "const 상수 (런타임): " << MAX_STUDENTS << endl;
    cout << "constexpr 상수 (컴파일타임): " << ARRAY_SIZE << endl;
    cout << "매크로 상수 (전처리): " << MAX_BUFFER_SIZE << endl;
    
    // const 변수는 초기화 후 변경 불가
    // MAX_STUDENTS = 40; // 오류!
    
    return 0;
}
```

---

## 19. 예제 19: 형변환 (19_type_casting.cpp)

### 예제 정의
C++의 다양한 형변환 방법과 안전한 캐스팅을 학습합니다.

```cpp
/*
주제: 형변환 (Type Casting)
정의: 하나의 데이터 타입을 다른 데이터 타입으로 변환하는 과정

핵심 개념: 암시적 변환, 명시적 변환, C++ 캐스트 연산자, void* 포인터
정의:
- 암시적 변환: 컴파일러가 자동으로 수행하는 타입 변환
- 명시적 변환: 프로그래머가 의도적으로 지시하는 타입 변환
- C++ 캐스트 연산자: static_cast, dynamic_cast, const_cast, reinterpret_cast
- void* 포인터: 어떤 타입의 포인터든 저장할 수 있는 범용 포인터 (타입 정보 없음)
*/

#include <iostream>
using namespace std;

int main() {
    cout << "=== 암시적 형변환 ===" << endl;
    int intValue = 10;
    double doubleValue = intValue;  // int → double (자동)
    cout << "int " << intValue << " → double " << doubleValue << endl;
    
    char charValue = 'A';
    int asciiValue = charValue;     // char → int (자동)
    cout << "char '" << charValue << "' → int " << asciiValue << endl;
    
    cout << "\n=== 명시적 형변환 (C 스타일) ===" << endl;
    double pi = 3.14159;
    int truncated = (int)pi;        // 소수점 이하 버림
    cout << "double " << pi << " → int " << truncated << endl;
    
    cout << "\n=== static_cast ===" << endl;
    double result = static_cast<double>(intValue) / 3;
    cout << "정확한 나눗셈: " << intValue << " / 3 = " << result << endl;
    
    // void* 포인터와 캐스팅
    cout << "\n=== void* 포인터 활용 ===" << endl;
    void* voidPtr = &intValue;  // void*는 어떤 타입의 포인터든 받을 수 있음
    cout << "void* 주소: " << voidPtr << endl;
    cout << "int 변수 주소: " << &intValue << endl;
    
    // void*는 역참조할 수 없으므로 적절한 타입으로 캐스팅 필요
    int* intPtr = static_cast<int*>(voidPtr);
    cout << "void* → int* 캐스팅 후 값: " << *intPtr << endl;
    
    // 다른 타입도 void*에 저장 가능
    double doubleVar = 99.9;
    voidPtr = &doubleVar;  // 같은 void*에 다른 타입 주소 저장
    double* doublePtr = static_cast<double*>(voidPtr);
    cout << "void*에 double 저장 후: " << *doublePtr << endl;
    
    cout << "\n=== void* 포인터의 특징과 주의사항 ===" << endl;
    // void*는 타입 안전성이 없으므로 잘못된 캐스팅 가능
    int intVar = 42;
    void* genericPtr = &intVar;
    
    // 올바른 사용
    int* correctPtr = static_cast<int*>(genericPtr);
    cout << "올바른 캐스팅: " << *correctPtr << endl;
    
    // 위험한 사용 (컴파일은 되지만 결과 예측 불가)
    // double* wrongPtr = static_cast<double*>(genericPtr);
    // cout << "잘못된 캐스팅: " << *wrongPtr << endl;  // 위험!
    
    cout << "주의: void*는 타입 정보가 없어 잘못된 캐스팅 시 예측 불가능한 결과 발생" << endl;
    int largeInt = 300;
    char smallChar = static_cast<char>(largeInt);
    cout << "int " << largeInt << " → char " << static_cast<int>(smallChar) 
         << " (범위 초과로 데이터 손실 가능)" << endl;
    
    cout << "\n=== 실용적 예제 ===" << endl;
    // 평균 계산 시 정확한 결과를 위한 캐스팅
    int score1 = 85, score2 = 90, score3 = 78;
    double average = static_cast<double>(score1 + score2 + score3) / 3;
    cout << "평균 점수: " << average << endl;
    
    // 퍼센트 계산
    int correct = 23, total = 30;
    double percentage = static_cast<double>(correct) / total * 100;
    cout << "정답률: " << percentage << "%" << endl;
    
    return 0;
}
```

---

## 20. 예제 20: nullptr과 안전성 (20_nullptr_safety.cpp)

### 예제 정의
nullptr을 사용한 안전한 포인터 사용법을 학습합니다.

```cpp
/*
주제: 포인터 안전성 (Pointer Safety)
정의: 포인터 사용 시 발생할 수 있는 오류를 방지하고 안전하게 메모리에 접근하는 프로그래밍 기법

핵심 개념: nullptr, 널 포인터 검사, 댕글링 포인터 방지
정의:
- nullptr: 아무것도 가리키지 않는 포인터 상태를 나타내는 C++11의 널 포인터 상수
- 널 포인터 검사: 포인터가 유효한 메모리를 가리키는지 확인하는 안전 검사
- 댕글링 포인터 방지: 해제된 메모리를 가리키는 포인터 사용을 막는 기법
*/

#include <iostream>
using namespace std;

int main() {
    int* ptr = nullptr;
    
    // 안전한 포인터 사용
    if (ptr != nullptr) {
        cout << "값: " << *ptr << endl;
    } else {
        cout << "포인터가 nullptr입니다." << endl;
    }
    
    // 포인터에 메모리 할당
    ptr = new int(100);
    
    if (ptr != nullptr) {
        cout << "할당 후 값: " << *ptr << endl;
        delete ptr;
        ptr = nullptr;
    }
    
    return 0;
}
```

---

## 21. 예제 21: unique_ptr 기초 (21_unique_ptr.cpp)

### 예제 정의
unique_ptr을 사용한 자동 메모리 관리를 학습합니다.

```cpp
/*
주제: 스마트 포인터 (Smart Pointers)
정의: 자동으로 메모리를 관리해주는 포인터 래퍼 클래스로, 메모리 누수를 방지하는 현대 C++의 핵심 기능

핵심 개념: unique_ptr, make_unique, 자동 해제, 독점 소유권
정의:
- unique_ptr: 하나의 객체를 독점적으로 소유하는 스마트 포인터
- make_unique: unique_ptr을 안전하게 생성하는 헬퍼 함수
- 자동 해제: 스코프를 벗어날 때 자동으로 메모리를 해제하는 기능
- 독점 소유권: 한 번에 하나의 unique_ptr만이 객체를 소유할 수 있는 특성
*/

#include <iostream>
#include <memory>
using namespace std;

int main() {
    // unique_ptr 생성
    auto ptr = make_unique<int>(42);
    cout << "값: " << *ptr << endl;
    
    // 배열 unique_ptr
    auto arr = make_unique<int[]>(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    
    for (int i = 0; i < 3; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 스코프 종료 시 자동 해제
    return 0;
}
```

---

## 22. 예제 22: shared_ptr 기초 (22_shared_ptr.cpp)

### 예제 정의
shared_ptr을 사용한 공유 메모리 관리를 학습합니다.

```cpp
/*
주제: 공유 스마트 포인터 (Shared Smart Pointer)
정의: 여러 포인터가 하나의 객체를 공유할 수 있게 해주는 참조 카운팅 기반의 스마트 포인터

핵심 개념: shared_ptr, make_shared, 참조 카운팅, use_count()
정의:
- shared_ptr: 여러 포인터가 같은 객체를 공유할 수 있는 스마트 포인터
- make_shared: shared_ptr을 효율적으로 생성하는 헬퍼 함수
- 참조 카운팅: 객체를 참조하는 포인터의 개수를 추적하는 메모리 관리 기법
- use_count(): 현재 객체를 참조하는 shared_ptr의 개수를 반환하는 함수
*/

#include <iostream>
#include <memory>
using namespace std;

int main() {
    auto ptr1 = make_shared<int>(100);
    cout << "값: " << *ptr1 << endl;
    cout << "참조 카운트: " << ptr1.use_count() << endl;
    
    {
        auto ptr2 = ptr1;  // 공유
        cout << "ptr2 생성 후 참조 카운트: " << ptr1.use_count() << endl;
    }  // ptr2 소멸
    
    cout << "ptr2 소멸 후 참조 카운트: " << ptr1.use_count() << endl;
    
    return 0;
}
```

---

## 이번 챕터 요약

### 학습한 내용
**기본 개념**: 데이터 타입, 변수 초기화, 상수와 리터럴
**연산자**: 산술, 증감, 비교, 논리 연산자
**제어문**: if, switch, for, while, do-while
**형변환**: 암시적/명시적 변환, static_cast
**메모리**: 레퍼런스, 포인터, 동적 할당, 스마트 포인터

### 핵심 키워드
- 데이터 타입: `int`, `double`, `bool`, `char`
- 상수: `const`, `constexpr`, 리터럴 접미사
- 연산자: `+`, `-`, `*`, `/`, `%`, `++`, `--`, `==`, `!=`, `&&`, `||`
- 제어문: `if`, `else`, `switch`, `for`, `while`, `do-while`
- 형변환: `static_cast`, 암시적 변환, 명시적 변환
- 메모리: `&`, `*`, `new`, `delete`, `unique_ptr`, `shared_ptr`

---

## 실습 과제

### 과제 1: 향상된 계산기
두 숫자와 연산자를 입력받아 계산하는 프로그램 (상수 활용, 안전한 형변환 사용)

### 과제 2: 성적 관리 시스템
여러 과목의 점수를 입력받아 평균과 등급을 계산하는 프로그램 (constexpr 상수 활용)

### 과제 3: 숫자 맞히기 게임 개선
1-100 사이 숫자를 맞히는 게임 (범위 상수, 형변환 활용)

### 과제 4: 스마트 포인터 기반 동적 배열
사용자가 입력한 개수만큼 숫자를 저장하고 통계를 계산하는 프로그램 (unique_ptr 사용)

---

## 다음 챕터 예고
**Chapter 03: 함수와 배열**에서는 코드의 재사용성을 높이는 함수와 효율적인 배열 처리를 학습합니다.
