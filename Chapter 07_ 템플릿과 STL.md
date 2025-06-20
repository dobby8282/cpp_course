
---

# Chapter 07: 템플릿과 STL (예제 01~10)

## 1. 예제 01: 함수 템플릿 기초 (01_function_template_basic.cpp)

### 예제 정의
함수 템플릿의 기본 개념과 사용법을 학습합니다.

```cpp
/*
주제: 함수 템플릿 기초 (Function Template Basics)
정의: 다양한 타입에 대해 동일한 로직을 적용할 수 있는 제네릭 함수
*/

#include <iostream>
using namespace std;

// 함수 템플릿
template<typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// 여러 매개변수를 가진 템플릿
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 다중 타입 템플릿
template<typename T, typename U>
void printPair(T first, U second) {
    cout << "(" << first << ", " << second << ")" << endl;
}

int main() {
    // 정수형
    cout << "최댓값(10, 20): " << getMax(10, 20) << endl;
    
    // 실수형
    cout << "최댓값(3.5, 2.8): " << getMax(3.5, 2.8) << endl;
    
    // 문자열
    cout << "최댓값(\"apple\", \"banana\"): " << getMax(string("apple"), string("banana")) << endl;
    
    // swap 테스트
    int x = 5, y = 10;
    cout << "\nswap 전: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "swap 후: x=" << x << ", y=" << y << endl;
    
    // 다중 타입 템플릿
    printPair(42, "hello");
    printPair(3.14, 100);
    
    return 0;
}
```

---

## 2. 예제 02: 클래스 템플릿 기초 (02_class_template_basic.cpp)

### 예제 정의
클래스 템플릿을 사용하여 제네릭 클래스를 만드는 방법을 학습합니다.

```cpp
/*
주제: 클래스 템플릿 기초 (Class Template Basics)
정의: 다양한 타입을 다룰 수 있는 제네릭 클래스
*/

#include <iostream>
using namespace std;

template<typename T>
class Box {
private:
    T item;
    
public:
    Box(T i) : item(i) {}
    
    void setItem(T i) {
        item = i;
    }
    
    T getItem() {
        return item;
    }
    
    void display() {
        cout << "Box contains: " << item << endl;
    }
};

// 배열을 관리하는 클래스 템플릿
template<typename T, int SIZE>
class Array {
private:
    T data[SIZE];
    
public:
    void set(int index, T value) {
        if (index >= 0 && index < SIZE) {
            data[index] = value;
        }
    }
    
    T get(int index) {
        if (index >= 0 && index < SIZE) {
            return data[index];
        }
        return T{};  // 기본값 반환
    }
    
    void display() {
        for (int i = 0; i < SIZE; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // 다양한 타입의 Box 생성
    Box<int> intBox(42);
    Box<string> stringBox("Hello");
    Box<double> doubleBox(3.14);
    
    intBox.display();
    stringBox.display();
    doubleBox.display();
    
    // 크기가 고정된 배열
    Array<int, 5> intArray;
    for (int i = 0; i < 5; i++) {
        intArray.set(i, i * 10);
    }
    intArray.display();
    
    Array<string, 3> stringArray;
    stringArray.set(0, "첫번째");
    stringArray.set(1, "두번째");
    stringArray.set(2, "세번째");
    stringArray.display();
    
    return 0;
}
```

---

## 3. 예제 03: 템플릿 특수화 (03_template_specialization.cpp)

### 예제 정의
템플릿 특수화를 통해 특정 타입에 대한 전용 구현을 제공하는 방법을 학습합니다.

```cpp
/*
주제: 템플릿 특수화 (Template Specialization)
정의: 특정 타입에 대해 템플릿의 특별한 구현을 제공
*/

#include <iostream>
#include <string>
using namespace std;

// 일반 템플릿
template<typename T>
class Printer {
public:
    void print(T value) {
        cout << "일반: " << value << endl;
    }
};

// string에 대한 특수화
template<>
class Printer<string> {
public:
    void print(string value) {
        cout << "문자열 특수화: \"" << value << "\"" << endl;
    }
};

// bool에 대한 특수화
template<>
class Printer<bool> {
public:
    void print(bool value) {
        cout << "불린 특수화: " << (value ? "참" : "거짓") << endl;
    }
};

// 함수 템플릿과 특수화
template<typename T>
void describe(T value) {
    cout << "알 수 없는 타입: " << value << endl;
}

// int 특수화
template<>
void describe<int>(int value) {
    cout << "정수 " << value << "입니다." << endl;
}

// double 특수화
template<>
void describe<double>(double value) {
    cout << "실수 " << value << "입니다." << endl;
}

int main() {
    Printer<int> intPrinter;
    Printer<string> stringPrinter;
    Printer<bool> boolPrinter;
    Printer<double> doublePrinter;
    
    intPrinter.print(42);
    stringPrinter.print("Hello World");
    boolPrinter.print(true);
    doublePrinter.print(3.14);
    
    cout << "\n함수 템플릿 특수화:" << endl;
    describe(100);
    describe(3.14159);
    describe("문자열");  // 일반 템플릿 사용
    
    return 0;
}
```

