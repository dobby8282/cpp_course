# Chapter 03: 함수와 배열

## 학습 목표
- 함수의 선언과 정의 방법 습득
- 다양한 매개변수 전달 방식 이해
- 함수 오버로딩과 디폴트 매개변수 활용
- 배열의 선언과 초기화 방법 학습
- 문자열 처리와 표준 라이브러리 string 활용
- 다차원 배열과 배열 알고리즘 구현

---

## 1. 예제 01: 함수 기초 (01_function_basic.cpp)

### 예제 정의
함수의 기본적인 선언, 정의, 호출 방법을 학습합니다.

```cpp
/*
주제: 함수 (Function)
정의: 특정 작업을 수행하는 코드 블록으로, 재사용 가능하고 모듈화된 프로그램 구성 요소

핵심 개념: 함수 선언, 함수 정의, 함수 호출, 반환값
정의:
- 함수 선언: 함수의 이름, 매개변수, 반환 타입을 컴파일러에게 알리는 것
- 함수 정의: 함수가 실제로 수행할 작업을 구현하는 것
- 함수 호출: 정의된 함수를 실행하는 것
- 반환값: 함수가 처리 결과로 돌려주는 값
*/

#include <iostream>
using namespace std;

// 함수 선언
int add(int a, int b);
void greet();

int main() {
    // 함수 호출
    greet();
    
    int result = add(5, 3);
    cout << "5 + 3 = " << result << endl;
    
    return 0;
}

// 함수 정의
int add(int a, int b) {
    return a + b;
}

void greet() {
    cout << "안녕하세요! 함수를 배워봅시다." << endl;
}
```

---

## 2. 예제 02: 반환값과 void 함수 (02_return_values.cpp)

### 예제 정의
반환값이 있는 함수와 없는 함수의 차이점을 학습합니다.

```cpp
/*
주제: 함수 반환값 (Function Return Value)
정의: 함수가 작업을 완료한 후 호출자에게 돌려주는 결과값

핵심 개념: return문, void 함수, 반환 타입
정의:
- return문: 함수에서 값을 반환하고 함수 실행을 종료하는 키워드
- void 함수: 반환값이 없는 함수 (출력이나 상태 변경만 수행)
- 반환 타입: 함수가 반환할 데이터의 타입 (int, double, bool 등)
*/

#include <iostream>
using namespace std;

// 반환값이 있는 함수
double calculateArea(double radius) {
    return 3.14159 * radius * radius;
}

// 반환값이 없는 함수
void printResult(double area) {
    cout << "원의 넓이: " << area << endl;
}

// bool 반환 함수
bool isEven(int number) {
    return number % 2 == 0;
}

int main() {
    double radius = 5.0;
    double area = calculateArea(radius);
    
    printResult(area);
    
    int num = 8;
    if (isEven(num)) {
        cout << num << "은 짝수입니다." << endl;
    }
    
    return 0;
}
```

---

## 3. 예제 03: 매개변수 전달 - 값 전달 (03_parameter_by_value.cpp)

### 예제 정의
값에 의한 매개변수 전달 방식을 학습합니다.

```cpp
/*
주제: 매개변수 전달 방식 (Parameter Passing)
정의: 함수 호출 시 인수를 매개변수로 전달하는 방법

핵심 개념: 값 전달, 복사본, 원본 보존
정의:
- 값 전달: 인수의 값을 복사하여 매개변수에 전달하는 방식
- 복사본: 원본과 별개의 메모리에 저장된 값의 사본
- 원본 보존: 함수 내에서 매개변수를 변경해도 원본은 영향받지 않음
*/

#include <iostream>
using namespace std;

void changeValue(int x) {
    cout << "함수 내 x 변경 전: " << x << endl;
    x = 100;
    cout << "함수 내 x 변경 후: " << x << endl;
}

void doubleValue(int num) {
    num = num * 2;
    cout << "함수 내에서 두 배: " << num << endl;
}

int main() {
    int original = 42;
    
    cout << "원본 값: " << original << endl;
    changeValue(original);
    cout << "함수 호출 후 원본: " << original << endl;
    
    cout << "\n--- 또 다른 예제 ---" << endl;
    int number = 5;
    cout << "원본: " << number << endl;
    doubleValue(number);
    cout << "함수 호출 후: " << number << endl;
    
    return 0;
}
```

