/*
 * break와 continue
 * 파일명: 13_break_continue.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 13_break_continue 13_break_continue.cpp
 * 실행: ./13_break_continue (Linux/Mac) 또는 13_break_continue.exe (Windows)
 */

/*
주제: 반복문 제어 (Loop Control)
정의: 반복문의 정상적인 흐름을 변경하여 반복을 중단하거나 다음 반복으로 건너뛰는 제어 기법

핵심 개념: break, continue, 반복문 제어
정의:
- break: 현재 반복문을 즉시 종료하고 반복문 다음 문장으로 이동하는 키워드
- continue: 현재 반복의 나머지 부분을 건너뛰고 다음 반복으로 이동하는 키워드
- 반복문 제어: 특정 조건에서 반복의 흐름을 변경하는 프로그래밍 기법
*/

#include <iostream>
using namespace std;

int main() {
    // continue 예제 - 홀수만 출력
    cout << "1부터 10까지 홀수만:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 짝수면 건너뛰기
        }
        cout << i << " ";
    }
    cout << endl;

    // break 예제 - 5에서 중단
    cout << "1부터 시작해서 5에서 중단:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            break;  // 5에서 중단
        }
        cout << i << " ";
    }
    cout << endl;

    return 0;
}