/*
 * 완벽한 전달
 * 파일명: 08_perfect_forwarding.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 08_perfect_forwarding 08_perfect_forwarding.cpp
 * 실행: ./08_perfect_forwarding (Linux/Mac) 또는 08_perfect_forwarding.exe (Windows)
 */

/*
주제: 완벽한 전달 (Perfect Forwarding)
정의: 인자를 원래 타입 그대로 다른 함수에 전달
*/

#include <iostream>
#include <utility>
using namespace std;

class Widget {
public:
    Widget(const string& name) {
        cout << "복사 생성: " << name << endl;
    }

    Widget(string&& name) {
        cout << "이동 생성: " << name << endl;
    }
};

// 완벽한 전달을 사용하는 팩토리 함수
template<typename T, typename... Args>
T createObject(Args&&... args) {
    return T(forward<Args>(args)...);
}

void processValue(const string& s) {
    cout << "lvalue: " << s << endl;
}

void processValue(string&& s) {
    cout << "rvalue: " << s << endl;
}

template<typename T>
void forwardValue(T&& value) {
    processValue(forward<T>(value));
}

int main() {
    // 팩토리 함수 테스트
    string name = "test";
    createObject<Widget>(name);        // 복사 생성
    createObject<Widget>("literal");   // 이동 생성

    // 완벽한 전달 테스트
    string str = "hello";
    forwardValue(str);                 // lvalue
    forwardValue("world");             // rvalue

    return 0;
}