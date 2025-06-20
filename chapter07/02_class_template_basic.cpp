/*
 * 클래스 템플릿 기초
 * 파일명: 02_class_template_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 02_class_template_basic 02_class_template_basic.cpp
 * 실행: ./02_class_template_basic (Linux/Mac) 또는 02_class_template_basic.exe (Windows)
 */

/*
주제: 클래스 템플릿 기초 (Class Template Basics)
정의: 다양한 타입을 다룰 수 있는 제네릭 클래스
*/

#include <iostream>
using namespace std;

template<typename T>
class Box {
private:
    T item;

public:
    Box(T i) : item(i) {}

    void setItem(T i) {
        item = i;
    }

    T getItem() {
        return item;
    }

    void display() {
        cout << "Box contains: " << item << endl;
    }
};

// 배열을 관리하는 클래스 템플릿
template<typename T, int SIZE>
class Array {
private:
    T data[SIZE];

public:
    void set(int index, T value) {
        if (index >= 0 && index < SIZE) {
            data[index] = value;
        }
    }

    T get(int index) {
        if (index >= 0 && index < SIZE) {
            return data[index];
        }
        return T{};  // 기본값 반환
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // 다양한 타입의 Box 생성
    Box<int> intBox(42);
    Box<string> stringBox("Hello");
    Box<double> doubleBox(3.14);

    intBox.display();
    stringBox.display();
    doubleBox.display();

    // 크기가 고정된 배열
    Array<int, 5> intArray;
    for (int i = 0; i < 5; i++) {
        intArray.set(i, i * 10);
    }
    intArray.display();

    Array<string, 3> stringArray;
    stringArray.set(0, "첫번째");
    stringArray.set(1, "두번째");
    stringArray.set(2, "세번째");
    stringArray.display();

    return 0;
}