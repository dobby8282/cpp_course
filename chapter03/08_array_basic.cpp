/*
 * 배열 기초
 * 파일명: 08_array_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 08_array_basic 08_array_basic.cpp
 * 실행: ./08_array_basic (Linux/Mac) 또는 08_array_basic.exe (Windows)
 */

/*
주제: 배열 (Array)
정의: 같은 타입의 여러 데이터를 연속된 메모리 공간에 저장하는 자료구조

핵심 개념: 배열 선언, 인덱스, 초기화, 크기
정의:
- 배열 선언: 타입과 크기를 지정하여 연속된 메모리 공간 할당
- 인덱스: 배열 요소에 접근하기 위한 위치 번호 (0부터 시작)
- 초기화: 배열 선언과 동시에 값을 설정하는 것
- 크기: 배열이 저장할 수 있는 요소의 개수
*/

#include <iostream>
using namespace std;

int main() {
    // 다양한 배열 선언과 초기화
    int numbers[5] = {10, 20, 30, 40, 50};
    int scores[] = {85, 90, 78, 92, 88};  // 크기 자동 결정
    double temperatures[3] = {25.5, 28.0, 22.3};

    // 배열 요소 출력
    cout << "numbers 배열:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }

    // 배열 요소 변경
    cout << "\nscores 배열 변경 전:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }

    scores[2] = 95;  // 세 번째 요소 변경
    cout << "\nscores 배열 변경 후:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    return 0;
}