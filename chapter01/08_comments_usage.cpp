/*
 * 주석 활용법
 * 파일명: 08_comments_usage.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 08_comments_usage 08_comments_usage.cpp
 * 실행: ./08_comments_usage (Linux/Mac) 또는 08_comments_usage.exe (Windows)
 */

/*
주제: 코드 문서화 (Code Documentation)
정의: 코드의 가독성과 유지보수성을 높이기 위한 주석과 문서화 기법

핵심 개념: 단일행 주석, 블록 주석, 문서화 주석, TODO/FIXME
정의:
- 단일행 주석(//): 한 줄짜리 간단한 설명을 위한 주석
- 블록 주석(/* */): 여러 줄에 걸친 긴 설명이나 코드 블록 비활성화용 주석
- 문서화 주석(/** */): 함수, 클래스 등의 공식 문서화를 위한 주석
- TODO/FIXME: 향후 개선사항이나 수정할 부분을 표시하는 특수 주석
*/

#include <iostream>
using namespace std;

/**
 * 원의 넓이를 계산하는 프로그램
 * 작성자: C++ 개발팀
 * 버전: 1.0
 */

int main() {
    const double PI = 3.14159;  // 원주율 상수
    double radius;              // 반지름

    cout << "원의 반지름을 입력하세요: ";
    cin >> radius;

    // 원의 넓이 계산: π × r²
    double area = PI * radius * radius;

    cout << "원의 넓이: " << area << endl;

    /* 
    TODO: 추후 개선사항
    - 입력 값 검증 추가
    - 둘레 계산 기능 추가
    - 예외 처리 구현
    */

    return 0;
}