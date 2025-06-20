/*
 * 클래스 기초
 * 파일명: 02_class_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 02_class_basic 02_class_basic.cpp
 * 실행: ./02_class_basic (Linux/Mac) 또는 02_class_basic.exe (Windows)
 */

/*
주제: 클래스 (Class)
정의: 데이터(멤버 변수)와 그 데이터를 조작하는 함수(멤버 함수)를 하나로 묶은 객체지향의 기본 단위

핵심 개념: class 키워드, 멤버 함수, 객체, 캡슐화
정의:
- class 키워드: 클래스를 정의하는 C++ 키워드
- 멤버 함수: 클래스 내부에 정의된 함수로 객체의 동작을 정의
- 객체: 클래스를 바탕으로 생성된 실체(인스턴스)
- 캡슐화: 데이터와 함수를 하나로 묶어 외부에서의 접근을 제어하는 개념
*/

#include <iostream>
#include <string>
using namespace std;

class Rectangle {
public:
    double width;
    double height;

    double getArea() {
        return width * height;
    }

    double getPerimeter() {
        return 2 * (width + height);
    }

    void display() {
        cout << "가로: " << width << ", 세로: " << height << endl;
        cout << "넓이: " << getArea() << ", 둘레: " << getPerimeter() << endl;
    }
};

int main() {
    Rectangle rect;
    rect.width = 5.0;
    rect.height = 3.0;

    cout << "=== 사각형 정보 ===" << endl;
    rect.display();

    return 0;
}