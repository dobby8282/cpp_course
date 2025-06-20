/*
 * 기본 디버깅
 * 파일명: 10_debugging_basics.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 10_debugging_basics 10_debugging_basics.cpp
 * 실행: ./10_debugging_basics (Linux/Mac) 또는 10_debugging_basics.exe (Windows)
 */

/*
주제: 디버깅 (Debugging)
정의: 프로그램의 오류를 찾아내고 수정하는 과정

핵심 개념: assert, 디버그 출력, 사전 조건 검사, 로그
정의:
- assert: 프로그램 실행 중 특정 조건이 참인지 확인하는 매크로
- 디버그 출력: 프로그램의 상태를 확인하기 위한 임시 출력
- 사전 조건 검사: 함수 실행 전 입력값의 유효성을 검사하는 기법
- 로그: 프로그램 실행 과정을 기록하는 메시지
*/

#include <iostream>
#include <cassert>
using namespace std;

int divide(int a, int b) {
    // 사전 조건 검사
    assert(b != 0 && "0으로 나눌 수 없습니다");

    cout << "[DEBUG] " << a << " / " << b << " 계산 중..." << endl;
    return a / b;
}

int main() {
    int x = 10, y = 2;

    cout << "=== 디버깅 예제 ===" << endl;
    cout << "계산 시작" << endl;

    // 정상적인 계산
    int result1 = divide(x, y);
    cout << "결과: " << result1 << endl;

    // 오류 상황 테스트 (주석 해제시 프로그램 중단)
    // int result2 = divide(x, 0);

    cout << "\n=== 디버깅 도구 활용법 ===" << endl;
    cout << "1. cout 출력으로 변수 값 확인" << endl;
    cout << "2. assert 매크로로 조건 검사" << endl;
    cout << "3. IDE 디버거로 중단점 설정" << endl;
    cout << "4. 정적 분석 도구로 코드 품질 검사" << endl;

    cout << "\n프로그램 정상 종료" << endl;

    return 0;
}