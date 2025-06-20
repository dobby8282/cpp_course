/*
 * 복사 생성자
 * 파일명: 07_copy_constructor.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 07_copy_constructor 07_copy_constructor.cpp
 * 실행: ./07_copy_constructor (Linux/Mac) 또는 07_copy_constructor.exe (Windows)
 */

/*
주제: 복사 생성자 (Copy Constructor)
정의: 같은 클래스의 객체로부터 새로운 객체를 복사 생성
*/

#include <iostream>
using namespace std;

class Array {
private:
    int* data;
    int size;

public:
    Array(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = i + 1;
        }
    }

    // 복사 생성자 (깊은 복사)
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "복사 생성자 호출" << endl;
    }

    ~Array() {
        delete[] data;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array arr1(3);
    Array arr2 = arr1;  // 복사 생성자 호출

    arr1.display();
    arr2.display();

    return 0;
}