---

## 4. 예제 04: 매개변수 전달 - 참조 전달 (04_parameter_by_reference.cpp)

### 예제 정의
참조에 의한 매개변수 전달 방식을 학습합니다.

```cpp
/*
주제: 참조 전달 (Pass by Reference)
정의: 매개변수로 변수의 참조(별명)를 전달하여 원본 변수를 직접 조작하는 방식

핵심 개념: 참조 매개변수, 원본 변경, 메모리 효율성
정의:
- 참조 매개변수: &를 사용하여 선언된 매개변수로 원본의 별명 역할
- 원본 변경: 함수 내에서 매개변수 변경 시 원본도 함께 변경됨
- 메모리 효율성: 복사본을 만들지 않아 메모리와 시간을 절약
*/

#include <iostream>
using namespace std;

void changeByReference(int& x) {
    cout << "함수 내 x 변경 전: " << x << endl;
    x = 100;
    cout << "함수 내 x 변경 후: " << x << endl;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int original = 42;
    
    cout << "원본 값: " << original << endl;
    changeByReference(original);
    cout << "함수 호출 후 원본: " << original << endl;
    
    cout << "\n--- 두 변수 교환 ---" << endl;
    int x = 10, y = 20;
    cout << "교환 전: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "교환 후: x=" << x << ", y=" << y << endl;
    
    return 0;
}
```

---

## 5. 예제 05: 매개변수 전달 - 포인터 전달 (05_parameter_by_pointer.cpp)

### 예제 정의
포인터에 의한 매개변수 전달 방식을 학습합니다.

```cpp
/*
주제: 포인터 전달 (Pass by Pointer)
정의: 매개변수로 변수의 주소를 전달하여 간접적으로 원본 변수에 접근하는 방식

핵심 개념: 포인터 매개변수, 역참조, 주소 전달
정의:
- 포인터 매개변수: *를 사용하여 선언된 매개변수로 주소값을 받음
- 역참조: *연산자를 사용하여 포인터가 가리키는 값에 접근
- 주소 전달: &연산자로 변수의 주소를 함수에 전달
*/

#include <iostream>
using namespace std;

void changeByPointer(int* x) {
    cout << "함수 내 *x 변경 전: " << *x << endl;
    *x = 100;
    cout << "함수 내 *x 변경 후: " << *x << endl;
}

void multiply(int* a, int* b, int* result) {
    *result = (*a) * (*b);
}

int main() {
    int original = 42;
    
    cout << "원본 값: " << original << endl;
    changeByPointer(&original);
    cout << "함수 호출 후 원본: " << original << endl;
    
    cout << "\n--- 곱셈 결과 ---" << endl;
    int num1 = 6, num2 = 7, product;
    multiply(&num1, &num2, &product);
    cout << num1 << " x " << num2 << " = " << product << endl;
    
    return 0;
}
```

---

## 6. 예제 06: 함수 오버로딩 (06_function_overloading.cpp)

### 예제 정의
같은 이름의 함수를 다른 매개변수로 정의하는 함수 오버로딩을 학습합니다.

```cpp
/*
주제: 함수 오버로딩 (Function Overloading)
정의: 같은 이름의 함수를 매개변수의 개수나 타입을 다르게 하여 여러 개 정의하는 기능

핵심 개념: 오버로딩, 함수 시그니처, 컴파일 타임 결정
정의:
- 오버로딩: 같은 이름의 함수를 다양한 형태로 정의하는 것
- 함수 시그니처: 함수명과 매개변수 목록으로 함수를 구분하는 정보
- 컴파일 타임 결정: 컴파일 시점에 어떤 함수를 호출할지 결정됨
*/

#include <iostream>
using namespace std;

// 정수 덧셈
int add(int a, int b) {
    cout << "정수 덧셈: ";
    return a + b;
}

// 실수 덧셈
double add(double a, double b) {
    cout << "실수 덧셈: ";
    return a + b;
}

// 세 개 정수 덧셈
int add(int a, int b, int c) {
    cout << "세 정수 덧셈: ";
    return a + b + c;
}

int main() {
    cout << add(3, 4) << endl;           // 정수 버전 호출
    cout << add(3.5, 4.2) << endl;      // 실수 버전 호출
    cout << add(1, 2, 3) << endl;       // 세 매개변수 버전 호출
    
    return 0;
}
```

