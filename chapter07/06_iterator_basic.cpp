/*
 * 반복자 기초
 * 파일명: 06_iterator_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 06_iterator_basic 06_iterator_basic.cpp
 * 실행: ./06_iterator_basic (Linux/Mac) 또는 06_iterator_basic.exe (Windows)
 */

/*
주제: 반복자 기초 (Iterator Basics)
정의: 컨테이너의 요소들을 순차적으로 접근하는 객체
*/

#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

int main() {
    cout << "=== vector 반복자 ===" << endl;
    vector<int> numbers = {10, 20, 30, 40, 50};

    // 순방향 반복자
    cout << "순방향: ";
    for (vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 역방향 반복자
    cout << "역방향: ";
    for (vector<int>::reverse_iterator it = numbers.rbegin(); it != numbers.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // auto 키워드 사용 (C++11)
    cout << "auto 사용: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n=== list 반복자 ===" << endl;
    list<string> words = {"hello", "world", "STL"};

    for (auto it = words.begin(); it != words.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n=== map 반복자 ===" << endl;
    map<string, int> ages = {{"김철수", 25}, {"이영희", 23}, {"박민수", 27}};

    for (auto it = ages.begin(); it != ages.end(); ++it) {
        cout << it->first << ": " << it->second << "세" << endl;
    }

    cout << "\n=== 반복자로 요소 수정 ===" << endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        *it *= 2;  // 각 요소를 2배로
    }

    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}