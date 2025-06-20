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
생성자의 기본 개념과 초기화 방법을 학습합니다.

```cpp
/*
주제: 생성자 기초 (Constructor Basics)
정의: 객체가 생성될 때 자동으로 호출되어 객체를 초기화하는 특별한 멤버 함수
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    
public:
    // 기본 생성자
    Student() : name("Unknown"), age(0) {
        cout << "기본 생성자: " << name << endl;
    }
    
    // 매개변수 생성자
    Student(string n, int a) : name(n), age(a) {
        cout << "매개변수 생성자: " << name << endl;
    }
    
    void display() {
        cout << name << " (" << age << "세)" << endl;
    }
};

int main() {
    Student s1;                    // 기본 생성자
    Student s2("김철수", 20);       // 매개변수 생성자
    
    s1.display();
    s2.display();
    
    return 0;
}
```

---

## 5. 예제 05: 소멸자 기초 (05_destructor_basic.cpp)

### 예제 정의
소멸자를 통한 자원 해제의 중요성을 학습합니다.

```cpp
/*
주제: 소멸자 기초 (Destructor Basics)
정의: 객체가 소멸될 때 자동으로 호출되어 정리 작업을 수행하는 함수
*/

#include <iostream>
using namespace std;

class Resource {
private:
    int* data;
    
public:
    Resource(int size) {
        data = new int[size];
        cout << "메모리 할당: " << data << endl;
    }
    
    ~Resource() {
        delete[] data;
        cout << "메모리 해제: " << data << endl;
    }
    
    void setValue(int value) {
        data[0] = value;
    }
};

int main() {
    {
        Resource r(10);
        r.setValue(42);
    } // 여기서 자동으로 소멸자 호출
    
    cout << "메인 계속 실행" << endl;
    return 0;
}
```

---

## 6. 예제 06: 생성자 오버로딩 (06_constructor_overloading.cpp)

### 예제 정의
다양한 형태의 생성자를 정의하여 유연한 객체 초기화를 제공합니다.

```cpp
/*
주제: 생성자 오버로딩 (Constructor Overloading)
정의: 서로 다른 매개변수를 가진 여러 개의 생성자를 정의
*/

#include <iostream>
using namespace std;

class Circle {
private:
    double radius;
    
public:
    Circle() : radius(1.0) {}                    // 기본 생성자
    Circle(double r) : radius(r) {}              // 반지름 지정
    Circle(const Circle& other) : radius(other.radius) {}  // 복사 생성자
    
    double getArea() {
        return 3.14159 * radius * radius;
    }
    
    void display() {
        cout << "반지름: " << radius << ", 넓이: " << getArea() << endl;
    }
};

int main() {
    Circle c1;          // 기본 생성자
    Circle c2(5.0);     // 매개변수 생성자
    Circle c3(c2);      // 복사 생성자
    
    c1.display();
    c2.display();
    c3.display();
    
    return 0;
}
```

---

## 7. 예제 07: 복사 생성자 (07_copy_constructor.cpp)

### 예제 정의
복사 생성자의 필요성과 깊은 복사를 학습합니다.

```cpp
/*
주제: 복사 생성자 (Copy Constructor)
정의: 같은 클래스의 객체로부터 새로운 객체를 복사 생성
*/

#include <iostream>
using namespace std;

class Array {
private:
    int* data;
    int size;
    
public:
    Array(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = i + 1;
        }
    }
    
    // 복사 생성자 (깊은 복사)
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "복사 생성자 호출" << endl;
    }
    
    ~Array() {
        delete[] data;
    }
    
    void display() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array arr1(3);
    Array arr2 = arr1;  // 복사 생성자 호출
    
    arr1.display();
    arr2.display();
    
    return 0;
}
```

---

## 8. 예제 08: 이동 생성자 (08_move_constructor.cpp)

### 예제 정의
이동 생성자를 통한 효율적인 자원 이동을 학습합니다.

```cpp
/*
주제: 이동 생성자 (Move Constructor)
정의: 임시 객체로부터 자원을 효율적으로 이동하는 생성자
*/

#include <iostream>
#include <utility>
using namespace std;

class StringHolder {
private:
    char* str;
    
public:
    StringHolder(const char* s) {
        int len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        cout << "생성: " << str << endl;
    }
    
    // 이동 생성자
    StringHolder(StringHolder&& other) noexcept : str(other.str) {
        other.str = nullptr;
        cout << "이동 생성" << endl;
    }
    
    ~StringHolder() {
        if (str) {
            cout << "소멸: " << str << endl;
            delete[] str;
        }
    }
    
    void display() {
        cout << (str ? str : "비어있음") << endl;
    }
};

int main() {
    StringHolder s1("Hello");
    StringHolder s2 = move(s1);  // 이동 생성자
    
    s1.display();  // 비어있음
    s2.display();  // Hello
    
    return 0;
}
```

---

## 9. 예제 09: 연산자 오버로딩 기초 (09_operator_overloading_basic.cpp)

### 예제 정의
기본적인 연산자 오버로딩으로 직관적인 클래스 사용법을 제공합니다.

```cpp
/*
주제: 연산자 오버로딩 기초 (Basic Operator Overloading)
정의: 사용자 정의 클래스에 대해 연산자의 동작을 정의
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
    
    // == 연산자 오버로딩
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    // << 연산자 오버로딩 (friend)
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p1(3, 4);
    Point p2(1, 2);
    
    Point p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;
    cout << "p1 == p2? " << (p1 == p2) << endl;
    
    return 0;
}
```

---

## 10. 예제 10: this 포인터 (10_this_pointer.cpp)

### 예제 정의
this 포인터의 개념과 메서드 체이닝 패턴을 학습합니다.

```cpp
/*
주제: this 포인터 (this Pointer)
정의: 현재 객체를 가리키는 포인터
*/

#include <iostream>
using namespace std;

class Calculator {
private:
    int value;
    
public:
    Calculator(int v = 0) : value(v) {}
    
    // this를 사용한 메서드 체이닝
    Calculator& add(int n) {
        this->value += n;
        return *this;
    }
    
    Calculator& multiply(int n) {
        this->value *= n;
        return *this;
    }
    
    // this를 사용한 자기 자신과의 비교
    bool isEqual(const Calculator& other) {
        return this->value == other.value;
    }
    
    void display() {
        cout << "값: " << value << endl;
    }
};

int main() {
    Calculator calc(5);
    
    // 메서드 체이닝
    calc.add(3).multiply(2);
    calc.display();  // 16
    
    Calculator calc2(16);
    cout << "같은가? " << calc.isEqual(calc2) << endl;
    
    return 0;
}
```