---

## 4. 예제 04: vector 기초 (04_vector_basic.cpp)

### 예제 정의
STL vector 컨테이너의 기본 사용법을 학습합니다.

```cpp
/*
주제: vector 기초 (Vector Basics)
정의: 동적 배열을 제공하는 STL 컨테이너
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // vector 생성과 초기화
    vector<int> numbers;
    vector<int> scores = {90, 85, 92, 78, 96};
    vector<string> names(3, "unknown");  // 3개 요소를 "unknown"으로 초기화
    
    cout << "=== 요소 추가 ===" << endl;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    
    cout << "numbers 크기: " << numbers.size() << endl;
    
    cout << "\n=== 요소 접근 ===" << endl;
    for (int i = 0; i < numbers.size(); i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }
    
    cout << "\n=== range-based for loop ===" << endl;
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;
    
    cout << "\n=== 요소 수정 ===" << endl;
    scores[0] = 95;
    scores.at(1) = 88;  // 범위 검사 포함
    
    cout << "\n=== 요소 삭제 ===" << endl;
    cout << "삭제 전 크기: " << scores.size() << endl;
    scores.pop_back();  // 마지막 요소 삭제
    cout << "삭제 후 크기: " << scores.size() << endl;
    
    cout << "\n=== vector 정보 ===" << endl;
    cout << "비어있는가? " << (numbers.empty() ? "예" : "아니오") << endl;
    cout << "첫 번째 요소: " << numbers.front() << endl;
    cout << "마지막 요소: " << numbers.back() << endl;
    
    return 0;
}
```

---

## 5. 예제 05: list와 map 기초 (05_list_map_basic.cpp)

### 예제 정의
STL list와 map 컨테이너의 기본 사용법을 학습합니다.

```cpp
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
```

---

## 6. 예제 06: 반복자 기초 (06_iterator_basic.cpp)

### 예제 정의
STL 반복자의 개념과 사용법을 학습합니다.

```cpp
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
```

---

## 7. 예제 07: STL 알고리즘 기초 (07_stl_algorithm_basic.cpp)

### 예제 정의
STL 알고리즘의 기본 사용법을 학습합니다.

```cpp
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
```

---

## 8. 예제 08: 람다 표현식 기초 (08_lambda_basic.cpp)

### 예제 정의
람다 표현식의 기본 문법과 사용법을 학습합니다.

```cpp
/*
주제: 람다 표현식 기초 (Lambda Expression Basics)
정의: 익명 함수를 생성하는 C++11의 기능
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    cout << "=== 기본 람다 ===" << endl;
    
    // 가장 간단한 람다
    auto hello = []() {
        cout << "Hello Lambda!" << endl;
    };
    hello();
    
    // 매개변수를 받는 람다
    auto add = [](int a, int b) {
        return a + b;
    };
    cout << "5 + 3 = " << add(5, 3) << endl;
    
    // 반환 타입을 명시한 람다
    auto divide = [](double a, double b) -> double {
        return b != 0 ? a / b : 0;
    };
    cout << "10.0 / 3.0 = " << divide(10.0, 3.0) << endl;
    
    cout << "\n=== 캡처 절 ===" << endl;
    int x = 10;
    int y = 20;
    
    // 값으로 캡처
    auto lambda1 = [x, y]() {
        cout << "값 캡처: x=" << x << ", y=" << y << endl;
    };
    
    // 참조로 캡처
    auto lambda2 = [&x, &y]() {
        x += 5;
        y += 10;
        cout << "참조 캡처 후: x=" << x << ", y=" << y << endl;
    };
    
    // 모든 변수를 값으로 캡처
    auto lambda3 = [=]() {
        cout << "모든 변수 값 캡처: x=" << x << ", y=" << y << endl;
    };
    
    lambda1();
    lambda2();
    lambda3();
    
    cout << "\n=== STL과 함께 사용 ===" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 짝수만 출력
    cout << "짝수: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        if (n % 2 == 0) cout << n << " ";
    });
    cout << endl;
    
    return 0;
}
```

---

## 9. 예제 09: 람다와 STL 알고리즘 (09_lambda_stl_algorithm.cpp)

### 예제 정의
람다 표현식을 STL 알고리즘과 함께 활용하는 방법을 학습합니다.

```cpp
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
```

---

## 10. 예제 10: 템플릿과 STL 종합 프로젝트 (파일 분리)

