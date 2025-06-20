/*
 * 산술 연산자
 * 파일명: 03_arithmetic_operators.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 03_arithmetic_operators 03_arithmetic_operators.cpp
 * 실행: ./03_arithmetic_operators (Linux/Mac) 또는 03_arithmetic_operators.exe (Windows)
 */

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