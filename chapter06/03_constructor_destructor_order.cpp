/*
 * 생성자/소멸자 호출 순서
 * 파일명: 03_constructor_destructor_order.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 03_constructor_destructor_order 03_constructor_destructor_order.cpp
 * 실행: ./03_constructor_destructor_order (Linux/Mac) 또는 03_constructor_destructor_order.exe (Windows)
 */

/*
주제: 생성자/소멸자 호출 순서
정의: 상속 관계에서 생성자는 부모→자식, 소멸자는 자식→부모 순으로 호출
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base 생성자" << endl;
    }

    ~Base() {
        cout << "Base 소멸자" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived 생성자" << endl;
    }

    ~Derived() {
        cout << "Derived 소멸자" << endl;
    }
};

class GrandChild : public Derived {
public:
    GrandChild() {
        cout << "GrandChild 생성자" << endl;
    }

    ~GrandChild() {
        cout << "GrandChild 소멸자" << endl;
    }
};

int main() {
    cout << "=== 객체 생성 ===" << endl;
    {
        GrandChild gc;
    } // 여기서 소멸
    cout << "=== 객체 소멸 완료 ===" << endl;

    return 0;
}