# Chapter 04: 클래스와 객체지향 I

## 학습 목표
- 구조체와 클래스의 차이점과 사용법 이해
- 클래스 멤버와 접근 제어자의 역할 습득
- 생성자와 소멸자를 통한 객체 생명주기 관리
- 복사 생성자와 이동 생성자의 개념 학습
- 연산자 오버로딩의 기초 활용법 습득
- 객체지향 프로그래밍의 기본 원리 이해

---

## 1. 예제 01: 구조체 기초 (01_struct_basic.cpp)

### 예제 정의
구조체를 사용하여 관련된 데이터를 하나로 묶는 방법을 학습합니다.

```cpp
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
```

---

## 2. 예제 02: 클래스 기초 (02_class_basic.cpp)

### 예제 정의
클래스의 기본 개념과 구조체와의 차이점을 학습합니다.

```cpp
/*
주제: 클래스 (Class)
정의: 데이터(멤버 변수)와 그 데이터를 조작하는 함수(멤버 함수)를 하나로 묶은 객체지향의 기본 단위

핵심 개념: class 키워드, 멤버 함수, 객체, 캡슐화
정의:
- class 키워드: 클래스를 정의하는 C++ 키워드
- 멤버 함수: 클래스 내부에 정의된 함수로 객체의 동작을 정의
- 객체: 클래스를 바탕으로 생성된 실체(인스턴스)
- 캡슐화: 데이터와 함수를 하나로 묶어 외부에서의 접근을 제어하는 개념
*/

#include <iostream>
#include <string>
using namespace std;

class Rectangle {
public:
    double width;
    double height;
    
    double getArea() {
        return width * height;
    }
    
    double getPerimeter() {
        return 2 * (width + height);
    }
    
    void display() {
        cout << "가로: " << width << ", 세로: " << height << endl;
        cout << "넓이: " << getArea() << ", 둘레: " << getPerimeter() << endl;
    }
};

int main() {
    Rectangle rect;
    rect.width = 5.0;
    rect.height = 3.0;
    
    cout << "=== 사각형 정보 ===" << endl;
    rect.display();
    
    return 0;
}
```

---

## 3. 예제 03: 접근 제어자 (03_access_control.cpp)

### 예제 정의
public, private, protected 접근 제어자의 사용법을 학습합니다.

```cpp
/*
주제: 접근 제어자 (Access Specifiers)
정의: 클래스 멤버에 대한 외부 접근을 제어하는 키워드

핵심 개념: public, private, protected, 정보 은닉
정의:
- public: 클래스 외부에서 자유롭게 접근 가능한 멤버
- private: 클래스 내부에서만 접근 가능한 멤버
- protected: 클래스 내부와 상속받은 클래스에서만 접근 가능한 멤버
- 정보 은닉: 객체의 내부 구현을 외부에서 직접 접근하지 못하도록 숨기는 원칙
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;
    
public:
    void setAccount(string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << amount << "원 입금되었습니다." << endl;
        }
    }
    
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << amount << "원 출금되었습니다." << endl;
        } else {
            cout << "출금할 수 없습니다." << endl;
        }
    }
    
    void displayBalance() {
        cout << "계좌번호: " << accountNumber << ", 잔액: " << balance << "원" << endl;
    }
};

int main() {
    BankAccount account;
    account.setAccount("123-456-789", 100000);
    
    account.displayBalance();
    account.deposit(50000);
    account.withdraw(30000);
    account.displayBalance();
    
    // account.balance = 1000000; // 오류: private 멤버에 직접 접근 불가
    
    return 0;
}
```

---

## 4. 예제 04: 생성자 기초 (04_constructor_basic.cpp)

### 예제 정의
생성자를 사용하여 객체를 초기화하는 방법을 학습합니다.

```cpp
/*
주제: 생성자 (Constructor)
정의: 객체가 생성될 때 자동으로 호출되어 객체를 초기화하는 특별한 멤버 함수

핵심 개념: 기본 생성자, 매개변수 있는 생성자, 초기화 리스트
정의:
- 기본 생성자: 매개변수가 없는 생성자로 기본값으로 객체를 초기화
- 매개변수 있는 생성자: 매개변수를 받아서 특정 값으로 객체를 초기화
- 초기화 리스트: 생성자에서 멤버 변수를 효율적으로 초기화하는 방법
*/

#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    // 기본 생성자
    Person() {
        name = "Unknown";
        age = 0;
        cout << "기본 생성자 호출: " << name << endl;
    }
    
    // 매개변수가 있는 생성자
    Person(string n, int a) {
        name = n;
        age = a;
        cout << "매개변수 생성자 호출: " << name << endl;
    }
    
    // 초기화 리스트를 사용하는 생성자
    Person(string n) : name(n), age(18) {
        cout << "초기화 리스트 생성자 호출: " << name << endl;
    }
    
    void display() {
        cout << "이름: " << name << ", 나이: " << age << endl;
    }
};

int main() {
    Person person1;                    // 기본 생성자
    Person person2("김철수", 25);       // 매개변수 생성자
    Person person3("이영희");           // 초기화 리스트 생성자
    
    cout << "\n=== 객체 정보 ===" << endl;
    person1.display();
    person2.display();
    person3.display();
    
    return 0;
}
```

---

## 5. 예제 05: 소멸자 기초 (05_destructor_basic.cpp)

### 예제 정의
소멸자를 사용하여 객체가 소멸될 때 정리 작업을 수행하는 방법을 학습합니다.

```cpp
/*
주제: 소멸자 (Destructor)
정의: 객체가 소멸될 때 자동으로 호출되어 정리 작업을 수행하는 특별한 멤버 함수

핵심 개념: ~클래스명, 자동 호출, 자원 해제, RAII
정의:
- ~클래스명: 소멸자의 이름은 클래스명 앞에 ~를 붙인 형태
- 자동 호출: 객체가 스코프를 벗어날 때 자동으로 호출됨
- 자원 해제: 동적 메모리나 파일 등의 자원을 해제하는 작업
- RAII: 자원 획득이 초기화라는 C++의 중요한 프로그래밍 기법
*/

#include <iostream>
#include <string>
using namespace std;

class Resource {
private:
    string resourceName;
    int* data;
    
public:
    Resource(string name, int size) : resourceName(name) {
        data = new int[size];
        cout << "생성자: " << resourceName << " 자원 할당 (크기: " << size << ")" << endl;
    }
    
    ~Resource() {
        delete[] data;
        cout << "소멸자: " << resourceName << " 자원 해제" << endl;
    }
    
    void useResource() {
        cout << resourceName << " 자원 사용 중..." << endl;
    }
};

int main() {
    cout << "=== 객체 생명주기 ===" << endl;
    
    {
        Resource res1("파일핸들러", 100);
        res1.useResource();
        
        Resource res2("네트워크연결", 50);
        res2.useResource();
        
        cout << "스코프 종료 예정..." << endl;
    } // 여기서 res2, res1 순서로 소멸자 호출
    
    cout << "메인 함수 종료" << endl;
    
    return 0;
}
```