### Container.h
```cpp
/*
주제: 템플릿과 STL 종합 프로젝트 - 제네릭 데이터 관리자 (헤더 파일)
정의: 템플릿, STL, 람다를 모두 활용한 실용적인 데이터 관리 시스템
*/

#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

// 제네릭 데이터 컨테이너 클래스
template<typename T>
class DataContainer {
private:
    vector<T> data;
    map<string, function<bool(const T&)>> filters;
    
public:
    void add(const T& item);
    void remove(const T& item);
    void clear();
    
    void sort();
    void sort(function<bool(const T&, const T&)> comparator);
    
    vector<T> filter(const string& filterName);
    void addFilter(const string& name, function<bool(const T&)> filter);
    
    void forEach(function<void(const T&)> action);
    T findFirst(function<bool(const T&)> predicate);
    
    void display();
    int size() const { return data.size(); }
    bool empty() const { return data.empty(); }
    
    // STL 스타일 인터페이스
    typename vector<T>::iterator begin() { return data.begin(); }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin(); }
    typename vector<T>::const_iterator end() const { return data.end(); }
};

// 학생 클래스
class Student {
public:
    string name;
    int age;
    double gpa;
    
    Student(string n, int a, double g) : name(n), age(a), gpa(g) {}
    
    bool operator==(const Student& other) const {
        return name == other.name;
    }
    
    bool operator<(const Student& other) const {
        return gpa < other.gpa;
    }
    
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.name << " (나이: " << s.age << ", GPA: " << s.gpa << ")";
        return os;
    }
};

#endif
```

### Container.cpp
```cpp
/*
구현 파일
*/

#include "Container.h"

template<typename T>
void DataContainer<T>::add(const T& item) {
    data.push_back(item);
}

template<typename T>
void DataContainer<T>::remove(const T& item) {
    data.erase(remove(data.begin(), data.end(), item), data.end());
}

template<typename T>
void DataContainer<T>::clear() {
    data.clear();
    filters.clear();
}

template<typename T>
void DataContainer<T>::sort() {
    std::sort(data.begin(), data.end());
}

template<typename T>
void DataContainer<T>::sort(function<bool(const T&, const T&)> comparator) {
    std::sort(data.begin(), data.end(), comparator);
}

template<typename T>
vector<T> DataContainer<T>::filter(const string& filterName) {
    vector<T> result;
    if (filters.find(filterName) != filters.end()) {
        copy_if(data.begin(), data.end(), back_inserter(result), filters[filterName]);
    }
    return result;
}

template<typename T>
void DataContainer<T>::addFilter(const string& name, function<bool(const T&)> filter) {
    filters[name] = filter;
}

template<typename T>
void DataContainer<T>::forEach(function<void(const T&)> action) {
    for_each(data.begin(), data.end(), action);
}

template<typename T>
T DataContainer<T>::findFirst(function<bool(const T&)> predicate) {
    auto it = find_if(data.begin(), data.end(), predicate);
    if (it != data.end()) {
        return *it;
    }
    throw runtime_error("요소를 찾을 수 없습니다.");
}

template<typename T>
void DataContainer<T>::display() {
    cout << "=== 컨테이너 내용 (" << data.size() << "개) ===" << endl;
    for (const auto& item : data) {
        cout << item << endl;
    }
}

// 명시적 템플릿 인스턴스화
template class DataContainer<int>;
template class DataContainer<string>;
template class DataContainer<Student>;
```

### main.cpp
```cpp
/*
메인 파일
*/

#include "Container.h"

int main() {
    cout << "=== 템플릿과 STL 종합 프로젝트 ===" << endl;
    
    // 학생 데이터 관리
    DataContainer<Student> students;
    
    students.add(Student("김철수", 20, 3.8));
    students.add(Student("이영희", 19, 4.0));
    students.add(Student("박민수", 21, 3.2));
    students.add(Student("최정화", 20, 3.9));
    
    students.display();
    
    cout << "\n=== GPA 순으로 정렬 ===" << endl;
    students.sort([](const Student& a, const Student& b) {
        return a.gpa > b.gpa;  // 내림차순
    });
    students.display();
    
    cout << "\n=== 필터 추가 및 사용 ===" << endl;
    students.addFilter("우등생", [](const Student& s) {
        return s.gpa >= 3.8;
    });
    
    students.addFilter("젊은학생", [](const Student& s) {
        return s.age < 21;
    });
    
    auto 우등생목록 = students.filter("우등생");
    cout << "우등생 (" << 우등생목록.size() << "명):" << endl;
    for (const auto& student : 우등생목록) {
        cout << "  " << student << endl;
    }
    
    cout << "\n=== 조건 검색 ===" << endl;
    try {
        auto topStudent = students.findFirst([](const Student& s) {
            return s.gpa >= 4.0;
        });
        cout << "GPA 4.0 이상 첫 번째 학생: " << topStudent << endl;
    } catch (const exception& e) {
        cout << "해당 조건의 학생 없음: " << e.what() << endl;
    }
    
    cout << "\n=== forEach로 일괄 처리 ===" << endl;
    students.forEach([](const Student& s) {
        if (s.gpa >= 3.5) {
            cout << "장학생: " << s.name << endl;
        }
    });
    
    cout << "\n=== 정수 컨테이너 테스트 ===" << endl;
    DataContainer<int> numbers;
    for (int i = 1; i <= 10; i++) {
        numbers.add(i);
    }
    
    numbers.addFilter("짝수", [](int n) { return n % 2 == 0; });
    auto evenNumbers = numbers.filter("짝수");
    
    cout << "짝수들: ";
    for (int n : evenNumbers) {
        cout << n << " ";
    }
    cout << endl;
    
    return 0;
}
```
