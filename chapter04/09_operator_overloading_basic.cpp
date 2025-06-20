/*
 * 연산자 오버로딩 기초
 * 파일명: 09_operator_overloading_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 09_operator_overloading_basic 09_operator_overloading_basic.cpp
 * 실행: ./09_operator_overloading_basic (Linux/Mac) 또는 09_operator_overloading_basic.exe (Windows)
 */

/*
주제: 연산자 오버로딩 기초 (Basic Operator Overloading)
정의: 사용자 정의 클래스에 대해 연산자의 동작을 정의
*/

#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // + 연산자 오버로딩
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    // == 연산자 오버로딩
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // << 연산자 오버로딩 (friend)
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p1(3, 4);
    Point p2(1, 2);

    Point p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;
    cout << "p1 == p2? " << (p1 == p2) << endl;

    return 0;
}