---

## 6. 예제 06: 멤버 함수 활용 (06_member_functions.cpp)

### 예제 정의
다양한 멤버 함수의 정의와 사용법을 학습합니다.

```cpp
/*
주제: 멤버 함수 (Member Functions)
정의: 클래스 내부에 정의되어 객체의 데이터를 조작하거나 객체의 동작을 정의하는 함수

핵심 개념: getter/setter, const 멤버 함수, 인라인 함수
정의:
- getter/setter: private 멤버 변수에 접근하기 위한 공용 함수들
- const 멤버 함수: 객체의 상태를 변경하지 않는 함수임을 보장하는 함수
- 인라인 함수: 함수 호출 오버헤드를 줄이기 위해 컴파일 시 함수 본체가 호출 지점에 삽입되는 함수
*/

#include <iostream>
#include <string>
using namespace std;

class Circle {
private:
    double radius;
    static const double PI;  // 정적 상수
    
public:
    // 생성자
    Circle(double r = 1.0) : radius(r) {}
    
    // Setter
    void setRadius(double r) {
        if (r > 0) {
            radius = r;
        }
    }
    
    // Getter (const 함수)
    double getRadius() const {
        return radius;
    }
    
    // 인라인 함수
    inline double getArea() const {
        return PI * radius * radius;
    }
    
    double getCircumference() const {
        return 2 * PI * radius;
    }
    
    // 객체 비교 함수
    bool isLarger(const Circle& other) const {
        return this->getArea() > other.getArea();
    }
    
    void display() const {
        cout << "반지름: " << radius 
             << ", 넓이: " << getArea() 
             << ", 둘레: " << getCircumference() << endl;
    }
};

// 정적 멤버 초기화
const double Circle::PI = 3.14159;

int main() {
    Circle c1(5.0);
    Circle c2(3.0);
    
    cout << "=== 원 정보 ===" << endl;
    cout << "원1: ";
    c1.display();
    cout << "원2: ";
    c2.display();
    
    if (c1.isLarger(c2)) {
        cout << "원1이 원2보다 큽니다." << endl;
    } else {
        cout << "원2가 원1보다 크거나 같습니다." << endl;
    }
    
    return 0;
}
```

---

## 7. 예제 07: 정적 멤버 (07_static_members.cpp)

### 예제 정의
정적 멤버 변수와 정적 멤버 함수의 사용법을 학습합니다.

```cpp
/*
주제: 정적 멤버 (Static Members)
정의: 클래스에 속하지만 특정 객체에 속하지 않는 멤버로, 모든 객체가 공유하는 멤버

핵심 개념: static 키워드, 클래스 변수, 클래스 함수, 공유 자원
정의:
- static 키워드: 정적 멤버를 선언하는 키워드
- 클래스 변수: 모든 객체가 공유하는 변수
- 클래스 함수: 객체 없이도 호출할 수 있는 함수
- 공유 자원: 모든 인스턴스가 동일한 메모리 위치를 참조하는 자원
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    static int totalCount;    // 정적 멤버 변수
    static int nextId;        // 다음 ID
    
public:
    Student(string n) : name(n) {
        id = nextId++;
        totalCount++;
        cout << "학생 생성: " << name << " (ID: " << id << ")" << endl;
    }
    
    ~Student() {
        totalCount--;
        cout << "학생 소멸: " << name << " (ID: " << id << ")" << endl;
    }
    
    // 정적 멤버 함수
    static int getTotalCount() {
        return totalCount;
    }
    
    static void printStatistics() {
        cout << "현재 총 학생 수: " << totalCount << endl;
        cout << "다음 학생 ID: " << nextId << endl;
    }
    
    void display() const {
        cout << "학생명: " << name << ", ID: " << id << endl;
    }
};

// 정적 멤버 변수 초기화 (클래스 외부에서)
int Student::totalCount = 0;
int Student::nextId = 1001;

int main() {
    cout << "=== 학생 관리 시스템 ===" << endl;
    
    Student::printStatistics();
    
    {
        Student s1("김철수");
        Student s2("이영희");
        Student s3("박민수");
        
        cout << "\n현재 학생들:" << endl;
        s1.display();
        s2.display();
        s3.display();
        
        cout << "\n총 학생 수: " << Student::getTotalCount() << endl;
    } // 스코프 종료로 모든 학생 객체 소멸
    
    cout << "\n스코프 종료 후:" << endl;
    Student::printStatistics();
    
    return 0;
}
```

---

## 8. 예제 08: const 멤버 (08_const_members.cpp)

### 예제 정의
const 멤버 변수와 const 멤버 함수의 사용법을 학습합니다.

```cpp
/*
주제: const 멤버 (const Members)
정의: 값을 변경할 수 없는 멤버 변수나 객체의 상태를 변경하지 않는 멤버 함수

핵심 개념: const 멤버 변수, const 멤버 함수, mutable, 불변성
정의:
- const 멤버 변수: 생성 후 값을 변경할 수 없는 멤버 변수
- const 멤버 함수: 객체의 멤버 변수를 변경하지 않는 함수
- mutable: const 객체에서도 수정 가능한 멤버 변수를 지정하는 키워드
- 불변성: 객체의 상태가 변경되지 않음을 보장하는 프로그래밍 원칙
*/

#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    const string isbn;        // const 멤버 변수
    string title;
    mutable int accessCount;  // mutable 멤버
    
public:
    // const 멤버 변수는 초기화 리스트에서만 초기화 가능
    Book(string isbnCode, string bookTitle) 
        : isbn(isbnCode), title(bookTitle), accessCount(0) {}
    
    // const 멤버 함수 - 객체 상태를 변경하지 않음
    string getISBN() const {
        accessCount++;  // mutable이므로 const 함수에서도 변경 가능
        return isbn;
    }
    
    string getTitle() const {
        accessCount++;
        return title;
    }
    
    int getAccessCount() const {
        return accessCount;
    }
    
    // 비const 멤버 함수 - 객체 상태를 변경할 수 있음
    void setTitle(string newTitle) {
        title = newTitle;
    }
    
    void display() const {
        cout << "ISBN: " << isbn 
             << ", 제목: " << title 
             << ", 접근 횟수: " << accessCount << endl;
    }
};

int main() {
    Book book("978-3-16-148410-0", "C++ 프로그래밍");
    const Book constBook("978-1-23-456789-0", "객체지향 설계");
    
    cout << "=== 도서 정보 ===" << endl;
    
    // 일반 객체
    book.display();
    book.setTitle("C++ 고급 프로그래밍");
    cout << "제목 변경 후: ";
    book.display();
    
    // const 객체
    cout << "\nconst 객체:" << endl;
    constBook.display();
    cout << "ISBN: " << constBook.getISBN() << endl;
    // constBook.setTitle("새 제목"); // 오류: const 객체에서 비const 함수 호출 불가
    
    cout << "접근 후 const 객체: ";
    constBook.display();
    
    return 0;
}
```

