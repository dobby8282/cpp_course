/*
 * 비교 연산자
 * 파일명: 05_comparison_operators.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 05_comparison_operators 05_comparison_operators.cpp
 * 실행: ./05_comparison_operators (Linux/Mac) 또는 05_comparison_operators.exe (Windows)
 */

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