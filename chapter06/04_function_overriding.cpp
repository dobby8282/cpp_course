/*
 * 함수 오버라이딩
 * 파일명: 04_function_overriding.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 04_function_overriding 04_function_overriding.cpp
 * 실행: ./04_function_overriding (Linux/Mac) 또는 04_function_overriding.exe (Windows)
 */

/*
주제: 함수 오버라이딩 (Function Overriding)
정의: 자식 클래스에서 부모 클래스의 함수를 재정의하는 것
*/

#include <iostream>
using namespace std;

class Shape {
protected:
    string name;

public:
    Shape(string n) : name(n) {}

    void display() {
        cout << "도형: " << name << endl;
    }

    double getArea() {
        cout << "기본 도형의 넓이" << endl;
        return 0;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("원"), radius(r) {}

    // 부모 클래스의 함수 오버라이딩
    double getArea() {
        cout << "원의 넓이 계산" << endl;
        return 3.14159 * radius * radius;
    }

    // 부모 함수 호출하기
    void showInfo() {
        Shape::display();  // 부모 클래스의 display() 호출
        cout << "반지름: " << radius << ", 넓이: " << getArea() << endl;
    }
};

int main() {
    Circle circle(5.0);

    circle.showInfo();

    // 부모 클래스 포인터로 자식 객체 참조
    Shape* shape = &circle;
    shape->display();     // 부모 클래스의 display()
    shape->getArea();     // 어떤 getArea()가 호출될까?

    return 0;
}