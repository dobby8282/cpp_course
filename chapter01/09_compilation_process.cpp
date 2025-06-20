/*
 * 컴파일 과정 이해
 * 파일명: 09_compilation_process.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 09_compilation_process 09_compilation_process.cpp
 * 실행: ./09_compilation_process (Linux/Mac) 또는 09_compilation_process.exe (Windows)
 */

/*
주제: 컴파일 과정 (Compilation Process)
정의: C++ 소스 코드가 실행 가능한 프로그램으로 변환되는 과정

핵심 개념: 전처리기, 매크로, 조건부 컴파일, #define
정의:
- 전처리기: 컴파일 전에 소스 코드를 변환하는 프로그램
- 매크로: 코드의 일부를 다른 텍스트로 치환하는 전처리 기능
- 조건부 컴파일: 특정 조건에 따라 코드의 일부를 포함하거나 제외하는 기법
- #define: 매크로를 정의하는 전처리 지시문
*/

#include <iostream>
#define MAX_SIZE 100
#define SQUARE(x) ((x) * (x))

#ifdef DEBUG
    #define LOG(msg) std::cout << "[DEBUG] " << msg << std::endl
#else
    #define LOG(msg)
#endif

using namespace std;

int main() {
    int array[MAX_SIZE];  // 전처리기에서 100으로 치환
    int value = 5;

    cout << "배열 크기: " << MAX_SIZE << endl;
    cout << value << "의 제곱: " << SQUARE(value) << endl;

    LOG("디버그 모드에서만 출력됨");

    cout << "\n=== 컴파일 단계 ===" << endl;
    cout << "1. 전처리 (Preprocessing)" << endl;
    cout << "2. 컴파일 (Compilation)" << endl;
    cout << "3. 어셈블리 (Assembly)" << endl;
    cout << "4. 링킹 (Linking)" << endl;

    return 0;
}