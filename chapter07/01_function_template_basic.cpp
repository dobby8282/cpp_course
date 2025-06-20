/*
 * 함수 템플릿 기초
 * 파일명: 01_function_template_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 01_function_template_basic 01_function_template_basic.cpp
 * 실행: ./01_function_template_basic (Linux/Mac) 또는 01_function_template_basic.exe (Windows)
 */

/*
주제: 함수 템플릿 기초 (Function Template Basics)
정의: 다양한 타입에 대해 동일한 로직을 적용할 수 있는 제네릭 함수
*/

#include <iostream>
using namespace std;

// 함수 템플릿
template<typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// 여러 매개변수를 가진 템플릿
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 다중 타입 템플릿
template<typename T, typename U>
void printPair(T first, U second) {
    cout << "(" << first << ", " << second << ")" << endl;
}

int main() {
    // 정수형
    cout << "최댓값(10, 20): " << getMax(10, 20) << endl;

    // 실수형
    cout << "최댓값(3.5, 2.8): " << getMax(3.5, 2.8) << endl;

    // 문자열
    cout << "최댓값(\"apple\", \"banana\"): " << getMax(string("apple"), string("banana")) << endl;

    // swap 테스트
    int x = 5, y = 10;
    cout << "\nswap 전: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "swap 후: x=" << x << ", y=" << y << endl;

    // 다중 타입 템플릿
    printPair(42, "hello");
    printPair(3.14, 100);

    return 0;
}