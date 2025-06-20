/*
 * 구조체 기초
 * 파일명: 01_struct_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 01_struct_basic 01_struct_basic.cpp
 * 실행: ./01_struct_basic (Linux/Mac) 또는 01_struct_basic.exe (Windows)
 */

/*
주제: 구조체 (Structure)
정의: 서로 다른 타입의 데이터를 하나의 단위로 묶어서 관리하는 사용자 정의 데이터 타입

핵심 개념: struct 키워드, 멤버 변수, 구조체 초기화, 멤버 접근
정의:
- struct 키워드: 구조체를 정의하는 C++ 키워드
- 멤버 변수: 구조체 내부에 정의된 변수들
- 구조체 초기화: 구조체 변수를 생성할 때 초기값을 설정하는 방법
- 멤버 접근: 점(.) 연산자를 사용하여 구조체의 멤버에 접근하는 방법
*/

#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
    double gpa;
};

int main() {
    // 구조체 변수 선언과 초기화
    Student student1;
    student1.name = "김철수";
    student1.age = 20;
    student1.gpa = 3.8;

    // 초기화 리스트 사용
    Student student2 = {"이영희", 19, 4.0};

    cout << "=== 학생 정보 ===" << endl;
    cout << "학생1: " << student1.name << ", " << student1.age << "세, GPA: " << student1.gpa << endl;
    cout << "학생2: " << student2.name << ", " << student2.age << "세, GPA: " << student2.gpa << endl;

    return 0;
}