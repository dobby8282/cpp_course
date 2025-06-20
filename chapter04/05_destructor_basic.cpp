/*
 * 소멸자 기초
 * 파일명: 05_destructor_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 05_destructor_basic 05_destructor_basic.cpp
 * 실행: ./05_destructor_basic (Linux/Mac) 또는 05_destructor_basic.exe (Windows)
 */

/*
주제: 소멸자 기초 (Destructor Basics)
정의: 객체가 소멸될 때 자동으로 호출되어 정리 작업을 수행하는 함수
*/

#include <iostream>
using namespace std;

class Resource {
private:
    int* data;

public:
    Resource(int size) {
        data = new int[size];
        cout << "메모리 할당: " << data << endl;
    }

    ~Resource() {
        delete[] data;
        cout << "메모리 해제: " << data << endl;
    }

    void setValue(int value) {
        data[0] = value;
    }
};

int main() {
    {
        Resource r(10);
        r.setValue(42);
    } // 여기서 자동으로 소멸자 호출

    cout << "메인 계속 실행" << endl;
    return 0;
}