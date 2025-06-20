/*
 * 논리 연산자
 * 파일명: 06_logical_operators.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 06_logical_operators 06_logical_operators.cpp
 * 실행: ./06_logical_operators (Linux/Mac) 또는 06_logical_operators.exe (Windows)
 */

/*
주제: 논리 연산자 (Logical Operators)
정의: 논리값(true/false)들을 조합하여 복합적인 조건을 만드는 연산자

핵심 개념: &&, ||, !, 단락 평가
정의:
- && (논리 AND): 두 조건이 모두 참일 때만 참을 반환하는 연산자
- || (논리 OR): 두 조건 중 하나라도 참이면 참을 반환하는 연산자  
- ! (논리 NOT): 논리값을 반대로 바꾸는 단항 연산자
- 단락 평가: 결과가 확정되면 나머지 조건을 평가하지 않는 최적화 기법
*/

#include <iostream>
using namespace std;

int main() {
    bool a = true, b = false;

    cout << "a = " << a << ", b = " << b << endl;
    cout << "a && b: " << (a && b) << endl;  // AND
    cout << "a || b: " << (a || b) << endl;  // OR
    cout << "!a: " << (!a) << endl;          // NOT

    // 실용적 예제
    int age = 25;
    bool hasLicense = true;

    if (age >= 18 && hasLicense) {
        cout << "운전 가능" << endl;
    } else {
        cout << "운전 불가능" << endl;
    }

    return 0;
}