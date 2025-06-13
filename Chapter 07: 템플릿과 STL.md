# Chapter 07: 템플릿과 STL

## 학습 목표
- 함수 템플릿과 클래스 템플릿의 기본 개념 이해
- 템플릿 특화(specialization)와 매개변수 추론 학습
- STL 컨테이너(vector, list, map, set)의 활용법 습득
- 반복자(iterator)의 종류와 사용법 학습
- STL 알고리즘과 함수 객체 활용 기법 습득
- 람다 표현식과 현대적 C++ 기능 활용
- 사용자 정의 템플릿 설계 방법 학습

---

## 1. 예제 01: 함수 템플릿 기초 (01_function_template.cpp)

### 예제 정의
함수 템플릿의 기본 개념과 사용법을 학습합니다.

```cpp
/*
주제: 함수 템플릿 (Function Templates)
정의: 타입에 독립적인 함수를 정의하여 다양한 데이터 타입에 대해 동일한 알고리즘을 적용할 수 있게 하는 C++의 제네릭 프로그래밍 기능

핵심 개념: template 키워드, 타입 매개변수, 템플릿 인스턴스화, 타입 추론
정의:
- template 키워드: 템플릿을 선언하는 키워드
- 타입 매개변수: 템플릿에서 사용되는 가상의 타입 이름 (보통 T, U, V 등)
- 템플릿 인스턴스화: 컴파일 시점에 구체적인 타입으로 템플릿 함수가 생성되는 과정
- 타입 추론: 컴파일러가 함수 호출 시 전달된 인수를 통해 자동으로 타입을 결정하는 기능
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 기본 함수 템플릿
template<typename T>
T getMax(T a, T b) {
    cout << "getMax 호출: 타입 크기 " << sizeof(T) << " 바이트" << endl;
    return (a > b) ? a : b;
}

// 두 개의 타입 매개변수를 가진 템플릿
template<typename T, typename U>
void printPair(T first, U second) {
    cout << "첫 번째: " << first << " (타입 크기: " << sizeof(T) << " 바이트)" << endl;
    cout << "두 번째: " << second << " (타입 크기: " << sizeof(U) << " 바이트)" << endl;
}

// 배열의 최대값을 찾는 템플릿
template<typename T, int N>
T findArrayMax(T (&arr)[N]) {
    T max = arr[0];
    cout << "배열 크기: " << N << ", 요소 타입 크기: " << sizeof(T) << " 바이트" << endl;
    
    for (int i = 1; i < N; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 기본값을 가진 템플릿 매개변수
template<typename T = int>
T multiply(T a, T b) {
    return a * b;
}

// 가변 인자 템플릿 (C++11)
template<typename T>
T sum(T value) {
    return value;  // 재귀의 기저 사례
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);  // 재귀 호출
}

// 함수 오버로딩과 템플릿
void print(int value) {
    cout << "일반 함수 print(int): " << value << endl;
}

template<typename T>
void print(T value) {
    cout << "템플릿 함수 print(T): " << value << endl;
}

// 타입 제약을 위한 SFINAE 예제 (간단한 버전)
template<typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
safeDivide(T a, T b) {
    if (b == 0) {
        cout << "0으로 나눌 수 없습니다!" << endl;
        return T{};
    }
    return a / b;
}

// 스왑 함수 템플릿
template<typename T>
void mySwap(T& a, T& b) {
    cout << "스왑 전: a=" << a << ", b=" << b << endl;
    T temp = a;
    a = b;
    b = temp;
    cout << "스왑 후: a=" << a << ", b=" << b << endl;
}

// 비교 함수 템플릿
template<typename T>
bool isEqual(const T& a, const T& b) {
    return a == b;
}

// 배열 출력 템플릿
template<typename T, size_t N>
void printArray(const T (&arr)[N]) {
    cout << "배열 [" << N << "]: ";
    for (size_t i = 0; i < N; ++i) {
        cout << arr[i];
        if (i < N - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    cout << "=== 함수 템플릿 기초 ===" << endl;
    
    // 1. 기본 함수 템플릿 사용
    cout << "\n--- 기본 함수 템플릿 ---" << endl;
    cout << "정수 최대값: " << getMax(10, 20) << endl;
    cout << "실수 최대값: " << getMax(3.14, 2.71) << endl;
    cout << "문자 최대값: " << getMax('a', 'z') << endl;
    cout << "문자열 최대값: " << getMax(string("apple"), string("banana")) << endl;
    
    // 2. 명시적 타입 지정
    cout << "\n--- 명시적 타입 지정 ---" << endl;
    cout << "명시적 지정: " << getMax<double>(10, 20.5) << endl;
    
    // 3. 두 개의 타입 매개변수
    cout << "\n--- 두 개의 타입 매개변수 ---" << endl;
    printPair(42, string("Hello"));
    printPair(3.14, 'A');
    
    // 4. 배열 템플릿
    cout << "\n--- 배열 템플릿 ---" << endl;
    int intArr[] = {1, 5, 3, 9, 2};
    double doubleArr[] = {1.1, 5.5, 3.3, 9.9, 2.2};
    
    cout << "정수 배열 최대값: " << findArrayMax(intArr) << endl;
    cout << "실수 배열 최대값: " << findArrayMax(doubleArr) << endl;
    
    // 5. 기본값을 가진 템플릿
    cout << "\n--- 기본값 템플릿 ---" << endl;
    cout << "기본 타입(int): " << multiply(5, 6) << endl;
    cout << "명시적 타입: " << multiply<double>(5.5, 6.6) << endl;
    
    // 6. 가변 인자 템플릿
    cout << "\n--- 가변 인자 템플릿 ---" << endl;
    cout << "정수 합: " << sum(1, 2, 3, 4, 5) << endl;
    cout << "실수 합: " << sum(1.1, 2.2, 3.3) << endl;
    cout << "문자열 연결: " << sum(string("Hello"), string(" "), string("World")) << endl;
    
    // 7. 함수 오버로딩과 템플릿
    cout << "\n--- 함수 오버로딩과 템플릿 ---" << endl;
    print(42);        // 일반 함수 호출
    print(3.14);      // 템플릿 함수 호출
    print('A');       // 템플릿 함수 호출
    print<int>(42);   // 명시적으로 템플릿 함수 호출
    
    // 8. 안전한 나눗셈 (SFINAE)
    cout << "\n--- 안전한 나눗셈 ---" << endl;
    cout << "10 / 3 = " << safeDivide(10, 3) << endl;
    cout << "10.0 / 3.0 = " << safeDivide(10.0, 3.0) << endl;
    cout << "10 / 0 = " << safeDivide(10, 0) << endl;
    
    // 9. 스왑 함수
    cout << "\n--- 스왑 함수 ---" << endl;
    int x = 100, y = 200;
    mySwap(x, y);
    
    string str1 = "Hello", str2 = "World";
    mySwap(str1, str2);
    
    // 10. 배열 출력
    cout << "\n--- 배열 출력 ---" << endl;
    int numbers[] = {1, 2, 3, 4, 5};
    char letters[] = {'A', 'B', 'C'};
    
    printArray(numbers);
    printArray(letters);
    
    // 11. 비교 함수
    cout << "\n--- 비교 함수 ---" << endl;
    cout << "10과 10이 같은가? " << isEqual(10, 10) << endl;
    cout << "\"ABC\"와 \"ABC\"가 같은가? " << isEqual(string("ABC"), string("ABC")) << endl;
    cout << "3.14와 2.71이 같은가? " << isEqual(3.14, 2.71) << endl;
    
    cout << "\n=== 함수 템플릿 핵심 개념 ===" << endl;
    cout << "1. template<typename T>로 선언" << endl;
    cout << "2. 컴파일 시점에 타입별로 함수 생성" << endl;
    cout << "3. 타입 추론으로 자동 타입 결정" << endl;
    cout << "4. 명시적 타입 지정도 가능" << endl;
    cout << "5. 가변 인자 템플릿으로 유연성 극대화" << endl;
    cout << "6. SFINAE로 타입 제약 가능" << endl;
    
    return 0;
}
```