---

## 7. 예제 07: 디폴트 매개변수 (07_default_parameters.cpp)

### 예제 정의
매개변수에 기본값을 설정하는 디폴트 매개변수를 학습합니다.

```cpp
/*
주제: 디폴트 매개변수 (Default Parameters)
정의: 함수 선언 시 매개변수에 기본값을 설정하여, 호출 시 인수가 생략되면 기본값을 사용하는 기능

핵심 개념: 기본값, 매개변수 생략, 오른쪽부터 설정
정의:
- 기본값: 인수가 전달되지 않을 때 사용되는 미리 정의된 값
- 매개변수 생략: 디폴트값이 있는 매개변수는 호출 시 생략 가능
- 오른쪽부터 설정: 디폴트 매개변수는 매개변수 목록의 오른쪽부터 설정해야 함
*/

#include <iostream>
using namespace std;

// 디폴트 매개변수가 있는 함수
void printMessage(string message, int count = 1, char separator = '-') {
    for (int i = 0; i < count; i++) {
        cout << message;
        if (i < count - 1) {
            cout << separator;
        }
    }
    cout << endl;
}

// 원의 넓이 계산 (pi 값 디폴트)
double calculateCircleArea(double radius, double pi = 3.14159) {
    return pi * radius * radius;
}

int main() {
    // 다양한 방식으로 함수 호출
    printMessage("Hello");                    // count=1, separator='-'
    printMessage("Hi", 3);                    // separator='-'
    printMessage("Test", 2, '*');             // 모든 매개변수 지정
    
    cout << "\n원의 넓이:" << endl;
    cout << "반지름 5 (기본 pi): " << calculateCircleArea(5) << endl;
    cout << "반지름 5 (정확한 pi): " << calculateCircleArea(5, 3.141592653589793) << endl;
    
    return 0;
}
```

---

## 8. 예제 08: 배열 기초 (08_array_basic.cpp)

### 예제 정의
배열의 선언, 초기화, 접근 방법을 학습합니다.

```cpp
/*
주제: 배열 (Array)
정의: 같은 타입의 여러 데이터를 연속된 메모리 공간에 저장하는 자료구조

핵심 개념: 배열 선언, 인덱스, 초기화, 크기
정의:
- 배열 선언: 타입과 크기를 지정하여 연속된 메모리 공간 할당
- 인덱스: 배열 요소에 접근하기 위한 위치 번호 (0부터 시작)
- 초기화: 배열 선언과 동시에 값을 설정하는 것
- 크기: 배열이 저장할 수 있는 요소의 개수
*/

#include <iostream>
using namespace std;

int main() {
    // 다양한 배열 선언과 초기화
    int numbers[5] = {10, 20, 30, 40, 50};
    int scores[] = {85, 90, 78, 92, 88};  // 크기 자동 결정
    double temperatures[3] = {25.5, 28.0, 22.3};
    
    // 배열 요소 출력
    cout << "numbers 배열:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }
    
    // 배열 요소 변경
    cout << "\nscores 배열 변경 전:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    
    scores[2] = 95;  // 세 번째 요소 변경
    cout << "\nscores 배열 변경 후:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

---

## 9. 예제 09: 배열과 반복문 (09_array_loops.cpp)

### 예제 정의
배열과 반복문을 함께 사용하는 다양한 방법을 학습합니다.

```cpp
/*
주제: 배열과 반복문 (Array with Loops)
정의: 배열의 모든 요소에 대해 반복적인 작업을 수행하는 프로그래밍 패턴

핵심 개념: for 루프, 범위 기반 for, 배열 순회
정의:
- for 루프: 인덱스를 사용하여 배열 요소에 순차적으로 접근
- 범위 기반 for: C++11의 기능으로 배열 요소를 직접 순회
- 배열 순회: 배열의 모든 요소를 차례대로 방문하는 것
*/

