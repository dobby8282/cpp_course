/*
 * 연산자 오버로딩 심화
 * 파일명: 04_operator_overloading_advanced.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 04_operator_overloading_advanced 04_operator_overloading_advanced.cpp
 * 실행: ./04_operator_overloading_advanced (Linux/Mac) 또는 04_operator_overloading_advanced.exe (Windows)
 */

/*
주제: 연산자 오버로딩 심화 (Advanced Operator Overloading)
정의: 증감 연산자, 배열 인덱스 연산자 등의 고급 오버로딩
*/

#include <iostream>
using namespace std;

class Counter {
private:
    int value;

public:
    Counter(int v = 0) : value(v) {}

    // 전위 증가 (++obj)
    Counter& operator++() {
        ++value;
        return *this;
    }

    // 후위 증가 (obj++)
    Counter operator++(int) {
        Counter temp = *this;
        value++;
        return temp;
    }

    int getValue() const { return value; }
};

class Array {
private:
    int data[5];

public:
    Array() {
        for (int i = 0; i < 5; i++) data[i] = 0;
    }

    // 배열 인덱스 연산자
    int& operator[](int index) {
        return data[index];
    }
};

int main() {
    Counter c(5);
    cout << "전위: " << (++c).getValue() << endl;  // 6
    cout << "후위: " << (c++).getValue() << endl;  // 6 (증가 전 값 반환)
    cout << "현재: " << c.getValue() << endl;      // 7

    Array arr;
    arr[0] = 10;
    arr[1] = 20;
    cout << "arr[0] = " << arr[0] << endl;

    return 0;
}