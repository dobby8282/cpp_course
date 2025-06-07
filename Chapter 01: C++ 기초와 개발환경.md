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
C++ 프로그래밍의 첫 단계로, 가장 기본적인 프로그램 구조를 학습합니다.

```cpp
/*
주제: C++ 프로그램 구조 (C++ Program Structure)
정의: C++ 프로그램이 가져야 할 기본적인 구성 요소와 실행 흐름

핵심 개념: #include, main 함수, std::cout, return문
정의:
- #include: 헤더 파일을 포함시켜 필요한 라이브러리 기능을 사용할 수 있게 하는 전처리 지시문
- main 함수: 프로그램 실행의 시작점이 되는 함수
- std::cout: 표준 출력 스트림으로 화면에 데이터를 출력하는 객체
- return문: 함수의 실행을 종료하고 호출자에게 값을 반환하는 문장
*/

#include <iostream>

int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```

---

## 3. 예제 02: 네임스페이스 기초 (02_namespace_basic.cpp)

### 예제 정의
네임스페이스를 사용하여 이름 충돌을 방지하는 방법을 학습합니다.

```cpp
/*
주제: 네임스페이스 (Namespace)
정의: 이름 충돌을 방지하고 코드를 논리적으로 그룹화하기 위한 명명 영역

핵심 개념: namespace 키워드, 범위 해석 연산자(::), 이름 충돌 방지
정의:
- namespace 키워드: 새로운 명명 영역을 정의하는 키워드
- 범위 해석 연산자(::): 특정 네임스페이스의 요소에 접근하기 위한 연산자
- 이름 충돌 방지: 같은 이름의 함수나 변수를 다른 네임스페이스에서 구분하여 사용
*/

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

---

## 4. 예제 03: std 네임스페이스 활용 (03_namespace_std.cpp)

### 예제 정의
표준 라이브러리의 std 네임스페이스 사용법을 학습합니다.

```cpp
/*
주제: std 네임스페이스 (std Namespace)
정의: C++ 표준 라이브러리의 모든 구성 요소가 정의된 네임스페이스

핵심 개념: using namespace, using 선언, 표준 라이브러리
정의:
- using namespace: 특정 네임스페이스의 모든 요소를 현재 영역으로 가져오는 지시문
- using 선언: 특정 네임스페이스의 개별 요소만 가져오는 선언
- 표준 라이브러리: C++에서 제공하는 미리 작성된 함수와 클래스의 집합
*/

#include <iostream>
using namespace std;

int main() {
    cout << "using namespace std 사용" << endl;
    cout << "std:: 접두사 생략 가능" << endl;
    return 0;
}
```

---

## 5. 예제 04: 입출력 기초 (04_input_output_basic.cpp)

### 예제 정의
C++의 기본적인 입출력 방법을 학습합니다.

```cpp
/*
주제: 입출력 스트림 (Input/Output Stream)
정의: 데이터의 입력과 출력을 위한 C++의 스트림 기반 시스템

핵심 개념: cin, cout, 스트림 연산자, 타입 안전성
정의:
- cin: 표준 입력 스트림으로 키보드로부터 데이터를 입력받는 객체
- cout: 표준 출력 스트림으로 화면에 데이터를 출력하는 객체
- 스트림 연산자: << (출력), >> (입력) 연산자로 데이터 흐름을 제어
- 타입 안전성: 컴파일 시점에 데이터 타입을 검사하여 오류를 방지하는 특성
*/

#include <iostream>
#include <string>
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

---

## 6. 예제 05: 다중 데이터 출력 (05_multiple_output.cpp)

### 예제 정의
여러 데이터를 연속으로 출력하고 서식을 제어하는 방법을 학습합니다.

```cpp
/*
주제: 출력 서식 제어 (Output Formatting)
정의: 데이터를 원하는 형태로 정렬하고 표현하기 위한 출력 제어 기법

핵심 개념: 스트림 체이닝, setprecision, fixed, 진법 변환
정의:
- 스트림 체이닝: << 연산자를 연속으로 사용하여 여러 데이터를 한 번에 출력하는 기법
- setprecision: 부동소수점 수의 정밀도를 설정하는 조작자
- fixed: 고정소수점 표기법을 사용하도록 설정하는 조작자
- 진법 변환: hex(16진법), oct(8진법), dec(10진법) 조작자를 사용한 수 표현
*/

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

---

## 7. 예제 06: 사용자 입력 처리 (06_user_input.cpp)

### 예제 정의
다양한 입력 상황을 처리하고 입력 버퍼를 관리하는 방법을 학습합니다.

```cpp
/*
주제: 사용자 입력 처리 (User Input Handling)
정의: 사용자로부터 다양한 형태의 데이터를 안전하고 정확하게 입력받는 기법

핵심 개념: getline, cin.ignore, 입력 버퍼, 공백 처리
정의:
- getline: 공백을 포함한 한 줄 전체를 입력받는 함수
- cin.ignore: 입력 버퍼에 남아있는 문자들을 제거하는 함수
- 입력 버퍼: 입력된 데이터가 임시로 저장되는 메모리 공간
- 공백 처리: 문자열에 포함된 공백 문자를 올바르게 처리하는 방법
*/

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
표 형태의 정렬된 출력과 고급 서식 기능을 학습합니다.

