# Chapter 01: C++ 기초와 개발환경

## 학습 목표
- C++의 특징과 C 언어와의 차이점 이해
- 개발환경 설정 및 컴파일 과정 습득
- 네임스페이스(namespace) 개념과 활용법 학습
- 표준 입출력 스트림을 통한 기본 프로그래밍 실습

---

## 1. C++ 언어 소개

### C++의 특징
C++는 Bjarne Stroustrup이 1985년에 개발한 범용 프로그래밍 언어로, C 언어의 확장으로 시작되었습니다.

**주요 특징:**
- **객체지향 프로그래밍** 지원 (클래스, 상속, 다형성)
- **절차지향 프로그래밍** 지원 (C 스타일)
- **제네릭 프로그래밍** 지원 (템플릿)
- **메모리 관리** 직접 제어 가능
- **고성능** 시스템 및 애플리케이션 개발

### C와 C++의 차이점

| 특징 | C | C++ |
|------|---|-----|
| 패러다임 | 절차지향 | 다중 패러다임 (절차+객체+제네릭) |
| 파일 확장자 | .c | .cpp, .cxx, .cc |
| 입출력 | printf/scanf | iostream (cin/cout) |
| 메모리 할당 | malloc/free | new/delete + 스마트 포인터 |
| 함수 오버로딩 | 불가능 | 가능 |
| 네임스페이스 | 없음 | 있음 |

---

## 2. 예제 01: Hello World (01_hello_world.cpp)

### 기본 구조

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```

**실행 결과:**
```
Hello, C++!
```

### 코드 분석
- `#include <iostream>`: 입출력 스트림 헤더 포함
- `std::cout`: 표준 출력 스트림
- `std::endl`: 줄바꿈 및 버퍼 플러시
- `return 0`: 프로그램 정상 종료

---

## 3. 예제 02: 네임스페이스 기초 (02_namespace_basic.cpp)

### 네임스페이스 정의와 사용

```cpp
#include <iostream>

namespace Graphics {
    void draw() {
        std::cout << "Graphics::draw() 호출" << std::endl;
    }
}

namespace Audio {
    void draw() {
        std::cout << "Audio::draw() 호출" << std::endl;
    }
}

int main() {
    Graphics::draw();  // Graphics 네임스페이스의 draw 함수
    Audio::draw();     // Audio 네임스페이스의 draw 함수
    return 0;
}
```

**실행 결과:**
```
Graphics::draw() 호출
Audio::draw() 호출
```

### 네임스페이스의 장점
- **이름 충돌 방지**: 같은 이름의 함수나 변수를 다른 네임스페이스에서 사용 가능
- **코드 조직화**: 관련 기능을 논리적으로 그룹핑
- **라이브러리 통합**: 서로 다른 라이브러리의 충돌 방지

---

## 4. 예제 03: std 네임스페이스 활용 (03_namespace_std.cpp)

### using 지시문 활용

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "using namespace std 사용" << endl;
    cout << "std:: 접두사 생략 가능" << endl;
    return 0;
}
```

### 선택적 using 선언

```cpp
#include <iostream>
using std::cout;
using std::endl;

int main() {
    cout << "선택적 using 선언" << endl;
    // std::cin은 여전히 std:: 필요
    return 0;
}
```

**주의사항:** `using namespace std`는 편리하지만 대규모 프로젝트에서는 이름 충돌 위험이 있어 권장하지 않습니다.

---

## 5. 예제 04: 입출력 기초 (04_input_output_basic.cpp)

### 기본 입출력 연산

```cpp
#include <iostream>
using namespace std;

