/*
 * 형변환
 * 파일명: 19_type_casting.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 19_type_casting 19_type_casting.cpp
 * 실행: ./19_type_casting (Linux/Mac) 또는 19_type_casting.exe (Windows)
 */

/*
주제: 형변환 (Type Casting)
정의: 하나의 데이터 타입을 다른 데이터 타입으로 변환하는 과정

핵심 개념: 암시적 변환, 명시적 변환, C++ 캐스트 연산자, void* 포인터
정의:
- 암시적 변환: 컴파일러가 자동으로 수행하는 타입 변환
- 명시적 변환: 프로그래머가 의도적으로 지시하는 타입 변환
- C++ 캐스트 연산자: static_cast, dynamic_cast, const_cast, reinterpret_cast
- void* 포인터: 어떤 타입의 포인터든 저장할 수 있는 범용 포인터 (타입 정보 없음)

C++ 캐스트 연산자 상세:
1. static_cast<타입>(값):
   - 컴파일 타임에 타입 변환을 수행
   - 가장 일반적이고 안전한 캐스트
   - 기본 타입 간 변환, 상속 관계 포인터 변환 등
   - 런타임 검사 없음

2. dynamic_cast<타입>(값):
   - 런타임에 타입 안전성을 검사하는 캐스트
   - 다형성(상속, 가상함수)이 있는 클래스에서만 사용
   - 안전하지 않은 캐스트 시 nullptr 또는 예외 발생
   - 성능 오버헤드 있음

3. const_cast<타입>(값):
   - const 또는 volatile 속성을 제거하거나 추가
   - 실제 데이터 타입은 변경하지 않음
   - const 객체의 const성을 제거할 때 사용 (주의 필요)

4. reinterpret_cast<타입>(값):
   - 포인터를 다른 타입의 포인터로 재해석
   - 비트 패턴을 그대로 유지하면서 타입만 변경
   - 매우 위험하고 플랫폼 종속적
   - 시스템 프로그래밍에서 제한적 사용
*/

#include <iostream>
using namespace std;

int main() {
    cout << "=== 암시적 형변환 ===" << endl;
    int intValue = 10;
    double doubleValue = intValue;  // int → double (자동)
    cout << "int " << intValue << " → double " << doubleValue << endl;

    char charValue = 'A';
    int asciiValue = charValue;     // char → int (자동)
    cout << "char '" << charValue << "' → int " << asciiValue << endl;

    cout << "\n=== 명시적 형변환 (C 스타일) ===" << endl;
    double pi = 3.14159;
    int truncated = (int)pi;        // 소수점 이하 버림
    cout << "double " << pi << " → int " << truncated << endl;

    cout << "\n=== static_cast ===" << endl;
    double result = static_cast<double>(intValue) / 3;
    cout << "정확한 나눗셈: " << intValue << " / 3 = " << result << endl;

    // void* 포인터와 캐스팅
    cout << "\n=== void* 포인터 활용 ===" << endl;
    void* voidPtr = &intValue;  // void*는 어떤 타입의 포인터든 받을 수 있음
    cout << "void* 주소: " << voidPtr << endl;
    cout << "int 변수 주소: " << &intValue << endl;

    // void*는 역참조할 수 없으므로 적절한 타입으로 캐스팅 필요
    int* intPtr = static_cast<int*>(voidPtr);
    cout << "void* → int* 캐스팅 후 값: " << *intPtr << endl;

    // 다른 타입도 void*에 저장 가능
    double doubleVar = 99.9;
    voidPtr = &doubleVar;  // 같은 void*에 다른 타입 주소 저장
    double* doublePtr = static_cast<double*>(voidPtr);
    cout << "void*에 double 저장 후: " << *doublePtr << endl;

    cout << "\n=== C++ 캐스트 연산자 상세 ===" << endl;

    // 1. static_cast - 일반적인 타입 변환
    cout << "1. static_cast (일반적인 타입 변환):" << endl;
    int intNum = 10;
    double doubleNum = static_cast<double>(intNum);
    cout << "   int " << intNum << " → double " << doubleNum << endl;

    // 포인터 타입 변환
    void* voidPtr2 = &intNum;
    int* intPtr2 = static_cast<int*>(voidPtr2);
    cout << "   void* → int*: " << *intPtr2 << endl;

    // 2. const_cast - const 속성 제거/추가
    cout << "\n2. const_cast (const 속성 제거/추가):" << endl;
    const int constValue = 100;
    const int* constPtr = &constValue;

    // const 포인터에서 const 제거 (주의: 원본이 const면 수정하면 안됨!)
    int* nonConstPtr = const_cast<int*>(constPtr);
    cout << "   const int* → int*: " << *nonConstPtr << endl;

    // 비const를 const로 변환 (안전함)
    int normalInt = 200;
    int* normalPtr = &normalInt;
    const int* constPtr2 = const_cast<const int*>(normalPtr);
    cout << "   int* → const int*: " << *constPtr2 << endl;

    // 3. reinterpret_cast - 비트 패턴 재해석 (위험!)
    cout << "\n3. reinterpret_cast (비트 패턴 재해석 - 위험!):" << endl;
    int intForReinterpret = 0x41424344;  // ASCII 'ABCD'
    char* charPtr = reinterpret_cast<char*>(&intForReinterpret);
    cout << "   int의 비트를 char*로 재해석: ";
    for (int i = 0; i < 4; i++) {
        cout << charPtr[i] << " ";
    }
    cout << endl;

    // 포인터를 정수로 변환 (주소값 확인용)
    uintptr_t address = reinterpret_cast<uintptr_t>(&intNum);
    cout << "   포인터 주소를 정수로: 0x" << hex << address << dec << endl;

    cout << "\n=== 캐스트 연산자 안전성 비교 ===" << endl;
    cout << "static_cast:     안전함 (컴파일 타임 검사)" << endl;
    cout << "const_cast:      주의 필요 (const 의미 변경)" << endl;
    cout << "reinterpret_cast: 위험함 (비트 레벨 조작)" << endl;
    cout << "dynamic_cast:    가장 안전 (런타임 검사, 클래스에서 사용)" << endl;
    int largeInt = 300;
    char smallChar = static_cast<char>(largeInt);
    cout << "int " << largeInt << " → char " << static_cast<int>(smallChar) 
         << " (범위 초과로 데이터 손실 가능)" << endl;

    cout << "\n=== 실용적 예제 ===" << endl;
    // 평균 계산 시 정확한 결과를 위한 캐스팅
    int score1 = 85, score2 = 90, score3 = 78;
    double average = static_cast<double>(score1 + score2 + score3) / 3;
    cout << "평균 점수: " << average << endl;

    // 퍼센트 계산
    int correct = 23, total = 30;
    double percentage = static_cast<double>(correct) / total * 100;
    cout << "정답률: " << percentage << "%" << endl;

    return 0;
}