```cpp
/*
주제: 고급 출력 서식 (Advanced Output Formatting)
정의: 데이터를 표 형태로 정렬하고 전문적인 형태로 출력하는 고급 서식 제어 기법

핵심 개념: setw, left/right, 테이블 출력, 문자열 생성
정의:
- setw: 출력 필드의 폭을 설정하는 조작자
- left/right: 데이터의 정렬 방향을 설정하는 조작자
- 테이블 출력: 행과 열로 구성된 표 형태의 데이터 출력
- 문자열 생성: string 생성자를 이용한 반복 문자열 생성
*/

#include <iostream>
#include <iomanip>
#include <string>
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

---

## 9. 예제 08: 주석 활용법 (08_comments_usage.cpp)

### 예제 정의
효과적인 주석 작성 방법과 코드 문서화 전략을 학습합니다.

```cpp
/*
주제: 코드 문서화 (Code Documentation)
정의: 코드의 가독성과 유지보수성을 높이기 위한 주석과 문서화 기법

핵심 개념: 단일행 주석, 블록 주석, 문서화 주석, TODO/FIXME
정의:
- 단일행 주석(//): 한 줄짜리 간단한 설명을 위한 주석
- 블록 주석(/* */): 여러 줄에 걸친 긴 설명이나 코드 블록 비활성화용 주석
- 문서화 주석(/** */): 함수, 클래스 등의 공식 문서화를 위한 주석
- TODO/FIXME: 향후 개선사항이나 수정할 부분을 표시하는 특수 주석
*/

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

---

## 10. 예제 09: 컴파일 과정 이해 (09_compilation_process.cpp)

### 예제 정의
C++ 프로그램의 컴파일 과정과 전처리기 지시문을 학습합니다.

```cpp
/*
주제: 컴파일 과정 (Compilation Process)
정의: C++ 소스 코드가 실행 가능한 프로그램으로 변환되는 과정

핵심 개념: 전처리기, 매크로, 조건부 컴파일, #define
정의:
- 전처리기: 컴파일 전에 소스 코드를 변환하는 프로그램
- 매크로: 코드의 일부를 다른 텍스트로 치환하는 전처리 기능
- 조건부 컴파일: 특정 조건에 따라 코드의 일부를 포함하거나 제외하는 기법
- #define: 매크로를 정의하는 전처리 지시문
*/

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
    
    cout << "\n=== 컴파일 단계 ===" << endl;
    cout << "1. 전처리 (Preprocessing)" << endl;
    cout << "2. 컴파일 (Compilation)" << endl;
    cout << "3. 어셈블리 (Assembly)" << endl;
    cout << "4. 링킹 (Linking)" << endl;
    
    return 0;
}
```

---

## 11. 예제 10: 기본 디버깅 (10_debugging_basics.cpp)

### 예제 정의
프로그램 개발 시 필요한 기본적인 디버깅 기법을 학습합니다.

```cpp
/*
주제: 디버깅 (Debugging)
정의: 프로그램의 오류를 찾아내고 수정하는 과정

핵심 개념: assert, 디버그 출력, 사전 조건 검사, 로그
정의:
- assert: 프로그램 실행 중 특정 조건이 참인지 확인하는 매크로
- 디버그 출력: 프로그램의 상태를 확인하기 위한 임시 출력
- 사전 조건 검사: 함수 실행 전 입력값의 유효성을 검사하는 기법
- 로그: 프로그램 실행 과정을 기록하는 메시지
*/

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
    
    cout << "=== 디버깅 예제 ===" << endl;
    cout << "계산 시작" << endl;
    
    // 정상적인 계산
    int result1 = divide(x, y);
    cout << "결과: " << result1 << endl;
    
    // 오류 상황 테스트 (주석 해제시 프로그램 중단)
    // int result2 = divide(x, 0);
    
    cout << "\n=== 디버깅 도구 활용법 ===" << endl;
    cout << "1. cout 출력으로 변수 값 확인" << endl;
    cout << "2. assert 매크로로 조건 검사" << endl;
    cout << "3. IDE 디버거로 중단점 설정" << endl;
    cout << "4. 정적 분석 도구로 코드 품질 검사" << endl;
    
    cout << "\n프로그램 정상 종료" << endl;
    
    return 0;
}
```

---

## 이번 챕터 요약

### 학습한 내용
**C++ 기본 구조**: 헤더 포함, main 함수, 표준 출력
**네임스페이스**: 이름 충돌 방지와 코드 조직화
**입출력 스트림**: cin/cout을 통한 데이터 처리
**서식 제어**: iomanip을 활용한 출력 형식 지정
**주석과 전처리기**: 코드 문서화와 컴파일 과정
**기본 디버깅**: assert와 로그를 활용한 오류 탐지

### 핵심 키워드
- `#include`, `namespace`, `std::cout`, `std::cin`
- `endl`, `using`, `setw()`, `setprecision()`
- `assert()`, 전처리기 지시문
- `getline()`, `cin.ignore()`

### 프로그래밍 원칙
1. 명확한 네임스페이스 사용
2. 적절한 입출력 처리
3. 효과적인 코드 문서화
4. 기본적인 오류 방지

---

## 실습 과제

### 과제 1: 개인 정보 관리 프로그램
사용자로부터 이름, 나이, 전공을 입력받아 보기 좋게 출력하는 프로그램을 작성하세요.

### 과제 2: 간단한 계산기
두 개의 실수를 입력받아 사칙연산 결과를 소수점 2자리까지 출력하는 프로그램을 작성하세요.

### 과제 3: 네임스페이스 활용
`MathUtils`와 `StringUtils` 네임스페이스를 만들고 각각 유용한 함수를 정의해보세요.

### 과제 4: 서식 있는 리포트
학생 성적 정보를 표 형태로 정렬하여 출력하는 프로그램을 작성하세요.

---

## 다음 챕터 예고
**Chapter 02: 변수, 데이터 타입, 연산자와 제어문**에서는 C++의 다양한 데이터 타입과 연산자, 그리고 프로그램 흐름을 제어하는 조건문과 반복문에 대해 학습합니다.
