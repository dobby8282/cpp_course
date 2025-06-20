/*
 * nullptr과 안전성
 * 파일명: 20_nullptr_safety.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 20_nullptr_safety 20_nullptr_safety.cpp
 * 실행: ./20_nullptr_safety (Linux/Mac) 또는 20_nullptr_safety.exe (Windows)
 */

/*
주제: 포인터 안전성 (Pointer Safety)
정의: 포인터 사용 시 발생할 수 있는 오류를 방지하고 안전하게 메모리에 접근하는 프로그래밍 기법

핵심 개념: nullptr, 널 포인터 검사, 댕글링 포인터 방지
정의:
- nullptr: 아무것도 가리키지 않는 포인터 상태를 나타내는 C++11의 널 포인터 상수
- 널 포인터 검사: 포인터가 유효한 메모리를 가리키는지 확인하는 안전 검사
- 댕글링 포인터 방지: 해제된 메모리를 가리키는 포인터 사용을 막는 기법
*/

#include <iostream>
using namespace std;

int main() {
    int* ptr = nullptr;

    // 안전한 포인터 사용
    if (ptr != nullptr) {
        cout << "값: " << *ptr << endl;
    } else {
        cout << "포인터가 nullptr입니다." << endl;
    }

    // 포인터에 메모리 할당
    ptr = new int(100);

    if (ptr != nullptr) {
        cout << "할당 후 값: " << *ptr << endl;
        delete ptr;
        ptr = nullptr;
    }

    return 0;
}