#include <iostream>
using namespace std;

int main() {
    int numbers[] = {2, 4, 6, 8, 10};
    int size = 5;
    
    // 일반 for 루프로 출력
    cout << "일반 for 루프:" << endl;
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // 범위 기반 for 루프로 출력 (C++11)
    cout << "범위 기반 for 루프:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 배열 요소의 합 계산
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    cout << "합계: " << sum << endl;
    
    // 최대값 찾기
    int max = numbers[0];
    for (int i = 1; i < size; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    cout << "최대값: " << max << endl;
    
    return 0;
}
```

---

## 10. 예제 10: 배열과 함수 (10_array_functions.cpp)

### 예제 정의
배열을 함수의 매개변수로 전달하고 처리하는 방법을 학습합니다.

```cpp
/*
주제: 배열과 함수 (Array and Functions)
정의: 배열을 함수에 전달하여 처리하는 방법과 그 특성

핵심 개념: 배열 매개변수, 포인터 전달, 크기 정보
정의:
- 배열 매개변수: 배열을 함수의 매개변수로 받는 방식
- 포인터 전달: 배열명은 첫 번째 요소의 주소로 전달됨
- 크기 정보: 배열 크기는 별도로 전달해야 함 (sizeof 사용 불가)
*/

#include <iostream>
using namespace std;

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 배열 요소 합계 계산
int calculateSum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 배열 요소를 2배로 증가
void doubleArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    cout << "원본 배열: ";
    printArray(numbers, size);
    
    cout << "합계: " << calculateSum(numbers, size) << endl;
    
    doubleArray(numbers, size);
    cout << "2배 증가 후: ";
    printArray(numbers, size);
    
    return 0;
}
```

---

## 11. 예제 11: 문자 배열과 C 스타일 문자열 (11_c_string.cpp)

### 예제 정의
C 스타일 문자열의 기본 사용법을 학습합니다.

```cpp
/*
주제: C 스타일 문자열 (C-style String)
정의: null 문자('\0')로 끝나는 문자 배열로 구현된 전통적인 문자열 표현 방식

핵심 개념: 문자 배열, null 종료, 문자열 리터럴
정의:
- 문자 배열: char 타입 요소들로 구성된 배열
- null 종료: 문자열의 끝을 나타내는 '\0' 문자
- 문자열 리터럴: 큰따옴표로 둘러싸인 문자 시퀀스
*/

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // C 스타일 문자열 선언
    char greeting[] = "Hello";
    char name[20] = "World";
    char message[50];
    
    cout << "인사말: " << greeting << endl;
    cout << "이름: " << name << endl;
    
    // 문자열 복사
    strcpy(message, greeting);
    cout << "복사된 메시지: " << message << endl;
    
    // 문자열 연결
    strcat(message, " ");
    strcat(message, name);
    cout << "연결된 메시지: " << message << endl;
    
    // 문자열 길이
    cout << "메시지 길이: " << strlen(message) << endl;
    
    // 문자열 비교
    if (strcmp(greeting, "Hello") == 0) {
        cout << "문자열이 일치합니다." << endl;
    }
    
    return 0;
}
```

---

## 12. 예제 12: C++ string 클래스 (12_cpp_string.cpp)

### 예제 정의
C++ 표준 라이브러리의 string 클래스 사용법을 학습합니다.

```cpp
/*
주제: C++ string 클래스 (C++ String Class)
정의: C++ 표준 라이브러리에서 제공하는 문자열 처리를 위한 클래스

핵심 개념: string 객체, 메서드, 연산자 오버로딩
정의:
- string 객체: 문자열을 저장하고 조작할 수 있는 객체
- 메서드: string 클래스에서 제공하는 멤버 함수들
- 연산자 오버로딩: +, ==, [] 등의 연산자를 string에서 사용 가능
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    // string 객체 생성과 초기화
    string greeting = "Hello";
    string name("World");
    string message;
    
    cout << "인사말: " << greeting << endl;
    cout << "이름: " << name << endl;
    
    // 문자열 연결 (+ 연산자)
    message = greeting + " " + name + "!";
    cout << "연결된 메시지: " << message << endl;
    
    // 문자열 길이
    cout << "메시지 길이: " << message.length() << endl;
    
    // 문자열 부분 추출
    string sub = message.substr(6, 5);  // 6번째부터 5글자
    cout << "부분 문자열: " << sub << endl;
    
    // 문자열 찾기
    size_t pos = message.find("World");
    if (pos != string::npos) {
        cout << "'World'를 " << pos << "번째 위치에서 발견" << endl;
    }
    
    return 0;
}
```

---

## 13. 예제 13: 문자열 입력과 처리 (13_string_input.cpp)

### 예제 정의
다양한 문자열 입력 방법과 처리 기법을 학습합니다.

```cpp
/*
주제: 문자열 입력과 처리 (String Input and Processing)
정의: 사용자로부터 문자열을 입력받고 다양한 방식으로 처리하는 기법

핵심 개념: getline, 공백 처리, 문자열 조작
정의:
- getline: 공백을 포함한 한 줄 전체를 입력받는 함수
- 공백 처리: 문자열에서 공백 문자를 다루는 방법
- 문자열 조작: 문자열의 내용을 변경하거나 분석하는 작업
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    string fullName;
    string sentence;
    
    cout << "전체 이름을 입력하세요: ";
    getline(cin, fullName);
    
    cout << "한 문장을 입력하세요: ";
    getline(cin, sentence);
    
    cout << "\n=== 입력 결과 ===" << endl;
    cout << "이름: " << fullName << endl;
    cout << "문장: " << sentence << endl;
    
    // 문자열 분석
    cout << "\n=== 문자열 분석 ===" << endl;
    cout << "이름 길이: " << fullName.length() << "글자" << endl;
    cout << "문장 길이: " << sentence.length() << "글자" << endl;
    
    // 특정 문자 개수 세기
    int spaceCount = 0;
    for (char c : sentence) {
        if (c == ' ') {
            spaceCount++;
        }
    }
    cout << "문장의 공백 개수: " << spaceCount << "개" << endl;
    
    // 대문자로 변환
    string upperSentence = sentence;
    for (char& c : upperSentence) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
    }
    cout << "대문자 변환: " << upperSentence << endl;
    
    return 0;
}
```

---

## 14. 예제 14: 2차원 배열 기초 (14_2d_array_basic.cpp)

### 예제 정의
2차원 배열의 선언, 초기화, 접근 방법을 학습합니다.

```cpp
/*
주제: 2차원 배열 (Two-Dimensional Array)
정의: 행과 열의 2차원 구조로 데이터를 저장하는 배열

핵심 개념: 행과 열, 이중 인덱스, 중첩 루프
정의:
- 행과 열: 2차원 배열의 세로(행)와 가로(열) 구조
- 이중 인덱스: 2차원 배열 요소에 접근하기 위한 [행][열] 형태의 인덱스
- 중첩 루프: 2차원 배열을 순회하기 위한 이중 반복문
*/

