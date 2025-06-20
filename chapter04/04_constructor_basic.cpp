/*
 * 생성자 기초
 * 파일명: 04_constructor_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 04_constructor_basic 04_constructor_basic.cpp
 * 실행: ./04_constructor_basic (Linux/Mac) 또는 04_constructor_basic.exe (Windows)
 */

/*
주제: 생성자 기초 (Constructor Basics)
정의: 객체가 생성될 때 자동으로 호출되어 객체를 초기화하는 특별한 멤버 함수
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;

public:
    // 기본 생성자
    Student() : name("Unknown"), age(0) {
        cout << "기본 생성자: " << name << endl;
    }

    // 매개변수 생성자
    Student(string n, int a) : name(n), age(a) {
        cout << "매개변수 생성자: " << name << endl;
    }

    void display() {
        cout << name << " (" << age << "세)" << endl;
    }
};

int main() {
    Student s1;                    // 기본 생성자
    Student s2("김철수", 20);       // 매개변수 생성자

    s1.display();
    s2.display();

    return 0;
}