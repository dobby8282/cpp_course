/*
 * 함수 오버로딩
 * 파일명: 06_function_overloading.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 06_function_overloading 06_function_overloading.cpp
 * 실행: ./06_function_overloading (Linux/Mac) 또는 06_function_overloading.exe (Windows)
 */

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