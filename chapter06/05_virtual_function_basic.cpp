/*
 * 가상 함수 기초
 * 파일명: 05_virtual_function_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 05_virtual_function_basic 05_virtual_function_basic.cpp
 * 실행: ./05_virtual_function_basic (Linux/Mac) 또는 05_virtual_function_basic.exe (Windows)
 */

/*
주제: 가상 함수 기초 (Virtual Function Basics)
정의: 런타임에 실제 객체 타입에 따라 호출될 함수가 결정되는 함수
*/

#include <iostream>
using namespace std;

class Animal {
public:
    // 가상 함수
    virtual void makeSound() {
        cout << "동물이 소리를 냅니다." << endl;
    }

    // 일반 함수
    void move() {
        cout << "동물이 움직입니다." << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {  // override 키워드 사용 권장
        cout << "멍멍!" << endl;
    }

    void move() {
        cout << "개가 뛰어다닙니다." << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "야옹!" << endl;
    }

    void move() {
        cout << "고양이가 조용히 걷습니다." << endl;
    }
};

int main() {
    Dog dog;
    Cat cat;

    cout << "=== 직접 호출 ===" << endl;
    dog.makeSound();  // 멍멍!
    cat.makeSound();  // 야옹!

    cout << "\n=== 포인터로 호출 ===" << endl;
    Animal* animals[] = {&dog, &cat};

    for (Animal* animal : animals) {
        animal->makeSound();  // 가상 함수: 실제 타입의 함수 호출
        animal->move();       // 일반 함수: Animal의 함수 호출
    }

    return 0;
}