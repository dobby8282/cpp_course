/*
 * 배열과 반복문
 * 파일명: 09_array_loops.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 09_array_loops 09_array_loops.cpp
 * 실행: ./09_array_loops (Linux/Mac) 또는 09_array_loops.exe (Windows)
 */

/*
주제: 배열과 반복문 (Array with Loops)
정의: 배열의 모든 요소에 대해 반복적인 작업을 수행하는 프로그래밍 패턴

핵심 개념: for 루프, 범위 기반 for, 배열 순회
정의:
- for 루프: 인덱스를 사용하여 배열 요소에 순차적으로 접근
- 범위 기반 for: C++11의 기능으로 배열 요소를 직접 순회
- 배열 순회: 배열의 모든 요소를 차례대로 방문하는 것
*/

#include <iostream>
using namespace std;

int main() {
    int numbers[] = {2, 4, 6, 8, 10};
    int size = 5;

    // 일반 for 루프로 출력
    cout << "일반 for 루프:" << endl;
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // 범위 기반 for 루프로 출력 (C++11)
    cout << "범위 기반 for 루프:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // 배열 요소의 합 계산
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    cout << "합계: " << sum << endl;

    // 최대값 찾기
    int max = numbers[0];
    for (int i = 1; i < size; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    cout << "최대값: " << max << endl;

    return 0;
}