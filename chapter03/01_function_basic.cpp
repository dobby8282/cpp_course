/*
 * 함수 기초
 * 파일명: 01_function_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 01_function_basic 01_function_basic.cpp
 * 실행: ./01_function_basic (Linux/Mac) 또는 01_function_basic.exe (Windows)
 */

/*
주제: 함수 (Function)
정의: 특정 작업을 수행하는 코드 블록으로, 재사용 가능하고 모듈화된 프로그램 구성 요소

핵심 개념: 함수 선언, 함수 정의, 함수 호출, 반환값
정의:
- 함수 선언: 함수의 이름, 매개변수, 반환 타입을 컴파일러에게 알리는 것
- 함수 정의: 함수가 실제로 수행할 작업을 구현하는 것
- 함수 호출: 정의된 함수를 실행하는 것
- 반환값: 함수가 처리 결과로 돌려주는 값
*/

#include <iostream>
using namespace std;

// 함수 선언
int add(int a, int b);
void greet();

int main() {
    // 함수 호출
    greet();

    int result = add(5, 3);
    cout << "5 + 3 = " << result << endl;

    return 0;
}

// 함수 정의
int add(int a, int b) {
    return a + b;
}

void greet() {
    cout << "안녕하세요! 함수를 배워봅시다." << endl;
}