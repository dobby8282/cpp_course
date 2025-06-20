/*
 * 다중 데이터 출력
 * 파일명: 05_multiple_output.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 05_multiple_output 05_multiple_output.cpp
 * 실행: ./05_multiple_output (Linux/Mac) 또는 05_multiple_output.exe (Windows)
 */

/*
주제: 출력 서식 제어 (Output Formatting)
정의: 데이터를 원하는 형태로 정렬하고 표현하기 위한 출력 제어 기법

핵심 개념: 스트림 체이닝, setprecision, fixed, 진법 변환
정의:
- 스트림 체이닝: << 연산자를 연속으로 사용하여 여러 데이터를 한 번에 출력하는 기법
- setprecision: 부동소수점 수의 정밀도를 설정하는 조작자
- fixed: 고정소수점 표기법을 사용하도록 설정하는 조작자
- 진법 변환: hex(16진법), oct(8진법), dec(10진법) 조작자를 사용한 수 표현
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi = 3.14159265359;
    int number = 42;
    string language = "C++";

    // 체이닝을 통한 연속 출력
    cout << "언어: " << language 
         << ", 숫자: " << number 
         << ", 원주율: " << pi << endl;

    // 서식 지정
    cout << fixed << setprecision(2);
    cout << "원주율 (소수점 2자리): " << pi << endl;

    cout << "16진수: " << hex << number << endl;
    cout << "8진수: " << oct << number << endl;
    cout << "10진수: " << dec << number << endl;

    return 0;
}