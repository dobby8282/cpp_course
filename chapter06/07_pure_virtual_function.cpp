/*
 * 순수 가상 함수
 * 파일명: 07_pure_virtual_function.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 07_pure_virtual_function 07_pure_virtual_function.cpp
 * 실행: ./07_pure_virtual_function (Linux/Mac) 또는 07_pure_virtual_function.exe (Windows)
 */

/*
주제: 순수 가상 함수 (Pure Virtual Function)
정의: 구현이 없는 가상 함수로, 자식 클래스에서 반드시 구현해야 함
*/

#include <iostream>
using namespace std;

// 추상 클래스 (순수 가상 함수를 가진 클래스)
class Shape {
protected:
    string name;

public:
    Shape(string n) : name(n) {}

    // 순수 가상 함수 (= 0으로 선언)
    virtual double getArea() = 0;
    virtual void draw() = 0;

    // 일반 함수는 구현 가능
    void displayName() {
        cout << "도형 이름: " << name << endl;
    }

    virtual ~Shape() {}  // 가상 소멸자
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : Shape("사각형"), width(w), height(h) {}

    // 순수 가상 함수 구현 (필수)
    double getArea() override {
        return width * height;
    }

    void draw() override {
        cout << "사각형을 그립니다 (" << width << "x" << height << ")" << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("원"), radius(r) {}

    double getArea() override {
        return 3.14159 * radius * radius;
    }

    void draw() override {
        cout << "원을 그립니다 (반지름: " << radius << ")" << endl;
    }
};

int main() {
    // Shape shape;  // 오류: 추상 클래스는 인스턴스화 불가

    Rectangle rect(4, 5);
    Circle circle(3);

    Shape* shapes[] = {&rect, &circle};

    for (Shape* shape : shapes) {
        shape->displayName();
        shape->draw();
        cout << "넓이: " << shape->getArea() << endl << endl;
    }

    return 0;
}