/*
 * if 조건문
 * 파일명: 07_if_statement.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 07_if_statement 07_if_statement.cpp
 * 실행: ./07_if_statement (Linux/Mac) 또는 07_if_statement.exe (Windows)
 */

/*
주제: 조건문 (Conditional Statements)
정의: 주어진 조건의 참/거짓에 따라 프로그램의 실행 흐름을 분기하는 제어 구조

핵심 개념: if, else, 조건 판별, 삼항 연산자
정의:
- if: 조건이 참일 때 특정 코드 블록을 실행하는 키워드
- else: if 조건이 거짓일 때 실행할 대안 코드 블록을 지정하는 키워드
- 조건 판별: 표현식이 참인지 거짓인지 평가하는 과정
- 삼항 연산자 (?:): 조건에 따라 두 값 중 하나를 선택하는 간단한 조건 연산자
*/

#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "점수를 입력하세요: ";
    cin >> score;

    // 단순 if-else
    if (score >= 60) {
        cout << "합격!" << endl;
    } else {
        cout << "불합격..." << endl;
    }

    // 삼항 연산자
    string result = (score >= 60) ? "합격" : "불합격";
    cout << "결과: " << result << endl;

    return 0;
}