int main() {
    string name;
    int age;
    
    cout << "이름을 입력하세요: ";
    cin >> name;
    
    cout << "나이를 입력하세요: ";
    cin >> age;
    
    cout << "안녕하세요, " << name << "님!" << endl;
    cout << "나이: " << age << "세" << endl;
    
    return 0;
}
```

**실행 예시:**
```
이름을 입력하세요: 김개발
나이를 입력하세요: 25
안녕하세요, 김개발님!
나이: 25세
```

---

## 6. 예제 05: 다중 데이터 출력 (05_multiple_output.cpp)

### 체이닝과 서식 제어

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi = 3.14159265359;
    int number = 42;
    string language = "C++";
    
    // 체이닝을 통한 연속 출력
    cout << "언어: " << language 
         << ", 숫자: " << number 
         << ", 원주율: " << pi << endl;
    
    // 서식 지정
    cout << fixed << setprecision(2);
    cout << "원주율 (소수점 2자리): " << pi << endl;
    
    cout << "16진수: " << hex << number << endl;
    cout << "8진수: " << oct << number << endl;
    cout << "10진수: " << dec << number << endl;
    
    return 0;
}
```

**실행 결과:**
```
언어: C++, 숫자: 42, 원주율: 3.14159
원주율 (소수점 2자리): 3.14
16진수: 2a
8진수: 52
10진수: 42
```

---

## 7. 예제 06: 사용자 입력 처리 (06_user_input.cpp)

### 다양한 입력 방식

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName, lastName;
    string fullLine;
    int score;
    
    cout << "=== 학생 정보 입력 ===" << endl;
    
    cout << "이름(성): ";
    cin >> firstName;
    
    cout << "이름(이름): ";
    cin >> lastName;
    
    cout << "점수: ";
    cin >> score;
    
    // 입력 버퍼 정리
    cin.ignore();
    
    cout << "한줄 코멘트: ";
    getline(cin, fullLine);
    
    cout << "\n=== 입력된 정보 ===" << endl;
    cout << "전체 이름: " << firstName << " " << lastName << endl;
    cout << "점수: " << score << "점" << endl;
    cout << "코멘트: " << fullLine << endl;
    
    return 0;
}
```

---

## 8. 예제 07: 서식 있는 출력 (07_formatted_output.cpp)

### 고급 출력 서식

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double price = 1234.567;
    string product = "노트북";
    int quantity = 5;
    
    cout << "=== 상품 정보 ===" << endl;
    cout << left << setw(10) << "상품명" 
         << right << setw(10) << "단가" 
         << right << setw(8) << "수량" 
         << right << setw(12) << "총액" << endl;
    
    cout << string(40, '-') << endl;
    
    cout << left << setw(10) << product
         << right << setw(10) << fixed << setprecision(0) << price
         << right << setw(8) << quantity
         << right << setw(12) << price * quantity << endl;
    
    // 퍼센트 출력
    double rate = 0.15;
    cout << "\n할인율: " << setprecision(1) << (rate * 100) << "%" << endl;
    
    return 0;
}
```

**실행 결과:**
```
=== 상품 정보 ===
상품명          단가      수량        총액
----------------------------------------
노트북        1235       5        6173

할인율: 15.0%
```

---

## 9. 예제 08: 주석 활용법 (08_comments_usage.cpp)

### 효과적인 주석 작성

```cpp
#include <iostream>
using namespace std;

/**
 * 원의 넓이를 계산하는 프로그램
 * 작성자: C++ 개발팀
 * 버전: 1.0
 */

int main() {
    const double PI = 3.14159;  // 원주율 상수
    double radius;              // 반지름
    
    cout << "원의 반지름을 입력하세요: ";
    cin >> radius;
    
    // 원의 넓이 계산: π × r²
    double area = PI * radius * radius;
    
    cout << "원의 넓이: " << area << endl;
    
    /* 
    TODO: 추후 개선사항
    - 입력 값 검증 추가
    - 둘레 계산 기능 추가
    - 예외 처리 구현
    */
    
    return 0;
}
```

