/*
 * 서식 있는 출력
 * 파일명: 07_formatted_output.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 07_formatted_output 07_formatted_output.cpp
 * 실행: ./07_formatted_output (Linux/Mac) 또는 07_formatted_output.exe (Windows)
 */

/*
주제: 고급 출력 서식 (Advanced Output Formatting)
정의: 데이터를 표 형태로 정렬하고 전문적인 형태로 출력하는 고급 서식 제어 기법

핵심 개념: setw, left/right, 테이블 출력, 문자열 생성
정의:
- setw: 출력 필드의 폭을 설정하는 조작자
- left/right: 데이터의 정렬 방향을 설정하는 조작자
- 테이블 출력: 행과 열로 구성된 표 형태의 데이터 출력
- 문자열 생성: string 생성자를 이용한 반복 문자열 생성
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    double price = 1234.567;
    string product = "노트북";
    int quantity = 5;

    cout << "=== 상품 정보 ===" << endl;
    cout << left << setw(10) << "상품명" 
         << right << setw(10) << "단가" 
         << right << setw(8) << "수량" 
         << right << setw(12) << "총액" << endl;

    cout << string(40, '-') << endl;

    cout << left << setw(10) << product
         << right << setw(10) << fixed << setprecision(0) << price
         << right << setw(8) << quantity
         << right << setw(12) << price * quantity << endl;

    // 퍼센트 출력
    double rate = 0.15;
    cout << "\n할인율: " << setprecision(1) << (rate * 100) << "%" << endl;

    return 0;
}