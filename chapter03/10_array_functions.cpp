/*
 * 배열과 함수
 * 파일명: 10_array_functions.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 10_array_functions 10_array_functions.cpp
 * 실행: ./10_array_functions (Linux/Mac) 또는 10_array_functions.exe (Windows)
 */

/*
주제: 배열과 함수 (Array and Functions)
정의: 배열을 함수에 전달하여 처리하는 방법과 그 특성

핵심 개념: 배열 매개변수, 포인터 전달, 크기 정보
정의:
- 배열 매개변수: 배열을 함수의 매개변수로 받는 방식
- 포인터 전달: 배열명은 첫 번째 요소의 주소로 전달됨
- 크기 정보: 배열 크기는 별도로 전달해야 함 (sizeof 사용 불가)
*/

#include <iostream>
using namespace std;

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 배열 요소 합계 계산
int calculateSum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 배열 요소를 2배로 증가
void doubleArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;

    cout << "원본 배열: ";
    printArray(numbers, size);

    cout << "합계: " << calculateSum(numbers, size) << endl;

    doubleArray(numbers, size);
    cout << "2배 증가 후: ";
    printArray(numbers, size);

    return 0;
}