---

## 2. 예제 02: 클래스 템플릿 (02_class_template.cpp)

### 예제 정의
클래스 템플릿의 기본 사용법과 고급 기능을 학습합니다.

```cpp
/*
주제: 클래스 템플릿 (Class Templates)
정의: 타입에 독립적인 클래스를 정의하여 다양한 데이터 타입에 대해 동일한 구조와 동작을 제공하는 제네릭 프로그래밍 기법

핵심 개념: 템플릿 클래스, 멤버 함수 템플릿, 템플릿 특화, 비타입 매개변수
정의:
- 템플릿 클래스: template 키워드로 정의된 클래스로 타입 매개변수를 가짐
- 멤버 함수 템플릿: 클래스 템플릿의 멤버 함수도 템플릿이 될 수 있음
- 템플릿 특화: 특정 타입에 대해 특별한 구현을 제공하는 기법
- 비타입 매개변수: 타입이 아닌 값(상수)을 매개변수로 받는 템플릿
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
using namespace std;

// 기본 클래스 템플릿 - 동적 배열
template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;
    
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cout << "배열 크기 확장: " << capacity << endl;
    }
    
public:
    // 생성자
    explicit DynamicArray(size_t initialCapacity = 4) 
        : size(0), capacity(initialCapacity) {
        data = new T[capacity];
        cout << "DynamicArray<" << typeid(T).name() << "> 생성 (용량: " << capacity << ")" << endl;
    }
    
    // 소멸자
    ~DynamicArray() {
        delete[] data;
        cout << "DynamicArray<" << typeid(T).name() << "> 소멸" << endl;
    }
    
    // 복사 생성자
    DynamicArray(const DynamicArray& other) 
        : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        cout << "DynamicArray 복사 생성" << endl;
    }
    
    // 대입 연산자
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            cout << "DynamicArray 대입" << endl;
        }
        return *this;
    }
    
    // 요소 추가
    void push_back(const T& value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }
    
    // 인덱스 접근
    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // 크기 반환
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    
    // 출력
    void print() const {
        cout << "DynamicArray [" << size << "/" << capacity << "]: ";
        for (size_t i = 0; i < size; ++i) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << endl;
    }
    
    // 멤버 함수 템플릿
    template<typename U>
    void printWithType(const U& prefix) const {
        cout << prefix << ": ";
        print();
    }
};

// 비타입 매개변수를 가진 클래스 템플릿
template<typename T, size_t N>
class FixedArray {
private:
    T data[N];
    size_t currentSize;
    
public:
    FixedArray() : currentSize(0) {
        cout << "FixedArray<" << typeid(T).name() << ", " << N << "> 생성" << endl;
    }
    
    void add(const T& value) {
        if (currentSize >= N) {
            throw overflow_error("FixedArray is full");
        }
        data[currentSize++] = value;
    }
    
    T& operator[](size_t index) {
        if (index >= currentSize) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t size() const { return currentSize; }
    size_t capacity() const { return N; }
    
    void print() const {
        cout << "FixedArray [" << currentSize << "/" << N << "]: ";
        for (size_t i = 0; i < currentSize; ++i) {
            cout << data[i];
            if (i < currentSize - 1) cout << ", ";
        }
        cout << endl;
    }
};

// 두 개의 타입 매개변수를 가진 클래스 템플릿
template<typename K, typename V>
class KeyValuePair {
private:
    K key;
    V value;
    
public:
    KeyValuePair(const K& k, const V& v) : key(k), value(v) {
        cout << "KeyValuePair 생성: " << key << " -> " << value << endl;
    }
    
    const K& getKey() const { return key; }
    const V& getValue() const { return value; }
    
    void setValue(const V& v) { value = v; }
    
    void print() const {
        cout << "Key: " << key << ", Value: " << value << endl;
    }
};

// 간단한 스마트 포인터 템플릿
template<typename T>
class SimpleUniquePtr {
private:
    T* ptr;
    
public:
    explicit SimpleUniquePtr(T* p = nullptr) : ptr(p) {
        cout << "SimpleUniquePtr 생성" << endl;
    }
    
    ~SimpleUniquePtr() {
        delete ptr;
        cout << "SimpleUniquePtr 소멸" << endl;
    }
    
    // 복사 방지
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;
    
    // 이동 생성자
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
        cout << "SimpleUniquePtr 이동" << endl;
    }
    
    // 이동 대입 연산자
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    
    T* get() const { return ptr; }
    
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// 스택 템플릿
template<typename T>
class Stack {
private:
    static const size_t DEFAULT_CAPACITY = 10;
    T* data;
    size_t topIndex;
    size_t capacity;
    
public:
    explicit Stack(size_t cap = DEFAULT_CAPACITY) 
        : topIndex(0), capacity(cap) {
        data = new T[capacity];
        cout << "Stack<" << typeid(T).name() << "> 생성 (용량: " << capacity << ")" << endl;
    }
    
    ~Stack() {
        delete[] data;
        cout << "Stack<" << typeid(T).name() << "> 소멸" << endl;
    }
    
    void push(const T& value) {
        if (topIndex >= capacity) {
            throw overflow_error("Stack overflow");
        }
        data[topIndex++] = value;
        cout << "Push: " << value << endl;
    }
    
    T pop() {
        if (isEmpty()) {
            throw underflow_error("Stack underflow");
        }
        T value = data[--topIndex];
        cout << "Pop: " << value << endl;
        return value;
    }
    
    const T& top() const {
        if (isEmpty()) {
            throw underflow_error("Stack is empty");
        }
        return data[topIndex - 1];
    }
    
    bool isEmpty() const {
        return topIndex == 0;
    }
    
    size_t size() const {
        return topIndex;
    }
    
    void print() const {
        cout << "Stack [" << topIndex << "/" << capacity << "]: ";
        for (size_t i = 0; i < topIndex; ++i) {
            cout << data[i];
            if (i < topIndex - 1) cout << ", ";
        }
        cout << " (top: " << (isEmpty() ? "empty" : to_string(data[topIndex-1])) << ")" << endl;
    }
};

// 테스트용 클래스
class TestClass {
private:
    int value;
    string name;
    
public:
    TestClass(int v = 0, string n = "default") : value(v), name(n) {
        cout << "TestClass(" << value << ", " << name << ") 생성" << endl;
    }
    
    ~TestClass() {
        cout << "TestClass(" << value << ", " << name << ") 소멸" << endl;
    }
    
    int getValue() const { return value; }
    string getName() const { return name; }
    
    void setValue(int v) { value = v; }
    void setName(const string& n) { name = n; }
    
    friend ostream& operator<<(ostream& os, const TestClass& obj) {
        os << obj.name << "(" << obj.value << ")";
        return os;
    }
};

int main() {
    cout << "=== 클래스 템플릿 ===" << endl;
    
    // 1. 동적 배열 템플릿
    cout << "\n--- 동적 배열 템플릿 ---" << endl;
    DynamicArray<int> intArray;
    for (int i = 1; i <= 6; ++i) {
        intArray.push_back(i * 10);
    }
    intArray.print();
    
    DynamicArray<string> stringArray;
    stringArray.push_back("Hello");
    stringArray.push_back("World");
    stringArray.push_back("Template");
    stringArray.print();
    
    // 멤버 함수 템플릿 사용
    intArray.printWithType("정수 배열");
    stringArray.printWithType(string("문자열 배열"));
    
    // 2. 고정 크기 배열 템플릿
    cout << "\n--- 고정 크기 배열 템플릿 ---" << endl;
    FixedArray<double, 5> fixedArray;
    for (int i = 1; i <= 4; ++i) {
        fixedArray.add(i * 1.1);
    }
    fixedArray.print();
    
    // 3. 키-값 쌍 템플릿
    cout << "\n--- 키-값 쌍 템플릿 ---" << endl;
    KeyValuePair<string, int> pair1("age", 25);
    KeyValuePair<int, string> pair2(42, "answer");
    
    pair1.print();
    pair2.print();
    
    // 4. 스마트 포인터 템플릿
    cout << "\n--- 스마트 포인터 템플릿 ---" << endl;
    {
        SimpleUniquePtr<TestClass> ptr(new TestClass(100, "Smart"));
        cout << "값: " << ptr->getValue() << ", 이름: " << ptr->getName() << endl;
        
        // 이동 의미론
        SimpleUniquePtr<TestClass> ptr2 = move(ptr);
        cout << "이동 후 ptr: " << (ptr ? "valid" : "null") << endl;
        cout << "이동 후 ptr2: " << (ptr2 ? "valid" : "null") << endl;
        
        if (ptr2) {
            cout << "ptr2 값: " << ptr2->getValue() << endl;
        }
    }
    
    // 5. 스택 템플릿
    cout << "\n--- 스택 템플릿 ---" << endl;
    try {
        Stack<int> intStack(5);
        
        // 푸시
        for (int i = 1; i <= 4; ++i) {
            intStack.push(i * 100);
            intStack.print();
        }
        
        // 팝
        while (!intStack.isEmpty()) {
            cout << "Top: " << intStack.top() << endl;
            intStack.pop();
            intStack.print();
        }
        
    } catch (const exception& e) {
        cout << "예외 발생: " << e.what() << endl;
    }
    
    // 6. 사용자 정의 클래스로 템플릿 사용
    cout << "\n--- 사용자 정의 클래스 템플릿 ---" << endl;
    DynamicArray<TestClass> objArray;
    objArray.push_back(TestClass(1, "First"));
    objArray.push_back(TestClass(2, "Second"));
    objArray.push_back(TestClass(3, "Third"));
    
    cout << "객체 배열 내용:" << endl;
    for (size_t i = 0; i < objArray.getSize(); ++i) {
        cout << "  [" << i << "]: " << objArray[i] << endl;
    }
    
    cout << "\n=== 클래스 템플릿 핵심 개념 ===" << endl;
    cout << "1. template<typename T> class ClassName 으로 선언" << endl;
    cout << "2. 타입과 비타입 매개변수 모두 가능" << endl;
    cout << "3. 멤버 함수도 템플릿이 될 수 있음" << endl;
    cout << "4. 컴파일 시점에 타입별로 클래스 생성" << endl;
    cout << "5. STL 컨테이너의 기반 기술" << endl;
    cout << "6. 타입 안전성과 재사용성 제공" << endl;
    
    return 0;
}
```