#include <iostream>
using namespace std;

int main() {
    // 2차원 배열 선언과 초기화
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    int scores[2][3] = {{85, 90, 78}, {92, 88, 95}};
    
    // 2차원 배열 출력
    cout << "매트릭스:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 점수 출력
    cout << "\n학생별 점수:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "학생 " << (i + 1) << ": ";
        for (int j = 0; j < 3; j++) {
            cout << scores[i][j] << " ";
        }
        cout << endl;
    }
    
    // 특정 요소 변경
    matrix[1][2] = 100;
    cout << "\nmatrix[1][2] 변경 후: " << matrix[1][2] << endl;
    
    return 0;
}
```

---

## 15. 예제 15: 2차원 배열과 함수 (15_2d_array_functions.cpp)

### 예제 정의
2차원 배열을 함수에 전달하고 처리하는 방법을 학습합니다.

```cpp
/*
주제: 2차원 배열과 함수 (2D Array with Functions)
정의: 2차원 배열을 함수의 매개변수로 전달하여 처리하는 방법

핵심 개념: 배열 매개변수, 열 크기 고정, 포인터 배열
정의:
- 배열 매개변수: 2차원 배열을 함수에 전달하는 방식
- 열 크기 고정: 2차원 배열 전달 시 열의 크기는 반드시 명시
- 포인터 배열: 배열의 이름은 첫 번째 행의 주소를 나타냄
*/

