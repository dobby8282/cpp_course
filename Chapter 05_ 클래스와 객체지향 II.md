# Chapter 05: 클래스와 객체지향 II (예제 01~10)

## 1. 예제 01: 정적(static) 멤버 변수 (01_static_member_variables.cpp)

### 예제 정의
정적 멤버 변수를 통해 클래스 레벨의 데이터를 관리합니다.

```cpp
/*
주제: 정적(static) 멤버 변수
정의: 모든 객체가 공유하는 클래스 레벨의 변수
*/

#include <iostream>
using namespace std;

class Student {
private:
    string name;
    static int totalCount;  // 정적 멤버 변수
    
public:
    Student(string n) : name(n) {
        totalCount++;
        cout << name << " 등록 (총 " << totalCount << "명)" << endl;
    }
    
    ~Student() {
        totalCount--;
        cout << name << " 졸업" << endl;
    }
    
    static int getTotalCount() {
        return totalCount;
    }
};

// 정적 멤버 변수 초기화
int Student::totalCount = 0;

int main() {
    cout << "시작: " << Student::getTotalCount() << "명" << endl;
    
    {
        Student s1("김철수");
        Student s2("이영희");
        cout << "현재: " << Student::getTotalCount() << "명" << endl;
    }
    
    cout << "종료: " << Student::getTotalCount() << "명" << endl;
    return 0;
}
```

---

## 2. 예제 02: 정적(static) 멤버 함수 (02_static_member_functions.cpp)

### 예제 정의
정적 멤버 함수의 특성과 활용법을 학습합니다.

```cpp
/*
주제: 정적(static) 멤버 함수
정의: 특정 객체에 속하지 않고 클래스 자체에 속하는 함수
*/

#include <iostream>
using namespace std;

class MathUtils {
private:
    static int calcCount;
    
public:
    static int add(int a, int b) {
        calcCount++;
        return a + b;
    }
    
    static int multiply(int a, int b) {
        calcCount++;
        return a * b;
    }
    
    static int getCalcCount() {
        return calcCount;
    }
};

int MathUtils::calcCount = 0;

int main() {
    // 객체 생성 없이 직접 호출
    cout << "5 + 3 = " << MathUtils::add(5, 3) << endl;
    cout << "4 * 7 = " << MathUtils::multiply(4, 7) << endl;
    
    cout << "총 계산 횟수: " << MathUtils::getCalcCount() << endl;
    
    return 0;
}
```

---

## 3. 예제 03: const 멤버 함수 (03_const_member_functions.cpp)

### 예제 정의
const 멤버 함수와 상수 객체의 관계를 학습합니다.

```cpp
/*
주제: const 멤버 함수
정의: 객체의 상태를 변경하지 않는 함수
*/

#include <iostream>
using namespace std;

class Book {
private:
    string title;
    int pages;
    mutable int readCount;  // const 함수에서도 수정 가능
    
public:
    Book(string t, int p) : title(t), pages(p), readCount(0) {}
    
    // const 멤버 함수
    string getTitle() const {
        readCount++;  // mutable이므로 수정 가능
        return title;
    }
    
    int getPages() const {
        return pages;
    }
    
    // 비 const 멤버 함수
    void setPages(int p) {
        pages = p;
    }
};

int main() {
    Book book("C++", 500);
    const Book constBook("상수책", 300);
    
    book.setPages(520);        // OK
    cout << constBook.getTitle() << endl;  // OK (const 함수)
    // constBook.setPages(400);  // 오류: const 객체는 비const 함수 호출 불가
    
    return 0;
}
```

---

## 4. 예제 04: 연산자 오버로딩 심화 (04_operator_overloading_advanced.cpp)

### 예제 정의
증감 연산자와 배열 인덱스 연산자를 오버로딩합니다.

