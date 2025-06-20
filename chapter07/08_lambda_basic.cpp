/*
 * 람다 표현식 기초
 * 파일명: 08_lambda_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 08_lambda_basic 08_lambda_basic.cpp
 * 실행: ./08_lambda_basic (Linux/Mac) 또는 08_lambda_basic.exe (Windows)
 */

/*
주제: 람다 표현식 기초 (Lambda Expression Basics)
정의: 익명 함수를 생성하는 C++11의 기능
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    cout << "=== 기본 람다 ===" << endl;

    // 가장 간단한 람다
    auto hello = []() {
        cout << "Hello Lambda!" << endl;
    };
    hello();

    // 매개변수를 받는 람다
    auto add = [](int a, int b) {
        return a + b;
    };
    cout << "5 + 3 = " << add(5, 3) << endl;

    // 반환 타입을 명시한 람다
    auto divide = [](double a, double b) -> double {
        return b != 0 ? a / b : 0;
    };
    cout << "10.0 / 3.0 = " << divide(10.0, 3.0) << endl;

    cout << "\n=== 캡처 절 ===" << endl;
    int x = 10;
    int y = 20;

    // 값으로 캡처
    auto lambda1 = [x, y]() {
        cout << "값 캡처: x=" << x << ", y=" << y << endl;
    };

    // 참조로 캡처
    auto lambda2 = [&x, &y]() {
        x += 5;
        y += 10;
        cout << "참조 캡처 후: x=" << x << ", y=" << y << endl;
    };

    // 모든 변수를 값으로 캡처
    auto lambda3 = [=]() {
        cout << "모든 변수 값 캡처: x=" << x << ", y=" << y << endl;
    };

    lambda1();
    lambda2();
    lambda3();

    cout << "\n=== STL과 함께 사용 ===" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 짝수만 출력
    cout << "짝수: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        if (n % 2 == 0) cout << n << " ";
    });
    cout << endl;

    return 0;
}