---

## 9. 예제 09: 복사 생성자 (09_copy_constructor.cpp)

### 예제 정의
복사 생성자의 필요성과 사용법을 학습합니다.

```cpp
/*
주제: 복사 생성자 (Copy Constructor)
정의: 기존 객체를 복사하여 새로운 객체를 생성할 때 호출되는 특별한 생성자

핵심 개념: 얕은 복사, 깊은 복사, 복사 생성자 호출 시점
정의:
- 얕은 복사: 포인터 값만 복사하여 같은 메모리를 가리키는 복사
- 깊은 복사: 포인터가 가리키는 메모리까지 새로 할당하여 복사하는 방법
- 복사 생성자 호출 시점: 객체를 다른 객체로 초기화할 때, 함수 매개변수로 전달할 때 등
*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class MyString {
private:
    char* data;
    int length;
    
public:
    // 생성자
    MyString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        cout << "생성자: \"" << data << "\" 생성" << endl;
    }
    
    // 복사 생성자 (깊은 복사)
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        cout << "복사 생성자: \"" << data << "\" 복사 생성" << endl;
    }
    
    // 소멸자
    ~MyString() {
        cout << "소멸자: \"" << data << "\" 해제" << endl;
        delete[] data;
    }
    
    void display() const {
        cout << "문자열: \"" << data << "\", 길이: " << length << endl;
    }
    
    void modify(char ch) {
        if (length > 0) {
            data[0] = ch;
        }
    }
};

int main() {
    cout << "=== 복사 생성자 테스트 ===" << endl;
    
    MyString str1("Hello");
    str1.display();
    
    // 복사 생성자 호출
    MyString str2 = str1;  // 또는 MyString str2(str1);
    str2.display();
    
    cout << "\n첫 번째 문자 수정 테스트:" << endl;
    str1.modify('h');
    str1.display();
    str2.display();  // 깊은 복사로 인해 영향받지 않음
    
    cout << "\n프로그램 종료..." << endl;
    
    return 0;
}
```

---

## 10. 예제 10: 이동 생성자 (10_move_constructor.cpp)

### 예제 정의
이동 생성자와 이동 의미론의 기본 개념을 학습합니다.

```cpp
/*
주제: 이동 생성자 (Move Constructor)
정의: 임시 객체나 더 이상 사용되지 않는 객체의 자원을 효율적으로 이동시키는 생성자

핵심 개념: 이동 의미론, 우측값 참조, std::move, 자원 이동
정의:
- 이동 의미론: 복사 대신 자원을 이동시켜 성능을 향상시키는 C++11의 개념
- 우측값 참조(&&): 임시 객체나 이동 가능한 객체를 참조하는 참조 타입
- std::move: 좌측값을 우측값으로 변환하여 이동을 강제하는 함수
- 자원 이동: 메모리나 파일 핸들 등의 자원 소유권을 다른 객체로 이전
*/

#include <iostream>
#include <string>
#include <utility>  // std::move
using namespace std;

class MovableResource {
private:
    int* data;
    size_t size;
    string name;
    
public:
    // 생성자
    MovableResource(size_t s, string n) : size(s), name(n) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
        cout << "생성자: " << name << " (크기: " << size << ")" << endl;
    }
    
    // 복사 생성자
    MovableResource(const MovableResource& other) : size(other.size), name(other.name + "_copy") {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        cout << "복사 생성자: " << name << " (크기: " << size << ")" << endl;
    }
    
    // 이동 생성자
    MovableResource(MovableResource&& other) noexcept 
        : data(other.data), size(other.size), name(other.name + "_moved") {
        other.data = nullptr;
        other.size = 0;
        cout << "이동 생성자: " << name << " (자원 이동)" << endl;
    }
    
    // 소멸자
    ~MovableResource() {
        if (data) {
            cout << "소멸자: " << name << " 해제" << endl;
            delete[] data;
        } else {
            cout << "소멸자: " << name << " (이미 이동됨)" << endl;
        }
    }
    
    void display() const {
        if (data) {
            cout << name << ": 첫 번째 요소 = " << data[0] << ", 크기 = " << size << endl;
        } else {
            cout << name << ": 자원 없음 (이동됨)" << endl;
        }
    }
};

int main() {
    cout << "=== 이동 생성자 테스트 ===" << endl;
    
    MovableResource res1(5, "Resource1");
    res1.display();
    
    // 복사 생성자 호출
    MovableResource res2 = res1;
    res2.display();
    
    // 이동 생성자 호출
    MovableResource res3 = std::move(res1);
    res3.display();
    
    cout << "\n이동 후 원본 객체:" << endl;
    res1.display();
    
    cout << "\n프로그램 종료..." << endl;
    
    return 0;
}
```

---

## 11. 예제 11: 연산자 오버로딩 기초 (11_operator_overloading.cpp)

### 예제 정의
기본적인 연산자 오버로딩의 개념과 사용법을 학습합니다.

```cpp
/*
주제: 연산자 오버로딩 (Operator Overloading)
정의: 사용자 정의 타입에 대해 기존 연산자의 동작을 재정의하는 기능

핵심 개념: operator 키워드, 멤버 함수 오버로딩, 이항 연산자
정의:
- operator 키워드: 연산자 오버로딩을 정의할 때 사용하는 키워드
- 멤버 함수 오버로딩: 클래스의 멤버 함수로 연산자를 오버로딩하는 방법
- 이항 연산자: 두 개의 피연산자를 가지는 연산자 (+, -, *, / 등)
*/

#include <iostream>
using namespace std;

class Point {
private:
    int x, y;
    
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    // + 연산자 오버로딩
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    // - 연산자 오버로딩
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    // == 연산자 오버로딩
    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
    
    // << 연산자 오버로딩 (friend 함수로 구현)
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
};

int main() {
    Point p1(3, 4);
    Point p2(1, 2);
    
    cout << "=== 연산자 오버로딩 테스트 ===" << endl;
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    
    Point p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;
    
    Point p4 = p1 - p2;
    cout << "p1 - p2 = " << p4 << endl;
    
    if (p1 == p2) {
        cout << "p1과 p2는 같습니다." << endl;
    } else {
        cout << "p1과 p2는 다릅니다." << endl;
    }
    
    return 0;
}
```

---

## 12. 예제 12: 객체 배열 (12_object_array.cpp)

### 예제 정의
객체 배열의 생성과 관리 방법을 학습합니다.

