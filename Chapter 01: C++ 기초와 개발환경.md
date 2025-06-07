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

| 항목 | C언어 | C++ |
|------|-------|-----|
| **프로그래밍 방식** | 절차지향 | 절차지향 + 객체지향 |
| **확장자** | .c | .cpp, .cxx, .cc |
| **입출력 방식** | printf, scanf | cout, cin |
| **메모리 관리** | malloc, free | new, delete |
| **함수 오버로딩** | 지원 안함 | 지원 |
| **클래스/객체** | 지원 안함 | 지원 |
| **참조(reference)** | 지원 안함 | 지원 |
| **인라인 함수** | 지원 안함 | 지원 |


---

## 2. 예제 01: Hello World (01_hello_world.cpp)

### 예제 정의
이 예제는 C++ 프로그래밍의 첫 단계로, 가장 기본적인 프로그램 구조를 학습합니다. 모든 C++ 프로그램이 가져야 할 필수 요소들(헤더 포함, main 함수, 표준 출력)을 이해하고, 컴파일부터 실행까지의 전체 과정을 경험합니다.

**학습 목표:**
- C++ 프로그램의 기본 구조 파악
- 표준 출력 스트림 사용법 이해
- 컴파일과 실행 과정 체험

**핵심 개념:** `#include`, `std::cout`, `main()` 함수, `return` 문

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

### 예제 정의
네임스페이스는 C++의 핵심 기능 중 하나로, 대규모 프로젝트에서 이름 충돌을 방지하고 코드를 논리적으로 조직화하는 중요한 메커니즘입니다. 이 예제를 통해 네임스페이스의 정의와 사용법을 학습하고, 실무에서 라이브러리 통합 시 발생할 수 있는 문제를 해결하는 방법을 익힙니다.

**학습 목표:**
- 네임스페이스의 개념과 필요성 이해
- 네임스페이스 정의 및 접근 방법 습득
- 이름 충돌 해결 방안 학습

**핵심 개념:** `namespace` 키워드, 범위 해석 연산자(`::`)

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

### 예제 정의
표준 라이브러리의 모든 구성 요소는 `std` 네임스페이스에 정의되어 있습니다. 이 예제는 `using` 지시문을 통해 네임스페이스 사용을 간소화하는 방법과 그에 따른 장단점을 학습합니다. 실무에서는 편의성과 안전성 사이의 균형을 고려해야 합니다.

**학습 목표:**
- `using namespace` 지시문의 역할 이해
- 선택적 `using` 선언의 활용법 습득
- 대규모 프로젝트에서의 네임스페이스 전략 이해

**핵심 개념:** `using namespace`, `using` 선언, 이름 충돌 위험성

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

### 예제 정의
사용자와의 상호작용은 프로그램의 핵심 기능입니다. 이 예제는 C++의 스트림 기반 입출력 시스템을 학습하여 사용자로부터 데이터를 입력받고 결과를 출력하는 방법을 익힙니다. C의 `scanf/printf`와 달리 C++의 `cin/cout`은 타입 안전성을 제공하며 더 직관적입니다.

**학습 목표:**
- 표준 입력 스트림 `cin` 사용법 습득
- 다양한 데이터 타입의 입출력 처리
- 스트림 연산자(`<<`, `>>`)의 동작 원리 이해

**핵심 개념:** `std::cin`, 스트림 연산자, 타입 안전성

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

### 예제 정의
데이터 시각화와 리포트 생성에서 중요한 서식 제어 기능을 학습합니다. 이 예제는 여러 데이터를 연속으로 출력하는 체이닝 기법과 `iomanip` 라이브러리를 활용한 정밀한 서식 제어를 다룹니다. 실무에서 로그 출력, 데이터 리포트, 사용자 인터페이스 구성에 필수적인 기술입니다.

**학습 목표:**
- 스트림 체이닝을 통한 연속 출력 방법
- 수치 데이터의 정밀한 서식 제어
- 진법 변환 출력 방법 습득

**핵심 개념:** 체이닝, `setprecision()`, `fixed`, `hex/oct/dec`

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

### 예제 정의
실제 애플리케이션에서는 단순한 단어나 숫자뿐만 아니라 공백이 포함된 문장도 입력받아야 합니다. 이 예제는 다양한 입력 시나리오를 처리하는 방법과 입력 버퍼 관리의 중요성을 학습합니다. 사용자 경험을 고려한 입력 처리는 전문적인 소프트웨어 개발의 필수 요소입니다.

**학습 목표:**
- `getline()` 함수를 통한 라인 단위 입력 처리
- 입력 버퍼 관리 방법 습득
- 사용자 친화적인 인터페이스 설계

**핵심 개념:** `getline()`, `cin.ignore()`, 입력 버퍼

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

### 예제 정의
데이터를 표 형태로 정렬하거나 리포트를 생성할 때 필요한 고급 서식 기능을 학습합니다. 이 예제는 실무에서 자주 사용되는 데이터 출력 패턴을 다루며, 특히 ERP 시스템이나 관리 프로그램에서 중요한 기술입니다. 정렬, 폭 지정, 정밀도 제어를 통해 전문적인 출력 형식을 구현합니다.

**학습 목표:**
- 컬럼 기반 데이터 정렬 방법
- 동적 폭 조정과 정렬 옵션 활용
- 숫자 데이터의 다양한 표현 방식

**핵심 개념:** `setw()`, `left/right`, 테이블 형식 출력

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

### 예제 정의
코드의 가독성과 유지보수성을 높이는 것은 전문 개발자의 필수 역량입니다. 이 예제는 효과적인 주석 작성 방법과 코드 문서화 전략을 학습합니다. 개인 프로젝트뿐만 아니라 팀 개발에서 코드의 의도를 명확히 전달하고, 향후 수정이나 확장을 용이하게 하는 방법을 익힙니다.

**학습 목표:**
- 다양한 주석 유형의 적절한 사용법
- 코드 문서화 베스트 프랙티스
- 협업을 위한 주석 작성 전략

**핵심 개념:** 단일행 주석, 블록 주석, 문서화 주석, TODO/FIXME

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