```cpp
/*
주제: 연산자 오버로딩 심화 (Advanced Operator Overloading)
정의: 증감 연산자, 배열 인덱스 연산자 등의 고급 오버로딩
*/

#include <iostream>
using namespace std;

class Counter {
private:
    int value;
    
public:
    Counter(int v = 0) : value(v) {}
    
    // 전위 증가 (++obj)
    Counter& operator++() {
        ++value;
        return *this;
    }
    
    // 후위 증가 (obj++)
    Counter operator++(int) {
        Counter temp = *this;
        value++;
        return temp;
    }
    
    int getValue() const { return value; }
};

class Array {
private:
    int data[5];
    
public:
    Array() {
        for (int i = 0; i < 5; i++) data[i] = 0;
    }
    
    // 배열 인덱스 연산자
    int& operator[](int index) {
        return data[index];
    }
};

int main() {
    Counter c(5);
    cout << "전위: " << (++c).getValue() << endl;  // 6
    cout << "후위: " << (c++).getValue() << endl;  // 6 (증가 전 값 반환)
    cout << "현재: " << c.getValue() << endl;      // 7
    
    Array arr;
    arr[0] = 10;
    arr[1] = 20;
    cout << "arr[0] = " << arr[0] << endl;
    
    return 0;
}
```

---

## 5. 예제 05: 프렌드(friend) 함수 (05_friend_function.cpp)

### 예제 정의
friend 함수를 통해 private 멤버에 접근합니다.

```cpp
/*
주제: 프렌드(friend) 함수
정의: 클래스의 private 멤버에 접근할 수 있는 외부 함수
*/

#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // friend 함수 선언
    friend double distance(const Point& p1, const Point& p2);
    friend ostream& operator<<(ostream& os, const Point& p);
};

// friend 함수 구현 - private 멤버에 직접 접근
double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

int main() {
    Point p1(3, 4);
    Point p2(0, 0);
    
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "거리: " << distance(p1, p2) << endl;
    
    return 0;
}
```

---

## 6. 예제 06: 프렌드(friend) 클래스 (06_friend_class.cpp)

### 예제 정의
friend 클래스를 통해 클래스 간 긴밀한 협력을 구현합니다.

```cpp
/*
주제: 프렌드(friend) 클래스
정의: 다른 클래스의 모든 private 멤버에 접근할 수 있는 클래스
*/

#include <iostream>
using namespace std;

class BankAccount {
private:
    string owner;
    double balance;
    
    friend class AccountManager;  // friend 클래스 선언
    
public:
    BankAccount(string o, double b) : owner(o), balance(b) {}
    
    void display() {
        cout << owner << ": " << balance << "원" << endl;
    }
};

class AccountManager {
public:
    // friend 권한으로 private 멤버에 접근
    void transfer(BankAccount& from, BankAccount& to, double amount) {
        if (from.balance >= amount) {
            from.balance -= amount;
            to.balance += amount;
            cout << "이체 완료: " << amount << "원" << endl;
        }
    }
    
    void displayBalance(const BankAccount& account) {
        cout << account.owner << "의 잔액: " << account.balance << "원" << endl;
    }
};

int main() {
    BankAccount acc1("김철수", 100000);
    BankAccount acc2("이영희", 50000);
    
    AccountManager manager;
    manager.transfer(acc1, acc2, 30000);
    
    acc1.display();
    acc2.display();
    
    return 0;
}
```

---

## 7. 예제 07: 이동 의미론 (07_move_semantics.cpp)

### 예제 정의
이동 생성자와 이동 대입 연산자를 통한 효율적인 자원 관리를 학습합니다.

```cpp
/*
주제: 이동 의미론 (Move Semantics)
정의: 불필요한 복사를 피하고 자원을 효율적으로 이동
*/

#include <iostream>
#include <utility>
using namespace std;

class Resource {
private:
    int* data;
    int size;
    
public:
    Resource(int s) : size(s) {
        data = new int[size];
        cout << "생성 (" << size << ")" << endl;
    }
    
    // 이동 생성자
    Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "이동 생성" << endl;
    }
    
    // 이동 대입 연산자
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            cout << "이동 대입" << endl;
        }
        return *this;
    }
    
    ~Resource() {
        delete[] data;
        if (size > 0) cout << "소멸 (" << size << ")" << endl;
    }
};

int main() {
    Resource r1(10);
    Resource r2 = move(r1);  // 이동 생성자
    
    Resource r3(5);
    r3 = move(r2);          // 이동 대입 연산자
    
    return 0;
}
```

---

## 8. 예제 08: 완벽한 전달 (08_perfect_forwarding.cpp)

### 예제 정의
템플릿과 std::forward를 사용한 완벽한 전달을 학습합니다.

