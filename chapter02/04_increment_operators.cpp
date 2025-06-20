/*
 * 증감 연산자
 * 파일명: 04_increment_operators.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 04_increment_operators 04_increment_operators.cpp
 * 실행: ./04_increment_operators (Linux/Mac) 또는 04_increment_operators.exe (Windows)
 */

/*
주제: 증감 연산자 (Increment/Decrement Operators)  
정의: 변수의 값을 1씩 증가시키거나 감소시키는 단항 연산자

핵심 개념: ++, --, 전위 연산자, 후위 연산자
정의:
- ++ (증가 연산자): 변수의 값을 1 증가시키는 연산자
- -- (감소 연산자): 변수의 값을 1 감소시키는 연산자
- 전위 연산자: 변수 앞에 위치하여 먼저 증감 후 값을 반환 (++x, --x)
- 후위 연산자: 변수 뒤에 위치하여 현재 값을 반환한 후 증감 (x++, x--)
*/

#include <iostream>
using namespace std;

int main() {
    int x = 5;

    cout << "초기 x = " << x << endl;
    cout << "++x = " << (++x) << ", x = " << x << endl;  // 전위: 먼저 증가

    x = 5;  // 초기화
    cout << "x++ = " << (x++) << ", x = " << x << endl;  // 후위: 나중에 증가

    cout << "--x = " << (--x) << ", x = " << x << endl;  // 전위 감소

    return 0;
}