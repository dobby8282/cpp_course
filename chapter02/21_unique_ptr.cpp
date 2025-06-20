/*
 * unique_ptr 기초
 * 파일명: 21_unique_ptr.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 21_unique_ptr 21_unique_ptr.cpp
 * 실행: ./21_unique_ptr (Linux/Mac) 또는 21_unique_ptr.exe (Windows)
 */

/*
주제: 스마트 포인터 (Smart Pointers)
정의: 자동으로 메모리를 관리해주는 포인터 래퍼 클래스로, 메모리 누수를 방지하는 현대 C++의 핵심 기능

핵심 개념: unique_ptr, make_unique, 자동 해제, 독점 소유권, auto 키워드
정의:
- unique_ptr: 하나의 객체를 독점적으로 소유하는 스마트 포인터
- make_unique: unique_ptr을 안전하게 생성하는 헬퍼 함수
- 자동 해제: 스코프를 벗어날 때 자동으로 메모리를 해제하는 기능
- 독점 소유권: 한 번에 하나의 unique_ptr만이 객체를 소유할 수 있는 특성
- auto 키워드: 컴파일러가 변수의 타입을 자동으로 추론하게 하는 키워드 (C++11)

unique_ptr의 독점 특성:
- 복사 불가능: unique_ptr은 복사 생성자와 복사 대입 연산자가 삭제됨
- 이동 가능: std::move를 통해 소유권 이전 가능
- 하나의 객체는 한 번에 하나의 unique_ptr만 소유 가능
- 소유권 이전 시 기존 unique_ptr은 nullptr이 됨

auto 키워드 특징:
- 컴파일 타임에 타입 자동 추론
- 복잡한 타입명을 간단하게 표현
- 템플릿과 함께 사용 시 매우 유용
- 초기화 표현식을 기반으로 타입 결정
*/

#include <iostream>
#include <memory>
using namespace std;

int main() {
    cout << "=== auto 키워드 활용 ===" << endl;

    // auto로 기본 타입 추론
    auto intVar = 42;        // int로 추론
    auto doubleVar = 3.14;   // double로 추론
    auto stringVar = "Hello"; // const char*로 추론

    cout << "auto intVar = 42; (타입: int)" << endl;
    cout << "auto doubleVar = 3.14; (타입: double)" << endl;
    cout << "auto stringVar = \"Hello\"; (타입: const char*)" << endl;

    // auto와 포인터
    int value = 100;
    auto ptr = &value;       // int*로 추론
    cout << "auto ptr = &value; (타입: int*) 값: " << *ptr << endl;

    cout << "\n=== unique_ptr 기본 사용법 ===" << endl;

    // unique_ptr 생성 (auto 사용)
    auto ptr1 = make_unique<int>(42);
    cout << "auto ptr1 = make_unique<int>(42); 값: " << *ptr1 << endl;
    cout << "ptr1 주소: " << ptr1.get() << endl;

    // 명시적 타입 선언과 비교
    unique_ptr<int> ptr2 = make_unique<int>(100);
    cout << "unique_ptr<int> ptr2 = make_unique<int>(100); 값: " << *ptr2 << endl;
    cout << "ptr2 주소: " << ptr2.get() << endl;

    cout << "\n=== unique_ptr의 독점 소유권 ===" << endl;

    auto original = make_unique<int>(999);
    cout << "original 포인터: " << original.get() << ", 값: " << *original << endl;

    // 복사 시도 (컴파일 에러!)
    // auto copy = original;  // 에러! unique_ptr은 복사 불가능

    // 소유권 이전 (이동)
    auto moved = std::move(original);
    cout << "이동 후:" << endl;
    cout << "moved 포인터: " << moved.get() << ", 값: " << *moved << endl;
    cout << "original 포인터: " << original.get() << " (nullptr)" << endl;

    // original은 이제 nullptr이므로 사용하면 안됨!
    if (original == nullptr) {
        cout << "original은 더 이상 객체를 소유하지 않음" << endl;
    }

    cout << "\n=== 배열 unique_ptr ===" << endl;

    // 배열 버전 unique_ptr
    auto arr = make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }

    cout << "배열 내용: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "\n=== unique_ptr vs 일반 포인터 비교 ===" << endl;

    // 일반 포인터 (수동 관리)
    int* rawPtr = new int(123);
    cout << "일반 포인터 값: " << *rawPtr << endl;
    delete rawPtr;  // 수동으로 해제 필요
    rawPtr = nullptr;

    // unique_ptr (자동 관리)
    {
        auto smartPtr = make_unique<int>(456);
        cout << "스마트 포인터 값: " << *smartPtr << endl;
        // 스코프 종료 시 자동으로 해제됨
    }
    cout << "스마트 포인터는 자동으로 해제됨" << endl;

    cout << "\n=== unique_ptr 유용한 멤버 함수들 ===" << endl;

    auto ptr3 = make_unique<int>(777);

    // get(): 내부 포인터 반환 (소유권은 유지)
    int* rawAddress = ptr3.get();
    cout << "get()으로 주소 얻기: " << rawAddress << ", 값: " << *rawAddress << endl;

    // reset(): 새로운 포인터로 재설정
    ptr3.reset(new int(888));
    cout << "reset() 후 값: " << *ptr3 << endl;

    // release(): 소유권 포기하고 포인터 반환
    int* releasedPtr = ptr3.release();
    cout << "release() 후:" << endl;
    cout << "ptr3: " << ptr3.get() << " (nullptr)" << endl;
    cout << "releasedPtr: " << releasedPtr << ", 값: " << *releasedPtr << endl;
    delete releasedPtr;  // release() 후에는 수동 삭제 필요!

    cout << "\n=== auto 키워드의 장점 ===" << endl;
    cout << "1. 타입 추론으로 코드 간소화" << endl;
    cout << "2. 타입 변경 시 유지보수 용이" << endl;
    cout << "3. 복잡한 템플릿 타입 간단하게 표현" << endl;
    cout << "4. 초기화 강제 (auto는 반드시 초기화 필요)" << endl;

    cout << "\n=== unique_ptr 사용 권장 사항 ===" << endl;
    cout << "1. new/delete 대신 make_unique 사용" << endl;
    cout << "2. 원시 포인터보다 스마트 포인터 우선" << endl;
    cout << "3. 소유권이 명확한 경우 unique_ptr 사용" << endl;
    cout << "4. auto 키워드로 코드 간소화" << endl;

    // 스코프 종료 시 모든 unique_ptr 자동 해제
    return 0;
}