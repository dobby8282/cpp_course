/*
 * 기본 데이터 타입
 * 파일명: 01_basic_datatypes.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 01_basic_datatypes 01_basic_datatypes.cpp
 * 실행: ./01_basic_datatypes (Linux/Mac) 또는 01_basic_datatypes.exe (Windows)
 */

/*
주제: 데이터 타입 (Data Types)
정의: 프로그램에서 사용할 수 있는 값의 종류와 그 값들이 메모리에서 차지하는 공간을 정의하는 분류 체계

핵심 개념: sizeof 연산자, 기본 데이터 타입
정의: 
- sizeof: 데이터 타입이나 변수가 메모리에서 차지하는 바이트 수를 반환하는 연산자
- 기본 데이터 타입: C++에서 미리 정의된 데이터 종류 (char, int, float, double, bool 등)
*/

#include <iostream>
using namespace std;

int main() {
    // 기본 데이터 타입들
    char ch = 'A';
    int num = 42;
    float f = 3.14f;
    double d = 3.14159;
    bool flag = true;

    cout << "=== 데이터 타입 크기 ===" << endl;
    cout << "char: " << sizeof(char) << "바이트, 값: " << ch << endl;
    cout << "int: " << sizeof(int) << "바이트, 값: " << num << endl;
    cout << "float: " << sizeof(float) << "바이트, 값: " << f << endl;
    cout << "double: " << sizeof(double) << "바이트, 값: " << d << endl;
    cout << "bool: " << sizeof(bool) << "바이트, 값: " << flag << endl;

    return 0;
}