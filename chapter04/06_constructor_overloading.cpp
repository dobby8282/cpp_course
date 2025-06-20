/*
 * 생성자 오버로딩
 * 파일명: 06_constructor_overloading.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 06_constructor_overloading 06_constructor_overloading.cpp
 * 실행: ./06_constructor_overloading (Linux/Mac) 또는 06_constructor_overloading.exe (Windows)
 */

/*
주제: 생성자 오버로딩 (Constructor Overloading)
정의: 서로 다른 매개변수를 가진 여러 개의 생성자를 정의
*/

#include <iostream>
using namespace std;

class Circle {
private:
    double radius;

public:
    Circle() : radius(1.0) {}                    // 기본 생성자
    Circle(double r) : radius(r) {}              // 반지름 지정
    Circle(const Circle& other) : radius(other.radius) {}  // 복사 생성자

    double getArea() {
        return 3.14159 * radius * radius;
    }

    void display() {
        cout << "반지름: " << radius << ", 넓이: " << getArea() << endl;
    }
};

int main() {
    Circle c1;          // 기본 생성자
    Circle c2(5.0);     // 매개변수 생성자
    Circle c3(c2);      // 복사 생성자

    c1.display();
    c2.display();
    c3.display();

    return 0;
}