/*
 * switch 문
 * 파일명: 09_switch_statement.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 09_switch_statement 09_switch_statement.cpp
 * 실행: ./09_switch_statement (Linux/Mac) 또는 09_switch_statement.exe (Windows)
 */

/*
주제: switch 문 (Switch Statement)
정의: 하나의 변수 값에 따라 여러 경우 중 하나를 선택하여 실행하는 다중 분기 제어 구조

핵심 개념: switch, case, break, default
정의:
- switch: 변수의 값에 따라 분기를 결정하는 키워드
- case: switch 변수의 특정 값에 대응하는 실행 블록을 정의하는 라벨
- break: 현재 case 실행 후 switch 문을 종료하는 키워드
- default: 모든 case에 해당하지 않을 때 실행되는 기본 케이스
*/

#include <iostream>
using namespace std;

int main() {
    int choice;
    cout << "메뉴 선택 (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "메뉴 1 선택" << endl;
            break;
        case 2:
            cout << "메뉴 2 선택" << endl;
            break;
        case 3:
            cout << "메뉴 3 선택" << endl;
            break;
        default:
            cout << "잘못된 선택" << endl;
            break;
    }

    return 0;
}