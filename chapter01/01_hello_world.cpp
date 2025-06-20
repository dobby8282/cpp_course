/*
 * Hello World
 * 파일명: 01_hello_world.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 01_hello_world 01_hello_world.cpp
 * 실행: ./01_hello_world (Linux/Mac) 또는 01_hello_world.exe (Windows)
 */

/*
주제: C++ 프로그램 구조 (C++ Program Structure)
정의: C++ 프로그램이 가져야 할 기본적인 구성 요소와 실행 흐름

핵심 개념: #include, main 함수, std::cout, return문
정의:
- #include: 헤더 파일을 포함시켜 필요한 라이브러리 기능을 사용할 수 있게 하는 전처리 지시문
- main 함수: 프로그램 실행의 시작점이 되는 함수
- std::cout: 표준 출력 스트림으로 화면에 데이터를 출력하는 객체
- return문: 함수의 실행을 종료하고 호출자에게 값을 반환하는 문장
*/

#include <iostream>

int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}