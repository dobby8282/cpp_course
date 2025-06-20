/*
 * else if 다중 조건
 * 파일명: 08_else_if.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 08_else_if 08_else_if.cpp
 * 실행: ./08_else_if (Linux/Mac) 또는 08_else_if.exe (Windows)
 */

/*
주제: 다중 조건문 (Multiple Conditional Statements)
정의: 여러 개의 조건을 순차적으로 검사하여 해당하는 조건에 맞는 코드를 실행하는 제어 구조

핵심 개념: else if, 다중 분기, 조건 연쇄
정의:
- else if: 이전 조건이 거짓일 때 추가 조건을 검사하는 키워드 조합
- 다중 분기: 여러 경우의 수에 따라 프로그램 흐름을 나누는 것
- 조건 연쇄: 여러 조건을 순서대로 연결하여 검사하는 구조
*/

#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "점수를 입력하세요: ";
    cin >> score;

    if (score >= 90) {
        cout << "A학점" << endl;
    } else if (score >= 80) {
        cout << "B학점" << endl;
    } else if (score >= 70) {
        cout << "C학점" << endl;
    } else if (score >= 60) {
        cout << "D학점" << endl;
    } else {
        cout << "F학점" << endl;
    }

    return 0;
}