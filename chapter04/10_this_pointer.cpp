/*
 * this 포인터
 * 파일명: 10_this_pointer.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 10_this_pointer 10_this_pointer.cpp
 * 실행: ./10_this_pointer (Linux/Mac) 또는 10_this_pointer.exe (Windows)
 */

/*
주제: this 포인터 (this Pointer)
정의: 현재 객체를 가리키는 포인터
*/

#include <iostream>
using namespace std;

class Calculator {
private:
    int value;

public:
    Calculator(int v = 0) : value(v) {}

    // this를 사용한 메서드 체이닝
    Calculator& add(int n) {
        this->value += n;
        return *this;
    }

    Calculator& multiply(int n) {
        this->value *= n;
        return *this;
    }

    // this를 사용한 자기 자신과의 비교
    bool isEqual(const Calculator& other) {
        return this->value == other.value;
    }

    void display() {
        cout << "값: " << value << endl;
    }
};

int main() {
    Calculator calc(5);

    // 메서드 체이닝
    calc.add(3).multiply(2);
    calc.display();  // 16

    Calculator calc2(16);
    cout << "같은가? " << calc.isEqual(calc2) << endl;

    return 0;
}