/*
 * 이동 생성자
 * 파일명: 08_move_constructor.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 08_move_constructor 08_move_constructor.cpp
 * 실행: ./08_move_constructor (Linux/Mac) 또는 08_move_constructor.exe (Windows)
 */

/*
주제: 이동 생성자 (Move Constructor)
정의: 임시 객체로부터 자원을 효율적으로 이동하는 생성자
*/

#include <iostream>
#include <utility>
using namespace std;

class StringHolder {
private:
    char* str;

public:
    StringHolder(const char* s) {
        int len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        cout << "생성: " << str << endl;
    }

    // 이동 생성자
    StringHolder(StringHolder&& other) noexcept : str(other.str) {
        other.str = nullptr;
        cout << "이동 생성" << endl;
    }

    ~StringHolder() {
        if (str) {
            cout << "소멸: " << str << endl;
            delete[] str;
        }
    }

    void display() {
        cout << (str ? str : "비어있음") << endl;
    }
};

int main() {
    StringHolder s1("Hello");
    StringHolder s2 = move(s1);  // 이동 생성자

    s1.display();  // 비어있음
    s2.display();  // Hello

    return 0;
}