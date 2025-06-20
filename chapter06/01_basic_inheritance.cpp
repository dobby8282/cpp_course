/*
 * 기본 상속
 * 파일명: 01_basic_inheritance.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 01_basic_inheritance 01_basic_inheritance.cpp
 * 실행: ./01_basic_inheritance (Linux/Mac) 또는 01_basic_inheritance.exe (Windows)
 */

/*
주제: 기본 상속 (Basic Inheritance)
정의: 기존 클래스의 기능을 확장하여 새로운 클래스를 만드는 기법
*/

#include <iostream>
#include <string>
using namespace std;

// 기본 클래스 (부모 클래스)
class Animal {
protected:
    string name;
    int age;

public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "동물 생성: " << name << endl;
    }

    void eat() {
        cout << name << "이(가) 먹이를 먹습니다." << endl;
    }

    void sleep() {
        cout << name << "이(가) 잠을 잡니다." << endl;
    }
};

// 파생 클래스 (자식 클래스)
class Dog : public Animal {
public:
    Dog(string n, int a) : Animal(n, a) {
        cout << "개 생성: " << name << endl;
    }

    void bark() {
        cout << name << "이(가) 멍멍 짖습니다." << endl;
    }
};

int main() {
    Dog dog("바둑이", 3);

    dog.eat();    // 부모 클래스의 메서드
    dog.sleep();  // 부모 클래스의 메서드
    dog.bark();   // 자식 클래스의 메서드

    return 0;
}