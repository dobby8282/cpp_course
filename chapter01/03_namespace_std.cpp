/*
 * std 네임스페이스 활용
 * 파일명: 03_namespace_std.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 03_namespace_std 03_namespace_std.cpp
 * 실행: ./03_namespace_std (Linux/Mac) 또는 03_namespace_std.exe (Windows)
 */

/*
주제: std 네임스페이스 (std Namespace)
정의: C++ 표준 라이브러리의 모든 구성 요소가 정의된 네임스페이스

핵심 개념: using namespace, using 선언, 표준 라이브러리
정의:
- using namespace: 특정 네임스페이스의 모든 요소를 현재 영역으로 가져오는 지시문
- using 선언: 특정 네임스페이스의 개별 요소만 가져오는 선언
- 표준 라이브러리: C++에서 제공하는 미리 작성된 함수와 클래스의 집합
*/

#include <iostream>
using namespace std;

int main() {
    cout << "using namespace std 사용" << endl;
    cout << "std:: 접두사 생략 가능" << endl;
    return 0;
}