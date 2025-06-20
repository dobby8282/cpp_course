/*
 * 종합 활용 - 간단한 벡터 클래스
 * 파일명: 10_simple_vector.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 10_simple_vector 10_simple_vector.cpp
 * 실행: ./10_simple_vector (Linux/Mac) 또는 10_simple_vector.exe (Windows)
 */

/*
주제: 종합 활용 - 간단한 벡터 클래스
정의: 모든 객체지향 개념을 통합한 실용적인 클래스
*/

#include <iostream>
#include <utility>
using namespace std;

class SimpleVector {
private:
    int* data;
    int size;
    static int totalVectors;

public:
    // 생성자
    SimpleVector(int s = 0) : size(s) {
        data = size > 0 ? new int[size] : nullptr;
        totalVectors++;
        cout << "벡터 생성 (크기: " << size << ")" << endl;
    }

    // 복사 생성자
    SimpleVector(const SimpleVector& other) : size(other.size) {
        data = size > 0 ? new int[size] : nullptr;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        totalVectors++;
        cout << "벡터 복사" << endl;
    }

    // 이동 생성자
    SimpleVector(SimpleVector&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        totalVectors++;
        cout << "벡터 이동" << endl;
    }

    // 소멸자
    ~SimpleVector() {
        delete[] data;
        totalVectors--;
    }

    // 연산자 오버로딩
    int& operator[](int index) { return data[index]; }
    const int& operator[](int index) const { return data[index]; }

    // 정적 함수
    static int getTotalVectors() { return totalVectors; }

    int getSize() const { return size; }

    void display() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int SimpleVector::totalVectors = 0;

int main() {
    SimpleVector v1(3);
    v1[0] = 10; v1[1] = 20; v1[2] = 30;
    v1.display();

    SimpleVector v2 = v1;           // 복사
    SimpleVector v3 = move(v1);     // 이동

    cout << "총 벡터 개수: " << SimpleVector::getTotalVectors() << endl;

    return 0;
}