### 주석 작성 가이드라인
- **한줄 주석 (//)**: 간단한 설명이나 변수 설명
- **블록 주석 (/* */)**: 긴 설명이나 임시 코드 비활성화
- **문서화 주석 (/** */)**: 함수나 클래스 설명용
- **TODO/FIXME**: 개선사항이나 버그 표시

---

## 10. 예제 09: 컴파일 과정 이해 (09_compilation_process.cpp)

### 전처리기 지시문

```cpp
#include <iostream>
#define MAX_SIZE 100
#define SQUARE(x) ((x) * (x))

#ifdef DEBUG
    #define LOG(msg) std::cout << "[DEBUG] " << msg << std::endl
#else
    #define LOG(msg)
#endif

using namespace std;

int main() {
    int array[MAX_SIZE];  // 전처리기에서 100으로 치환
    int value = 5;
    
    cout << "배열 크기: " << MAX_SIZE << endl;
    cout << value << "의 제곱: " << SQUARE(value) << endl;
    
    LOG("디버그 모드에서만 출력됨");
    
    return 0;
}
```

### 컴파일 단계
1. **전처리 (Preprocessing)**: 헤더 파일 포함, 매크로 치환
2. **컴파일 (Compilation)**: C++ → 어셈블리어
3. **어셈블리 (Assembly)**: 어셈블리어 → 기계어
4. **링킹 (Linking)**: 오브젝트 파일들을 실행 파일로 연결

---

## 11. 예제 10: 기본 디버깅 (10_debugging_basics.cpp)

### 디버깅 기법

```cpp
#include <iostream>
#include <cassert>
using namespace std;

int divide(int a, int b) {
    // 사전 조건 검사
    assert(b != 0 && "0으로 나눌 수 없습니다");
    
    cout << "[DEBUG] " << a << " / " << b << " 계산 중..." << endl;
    return a / b;
}

int main() {
    int x = 10, y = 2;
    
    cout << "계산 시작" << endl;
    
    // 정상적인 계산
    int result1 = divide(x, y);
    cout << "결과: " << result1 << endl;
    
    // 오류 상황 테스트 (주석 해제시 프로그램 중단)
    // int result2 = divide(x, 0);
    
    cout << "프로그램 종료" << endl;
    
    return 0;
}
```

### 디버깅 도구 활용
- **cout 출력**: 변수 값 확인
- **assert 매크로**: 조건 검사
- **IDE 디버거**: 중단점, 단계별 실행
- **정적 분석 도구**: 코드 품질 검사

---

## 📋 이번 챕터 요약

### 학습한 내용
- **C++ 기본 구조**: 헤더 포함, main 함수, 표준 출력
- **네임스페이스**: 이름 충돌 방지와 코드 조직화
- **입출력 스트림**: cin/cout을 통한 데이터 처리
- **서식 제어**: iomanip을 활용한 출력 형식 지정
- **주석과 전처리기**: 코드 문서화와 컴파일 과정
- **기본 디버깅**: assert와 로그를 활용한 오류 탐지

### 핵심 키워드
- `#include`, `namespace`, `std::cout`, `std::cin`
- `endl`, `using`, `setw()`, `setprecision()`
- `assert()`, 전처리기 지시문

---

## 🏠 실습 과제

### 과제 1: 개인 정보 관리 프로그램
사용자로부터 이름, 나이, 전공을 입력받아 보기 좋게 출력하는 프로그램을 작성하세요.

### 과제 2: 간단한 계산기
두 개의 실수를 입력받아 사칙연산 결과를 소수점 2자리까지 출력하는 프로그램을 작성하세요.

### 과제 3: 네임스페이스 활용
`MathUtils`와 `StringUtils` 네임스페이스를 만들고 각각 유용한 함수를 정의해보세요.

---

## 🎯 다음 챕터 예고
**Chapter 02: 변수, 데이터 타입과 메모리 관리**에서는 C++의 다양한 데이터 타입, 레퍼런스와 포인터의 차이점, 그리고 동적 메모리 관리에 대해 학습합니다.