```cpp
/*
주제: 객체 배열 (Object Array)
정의: 동일한 클래스의 여러 객체를 배열 형태로 저장하고 관리하는 방법

핵심 개념: 객체 배열 선언, 생성자 호출, 배열 순회
정의:
- 객체 배열 선언: 클래스 타입의 배열을 선언하는 방법
- 생성자 호출: 배열의 각 요소 객체가 생성될 때 생성자가 호출되는 과정
- 배열 순회: 객체 배열의 모든 요소에 대해 반복 작업을 수행하는 방법
*/

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string name;
    double price;
    int stock;
    
public:
    Product() : name("Unknown"), price(0.0), stock(0) {
        cout << "기본 생성자: " << name << endl;
    }
    
    Product(string n, double p, int s) : name(n), price(p), stock(s) {
        cout << "매개변수 생성자: " << name << endl;
    }
    
    ~Product() {
        cout << "소멸자: " << name << endl;
    }
    
    void setProduct(string n, double p, int s) {
        name = n;
        price = p;
        stock = s;
    }
    
    void display() const {
        cout << "상품: " << name << ", 가격: " << price << "원, 재고: " << stock << "개" << endl;
    }
    
    double getTotalValue() const {
        return price * stock;
    }
    
    string getName() const { return name; }
};

int main() {
    cout << "=== 객체 배열 생성 ===" << endl;
    
    // 기본 생성자로 배열 생성
    Product products[3];
    
    // 각 객체 초기화
    products[0].setProduct("노트북", 1200000, 5);
    products[1].setProduct("마우스", 25000, 20);
    products[2].setProduct("키보드", 80000, 15);
    
    cout << "\n=== 상품 목록 ===" << endl;
    for (int i = 0; i < 3; i++) {
        products[i].display();
    }
    
    cout << "\n=== 총 가치 계산 ===" << endl;
    double totalValue = 0;
    for (int i = 0; i < 3; i++) {
        double value = products[i].getTotalValue();
        cout << products[i].getName() << " 총 가치: " << value << "원" << endl;
        totalValue += value;
    }
    cout << "전체 재고 가치: " << totalValue << "원" << endl;
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 13. 예제 13: 객체와 함수 (13_objects_functions.cpp)

### 예제 정의
객체를 함수의 매개변수와 반환값으로 사용하는 방법을 학습합니다.

```cpp
/*
주제: 객체와 함수 (Objects and Functions)
정의: 객체를 함수의 매개변수로 전달하거나 반환값으로 사용하는 방법

핵심 개념: 객체 전달, 참조 전달, 객체 반환, 임시 객체
정의:
- 객체 전달: 객체를 함수의 매개변수로 전달하는 방법 (값, 참조, 포인터)
- 참조 전달: 객체의 복사 오버헤드를 피하기 위해 참조로 전달하는 방법
- 객체 반환: 함수에서 객체를 생성하여 반환하는 방법
- 임시 객체: 함수 반환 등에서 생성되는 임시적인 객체
*/

#include <iostream>
#include <string>
using namespace std;

class Calculator {
private:
    double result;
    
public:
    Calculator(double initial = 0) : result(initial) {
        cout << "계산기 생성 (초기값: " << result << ")" << endl;
    }
    
    Calculator(const Calculator& other) : result(other.result) {
        cout << "계산기 복사 생성 (값: " << result << ")" << endl;
    }
    
    ~Calculator() {
        cout << "계산기 소멸 (값: " << result << ")" << endl;
    }
    
    double getResult() const { return result; }
    
    void add(double value) { result += value; }
    void multiply(double value) { result *= value; }
    
    void display() const {
        cout << "현재 결과: " << result << endl;
    }
};

// 객체를 값으로 전달 (복사 발생)
void printCalculator(Calculator calc) {
    cout << "함수 내부에서 ";
    calc.display();
}

// 객체를 참조로 전달 (복사 없음)
void modifyCalculator(Calculator& calc) {
    calc.add(10);
    cout << "함수에서 10 추가 후 ";
    calc.display();
}

// 객체를 const 참조로 전달 (읽기 전용)
void readCalculator(const Calculator& calc) {
    cout << "읽기 전용 접근: ";
    calc.display();
}

// 객체 반환
Calculator createCalculator(double value) {
    Calculator temp(value);
    temp.multiply(2);
    return temp;  // 복사 또는 이동이 발생할 수 있음
}

