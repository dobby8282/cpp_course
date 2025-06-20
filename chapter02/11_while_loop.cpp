/*
 * while 반복문
 * 파일명: 11_while_loop.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 11_while_loop 11_while_loop.cpp
 * 실행: ./11_while_loop (Linux/Mac) 또는 11_while_loop.exe (Windows)
 */

/*
주제: while 반복문 (While Loop)
정의: 주어진 조건이 참인 동안 코드 블록을 반복 실행하는 제어 구조

핵심 개념: while, 조건 기반 반복, 무한 루프
정의:
- while: 조건이 참인 동안 반복을 수행하는 키워드
- 조건 기반 반복: 반복 횟수가 미리 정해지지 않고 조건에 의존하는 반복
- 무한 루프: 조건이 항상 참이어서 끝나지 않는 반복문 (while(true))
*/

#include <iostream>
using namespace std;

int main() {
    int num;
    int sum = 0;

    cout << "숫자를 입력하세요 (0 입력시 종료):" << endl;

    while (true) {
        cout << "숫자: ";
        cin >> num;

        if (num == 0) {
            break;
        }

        sum += num;
        cout << "현재 합계: " << sum << endl;
    }

    cout << "최종 합계: " << sum << endl;

    return 0;
}