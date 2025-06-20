/*
 * 동적 메모리 할당
 * 파일명: 17_dynamic_memory.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 17_dynamic_memory 17_dynamic_memory.cpp
 * 실행: ./17_dynamic_memory (Linux/Mac) 또는 17_dynamic_memory.exe (Windows)
 */

/*
주제: 동적 메모리 할당 (Dynamic Memory Allocation)
정의: 프로그램 실행 중에 필요에 따라 힙(heap) 메모리 영역에서 메모리를 할당하고 해제하는 기법

핵심 개념: new, delete, 힙 메모리, 스택 vs 힙, nullptr
정의:
- new: 힙 메모리에 새로운 객체를 할당하는 연산자
- delete: new로 할당된 메모리를 해제하는 연산자
- 힙 메모리: 동적 할당이 이루어지는 메모리 영역 (프로그래머가 직접 관리)
- 스택 vs 힙: 스택은 자동 관리, 힙은 수동 관리가 필요한 메모리 영역
- nullptr: null 포인터 리터럴, 포인터가 아무것도 가리키지 않는다는 것을 명시적으로 나타냄

C++ 메모리 구조 (Memory Layout):
┌─────────────────┐ ← 높은 주소 (0xFFFFFFFF)
│   커널 영역      │   (운영체제 전용)
├─────────────────┤
│   스택 (Stack)   │   - 지역변수, 함수 매개변수, 리턴 주소 저장
│       ↓        │   - 함수 호출 시 자동 생성, 함수 종료 시 자동 해제
│                │   - 크기 제한 있음 (보통 1-8MB)
│                │   - 빠른 접근 속도
├─────────────────┤
│   힙 (Heap)     │   - new/malloc으로 동적 할당되는 영역
│       ↑        │   - 프로그래머가 직접 관리 (new/delete)
│                │   - 크기 제한 거의 없음 (시스템 메모리까지)
│                │   - 상대적으로 느린 접근 속도
├─────────────────┤
│ 데이터 영역(BSS) │   - 초기화되지 않은 전역/정적 변수
├─────────────────┤
│ 데이터 영역(Data)│   - 초기화된 전역/정적 변수
├─────────────────┤
│ 코드 영역(Text)  │   - 실행 가능한 코드(기계어)
└─────────────────┘ ← 낮은 주소 (0x00000000)

스택과 힙의 성장 방향:
- 스택: 높은 주소 → 낮은 주소로 성장 (↓)
- 힙: 낮은 주소 → 높은 주소로 성장 (↑)
*/

#include <iostream>
using namespace std;

int main() {
    cout << "=== C++ 메모리 구조 이해 ===" << endl;

    // 스택 메모리 (자동 관리)
    int stackVar = 100;
    cout << "스택 변수: " << stackVar << ", 주소: " << &stackVar << endl;

    // 힙 메모리 (수동 관리)
    int* heapPtr = new int(200);
    cout << "힙 변수: " << *heapPtr << ", 주소: " << heapPtr << endl;
    cout << "포인터 자체 주소(스택): " << &heapPtr << endl;

    cout << "\n=== nullptr의 중요성 ===" << endl;

    // nullptr 사용법
    int* nullPtr = nullptr;  // C++11 이후 권장 방법
    int* oldNull = NULL;     // C 스타일 (권장하지 않음)
    int* zeroPtr = 0;        // 숫자 0 사용 (권장하지 않음)

    cout << "nullptr 값: " << nullPtr << endl;
    cout << "nullptr과 0 비교: " << (nullPtr == 0) << endl;
    cout << "nullptr과 NULL 비교: " << (nullPtr == NULL) << endl;

    // 안전한 포인터 사용 패턴
    if (nullPtr == nullptr) {
        cout << "포인터가 null입니다 - 안전함" << endl;
    }

    cout << "\n=== 동적 메모리 할당 예제 ===" << endl;

    // 정수 동적 할당
    int* intPtr = new int(42);
    cout << "동적 할당된 정수: " << *intPtr << endl;
    cout << "할당된 주소: " << intPtr << endl;

    // 값 변경
    *intPtr = 100;
    cout << "값 변경 후: " << *intPtr << endl;

    // 메모리 해제 후 nullptr 설정 (중요!)
    delete intPtr;
    intPtr = nullptr;  // 댕글링 포인터 방지
    cout << "메모리 해제 후 포인터: " << intPtr << endl;

    cout << "\n=== 다양한 타입의 동적 할당 ===" << endl;

    // double 타입 동적 할당
    double* doublePtr = new double(3.14159);
    cout << "동적 할당된 실수: " << *doublePtr << endl;

    // bool 타입 동적 할당
    bool* boolPtr = new bool(true);
    cout << "동적 할당된 불린: " << *boolPtr << endl;

    // char 타입 동적 할당
    char* charPtr = new char('A');
    cout << "동적 할당된 문자: " << *charPtr << endl;

    // 메모리 해제 및 nullptr 설정
    delete doublePtr;
    delete boolPtr;
    delete charPtr;
    doublePtr = nullptr;
    boolPtr = nullptr;
    charPtr = nullptr;

    cout << "\n=== 메모리 주소 비교 ===" << endl;
    int stackVar1 = 10;
    int stackVar2 = 20;
    int* heapVar1 = new int(30);
    int* heapVar2 = new int(40);

    cout << "스택 변수1 주소: " << &stackVar1 << endl;
    cout << "스택 변수2 주소: " << &stackVar2 << endl;
    cout << "힙 변수1 주소: " << heapVar1 << endl;
    cout << "힙 변수2 주소: " << heapVar2 << endl;

    cout << "\n스택 주소들은 서로 가깝고, 힙 주소들도 서로 가까운 것을 확인!" << endl;

    // 정리
    delete heapVar1;
    delete heapVar2;
    heapVar1 = nullptr;
    heapVar2 = nullptr;

    cout << "\n=== 동적 할당 vs 정적 할당 비교 ===" << endl;
    cout << "정적 할당 (스택):" << endl;
    cout << "  - 빠른 할당/해제" << endl;
    cout << "  - 자동 메모리 관리" << endl;
    cout << "  - 크기 제한 있음" << endl;
    cout << "  - 함수 종료시 자동 해제" << endl;

    cout << "\n동적 할당 (힙):" << endl;
    cout << "  - 상대적으로 느린 할당/해제" << endl;
    cout << "  - 수동 메모리 관리 필요" << endl;
    cout << "  - 큰 메모리 할당 가능" << endl;
    cout << "  - 명시적 해제 전까지 유지" << endl;

    return 0;
}