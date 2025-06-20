/*
 * 이동 의미론
 * 파일명: 07_move_semantics.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 07_move_semantics 07_move_semantics.cpp
 * 실행: ./07_move_semantics (Linux/Mac) 또는 07_move_semantics.exe (Windows)
 */

/*
주제: 이동 의미론 (Move Semantics)
정의: 불필요한 복사를 피하고 자원을 효율적으로 이동
*/

#include <iostream>
#include <utility>
using namespace std;

class Resource {
private:
    int* data;
    int size;

public:
    Resource(int s) : size(s) {
        data = new int[size];
        cout << "생성 (" << size << ")" << endl;
    }

    // 이동 생성자
    Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "이동 생성" << endl;
    }

    // 이동 대입 연산자
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            cout << "이동 대입" << endl;
        }
        return *this;
    }

    ~Resource() {
        delete[] data;
        if (size > 0) cout << "소멸 (" << size << ")" << endl;
    }
};

int main() {
    Resource r1(10);
    Resource r2 = move(r1);  // 이동 생성자

    Resource r3(5);
    r3 = move(r2);          // 이동 대입 연산자

    return 0;
}