int main() {
    cout << "=== 객체와 함수 ===" << endl;
    
    Calculator calc1(5.0);
    calc1.display();
    
    cout << "\n--- 값 전달 ---" << endl;
    printCalculator(calc1);  // 복사 생성자 호출
    
    cout << "\n--- 참조 전달 ---" << endl;
    modifyCalculator(calc1);  // 원본 수정
    
    cout << "\n--- const 참조 전달 ---" << endl;
    readCalculator(calc1);
    
    cout << "\n--- 객체 반환 ---" << endl;
    Calculator calc2 = createCalculator(3.0);
    calc2.display();
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 14. 예제 14: this 포인터 (14_this_pointer.cpp)

### 예제 정의
this 포인터의 개념과 사용법을 학습합니다.

```cpp
/*
주제: this 포인터 (this Pointer)
정의: 현재 객체를 가리키는 포인터로, 멤버 함수 내에서 자동으로 제공되는 포인터

핵심 개념: this 키워드, 자기 참조, 체이닝, 멤버 변수 구분
정의:
- this 키워드: 현재 객체의 주소를 가리키는 포인터
- 자기 참조: 객체가 자기 자신을 참조하는 것
- 체이닝: 멤버 함수가 자기 자신을 반환하여 연속 호출을 가능하게 하는 기법
- 멤버 변수 구분: 매개변수와 멤버 변수의 이름이 같을 때 구분하는 방법
*/

#include <iostream>
#include <string>
using namespace std;

class ChainableCalculator {
private:
    double value;
    
public:
    ChainableCalculator(double value = 0) : value(value) {}
    
    // this 포인터를 사용한 매개변수와 멤버 변수 구분
    ChainableCalculator& setValue(double value) {
        this->value = value;  // this->를 사용하여 멤버 변수 지정
        return *this;         // 자기 자신의 참조 반환
    }
    
    // 체이닝을 위한 멤버 함수들
    ChainableCalculator& add(double value) {
        this->value += value;
        return *this;
    }
    
    ChainableCalculator& multiply(double value) {
        this->value *= value;
        return *this;
    }
    
    ChainableCalculator& subtract(double value) {
        this->value -= value;
        return *this;
    }
    
    double getValue() const {
        return value;
    }
    
    void display() const {
        cout << "값: " << value << endl;
    }
    
    // 객체 비교 함수
    bool isEqual(const ChainableCalculator& other) const {
        return this->value == other.value;
    }
    
    // 자기 자신과의 비교 확인
    bool isSameObject(const ChainableCalculator& other) const {
        return this == &other;
    }
};

int main() {
    cout << "=== this 포인터 활용 ===" << endl;
    
    ChainableCalculator calc1(10);
    ChainableCalculator calc2;
    
    // 체이닝을 이용한 연속 연산
    calc2.setValue(5).add(3).multiply(2).subtract(1);
    
    cout << "calc1: ";
    calc1.display();
    cout << "calc2 (체이닝 연산 후): ";
    calc2.display();
    
    // 객체 비교
    cout << "\n=== 객체 비교 ===" << endl;
    cout << "값이 같은가? " << calc1.isEqual(calc2) << endl;
    cout << "같은 객체인가? " << calc1.isSameObject(calc2) << endl;
    cout << "자기 자신과 같은 객체인가? " << calc1.isSameObject(calc1) << endl;
    
    return 0;
}
```

---

## 15. 예제 15: 프렌드 함수 기초 (15_friend_functions.cpp)

### 예제 정의
프렌드 함수의 개념과 기본 사용법을 학습합니다.

```cpp
/*
주제: 프렌드 함수 (Friend Functions)
정의: 클래스의 private 및 protected 멤버에 접근할 수 있는 특별한 권한을 가진 외부 함수

핵심 개념: friend 키워드, 캡슐화 예외, 연산자 오버로딩, 클래스 간 협력
정의:
- friend 키워드: 함수나 클래스에게 private 멤버 접근 권한을 부여하는 키워드
- 캡슐화 예외: 정보 은닉 원칙의 예외적 허용
- 연산자 오버로딩: 특히 이항 연산자를 구현할 때 유용
- 클래스 간 협력: 서로 다른 클래스가 내부 데이터를 공유해야 할 때 사용
*/

#include <iostream>
#include <cmath>
using namespace std;

class Vector2D {
private:
    double x, y;
    
public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    // friend 함수 선언
    friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
    friend double dotProduct(const Vector2D& v1, const Vector2D& v2);
    friend ostream& operator<<(ostream& os, const Vector2D& v);
    friend istream& operator>>(istream& is, Vector2D& v);
    
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
};

// friend 함수 구현 - 클래스 외부에서 정의
Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.x + v2.x, v1.y + v2.y);  // private 멤버 직접 접근
}

double dotProduct(const Vector2D& v1, const Vector2D& v2) {
    return v1.x * v2.x + v1.y * v2.y;  // private 멤버 직접 접근
}

ostream& operator<<(ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";  // private 멤버 직접 접근
    return os;
}

istream& operator>>(istream& is, Vector2D& v) {
    cout << "x 좌표 입력: ";
    is >> v.x;  // private 멤버 직접 접근
    cout << "y 좌표 입력: ";
    is >> v.y;  // private 멤버 직접 접근
    return is;
}

int main() {
    cout << "=== 프렌드 함수 활용 ===" << endl;
    
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    
    cout << "벡터1: " << v1 << endl;
    cout << "벡터2: " << v2 << endl;
    cout << "벡터1 크기: " << v1.magnitude() << endl;
    
    // friend 함수들 사용
    Vector2D v3 = v1 + v2;  // operator+ 사용
    cout << "벡터1 + 벡터2 = " << v3 << endl;
    
    double dot = dotProduct(v1, v2);
    cout << "내적: " << dot << endl;
    
    // 사용자 입력 (주석 처리됨)
    // Vector2D userVector;
    // cin >> userVector;
    // cout << "입력된 벡터: " << userVector << endl;
    
    return 0;
}
```

---

## 16. 예제 16: 상속 기초 (16_inheritance_basic.cpp)

### 예제 정의
상속의 기본 개념과 사용법을 학습합니다.

```cpp
/*
주제: 상속 (Inheritance)
정의: 기존 클래스(부모 클래스)의 속성과 메서드를 새로운 클래스(자식 클래스)가 물려받는 객체지향의 핵심 개념

핵심 개념: 부모 클래스, 자식 클래스, 상속 접근 지정자, 코드 재사용
정의:
- 부모 클래스(기본 클래스): 상속을 제공하는 클래스
- 자식 클래스(파생 클래스): 상속을 받는 클래스
- 상속 접근 지정자: public, protected, private 상속의 종류
- 코드 재사용: 기존 코드를 재사용하여 새로운 기능을 구현하는 방법
*/

#include <iostream>
#include <string>
using namespace std;

// 부모 클래스 (기본 클래스)
class Animal {
protected:  // 자식 클래스에서 접근 가능
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "동물 생성: " << name << endl;
    }
    
    virtual ~Animal() {  // 가상 소멸자
        cout << "동물 소멸: " << name << endl;
    }
    
    void eat() {
        cout << name << "가 먹이를 먹습니다." << endl;
    }
    
    void sleep() {
        cout << name << "가 잠을 잡니다." << endl;
    }
    
    virtual void makeSound() {  // 가상 함수
        cout << name << "가 소리를 냅니다." << endl;
    }
    
    void displayInfo() {
        cout << "이름: " << name << ", 나이: " << age << "세" << endl;
    }
};

// 자식 클래스 1
class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "개 생성: " << name << " (" << breed << ")" << endl;
    }
    
    ~Dog() {
        cout << "개 소멸: " << name << endl;
    }
    
    // 부모의 가상 함수 오버라이딩
    void makeSound() override {
        cout << name << "가 멍멍 짖습니다." << endl;
    }
    
    // 자식 클래스만의 고유 메서드
    void fetch() {
        cout << name << "가 공을 가져옵니다." << endl;
    }
    
    void displayBreed() {
        cout << "품종: " << breed << endl;
    }
};

// 자식 클래스 2
class Cat : public Animal {
public:
    Cat(string n, int a) : Animal(n, a) {
        cout << "고양이 생성: " << name << endl;
    }
    
    ~Cat() {
        cout << "고양이 소멸: " << name << endl;
    }
    
    void makeSound() override {
        cout << name << "가 야옹 웁니다." << endl;
    }
    
    void climb() {
        cout << name << "가 나무에 올라갑니다." << endl;
    }
};

int main() {
    cout << "=== 상속 기초 ===" << endl;
    
    Dog dog("멍멍이", 3, "골든리트리버");
    Cat cat("나비", 2);
    
    cout << "\n=== 기본 정보 ===" << endl;
    dog.displayInfo();
    dog.displayBreed();
    cat.displayInfo();
    
    cout << "\n=== 공통 동작 ===" << endl;
    dog.eat();
    dog.sleep();
    cat.eat();
    cat.sleep();
    
    cout << "\n=== 고유 동작 ===" << endl;
    dog.makeSound();
    dog.fetch();
    cat.makeSound();
    cat.climb();
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 17. 예제 17: 가상 함수 기초 (17_virtual_functions.cpp)

### 예제 정의
가상 함수와 다형성의 기본 개념을 학습합니다.

```cpp
/*
주제: 가상 함수 (Virtual Functions)
정의: 런타임에 실제 객체 타입에 따라 호출될 함수가 결정되는 함수

핵심 개념: virtual 키워드, 다형성, 동적 바인딩, 가상 함수 테이블
정의:
- virtual 키워드: 함수를 가상 함수로 선언하는 키워드
- 다형성: 하나의 인터페이스로 여러 타입의 객체를 다루는 능력
- 동적 바인딩: 런타임에 실제 호출할 함수가 결정되는 방식
- 가상 함수 테이블: 가상 함수 호출을 위한 함수 포인터 테이블
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Shape {
protected:
    string name;
    
public:
    Shape(string n) : name(n) {
        cout << "도형 생성: " << name << endl;
    }
    
    virtual ~Shape() {
        cout << "도형 소멸: " << name << endl;
    }
    
    // 순수 가상 함수
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    
    // 가상 함수
    virtual void display() const {
        cout << "도형: " << name << endl;
    }
    
    string getName() const { return name; }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("사각형"), width(w), height(h) {}
    
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        cout << "사각형 - 가로: " << width << ", 세로: " << height << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    static const double PI;
    
public:
    Circle(double r) : Shape("원"), radius(r) {}
    
    double getArea() const override {
        return PI * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * PI * radius;
    }
    
    void display() const override {
        cout << "원 - 반지름: " << radius << endl;
    }
};

const double Circle::PI = 3.14159;

int main() {
    cout << "=== 가상 함수와 다형성 ===" << endl;
    
    // 다형성을 위한 포인터 배열
    vector<unique_ptr<Shape>> shapes;
    
    shapes.push_back(make_unique<Rectangle>(5, 3));
    shapes.push_back(make_unique<Circle>(4));
    shapes.push_back(make_unique<Rectangle>(2, 7));
    
    cout << "\n=== 도형 정보 출력 ===" << endl;
    for (const auto& shape : shapes) {
        shape->display();  // 가상 함수 호출 - 실제 타입에 따라 결정
        cout << "넓이: " << shape->getArea() << endl;
        cout << "둘레: " << shape->getPerimeter() << endl;
        cout << "----------------" << endl;
    }
    
    cout << "\n=== 총 넓이 계산 ===" << endl;
    double totalArea = 0;
    for (const auto& shape : shapes) {
        totalArea += shape->getArea();  // 다형성을 통한 통일된 인터페이스
    }
    cout << "모든 도형의 총 넓이: " << totalArea << endl;
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 18. 예제 18: 다형성 활용 (18_polymorphism.cpp)

### 예제 정의
다형성을 활용한 실제적인 프로그래밍 기법을 학습합니다.

```cpp
/*
주제: 다형성 활용 (Polymorphism Application)
정의: 상속과 가상 함수를 통해 서로 다른 타입의 객체를 통일된 방식으로 처리하는 프로그래밍 기법

핵심 개념: 인터페이스 통일, 타입 안전성, 확장성, 팩토리 패턴
정의:
- 인터페이스 통일: 다양한 타입의 객체를 같은 방식으로 사용할 수 있게 하는 것
- 타입 안전성: 컴파일 시점과 런타임에 타입 오류를 방지하는 특성
- 확장성: 새로운 타입을 추가할 때 기존 코드 변경 없이 확장 가능한 특성
- 팩토리 패턴: 객체 생성을 캡슐화하여 다형성을 활용하는 디자인 패턴
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// 추상 기본 클래스
class Employee {
protected:
    string name;
    int id;
    double baseSalary;
    
public:
    Employee(string n, int i, double salary) : name(n), id(i), baseSalary(salary) {}
    
    virtual ~Employee() = default;
    
    // 순수 가상 함수 - 각 직원 타입마다 다르게 구현
    virtual double calculateSalary() const = 0;
    virtual string getJobTitle() const = 0;
    virtual void displayDetails() const = 0;
    
    // 공통 인터페이스
    string getName() const { return name; }
    int getId() const { return id; }
    double getBaseSalary() const { return baseSalary; }
};

class FullTimeEmployee : public Employee {
private:
    double bonus;
    
public:
    FullTimeEmployee(string n, int i, double salary, double b) 
        : Employee(n, i, salary), bonus(b) {}
    
    double calculateSalary() const override {
        return baseSalary + bonus;
    }
    
    string getJobTitle() const override {
        return "정규직";
    }
    
    void displayDetails() const override {
        cout << "정규직 - " << name << " (ID: " << id << ")" << endl;
        cout << "  기본급: " << baseSalary << ", 보너스: " << bonus << endl;
        cout << "  총 급여: " << calculateSalary() << endl;
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;
    
public:
    PartTimeEmployee(string n, int i, double rate, int hours) 
        : Employee(n, i, 0), hourlyRate(rate), hoursWorked(hours) {}
    
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    
    string getJobTitle() const override {
        return "시간제";
    }
    
    void displayDetails() const override {
        cout << "시간제 - " << name << " (ID: " << id << ")" << endl;
        cout << "  시급: " << hourlyRate << ", 근무시간: " << hoursWorked << endl;
        cout << "  총 급여: " << calculateSalary() << endl;
    }
};

class Contractor : public Employee {
private:
    double projectFee;
    
public:
    Contractor(string n, int i, double fee) 
        : Employee(n, i, 0), projectFee(fee) {}
    
    double calculateSalary() const override {
        return projectFee;
    }
    
    string getJobTitle() const override {
        return "계약직";
    }
    
    void displayDetails() const override {
        cout << "계약직 - " << name << " (ID: " << id << ")" << endl;
        cout << "  프로젝트 수수료: " << projectFee << endl;
        cout << "  총 급여: " << calculateSalary() << endl;
    }
};

// 다형성을 활용한 급여 관리 시스템
class PayrollSystem {
private:
    vector<unique_ptr<Employee>> employees;
    
public:
    void addEmployee(unique_ptr<Employee> emp) {
        employees.push_back(move(emp));
    }
    
    void displayAllEmployees() const {
        cout << "=== 전체 직원 정보 ===" << endl;
        for (const auto& emp : employees) {
            emp->displayDetails();  // 다형성: 실제 타입에 따라 다른 함수 호출
            cout << "--------------------" << endl;
        }
    }
    
    double calculateTotalPayroll() const {
        double total = 0;
        for (const auto& emp : employees) {
            total += emp->calculateSalary();  // 다형성 활용
        }
        return total;
    }
    
    void displayPayrollSummary() const {
        cout << "=== 급여 요약 ===" << endl;
        for (const auto& emp : employees) {
            cout << emp->getName() << " (" << emp->getJobTitle() << "): " 
                 << emp->calculateSalary() << "원" << endl;
        }
        cout << "총 급여 지출: " << calculateTotalPayroll() << "원" << endl;
    }
};

int main() {
    cout << "=== 다형성 기반 급여 시스템 ===" << endl;
    
    PayrollSystem payroll;
    
    // 다양한 타입의 직원 추가
    payroll.addEmployee(make_unique<FullTimeEmployee>("김정규", 1001, 3000000, 500000));
    payroll.addEmployee(make_unique<PartTimeEmployee>("이시간", 1002, 15000, 80));
    payroll.addEmployee(make_unique<Contractor>("박계약", 1003, 2000000));
    payroll.addEmployee(make_unique<FullTimeEmployee>("최정규", 1004, 3500000, 700000));
    
    payroll.displayAllEmployees();
    cout << endl;
    payroll.displayPayrollSummary();
    
    return 0;
}
```

---

## 19. 예제 19: 객체 수명 관리 (19_object_lifetime.cpp)

### 예제 정의
객체의 생성과 소멸 과정을 자세히 관찰하고 수명 관리를 학습합니다.

```cpp
/*
주제: 객체 수명 관리 (Object Lifetime Management)
정의: 객체가 생성되고 소멸되는 전체 과정을 이해하고 적절히 관리하는 방법

핵심 개념: 스택 객체, 힙 객체, 스코프, RAII 패턴
정의:
- 스택 객체: 스택 메모리에 생성되어 스코프를 벗어날 때 자동으로 소멸되는 객체
- 힙 객체: 힙 메모리에 동적으로 생성되어 명시적으로 해제해야 하는 객체
- 스코프: 변수나 객체가 유효한 범위
- RAII 패턴: 자원 획득은 초기화 시점에, 자원 해제는 소멸 시점에 수행하는 패턴
*/

#include <iostream>
#include <string>
#include <memory>
using namespace std;

class LifetimeTracker {
private:
    string name;
    static int objectCount;
    
public:
    LifetimeTracker(string n) : name(n) {
        objectCount++;
        cout << "[" << objectCount << "] 생성자: " << name << " 생성" << endl;
    }
    
    LifetimeTracker(const LifetimeTracker& other) : name(other.name + "_copy") {
        objectCount++;
        cout << "[" << objectCount << "] 복사 생성자: " << name << " 생성" << endl;
    }
    
    LifetimeTracker& operator=(const LifetimeTracker& other) {
        if (this != &other) {
            name = other.name + "_assigned";
            cout << "대입 연산자: " << name << " 대입됨" << endl;
        }
        return *this;
    }
    
    ~LifetimeTracker() {
        cout << "[" << objectCount << "] 소멸자: " << name << " 소멸" << endl;
        objectCount--;
    }
    
    void action() const {
        cout << name << "가 동작 중..." << endl;
    }
    
    string getName() const { return name; }
    static int getObjectCount() { return objectCount; }
};

int LifetimeTracker::objectCount = 0;

void demonstrateStackObjects() {
    cout << "\n=== 스택 객체 데모 ===" << endl;
    LifetimeTracker obj1("스택객체1");
    obj1.action();
    
    {
        LifetimeTracker obj2("스택객체2");
        obj2.action();
        cout << "내부 스코프 종료 예정..." << endl;
    } // obj2 소멸
    
    cout << "외부 스코프 계속..." << endl;
    obj1.action();
    cout << "외부 스코프 종료 예정..." << endl;
} // obj1 소멸

void demonstrateHeapObjects() {
    cout << "\n=== 힙 객체 데모 ===" << endl;
    
    // 원시 포인터 (권장하지 않음)
    LifetimeTracker* rawPtr = new LifetimeTracker("힙객체1");
    rawPtr->action();
    delete rawPtr;  // 명시적 해제 필요
    
    // 스마트 포인터 (권장)
    {
        auto smartPtr = make_unique<LifetimeTracker>("힙객체2");
        smartPtr->action();
        cout << "스마트 포인터 스코프 종료 예정..." << endl;
    } // 자동 해제
}

void demonstrateCopySemantics() {
    cout << "\n=== 복사 의미론 데모 ===" << endl;
    LifetimeTracker original("원본");
    
    LifetimeTracker copy1 = original;  // 복사 생성자
    LifetimeTracker copy2("임시");
    copy2 = original;  // 대입 연산자
    
    cout << "복사 데모 종료 예정..." << endl;
}

int main() {
    cout << "=== 객체 수명 관리 ===" << endl;
    cout << "시작 시 객체 수: " << LifetimeTracker::getObjectCount() << endl;
    
    demonstrateStackObjects();
    cout << "스택 데모 후 객체 수: " << LifetimeTracker::getObjectCount() << endl;
    
    demonstrateHeapObjects();
    cout << "힙 데모 후 객체 수: " << LifetimeTracker::getObjectCount() << endl;
    
    demonstrateCopySemantics();
    cout << "복사 데모 후 객체 수: " << LifetimeTracker::getObjectCount() << endl;
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    cout << "최종 객체 수: " << LifetimeTracker::getObjectCount() << endl;
    
    return 0;
}
```

---

## 20. 예제 20: 종합 실습 - 도서관 관리 시스템 (20_library_system.cpp)

### 예제 정의
지금까지 학습한 클래스와 객체지향 개념을 종합하여 도서관 관리 시스템을 구현합니다.

```cpp
/*
주제: 종합 실습 프로젝트 (Comprehensive Practice Project)
정의: 클래스, 상속, 다형성, 캡슐화 등 객체지향의 모든 개념을 통합하여 실제 시스템을 구현

핵심 개념: 시스템 설계, 클래스 계층, 데이터 관리, 사용자 인터페이스
정의:
- 시스템 설계: 요구사항을 분석하여 적절한 클래스 구조로 설계하는 과정
- 클래스 계층: 상속을 활용하여 계층적으로 구조화된 클래스들
- 데이터 관리: 객체들의 생성, 저장, 검색, 삭제 등을 관리하는 방법
- 사용자 인터페이스: 사용자와 시스템 간의 상호작용을 처리하는 부분
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// 기본 도서 클래스
class Book {
protected:
    string title;
    string author;
    string isbn;
    bool isAvailable;
    static int nextId;
    int id;
    
public:
    Book(string t, string a, string i) 
        : title(t), author(a), isbn(i), isAvailable(true), id(nextId++) {}
    
    virtual ~Book() = default;
    
    // 가상 함수들
    virtual void displayInfo() const {
        cout << "ID: " << id << ", 제목: " << title 
             << ", 저자: " << author << ", ISBN: " << isbn
             << ", 상태: " << (isAvailable ? "대출가능" : "대출중") << endl;
    }
    
    virtual string getType() const { return "일반도서"; }
    virtual double getLateFee(int daysLate) const { return daysLate * 100; }
    
    // Getter/Setter
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getAvailability() const { return isAvailable; }
    
    void setAvailability(bool available) { isAvailable = available; }
};

int Book::nextId = 1001;

// 전문 서적 클래스
class TechnicalBook : public Book {
private:
    string field;
    
public:
    TechnicalBook(string t, string a, string i, string f) 
        : Book(t, a, i), field(f) {}
    
    void displayInfo() const override {
        Book::displayInfo();
        cout << "    분야: " << field << " (전문서적)" << endl;
    }
    
    string getType() const override { return "전문서적"; }
    
    double getLateFee(int daysLate) const override { 
        return daysLate * 200; // 전문서적은 연체료가 더 높음
    }
};

// 소설 클래스
class Novel : public Book {
private:
    string genre;
    
public:
    Novel(string t, string a, string i, string g) 
        : Book(t, a, i), genre(g) {}
    
    void displayInfo() const override {
        Book::displayInfo();
        cout << "    장르: " << genre << " (소설)" << endl;
    }
    
    string getType() const override { return "소설"; }
};

// 도서관 이용자 클래스
class Member {
private:
    string name;
    int memberId;
    vector<int> borrowedBooks;
    static int nextMemberId;
    
public:
    Member(string n) : name(n), memberId(nextMemberId++) {}
    
    void borrowBook(int bookId) {
        borrowedBooks.push_back(bookId);
    }
    
    bool returnBook(int bookId) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            return true;
        }
        return false;
    }
    
    void displayInfo() const {
        cout << "회원 ID: " << memberId << ", 이름: " << name 
             << ", 대출 도서 수: " << borrowedBooks.size() << endl;
        if (!borrowedBooks.empty()) {
            cout << "    대출 중인 도서 ID: ";
            for (int id : borrowedBooks) {
                cout << id << " ";
            }
            cout << endl;
        }
    }
    
    int getMemberId() const { return memberId; }
    string getName() const { return name; }
    size_t getBorrowedCount() const { return borrowedBooks.size(); }
};

int Member::nextMemberId = 2001;

// 도서관 관리 시스템
class Library {
private:
    vector<unique_ptr<Book>> books;
    vector<unique_ptr<Member>> members;
    
public:
    void addBook(unique_ptr<Book> book) {
        books.push_back(move(book));
        cout << "도서가 추가되었습니다." << endl;
    }
    
    void addMember(unique_ptr<Member> member) {
        members.push_back(move(member));
        cout << "회원이 등록되었습니다." << endl;
    }
    
    void displayAllBooks() const {
        cout << "\n=== 전체 도서 목록 ===" << endl;
        for (const auto& book : books) {
            book->displayInfo();
        }
    }
    
    void displayAllMembers() const {
        cout << "\n=== 전체 회원 목록 ===" << endl;
        for (const auto& member : members) {
            member->displayInfo();
        }
    }
    
    bool borrowBook(int memberId, int bookId) {
        auto member = findMember(memberId);
        auto book = findBook(bookId);
        
        if (!member || !book) {
            cout << "회원 또는 도서를 찾을 수 없습니다." << endl;
            return false;
        }
        
        if (!book->getAvailability()) {
            cout << "도서가 이미 대출 중입니다." << endl;
            return false;
        }
        
        if (member->getBorrowedCount() >= 3) {
            cout << "대출 한도를 초과했습니다. (최대 3권)" << endl;
            return false;
        }
        
        book->setAvailability(false);
        member->borrowBook(bookId);
        cout << member->getName() << "님이 \"" << book->getTitle() << "\"을(를) 대출했습니다." << endl;
        return true;
    }
    
    bool returnBook(int memberId, int bookId) {
        auto member = findMember(memberId);
        auto book = findBook(bookId);
        
        if (!member || !book) {
            cout << "회원 또는 도서를 찾을 수 없습니다." << endl;
            return false;
        }
        
        if (member->returnBook(bookId)) {
            book->setAvailability(true);
            cout << member->getName() << "님이 \"" << book->getTitle() << "\"을(를) 반납했습니다." << endl;
            return true;
        } else {
            cout << "해당 회원이 대출한 도서가 아닙니다." << endl;
            return false;
        }
    }
    
private:
    Member* findMember(int memberId) {
        for (const auto& member : members) {
            if (member->getMemberId() == memberId) {
                return member.get();
            }
        }
        return nullptr;
    }
    
    Book* findBook(int bookId) {
        for (const auto& book : books) {
            if (book->getId() == bookId) {
                return book.get();
            }
        }
        return nullptr;
    }
};

int main() {
    cout << "=== 도서관 관리 시스템 ===" << endl;
    
    Library library;
    
    // 도서 추가
    library.addBook(make_unique<Novel>("해리 포터", "J.K. 롤링", "978-1-1111", "판타지"));
    library.addBook(make_unique<TechnicalBook>("C++ 프로그래밍", "김개발", "978-2-2222", "컴퓨터과학"));
    library.addBook(make_unique<Novel>("1984", "조지 오웰", "978-3-3333", "디스토피아"));
    library.addBook(make_unique<TechnicalBook>("데이터구조", "이알고", "978-4-4444", "컴퓨터과학"));
    
    // 회원 등록
    library.addMember(make_unique<Member>("김독서"));
    library.addMember(make_unique<Member>("이학습"));
    
    // 전체 목록 확인
    library.displayAllBooks();
    library.displayAllMembers();
    
    // 대출/반납 테스트
    cout << "\n=== 대출/반납 테스트 ===" << endl;
    library.borrowBook(2001, 1001);  // 김독서가 해리포터 대출
    library.borrowBook(2002, 1002);  // 이학습이 C++ 프로그래밍 대출
    library.borrowBook(2001, 1002);  // 김독서가 이미 대출된 책 대출 시도
    
    cout << "\n=== 대출 후 상태 ===" << endl;
    library.displayAllBooks();
    library.displayAllMembers();
    
    library.returnBook(2001, 1001);  // 김독서가 해리포터 반납
    
    cout << "\n=== 반납 후 상태 ===" << endl;
    library.displayAllBooks();
    library.displayAllMembers();
    
    return 0;
}
```

---

## 이번 챕터 요약

### 학습한 내용
**기본 개념**: 구조체, 클래스, 접근 제어자
**생성자/소멸자**: 객체 생성과 소멸 관리
**멤버 함수**: 정적 멤버, const 멤버, this 포인터
**복사 의미론**: 복사 생성자, 이동 생성자
**고급 기능**: 연산자 오버로딩, 프렌드 함수
**상속과 다형성**: 가상 함수, 다형성 활용

### 핵심 키워드
- 클래스: `class`, `public`, `private`, `protected`
- 생성자/소멸자: 생성자, `~클래스명`, 초기화 리스트
- 특수 함수: 복사 생성자, 이동 생성자, `operator=`
- 상속: 상속 지정자, `virtual`, `override`, 다형성

### 객체지향 원칙
1. 캡슐화: 데이터와 함수를 하나로 묶기
2. 상속: 기존 클래스를 확장하여 재사용
3. 다형성: 하나의 인터페이스로 다양한 타입 처리
4. 추상화: 복잡한 구현을 숨기고 인터페이스 제공

---

## 실습 과제

### 과제 1: 은행 계좌 클래스
예금, 출금, 이체 기능을 가진 은행 계좌 클래스를 생성자, 소멸자와 함께 구현하세요.

### 과제 2: 도형 클래스 계층
Shape 기본 클래스를 상속받는 다양한 도형 클래스들을 가상 함수와 함께 구현하세요.

### 과제 3: 학생 관리 시스템
Student 클래스와 이를 관리하는 시스템을 다형성을 활용하여 구현하세요.

### 과제 4: 게임 캐릭터 시스템
Character 기본 클래스를 상속받는 다양한 직업의 캐릭터를 구현하고 전투 시스템을 만드세요.

---

## 다음 챕터 예고
**Chapter 05: 클래스와 객체지향 II**에서는 더 고급 객체지향 기법들인 추상 클래스, 인터페이스, 다중 상속, 그리고 현대 C++의 고급 기능들을 학습합니다.
