/*
 * 네임스페이스 기초
 * 파일명: 02_namespace_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 02_namespace_basic 02_namespace_basic.cpp
 * 실행: ./02_namespace_basic (Linux/Mac) 또는 02_namespace_basic.exe (Windows)
 */

/*
주제: 네임스페이스 (Namespace)
정의: 이름 충돌을 방지하고 코드를 논리적으로 그룹화하기 위한 명명 영역

핵심 개념: namespace 키워드, 범위 해석 연산자(::), 이름 충돌 방지
정의:
- namespace 키워드: 새로운 명명 영역을 정의하는 키워드
- 범위 해석 연산자(::): 특정 네임스페이스의 요소에 접근하기 위한 연산자
- 이름 충돌 방지: 같은 이름의 함수나 변수를 다른 네임스페이스에서 구분하여 사용
*/

#include <iostream>

namespace Graphics {
    void draw() {
        std::cout << "Graphics::draw() 호출" << std::endl;
    }
}

namespace Audio {
    void draw() {
        std::cout << "Audio::draw() 호출" << std::endl;
    }
}

int main() {
    Graphics::draw();  // Graphics 네임스페이스의 draw 함수
    Audio::draw();     // Audio 네임스페이스의 draw 함수
    return 0;
}