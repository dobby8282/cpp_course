/*
 * 입출력 기초
 * 파일명: 04_input_output_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 04_input_output_basic 04_input_output_basic.cpp
 * 실행: ./04_input_output_basic (Linux/Mac) 또는 04_input_output_basic.exe (Windows)
 */

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