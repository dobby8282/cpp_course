/*
 * 사용자 입력 처리
 * 파일명: 06_user_input.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 06_user_input 06_user_input.cpp
 * 실행: ./06_user_input (Linux/Mac) 또는 06_user_input.exe (Windows)
 */

/*
주제: 사용자 입력 처리 (User Input Handling)
정의: 사용자로부터 다양한 형태의 데이터를 안전하고 정확하게 입력받는 기법

핵심 개념: getline, cin.ignore, 입력 버퍼, 공백 처리
정의:
- getline: 공백을 포함한 한 줄 전체를 입력받는 함수
- cin.ignore: 입력 버퍼에 남아있는 문자들을 제거하는 함수
- 입력 버퍼: 입력된 데이터가 임시로 저장되는 메모리 공간
- 공백 처리: 문자열에 포함된 공백 문자를 올바르게 처리하는 방법
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName, lastName;
    string fullLine;
    int score;

    cout << "=== 학생 정보 입력 ===" << endl;

    cout << "이름(성): ";
    cin >> firstName;

    cout << "이름(이름): ";
    cin >> lastName;

    cout << "점수: ";
    cin >> score;

    // 입력 버퍼 정리
    cin.ignore();

    cout << "한줄 코멘트: ";
    getline(cin, fullLine);

    cout << "\n=== 입력된 정보 ===" << endl;
    cout << "전체 이름: " << firstName << " " << lastName << endl;
    cout << "점수: " << score << "점" << endl;
    cout << "코멘트: " << fullLine << endl;

    return 0;
}