---

## 3. 예제 03: 템플릿 특화 (03_template_specialization.cpp)

### 예제 정의
템플릿 특화(specialization)의 개념과 활용법을 학습합니다.

```cpp
/*
주제: 템플릿 특화 (Template Specialization)
정의: 특정 타입에 대해 템플릿의 일반적인 구현과 다른 특별한 구현을 제공하는 기법

핵심 개념: 완전 특화, 부분 특화, 함수 템플릿 특화, 클래스 템플릿 특화
정의:
- 완전 특화: 모든 템플릿 매개변수를 구체적인 타입으로 지정하는 특화
- 부분 특화: 일부 템플릿 매개변수만 구체화하거나 제약을 가하는 특화
- 함수 템플릿 특화: 함수 템플릿에 대한 특화 (보통 오버로딩으로 대체)
- 클래스 템플릿 특화: 클래스 템플릿에 대한 특화
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

// 기본 템플릿
template<typename T>
class Container {
private:
    T data;
    
public:
    Container(const T& value) : data(value) {
        cout << "일반 템플릿 Container 생성: " << data << endl;
    }
    
    void display() const {
        cout << "일반 타입 데이터: " << data << endl;
    }
    
    T getData() const {
        return data;
    }
    
    void process() {
        cout << "일반 타입 처리: 기본 동작" << endl;
    }
};

// 완전 특화 - string 타입에 대한 특별한 구현
template<>
class Container<string> {
private:
    string data;
    
public:
    Container(const string& value) : data(value) {
        cout << "string 특화 Container 생성: \"" << data << "\"" << endl;
    }
    
    void display() const {
        cout << "문자열 데이터 (길이 " << data.length() << "): \"" << data << "\"" << endl;
    }
    
    string getData() const {
        return data;
    }
    
    void process() {
        cout << "문자열 특화 처리: 대문자 변환" << endl;
        for (char& c : data) {
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
            }
        }
        cout << "변환 결과: \"" << data << "\"" << endl;
    }
    
    // string 특화만의 고유 메서드
    void reverse() {
        std::reverse(data.begin(), data.end());
        cout << "문자열 뒤집기: \"" << data << "\"" << endl;
    }
};

// 완전 특화 - bool 타입에 대한 특별한 구현
template<>
class Container<bool> {
private:
    bool data;
    
public:
    Container(bool value) : data(value) {
        cout << "bool 특화 Container 생성: " << (data ? "true" : "false") << endl;
    }
    
    void display() const {
        cout << "불린 데이터: " << (data ? "TRUE" : "FALSE") << endl;
    }
    
    bool getData() const {
        return data;
    }
    
    void process() {
        cout << "불린 특화 처리: 값 토글" << endl;
        data = !data;
        cout << "토글 결과: " << (data ? "true" : "false") << endl;
    }
    
    // bool 특화만의 고유 메서드
    void toggle() {
        data = !data;
        cout << "토글: " << (data ? "true" : "false") << endl;
    }
};

// 포인터 타입에 대한 부분 특화
template<typename T>
class Container<T*> {
private:
    T* data;
    bool ownsData;
    
public:
    Container(T* value, bool owns = false) : data(value), ownsData(owns) {
        cout << "포인터 특화 Container 생성: " << data << endl;
    }
    
    ~Container() {
        if (ownsData && data) {
            delete data;
            cout << "포인터 특화: 동적 메모리 해제" << endl;
        }
    }
    
    void display() const {
        if (data) {
            cout << "포인터 데이터 (주소: " << data << "): " << *data << endl;
        } else {
            cout << "포인터 데이터: nullptr" << endl;
        }
    }
    
    T* getData() const {
        return data;
    }
    
    void process() {
        if (data) {
            cout << "포인터 특화 처리: 간접 접근을 통한 데이터 조작" << endl;
            cout << "원본 값: " << *data << endl;
        } else {
            cout << "nullptr이므로 처리할 수 없습니다." << endl;
        }
    }
    
    // 포인터 특화만의 고유 메서드
    bool isNull() const {
        return data == nullptr;
    }
    
    void setOwnership(bool owns) {
        ownsData = owns;
    }
};

// 함수 템플릿과 특화
template<typename T>
void printValue(const T& value) {
    cout << "일반 타입 출력: " << value << endl;
}

// 함수 템플릿의 완전 특화
template<>
void printValue<const char*>(const char* const& value) {
    cout << "C 문자열 특화 출력: \"" << value << "\" (길이: " << strlen(value) << ")" << endl;
}

template<>
void printValue<char>(const char& value) {
    cout << "문자 특화 출력: '" << value << "' (ASCII: " << static_cast<int>(value) << ")" << endl;
}

// 비교 함수 템플릿
template<typename T>
bool isEqual(const T& a, const T& b) {
    cout << "일반 비교 함수 사용" << endl;
    return a == b;
}

// float에 대한 특화 (부동소수점 비교)
template<>
bool isEqual<float>(const float& a, const float& b) {
    cout << "float 특화 비교 함수 사용 (오차 허용)" << endl;
    const float epsilon = 1e-6f;
    return abs(a - b) < epsilon;
}

// 두 개의 타입 매개변수를 가진 템플릿
template<typename T, typename U>
class Pair {
private:
    T first;
    U second;
    
public:
    Pair(const T& f, const U& s) : first(f), second(s) {
        cout << "일반 Pair 생성: (" << first << ", " << second << ")" << endl;
    }
    
    void display() const {
        cout << "Pair: (" << first << ", " << second << ")" << endl;
    }
    
    T getFirst() const { return first; }
    U getSecond() const { return second; }
};

// 같은 타입의 쌍에 대한 부분 특화
template<typename T>
class Pair<T, T> {
private:
    T first;
    T second;
    
public:
    Pair(const T& f, const T& s) : first(f), second(s) {
        cout << "동일 타입 Pair 특화 생성: (" << first << ", " << second << ")" << endl;
    }
    
    void display() const {
        cout << "동일 타입 Pair: (" << first << ", " << second << ")" << endl;
    }
    
    T getFirst() const { return first; }
    T getSecond() const { return second; }
    
    // 동일 타입 특화만의 메서드
    void swap() {
        T temp = first;
        first = second;
        second = temp;
        cout << "스왑 완료: (" << first << ", " << second << ")" << endl;
    }
    
    bool isEqual() const {
        return first == second;
    }
};

// 배열 처리를 위한 특화
template<typename T, int N>
class Array {
private:
    T data[N];
    
public:
    Array() {
        cout << "일반 Array<" << typeid(T).name() << ", " << N << "> 생성" << endl;
        for (int i = 0; i < N; ++i) {
            data[i] = T{};  // 기본값으로 초기화
        }
    }
    
    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
        return data[index];
    }
    
    void fill(const T& value) {
        for (int i = 0; i < N; ++i) {
            data[i] = value;
        }
    }
    
    void print() const {
        cout << "Array [" << N << "]: ";
        for (int i = 0; i < N; ++i) {
            cout << data[i];
            if (i < N - 1) cout << ", ";
        }
        cout << endl;
    }
};

// bool 배열에 대한 특화 (비트 최적화 시뮬레이션)
template<int N>
class Array<bool, N> {
private:
    unsigned char data[(N + 7) / 8];  // 비트 패킹
    
public:
    Array() {
        cout << "bool Array 특화 생성 (비트 최적화): " << N << " bits" << endl;
        memset(data, 0, sizeof(data));
    }
    
    void set(int index, bool value) {
        if (index < 0 || index >= N) return;
        
        int byteIndex = index / 8;
        int bitIndex = index % 8;
        
        if (value) {
            data[byteIndex] |= (1 << bitIndex);
        } else {
            data[byteIndex] &= ~(1 << bitIndex);
        }
    }
    
    bool get(int index) const {
        if (index < 0 || index >= N) return false;
        
        int byteIndex = index / 8;
        int bitIndex = index % 8;
        
        return (data[byteIndex] & (1 << bitIndex)) != 0;
    }
    
    void print() const {
        cout << "bool Array [" << N << " bits]: ";
        for (int i = 0; i < N; ++i) {
            cout << (get(i) ? "1" : "0");
        }
        cout << " (메모리 사용: " << sizeof(data) << " 바이트)" << endl;
    }
};

int main() {
    cout << "=== 템플릿 특화 ===" << endl;
    
    // 1. 클래스 템플릿 완전 특화
    cout << "\n--- 클래스 템플릿 완전 특화 ---" << endl;
    Container<int> intContainer(42);
    Container<string> stringContainer("Hello World");
    Container<bool> boolContainer(true);
    
    intContainer.display();
    intContainer.process();
    
    stringContainer.display();
    stringContainer.process();
    stringContainer.reverse();
    
    boolContainer.display();
    boolContainer.process();
    boolContainer.toggle();
    
    // 2. 포인터 타입 부분 특화
    cout << "\n--- 포인터 타입 부분 특화 ---" << endl;
    int value = 100;
    Container<int*> ptrContainer(&value, false);
    ptrContainer.display();
    ptrContainer.process();
    cout << "nullptr 체크: " << ptrContainer.isNull() << endl;
    
    Container<int*> dynPtrContainer(new int(200), true);
    dynPtrContainer.display();
    dynPtrContainer.process();
    
    // 3. 함수 템플릿 특화
    cout << "\n--- 함수 템플릿 특화 ---" << endl;
    printValue(42);
    printValue(3.14);
    printValue("Hello");
    printValue('A');
    
    // 4. 비교 함수 특화
    cout << "\n--- 비교 함수 특화 ---" << endl;
    cout << "정수 비교 (5, 5): " << isEqual(5, 5) << endl;
    cout << "정수 비교 (5, 3): " << isEqual(5, 3) << endl;
    cout << "float 비교 (3.14f, 3.14f): " << isEqual(3.14f, 3.14f) << endl;
    cout << "float 비교 (3.140001f, 3.140002f): " << isEqual(3.140001f, 3.140002f) << endl;
    
    // 5. Pair 템플릿과 부분 특화
    cout << "\n--- Pair 부분 특화 ---" << endl;
    Pair<int, string> mixedPair(42, "Hello");
    Pair<int, int> samePair(10, 20);
    
    mixedPair.display();
    samePair.display();
    samePair.swap();
    cout << "같은 값인가? " << samePair.isEqual() << endl;
    
    // 6. 배열 특화
    cout << "\n--- 배열 특화 ---" << endl;
    Array<int, 5> intArray;
    intArray.fill(7);
    intArray.print();
    
    Array<bool, 10> boolArray;
    boolArray.set(0, true);
    boolArray.set(3, true);
    boolArray.set(7, true);
    boolArray.set(9, true);
    boolArray.print();
    
    cout << "\n=== 템플릿 특화 핵심 개념 ===" << endl;
    cout << "1. 완전 특화: template<> class ClassName<SpecificType>" << endl;
    cout << "2. 부분 특화: template<typename T> class ClassName<T*>" << endl;
    cout << "3. 특정 타입에 대한 최적화된 구현 제공" << endl;
    cout << "4. 함수 템플릿 특화보다는 오버로딩 권장" << endl;
    cout << "5. STL의 많은 특화가 이 기법을 활용" << endl;
    cout << "6. 컴파일 타임에 가장 적합한 특화 선택" << endl;
    
    return 0;
}
```

이제 Chapter 08: 예외 처리와 프로젝트를 작성하겠습니다.