```cpp
/*
주제: 완벽한 전달 (Perfect Forwarding)
정의: 인자를 원래 타입 그대로 다른 함수에 전달
*/

#include <iostream>
#include <utility>
using namespace std;

class Widget {
public:
    Widget(const string& name) {
        cout << "복사 생성: " << name << endl;
    }
    
    Widget(string&& name) {
        cout << "이동 생성: " << name << endl;
    }
};

// 완벽한 전달을 사용하는 팩토리 함수
template<typename T, typename... Args>
T createObject(Args&&... args) {
    return T(forward<Args>(args)...);
}

void processValue(const string& s) {
    cout << "lvalue: " << s << endl;
}

void processValue(string&& s) {
    cout << "rvalue: " << s << endl;
}

template<typename T>
void forwardValue(T&& value) {
    processValue(forward<T>(value));
}

int main() {
    // 팩토리 함수 테스트
    string name = "test";
    createObject<Widget>(name);        // 복사 생성
    createObject<Widget>("literal");   // 이동 생성
    
    // 완벽한 전달 테스트
    string str = "hello";
    forwardValue(str);                 // lvalue
    forwardValue("world");             // rvalue
    
    return 0;
}
```

---

## 9. 예제 09: RAII 패턴 (09_raii_pattern.cpp)

### 예제 정의
RAII 패턴을 통한 자동 자원 관리를 학습합니다.

```cpp
/*
주제: RAII 패턴 (Resource Acquisition Is Initialization)
정의: 자원의 획득과 해제를 객체의 생성과 소멸에 연결
*/

#include <iostream>
#include <fstream>
using namespace std;

class FileManager {
private:
    ofstream file;
    string filename;
    
public:
    FileManager(const string& fname) : filename(fname) {
        file.open(filename);
        cout << "파일 열기: " << filename << endl;
    }
    
    ~FileManager() {
        if (file.is_open()) {
            file.close();
            cout << "파일 닫기: " << filename << endl;
        }
    }
    
    void write(const string& content) {
        if (file.is_open()) {
            file << content << endl;
        }
    }
};

class MemoryManager {
private:
    int* data;
    
public:
    MemoryManager(int size) {
        data = new int[size];
        cout << "메모리 할당: " << data << endl;
    }
    
    ~MemoryManager() {
        delete[] data;
        cout << "메모리 해제: " << data << endl;
    }
    
    int* get() { return data; }
};

int main() {
    {
        FileManager fm("test.txt");
        fm.write("RAII 패턴 테스트");
        
        MemoryManager mm(10);
        mm.get()[0] = 42;
    } // 여기서 자동으로 자원 해제
    
    cout << "자원이 안전하게 해제되었습니다." << endl;
    return 0;
}
```

---

## 10. 예제 10: 종합 활용 - 간단한 벡터 클래스 (10_simple_vector.cpp)

### 예제 정의
지금까지 학습한 모든 개념을 활용한 간단한 벡터 클래스를 구현합니다.

```cpp
/*
주제: 종합 활용 - 간단한 벡터 클래스
정의: 모든 객체지향 개념을 통합한 실용적인 클래스
*/

#include <iostream>
#include <utility>
using namespace std;

class SimpleVector {
private:
    int* data;
    int size;
    static int totalVectors;
    
public:
    // 생성자
    SimpleVector(int s = 0) : size(s) {
        data = size > 0 ? new int[size] : nullptr;
        totalVectors++;
        cout << "벡터 생성 (크기: " << size << ")" << endl;
    }
    
    // 복사 생성자
    SimpleVector(const SimpleVector& other) : size(other.size) {
        data = size > 0 ? new int[size] : nullptr;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        totalVectors++;
        cout << "벡터 복사" << endl;
    }
    
    // 이동 생성자
    SimpleVector(SimpleVector&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        totalVectors++;
        cout << "벡터 이동" << endl;
    }
    
    // 소멸자
    ~SimpleVector() {
        delete[] data;
        totalVectors--;
    }
    
    // 연산자 오버로딩
    int& operator[](int index) { return data[index]; }
    const int& operator[](int index) const { return data[index]; }
    
    // 정적 함수
    static int getTotalVectors() { return totalVectors; }
    
    int getSize() const { return size; }
    
    void display() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int SimpleVector::totalVectors = 0;

int main() {
    SimpleVector v1(3);
    v1[0] = 10; v1[1] = 20; v1[2] = 30;
    v1.display();
    
    SimpleVector v2 = v1;           // 복사
    SimpleVector v3 = move(v1);     // 이동
    
    cout << "총 벡터 개수: " << SimpleVector::getTotalVectors() << endl;
    
    return 0;
}
```

---
