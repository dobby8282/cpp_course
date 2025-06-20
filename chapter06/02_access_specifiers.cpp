/*
 * 접근 지정자
 * 파일명: 02_access_specifiers.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 02_access_specifiers 02_access_specifiers.cpp
 * 실행: ./02_access_specifiers (Linux/Mac) 또는 02_access_specifiers.exe (Windows)
 */

/*
주제: 접근 지정자 (Access Specifiers in Inheritance)
정의: 상속 시 멤버들의 접근 권한을 제어하는 키워드
*/

#include <iostream>
using namespace std;

class Base {
public:
    int publicVar;
protected:
    int protectedVar;
private:
    int privateVar;

public:
    Base() : publicVar(1), protectedVar(2), privateVar(3) {}

    void showBase() {
        cout << "Base - public: " << publicVar 
             << ", protected: " << protectedVar 
             << ", private: " << privateVar << endl;
    }
};

class Derived : public Base {
public:
    void showDerived() {
        cout << "Derived - public: " << publicVar << endl;      // OK
        cout << "Derived - protected: " << protectedVar << endl; // OK
        // cout << "Derived - private: " << privateVar << endl;  // 오류!
    }

    void setProtected(int value) {
        protectedVar = value;  // protected는 자식에서 접근 가능
    }
};

int main() {
    Derived d;
    d.publicVar = 10;        // OK: public 멤버
    // d.protectedVar = 20;  // 오류: protected는 외부에서 접근 불가

    d.showBase();
    d.showDerived();
    d.setProtected(99);
    d.showDerived();

    return 0;
}