#include <iostream>
using namespace std;

// 2차원 배열 출력 함수
void printMatrix(int arr[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

// 2차원 배열의 합 계산
int calculateSum(int arr[][3], int rows) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            sum += arr[i][j];
        }
    }
    return sum;
}

// 각 행의 평균 계산
void calculateRowAverages(int arr[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += arr[i][j];
        }
        double average = static_cast<double>(sum) / 3;
        cout << "행 " << i << " 평균: " << average << endl;
    }
}

int main() {
    int scores[2][3] = {{85, 90, 78}, {92, 88, 95}};
    
    cout << "점수 행렬:" << endl;
    printMatrix(scores, 2);
    
    cout << "\n전체 합계: " << calculateSum(scores, 2) << endl;
    
    cout << "\n행별 평균:" << endl;
    calculateRowAverages(scores, 2);
    
    return 0;
}
```

---

## 16. 예제 16: 배열 정렬 - 버블 정렬 (16_bubble_sort.cpp)
![버블정렬](https://github.com/user-attachments/assets/fa60f87f-ebee-401c-9760-b659d2cb91b2)

### 예제 정의
버블 정렬 알고리즘을 구현하여 배열을 정렬합니다.

```cpp
/*
주제: 정렬 알고리즘 (Sorting Algorithm)
정의: 배열의 요소들을 특정 순서(오름차순 또는 내림차순)로 재배열하는 알고리즘

핵심 개념: 버블 정렬, 요소 교환, 시간 복잡도
정의:
- 버블 정렬: 인접한 두 요소를 비교하여 교환하는 단순한 정렬 알고리즘
- 요소 교환: 두 배열 요소의 위치를 바꾸는 연산
- 시간 복잡도: 알고리즘의 실행 시간이 입력 크기에 따라 증가하는 정도
*/

#include <iostream>
using namespace std;

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 버블 정렬 함수
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // 요소 교환
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;
    
    cout << "정렬 전 배열: ";
    printArray(numbers, size);
    
    bubbleSort(numbers, size);
    
    cout << "정렬 후 배열: ";
    printArray(numbers, size);
    
    return 0;
}
```

---

## 17. 예제 17: 배열 검색 - 선형 검색 (17_linear_search.cpp)
![선형검색](https://github.com/user-attachments/assets/d1f147c9-57a9-49e8-8183-caa279763d56)

### 예제 정의
선형 검색 알고리즘을 구현하여 배열에서 특정 값을 찾습니다.

```cpp
/*
주제: 검색 알고리즘 (Search Algorithm)
정의: 배열이나 데이터 구조에서 특정 값을 찾는 알고리즘

핵심 개념: 선형 검색, 순차 탐색, 인덱스 반환
정의:
- 선형 검색: 배열의 처음부터 끝까지 순차적으로 탐색하는 알고리즘
- 순차 탐색: 요소를 하나씩 차례대로 확인하는 탐색 방법
- 인덱스 반환: 찾은 요소의 위치를 반환하거나 못 찾으면 -1 반환
*/

#include <iostream>
using namespace std;

// 선형 검색 함수
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // 찾은 인덱스 반환
        }
    }
    return -1;  // 못 찾으면 -1 반환
}

// 배열에서 특정 값의 개수 세기
int countOccurrences(int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}

int main() {
    int numbers[] = {10, 25, 30, 25, 40, 55, 25};
    int size = 7;
    
    int target = 25;
    
    cout << "배열: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    int index = linearSearch(numbers, size, target);
    if (index != -1) {
        cout << target << "을(를) 인덱스 " << index << "에서 발견" << endl;
    } else {
        cout << target << "을(를) 찾을 수 없습니다." << endl;
    }
    
    int count = countOccurrences(numbers, size, target);
    cout << target << "의 개수: " << count << "개" << endl;
    
    return 0;
}
```

---

## 18. 예제 18: 배열 통계 계산 (18_array_statistics.cpp)

### 예제 정의
배열의 다양한 통계 정보를 계산하는 함수들을 구현합니다.

```cpp
/*
주제: 배열 통계 (Array Statistics)
정의: 배열 데이터에서 의미 있는 수치 정보를 계산하는 과정

핵심 개념: 평균, 최대값, 최소값, 표준편차
정의:
- 평균: 모든 요소의 합을 요소 개수로 나눈 값
- 최대값: 배열에서 가장 큰 값
- 최소값: 배열에서 가장 작은 값
- 표준편차: 데이터의 분산 정도를 나타내는 통계 지표
*/

