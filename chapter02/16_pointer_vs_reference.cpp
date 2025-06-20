/*
 * 포인터와 레퍼런스 비교
 * 파일명: 16_pointer_vs_reference.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 16_pointer_vs_reference 16_pointer_vs_reference.cpp
 * 실행: ./16_pointer_vs_reference (Linux/Mac) 또는 16_pointer_vs_reference.exe (Windows)
 */

/*
주제: 포인터 vs 레퍼런스 (Pointer vs Reference)
정의: 간접 접근을 제공하는 두 가지 방법의 특성과 사용법 차이점 비교

핵심 개념: 재할당 가능성, 초기화 요구사항, 문법 차이
정의:
- 재할당 가능성: 포인터는 다른 변수를 가리킬 수 있지만 레퍼런스는 불가능
- 초기화 요구사항: 레퍼런스는 선언 시 반드시 초기화, 포인터는 나중에 가능
- 문법 차이: 포인터는 *로 역참조 필요, 레퍼런스는 직접 사용
*/

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;

    // 레퍼런스
    int& ref = a;
    cout << "레퍼런스: " << ref << endl;

    // 포인터
    int* ptr = &a;
    cout << "포인터가 가리키는 값: " << *ptr << endl;

    // 포인터는 재할당 가능
    ptr = &b;
    cout << "포인터 재할당 후: " << *ptr << endl;

    // 레퍼런스는 재할당 불가능 (다른 변수 참조 불가)
    // ref = b;  // 이것은 b의 값을 a에 복사하는 것

    return 0;
}