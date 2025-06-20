/*
 * 람다와 STL 알고리즘
 * 파일명: 09_lambda_stl_algorithm.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 09_lambda_stl_algorithm 09_lambda_stl_algorithm.cpp
 * 실행: ./09_lambda_stl_algorithm (Linux/Mac) 또는 09_lambda_stl_algorithm.exe (Windows)
 */

/*
주제: 람다와 STL 알고리즘 (Lambda with STL Algorithms)
정의: 람다 표현식을 STL 알고리즘과 함께 사용하여 강력한 기능 구현
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "=== find_if 알고리즘 ===" << endl;
    // 첫 번째 짝수 찾기
    auto it = find_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });

    if (it != numbers.end()) {
        cout << "첫 번째 짝수: " << *it << endl;
    }

    cout << "\n=== count_if 알고리즘 ===" << endl;
    // 5보다 큰 수의 개수
    int count = count_if(numbers.begin(), numbers.end(), [](int n) {
        return n > 5;
    });
    cout << "5보다 큰 수의 개수: " << count << endl;

    cout << "\n=== transform 알고리즘 ===" << endl;
    vector<int> squared(numbers.size());
    transform(numbers.begin(), numbers.end(), squared.begin(), [](int n) {
        return n * n;
    });

    cout << "제곱값: ";
    for (int n : squared) cout << n << " ";
    cout << endl;

    cout << "\n=== sort with 람다 ===" << endl;
    vector<string> words = {"banana", "apple", "cherry", "date"};

    // 길이 순으로 정렬
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });

    cout << "길이 순 정렬: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;

    cout << "\n=== remove_if 알고리즘 ===" << endl;
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 홀수 제거
    auto newEnd = remove_if(data.begin(), data.end(), [](int n) {
        return n % 2 == 1;
    });
    data.erase(newEnd, data.end());

    cout << "홀수 제거 후: ";
    for (int n : data) cout << n << " ";
    cout << endl;

    cout << "\n=== for_each with 캡처 ===" << endl;
    int sum = 0;
    for_each(numbers.begin(), numbers.end(), [&sum](int n) {
        sum += n;
    });
    cout << "총합: " << sum << endl;

    return 0;
}