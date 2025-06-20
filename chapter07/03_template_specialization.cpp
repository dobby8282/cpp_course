/*
 * 템플릿 특수화
 * 파일명: 03_template_specialization.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 03_template_specialization 03_template_specialization.cpp
 * 실행: ./03_template_specialization (Linux/Mac) 또는 03_template_specialization.exe (Windows)
 */

/*
주제: 템플릿 특수화 (Template Specialization)
정의: 특정 타입에 대해 템플릿의 특별한 구현을 제공
*/

#include <iostream>
#include <string>
using namespace std;

// 일반 템플릿
template<typename T>
class Printer {
public:
    void print(T value) {
        cout << "일반: " << value << endl;
    }
};

// string에 대한 특수화
template<>
class Printer<string> {
public:
    void print(string value) {
        cout << "문자열 특수화: \"" << value << "\"" << endl;
    }
};

// bool에 대한 특수화
template<>
class Printer<bool> {
public:
    void print(bool value) {
        cout << "불린 특수화: " << (value ? "참" : "거짓") << endl;
    }
};

// 함수 템플릿과 특수화
template<typename T>
void describe(T value) {
    cout << "알 수 없는 타입: " << value << endl;
}

// int 특수화
template<>
void describe<int>(int value) {
    cout << "정수 " << value << "입니다." << endl;
}

// double 특수화
template<>
void describe<double>(double value) {
    cout << "실수 " << value << "입니다." << endl;
}

int main() {
    Printer<int> intPrinter;
    Printer<string> stringPrinter;
    Printer<bool> boolPrinter;
    Printer<double> doublePrinter;

    intPrinter.print(42);
    stringPrinter.print("Hello World");
    boolPrinter.print(true);
    doublePrinter.print(3.14);

    cout << "\n함수 템플릿 특수화:" << endl;
    describe(100);
    describe(3.14159);
    describe("문자열");  // 일반 템플릿 사용

    return 0;
}