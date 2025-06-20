/*
 * 변수 초기화 방법
 * 파일명: 02_variable_initialization.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 02_variable_initialization 02_variable_initialization.cpp
 * 실행: ./02_variable_initialization (Linux/Mac) 또는 02_variable_initialization.exe (Windows)
 */

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