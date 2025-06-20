/*
 * STL 알고리즘 기초
 * 파일명: 07_stl_algorithm_basic.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 07_stl_algorithm_basic 07_stl_algorithm_basic.cpp
 * 실행: ./07_stl_algorithm_basic (Linux/Mac) 또는 07_stl_algorithm_basic.exe (Windows)
 */

/*
주제: STL 알고리즘 기초 (STL Algorithm Basics)
정의: 컨테이너에 적용할 수 있는 다양한 알고리즘 함수들
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<int> numbers = {5, 2, 8, 1, 9, 3};

    cout << "원본: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    cout << "\n=== 정렬 알고리즘 ===" << endl;
    sort(numbers.begin(), numbers.end());
    cout << "오름차순: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    sort(numbers.begin(), numbers.end(), greater<int>());
    cout << "내림차순: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    cout << "\n=== 검색 알고리즘 ===" << endl;
    sort(numbers.begin(), numbers.end());  // 이진 검색을 위해 정렬

    int target = 5;
    if (binary_search(numbers.begin(), numbers.end(), target)) {
        cout << target << "을(를) 찾았습니다." << endl;
    }

    auto it = find(numbers.begin(), numbers.end(), 8);
    if (it != numbers.end()) {
        cout << "8의 위치: " << distance(numbers.begin(), it) << endl;
    }

    cout << "\n=== 수치 알고리즘 ===" << endl;
    int sum = accumulate(numbers.begin(), numbers.end(), 0);
    cout << "합계: " << sum << endl;

    int maxVal = *max_element(numbers.begin(), numbers.end());
    int minVal = *min_element(numbers.begin(), numbers.end());
    cout << "최댓값: " << maxVal << ", 최솟값: " << minVal << endl;

    cout << "\n=== 변경 알고리즘 ===" << endl;
    replace(numbers.begin(), numbers.end(), 5, 50);  // 5를 50으로 변경
    cout << "5를 50으로 변경: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    return 0;
}