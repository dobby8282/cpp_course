/*
 * list와 map 기초
 * 파일명: 05_list_map_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 05_list_map_basic 05_list_map_basic.cpp
 * 실행: ./05_list_map_basic (Linux/Mac) 또는 05_list_map_basic.exe (Windows)
 */

/*
주제: list와 map 기초 (List & Map Basics)
정의: 연결 리스트와 키-값 쌍을 관리하는 STL 컨테이너
*/

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

int main() {
    cout << "=== list 기초 ===" << endl;
    list<string> todoList;

    // 요소 추가
    todoList.push_back("숙제하기");
    todoList.push_front("일어나기");
    todoList.push_back("운동하기");

    cout << "할 일 목록:" << endl;
    for (const string& todo : todoList) {
        cout << "- " << todo << endl;
    }

    // 요소 삭제
    todoList.pop_front();  // 첫 번째 요소 삭제
    cout << "\n첫 번째 일 완료 후:" << endl;
    for (const string& todo : todoList) {
        cout << "- " << todo << endl;
    }

    cout << "\n=== map 기초 ===" << endl;
    map<string, int> scores;

    // 키-값 쌍 추가
    scores["김철수"] = 90;
    scores["이영희"] = 95;
    scores["박민수"] = 88;
    scores.insert(make_pair("최정화", 92));

    cout << "학생 점수:" << endl;
    for (const auto& pair : scores) {
        cout << pair.first << ": " << pair.second << "점" << endl;
    }

    // 특정 키 검색
    string name = "이영희";
    if (scores.find(name) != scores.end()) {
        cout << "\n" << name << "의 점수: " << scores[name] << "점" << endl;
    }

    // 키 존재 여부 확인
    cout << "박민수 등록됨? " << (scores.count("박민수") ? "예" : "아니오") << endl;
    cout << "홍길동 등록됨? " << (scores.count("홍길동") ? "예" : "아니오") << endl;

    return 0;
}