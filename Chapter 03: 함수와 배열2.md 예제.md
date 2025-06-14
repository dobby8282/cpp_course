# C++ 함수와 배열 핵심 문법 예제 10선

새로운 문법과 반드시 알아야 할 핵심 개념 중심으로 선별한 필수 예제들입니다.

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

## 학습 목표
- 함수의 선언과 정의 방법 습득
- 다양한 매개변수 전달 방식 이해 (값, 참조, 포인터)
- 함수 오버로딩과 디폴트 매개변수 활용
- 배열의 선언과 초기화 방법 학습
- 배열과 함수의 연동 방법 마스터
- 범위 기반 for문 등 C++11 기능 활용

---

## 핵심 키워드
- 함수: `return`, `void`, 매개변수, 인수, 오버로딩
- 전달 방식: 값 전달, 참조 전달(`&`), 포인터 전달(`*`)
- 배열: `[]`, 인덱스, 초기화, 크기
- C++11: 범위 기반 for문, 디폴트 매개변수

---

## 다음 단계
이 10개 예제를 통해 C++ 함수와 배열의 핵심 문법을 완전히 이해한 후, 객체지향 프로그래밍으로 진행하시기 바랍니다.
