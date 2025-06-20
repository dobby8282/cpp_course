/*
 * 기본 예외 처리
 * 파일명: 01_basic_exception.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 01_basic_exception 01_basic_exception.cpp
 * 실행: ./01_basic_exception (Linux/Mac) 또는 01_basic_exception.exe (Windows)
 */

/*
주제: 기본 예외 처리 (Basic Exception Handling)
정의: try-catch 구문을 사용하여 런타임 오류를 안전하게 처리
*/

#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
    if (b == 0) {
        throw invalid_argument("0으로 나눌 수 없습니다!");
    }
    return a / b;
}

int getArrayElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("배열 인덱스가 범위를 벗어났습니다!");
    }
    return arr[index];
}

int main() {
    cout << "=== 기본 예외 처리 ===" << endl;

    // 나누기 예외 처리
    try {
        cout << "10 / 2 = " << divide(10, 2) << endl;
        cout << "10 / 0 = " << divide(10, 0) << endl;  // 예외 발생
    }
    catch (const invalid_argument& e) {
        cout << "오류 발생: " << e.what() << endl;
    }

    // 배열 접근 예외 처리
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;

    try {
        cout << "\n배열[2] = " << getArrayElement(numbers, size, 2) << endl;
        cout << "배열[10] = " << getArrayElement(numbers, size, 10) << endl;  // 예외 발생
    }
    catch (const out_of_range& e) {
        cout << "배열 오류: " << e.what() << endl;
    }

    // 여러 예외 처리
    try {
        cout << "\n5 / 1 = " << divide(5, 1) << endl;
        cout << "배열[0] = " << getArrayElement(numbers, size, 0) << endl;
        cout << "3 / 0 = " << divide(3, 0) << endl;  // 예외 발생
    }
    catch (const invalid_argument& e) {
        cout << "나누기 오류: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cout << "범위 오류: " << e.what() << endl;
    }
    catch (...) {  // 모든 예외 처리
        cout << "알 수 없는 오류가 발생했습니다." << endl;
    }

    cout << "\n프로그램이 정상적으로 계속됩니다." << endl;
    return 0;
}