#include <iostream>
#include <cmath>
using namespace std;

// 평균 계산
double calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return static_cast<double>(sum) / size;
}

// 최대값 찾기
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 최소값 찾기
int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int scores[] = {85, 92, 78, 96, 88, 91, 83, 89};
    int size = 8;
    
    cout << "점수: ";
    for (int i = 0; i < size; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;
    
    double average = calculateAverage(scores, size);
    int maxScore = findMax(scores, size);
    int minScore = findMin(scores, size);
    
    cout << "\n=== 통계 정보 ===" << endl;
    cout << "평균: " << average << endl;
    cout << "최고점: " << maxScore << endl;
    cout << "최저점: " << minScore << endl;
    cout << "점수 범위: " << (maxScore - minScore) << endl;
    
    return 0;
}
```

---

## 19. 예제 19: 동적 배열 (19_dynamic_array.cpp)

### 예제 정의
동적 메모리 할당을 사용하여 실행 시간에 크기가 결정되는 배열을 생성합니다.

```cpp
/*
주제: 동적 배열 (Dynamic Array)
정의: 프로그램 실행 중에 크기가 결정되고 힙 메모리에 할당되는 배열

핵심 개념: new[], delete[], 런타임 크기 결정
정의:
- new[]: 동적 배열을 힙 메모리에 할당하는 연산자
- delete[]: 동적 배열의 메모리를 해제하는 연산자
- 런타임 크기 결정: 프로그램 실행 중에 사용자 입력으로 배열 크기 결정
*/

#include <iostream>
using namespace std;

int main() {
    int size;
    cout << "배열 크기를 입력하세요: ";
    cin >> size;
    
    // 동적 배열 할당
    int* numbers = new int[size];
    
    // 배열 요소 입력
    cout << size << "개의 정수를 입력하세요:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "numbers[" << i << "]: ";
        cin >> numbers[i];
    }
    
    // 배열 내용 출력
    cout << "\n입력된 배열:" << endl;
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // 합계와 평균 계산
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    double average = static_cast<double>(sum) / size;
    
    cout << "\n합계: " << sum << endl;
    cout << "평균: " << average << endl;
    
    // 메모리 해제
    delete[] numbers;
    cout << "\n메모리 해제 완료" << endl;
    
    return 0;
}
```

---

## 20. 예제 20: 종합 실습 - 학생 성적 관리 (20_grade_management.cpp)

### 예제 정의
지금까지 학습한 함수와 배열 개념을 종합하여 학생 성적 관리 프로그램을 작성합니다.

```cpp
/*
주제: 종합 프로젝트 (Comprehensive Project)
정의: 함수와 배열의 모든 개념을 통합하여 실제 문제를 해결하는 프로그램

핵심 개념: 모듈화, 함수 분리, 배열 처리, 메뉴 시스템
정의:
- 모듈화: 프로그램을 기능별로 나누어 함수로 구현
- 함수 분리: 각 기능을 독립적인 함수로 분리하여 재사용성 향상
- 배열 처리: 여러 데이터를 효율적으로 관리하는 방법
- 메뉴 시스템: 사용자가 원하는 기능을 선택할 수 있는 인터페이스
*/

#include <iostream>
#include <string>
using namespace std;

// 전역 상수
const int MAX_STUDENTS = 10;

// 함수 선언
void printMenu();
void inputGrades(int grades[], int& count);
void printGrades(int grades[], int count);
double calculateAverage(int grades[], int count);
int findHighest(int grades[], int count);
int findLowest(int grades[], int count);

