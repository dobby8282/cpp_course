/*
 * do-while 반복문
 * 파일명: 12_do_while.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 12_do_while 12_do_while.cpp
 * 실행: ./12_do_while (Linux/Mac) 또는 12_do_while.exe (Windows)
 */

/*
주제: do-while 반복문 (Do-While Loop)
정의: 코드 블록을 먼저 실행한 후 조건을 검사하여 반복을 결정하는 후검사 반복문

핵심 개념: do-while, 후검사 반복, 최소 1회 실행
정의:
- do-while: 코드를 먼저 실행하고 나중에 조건을 검사하는 반복문
- 후검사 반복: 반복 조건을 코드 실행 후에 검사하는 반복 방식
- 최소 1회 실행: 조건에 관계없이 적어도 한 번은 코드가 실행되는 특성
*/

#include <iostream>
using namespace std;

int main() {
    int choice;

    do {
        cout << "\n=== 메뉴 ===" << endl;
        cout << "1. 인사말" << endl;
        cout << "2. 현재 시간" << endl;
        cout << "3. 종료" << endl;
        cout << "선택: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "안녕하세요!" << endl;
                break;
            case 2:
                cout << "현재는 수업 시간입니다." << endl;
                break;
            case 3:
                cout << "프로그램을 종료합니다." << endl;
                break;
            default:
                cout << "잘못된 선택입니다." << endl;
        }
    } while (choice != 3);

    return 0;
}