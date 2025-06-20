/*
 * for 반복문
 * 파일명: 10_for_loop.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 10_for_loop 10_for_loop.cpp
 * 실행: ./10_for_loop (Linux/Mac) 또는 10_for_loop.exe (Windows)
 */

/*
주제: 반복문 (Loop Statements)
정의: 특정 조건이 만족되는 동안 코드 블록을 반복적으로 실행하는 제어 구조

핵심 개념: for 루프, 초기화, 조건, 증감
정의:
- for 루프: 초기화, 조건, 증감을 한 곳에 모아 정의하는 반복문
- 초기화: 반복문 시작 전 변수를 설정하는 부분
- 조건: 반복을 계속할지 결정하는 논리 표현식
- 증감: 각 반복 후 제어 변수를 변경하는 부분
*/

#include <iostream>
using namespace std;

int main() {
    // 기본 for 문
    cout << "1부터 5까지:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;

    // 구구단
    int dan = 3;
    cout << dan << "단:" << endl;
    for (int i = 1; i <= 9; i++) {
        cout << dan << " x " << i << " = " << (dan * i) << endl;
    }

    return 0;
}