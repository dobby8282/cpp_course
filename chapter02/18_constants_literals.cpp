/*
 * 상수와 리터럴
 * 파일명: 18_constants_literals.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 18_constants_literals 18_constants_literals.cpp
 * 실행: ./18_constants_literals (Linux/Mac) 또는 18_constants_literals.exe (Windows)
 */

/*
주제: 상수와 리터럴 (Constants and Literals)
정의: 프로그램 실행 중 값이 변경되지 않는 데이터와 코드에 직접 기술되는 고정값

핵심 개념: const, constexpr, 리터럴 접미사, 매크로, 컴파일 단계
정의:
- const: 런타임에 값이 결정되고 이후 변경할 수 없는 상수
- constexpr: 컴파일 타임에 값이 결정되는 상수 표현식
- 리터럴 접미사: 리터럴의 타입을 명시하는 접미사 (f, L, u 등)
- 매크로: 전처리기에 의해 텍스트 치환되는 기호 상수

프로그램 실행 단계:
1. 전처리(Preprocessing): 
   - #include, #define 등의 전처리 지시문 처리
   - 매크로 치환, 헤더 파일 포함
   - 소스 코드 → 전처리된 소스 코드

2. 컴파일 타임(Compile Time):
   - 전처리된 소스 코드를 기계어로 번역
   - 문법 검사, 타입 검사, 최적화 수행
   - constexpr 값들이 이 단계에서 계산됨
   - 소스 코드 → 오브젝트 파일(.obj, .o)

3. 링크 타임(Link Time):
   - 여러 오브젝트 파일을 하나의 실행 파일로 결합
   - 라이브러리 연결, 외부 참조 해결

4. 런타임(Runtime):
   - 실제 프로그램이 실행되는 시점
   - const 변수의 값이 결정되고 메모리에 저장
   - 사용자 입력, 계산 결과 등이 처리됨

시간 순서: 전처리 → 컴파일 → 링크 → 런타임
*/

#include <iostream>
using namespace std;

// 매크로 상수 정의 (전처리 단계에서 텍스트 치환)
#define MAX_BUFFER_SIZE 1024
#define VERSION "2.1.0"
#define SQUARE(x) ((x) * (x))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    cout << "=== 프로그램 실행 단계별 상수 처리 ===" << endl;

    // 전처리 단계: 매크로 치환
    cout << "1. 전처리: #define MAX_BUFFER_SIZE → " << MAX_BUFFER_SIZE << endl;
    cout << "   (소스 코드에서 MAX_BUFFER_SIZE가 1024로 치환됨)" << endl;

    // 컴파일 타임: constexpr 계산
    constexpr int ARRAY_SIZE = 10;
    constexpr double GRAVITY = 9.8;
    constexpr int CALCULATED = SQUARE(5);  // 컴파일 시점에 25로 계산

    cout << "\n2. 컴파일 타임: constexpr 값들이 미리 계산됨" << endl;
    cout << "   constexpr int ARRAY_SIZE = " << ARRAY_SIZE << endl;
    cout << "   constexpr double GRAVITY = " << GRAVITY << endl;
    cout << "   constexpr int CALCULATED = " << CALCULATED << " (5*5가 컴파일 시 계산됨)" << endl;

    // 런타임: const 변수 초기화
    const int MAX_STUDENTS = 30;
    const double PI = 3.14159;
    const string SCHOOL_NAME = "C++ 학원";

    cout << "\n3. 런타임: const 변수들이 실행 시점에 초기화됨" << endl;
    cout << "   const int MAX_STUDENTS = " << MAX_STUDENTS << endl;
    cout << "   const double PI = " << PI << endl;
    cout << "   const string SCHOOL_NAME = " << SCHOOL_NAME << endl;

    // 사용자 입력을 받는 const (런타임에 결정)
    int userInput;
    cout << "\n숫자를 입력하세요: ";
    cin >> userInput;

    const int USER_CONSTANT = userInput;  // 런타임에 값이 결정됨
    cout << "사용자가 입력한 const 값: " << USER_CONSTANT << endl;

    cout << "\n=== 매크로 vs const vs constexpr 비교 ===" << endl;

    // 매크로 (전처리 단계)
    cout << "매크로 SQUARE(3): " << SQUARE(3) << " (전처리 시 ((3) * (3))로 치환)" << endl;
    cout << "매크로 버전: " << VERSION << " (전처리 시 \"2.1.0\"로 치환)" << endl;

    // constexpr (컴파일 타임)
    constexpr int COMPILE_TIME_CALC = 5 * 5;
    cout << "constexpr 계산: " << COMPILE_TIME_CALC << " (컴파일 시 25로 계산)" << endl;

    // const (런타임)
    const int RUNTIME_CONST = MAX_STUDENTS + 10;
    cout << "const 계산: " << RUNTIME_CONST << " (런타임에 40으로 계산)" << endl;

    cout << "\n=== 리터럴과 접미사 ===" << endl;
    cout << "정수 리터럴: " << 42 << " (컴파일 시 int 타입으로 결정)" << endl;
    cout << "실수 리터럴: " << 3.14 << " (컴파일 시 double 타입으로 결정)" << endl;
    cout << "float 리터럴: " << 3.14f << " (f 접미사로 float 타입 명시)" << endl;
    cout << "long 리터럴: " << 1000000L << " (L 접미사로 long 타입 명시)" << endl;
    cout << "unsigned 리터럴: " << 100u << " (u 접미사로 unsigned 타입 명시)" << endl;
    cout << "16진수 리터럴: " << 0xFF << " (0x 접두사, 10진수: " << 0xFF << ")" << endl;
    cout << "8진수 리터럴: " << 077 << " (0 접두사, 10진수: " << 077 << ")" << endl;
    cout << "2진수 리터럴: " << 0b1010 << " (0b 접두사, 10진수: " << 0b1010 << ")" << endl;

    // 배열에서 constexpr 사용 (컴파일 타임에 크기 결정)
    int numbers[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    cout << "\n배열 크기가 컴파일 타임에 결정됨: " << sizeof(numbers)/sizeof(int) << "개" << endl;

    // 매크로를 이용한 배열 (전처리 시점에 크기 결정)
    char buffer[MAX_BUFFER_SIZE];
    cout << "매크로로 정의된 버퍼 크기: " << sizeof(buffer) << " 바이트" << endl;

    cout << "\n=== 상수 타입별 장단점 ===" << endl;
    cout << "매크로 (#define):" << endl;
    cout << "  장점: 전처리 단계에서 치환, 조건부 컴파일 가능" << endl;
    cout << "  단점: 타입 안전성 없음, 디버깅 어려움, 스코프 무시" << endl;

    cout << "\nconst:" << endl;
    cout << "  장점: 타입 안전성, 스코프 존중, 런타임 값 사용 가능" << endl;
    cout << "  단점: 런타임 메모리 사용, 배열 크기로 사용 불가" << endl;

    cout << "\nconstexpr:" << endl;
    cout << "  장점: 컴파일 타임 계산, 타입 안전성, 성능 최적화" << endl;
    cout << "  단점: 컴파일 타임에 값이 결정되어야 함" << endl;

    // const 변수는 초기화 후 변경 불가
    // MAX_STUDENTS = 40; // 오류!
    // ARRAY_SIZE = 20;   // 오류!

    return 0;
}