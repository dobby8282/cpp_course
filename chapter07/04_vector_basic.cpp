/*
 * vector 기초
 * 파일명: 04_vector_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 04_vector_basic 04_vector_basic.cpp
 * 실행: ./04_vector_basic (Linux/Mac) 또는 04_vector_basic.exe (Windows)
 */

/*
주제: vector 기초 (Vector Basics)
정의: 동적 배열을 제공하는 STL 컨테이너
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // vector 생성과 초기화
    vector<int> numbers;
    vector<int> scores = {90, 85, 92, 78, 96};
    vector<string> names(3, "unknown");  // 3개 요소를 "unknown"으로 초기화

    cout << "=== 요소 추가 ===" << endl;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    cout << "numbers 크기: " << numbers.size() << endl;

    cout << "\n=== 요소 접근 ===" << endl;
    for (int i = 0; i < numbers.size(); i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }

    cout << "\n=== range-based for loop ===" << endl;
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;

    cout << "\n=== 요소 수정 ===" << endl;
    scores[0] = 95;
    scores.at(1) = 88;  // 범위 검사 포함

    cout << "\n=== 요소 삭제 ===" << endl;
    cout << "삭제 전 크기: " << scores.size() << endl;
    scores.pop_back();  // 마지막 요소 삭제
    cout << "삭제 후 크기: " << scores.size() << endl;

    cout << "\n=== vector 정보 ===" << endl;
    cout << "비어있는가? " << (numbers.empty() ? "예" : "아니오") << endl;
    cout << "첫 번째 요소: " << numbers.front() << endl;
    cout << "마지막 요소: " << numbers.back() << endl;

    return 0;
}