int main() {
    int grades[MAX_STUDENTS];
    int studentCount = 0;
    int choice;
    
    do {
        printMenu();
        cout << "선택: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                inputGrades(grades, studentCount);
                break;
            case 2:
                printGrades(grades, studentCount);
                break;
            case 3:
                if (studentCount > 0) {
                    cout << "평균: " << calculateAverage(grades, studentCount) << endl;
                    cout << "최고점: " << findHighest(grades, studentCount) << endl;
                    cout << "최저점: " << findLowest(grades, studentCount) << endl;
                } else {
                    cout << "입력된 성적이 없습니다." << endl;
                }
                break;
            case 4:
                cout << "프로그램을 종료합니다." << endl;
                break;
            default:
                cout << "잘못된 선택입니다." << endl;
        }
        cout << endl;
    } while (choice != 4);
    
    return 0;
}

// 메뉴 출력
void printMenu() {
    cout << "=== 학생 성적 관리 ===" << endl;
    cout << "1. 성적 입력" << endl;
    cout << "2. 성적 출력" << endl;
    cout << "3. 통계 보기" << endl;
    cout << "4. 종료" << endl;
}

// 성적 입력
void inputGrades(int grades[], int& count) {
    cout << "학생 수를 입력하세요 (최대 " << MAX_STUDENTS << "명): ";
    cin >> count;
    
    if (count > MAX_STUDENTS) {
        count = MAX_STUDENTS;
        cout << "최대 " << MAX_STUDENTS << "명으로 제한됩니다." << endl;
    }
    
    for (int i = 0; i < count; i++) {
        cout << (i + 1) << "번 학생 성적: ";
        cin >> grades[i];
    }
    cout << "성적 입력 완료!" << endl;
}

// 성적 출력
void printGrades(int grades[], int count) {
    if (count == 0) {
        cout << "입력된 성적이 없습니다." << endl;
        return;
    }
    
    cout << "학생별 성적:" << endl;
    for (int i = 0; i < count; i++) {
        cout << (i + 1) << "번 학생: " << grades[i] << "점" << endl;
    }
}

// 평균 계산
double calculateAverage(int grades[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += grades[i];
    }
    return static_cast<double>(sum) / count;
}

// 최고점 찾기
int findHighest(int grades[], int count) {
    int highest = grades[0];
    for (int i = 1; i < count; i++) {
        if (grades[i] > highest) {
            highest = grades[i];
        }
    }
    return highest;
}

// 최저점 찾기
int findLowest(int grades[], int count) {
    int lowest = grades[0];
    for (int i = 1; i < count; i++) {
        if (grades[i] < lowest) {
            lowest = grades[i];
        }
    }
    return lowest;
}
```

---

## 이번 챕터 요약

### 학습한 내용
**함수**: 선언, 정의, 호출, 반환값, 매개변수 전달 방식
**함수 고급**: 오버로딩, 디폴트 매개변수
**배열**: 1차원, 2차원 배열, 배열과 함수
**문자열**: C 스타일 문자열, C++ string 클래스
**알고리즘**: 정렬, 검색, 통계 계산

### 핵심 키워드
- 함수: `return`, `void`, 매개변수, 인수
- 배열: `[]`, 인덱스, 초기화, 크기
- 문자열: `char[]`, `string`, `strcpy`, `strlen`
- 전달 방식: 값 전달, 참조 전달, 포인터 전달

---

## 실습 과제

### 과제 1: 계산기 함수
사칙연산을 수행하는 함수들을 만들고 메뉴 기반으로 동작하는 계산기 프로그램 작성

### 과제 2: 배열 정렬 프로그램
선택 정렬이나 삽입 정렬 알고리즘을 구현하여 배열을 정렬하는 프로그램 작성

### 과제 3: 단어 카운터
문자열을 입력받아 단어 개수, 문자 개수, 특정 문자 개수를 세는 프로그램 작성

### 과제 4: 행렬 계산기
두 2차원 배열의 덧셈, 뺄셈, 곱셈을 수행하는 함수들을 구현

---

## 다음 챕터 예고
**Chapter 04: 클래스와 객체지향 I**에서는 C++의 핵심인 객체지향 프로그래밍의 기초를 학습합니다.
