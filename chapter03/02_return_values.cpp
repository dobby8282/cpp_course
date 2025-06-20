/*
 * 반환값과 void 함수
 * 파일명: 02_return_values.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 02_return_values 02_return_values.cpp
 * 실행: ./02_return_values (Linux/Mac) 또는 02_return_values.exe (Windows)
 */

/*
주제: 함수 반환값 (Function Return Value)
정의: 함수가 작업을 완료한 후 호출자에게 돌려주는 결과값

핵심 개념: return문, void 함수, 반환 타입
정의:
- return문: 함수에서 값을 반환하고 함수 실행을 종료하는 키워드
- void 함수: 반환값이 없는 함수 (출력이나 상태 변경만 수행)
- 반환 타입: 함수가 반환할 데이터의 타입 (int, double, bool 등)
*/

#include <iostream>
using namespace std;

// 반환값이 있는 함수
double calculateArea(double radius) {
    return 3.14159 * radius * radius;
}

// 반환값이 없는 함수
void printResult(double area) {
    cout << "원의 넓이: " << area << endl;
}

// bool 반환 함수
bool isEven(int number) {
    return number % 2 == 0;
}

int main() {
    double radius = 5.0;
    double area = calculateArea(radius);

    printResult(area);

    int num = 8;
    if (isEven(num)) {
        cout << num << "은 짝수입니다." << endl;
    }

    return 0;
}