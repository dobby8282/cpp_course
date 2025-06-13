# Chapter 06: 상속과 다형성

## 학습 목표
- 상속의 개념과 접근 지정자의 역할 이해
- 생성자와 소멸자의 상속 메커니즘 습득
- 가상 함수와 함수 오버라이딩의 활용법 학습
- 순수 가상 함수와 추상 클래스 설계 방법 이해
- 다형성을 활용한 유연한 프로그램 설계 기법 습득
- 가상 소멸자의 중요성과 사용법 학습
- 다중 상속의 개념과 주의사항 이해
- 객체 포인터를 통한 다형성 구현 방법 습득

---

## 1. 예제 01: 상속 기초 (01_inheritance_basic.cpp)

### 예제 정의
기본적인 상속 개념과 구문을 학습합니다.

```cpp
/*
주제: 상속 (Inheritance)
정의: 기존 클래스(부모 클래스)의 속성과 메서드를 새로운 클래스(자식 클래스)가 물려받아 재사용하고 확장하는 객체지향의 핵심 개념

핵심 개념: 부모 클래스, 자식 클래스, 상속 관계, 코드 재사용
정의:
- 부모 클래스(기본 클래스): 상속을 제공하는 클래스
- 자식 클래스(파생 클래스): 상속을 받는 클래스
- 상속 관계: "is-a" 관계를 나타내는 클래스 간의 계층 구조
- 코드 재사용: 기존 코드를 재작성하지 않고 활용하는 프로그래밍 기법
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
        cout << "Animal 생성자: " << name << endl;
    }
    
    void eat() {
        cout << name << "가 먹이를 먹습니다." << endl;
    }
    
    void sleep() {
        cout << name << "가 잠을 잡니다." << endl;
    }
    
    void displayInfo() {
        cout << "이름: " << name << ", 나이: " << age << "세" << endl;
    }
    
    string getName() const { return name; }
    int getAge() const { return age; }
};

// 자식 클래스 1
class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "Dog 생성자: " << name << " (" << breed << ")" << endl;
    }
    
    // 자식 클래스만의 고유 메서드
    void bark() {
        cout << name << "가 멍멍 짖습니다." << endl;
    }
    
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
        cout << "Cat 생성자: " << name << endl;
    }
    
    void meow() {
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
    
    cout << "\n=== 부모 클래스로부터 상속받은 기능 ===" << endl;
    dog.displayInfo();
    dog.eat();
    dog.sleep();
    
    cat.displayInfo();
    cat.eat();
    cat.sleep();
    
    cout << "\n=== 자식 클래스만의 고유 기능 ===" << endl;
    dog.bark();
    dog.fetch();
    dog.displayBreed();
    
    cat.meow();
    cat.climb();
    
    return 0;
}
```

---

## 2. 예제 02: 접근 지정자 (02_access_specifiers.cpp)

### 예제 정의
상속 시 접근 지정자(public, protected, private)의 역할을 학습합니다.

```cpp
/*
주제: 상속 접근 지정자 (Inheritance Access Specifiers)
정의: 상속 관계에서 부모 클래스의 멤버들이 자식 클래스에서 어떻게 접근될 수 있는지를 결정하는 지정자

핵심 개념: public 상속, protected 상속, private 상속, 접근 권한 변화
정의:
- public 상속: 부모의 public은 public으로, protected는 protected로 유지
- protected 상속: 부모의 public과 protected가 모두 protected가 됨
- private 상속: 부모의 public과 protected가 모두 private가 됨
- 접근 권한 변화: 상속 방식에 따른 멤버 접근 권한의 변화
*/

#include <iostream>
#include <string>
using namespace std;

class Base {
public:
    int publicVar;
    
    Base() : publicVar(1), protectedVar(2), privateVar(3) {
        cout << "Base 생성자 호출" << endl;
    }
    
    void publicMethod() {
        cout << "Base::publicMethod() 호출" << endl;
    }
    
protected:
    int protectedVar;
    
    void protectedMethod() {
        cout << "Base::protectedMethod() 호출" << endl;
    }
    
private:
    int privateVar;
    
    void privateMethod() {
        cout << "Base::privateMethod() 호출" << endl;
    }
};

// public 상속
class PublicDerived : public Base {
public:
    void testAccess() {
        cout << "\n=== PublicDerived에서 접근 테스트 ===" << endl;
        
        publicVar = 10;           // OK: public 멤버
        protectedVar = 20;        // OK: protected 멤버
        // privateVar = 30;       // 오류: private 멤버 접근 불가
        
        publicMethod();           // OK: public 메서드
        protectedMethod();        // OK: protected 메서드
        // privateMethod();       // 오류: private 메서드 접근 불가
    }
};

// protected 상속
class ProtectedDerived : protected Base {
public:
    void testAccess() {
        cout << "\n=== ProtectedDerived에서 접근 테스트 ===" << endl;
        
        publicVar = 10;           // OK: public→protected로 변경됨
        protectedVar = 20;        // OK: protected 유지
        // privateVar = 30;       // 오류: private 멤버 접근 불가
        
        publicMethod();           // OK: public→protected로 변경됨
        protectedMethod();        // OK: protected 유지
    }
};

// private 상속
class PrivateDerived : private Base {
public:
    void testAccess() {
        cout << "\n=== PrivateDerived에서 접근 테스트 ===" << endl;
        
        publicVar = 10;           // OK: public→private로 변경됨
        protectedVar = 20;        // OK: protected→private로 변경됨
        // privateVar = 30;       // 오류: private 멤버 접근 불가
        
        publicMethod();           // OK: public→private로 변경됨
        protectedMethod();        // OK: protected→private로 변경됨
    }
};

int main() {
    cout << "=== 상속 접근 지정자 테스트 ===" << endl;
    
    PublicDerived pubDerived;
    ProtectedDerived protDerived;
    PrivateDerived privDerived;
    
    // 외부에서 접근 테스트
    cout << "\n=== 외부에서 접근 테스트 ===" << endl;
    
    // PublicDerived: public 상속이므로 Base의 public 멤버에 접근 가능
    pubDerived.publicVar = 100;   // OK
    pubDerived.publicMethod();    // OK
    
    // ProtectedDerived: protected 상속이므로 외부에서 접근 불가
    // protDerived.publicVar = 100;   // 오류: protected가 됨
    // protDerived.publicMethod();    // 오류: protected가 됨
    
    // PrivateDerived: private 상속이므로 외부에서 접근 불가
    // privDerived.publicVar = 100;   // 오류: private가 됨
    // privDerived.publicMethod();    // 오류: private가 됨
    
    // 각 클래스의 내부 접근 테스트
    pubDerived.testAccess();
    protDerived.testAccess();
    privDerived.testAccess();
    
    cout << "\n=== 접근 지정자 요약 ===" << endl;
    cout << "public 상속: Base의 public/protected 유지" << endl;
    cout << "protected 상속: Base의 public→protected, protected 유지" << endl;
    cout << "private 상속: Base의 public/protected→private" << endl;
    
    return 0;
}
```

---

## 3. 예제 03: 생성자와 소멸자 상속 (03_constructor_inheritance.cpp)

### 예제 정의
상속 관계에서 생성자와 소멸자의 호출 순서를 학습합니다.

```cpp
/*
주제: 상속에서의 생성자와 소멸자 (Constructor and Destructor in Inheritance)
정의: 상속 관계에서 객체 생성 시 부모와 자식의 생성자/소멸자가 호출되는 순서와 방법

핵심 개념: 생성자 호출 순서, 소멸자 호출 순서, 초기화 리스트, 가상 소멸자
정의:
- 생성자 호출 순서: 부모 클래스 생성자 → 자식 클래스 생성자
- 소멸자 호출 순서: 자식 클래스 소멸자 → 부모 클래스 소멸자
- 초기화 리스트: 자식 클래스에서 부모 클래스 생성자를 호출하는 방법
- 가상 소멸자: 다형성에서 올바른 소멸자 호출을 보장하는 메커니즘
*/

#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string brand;
    int year;
    
public:
    Vehicle() {
        cout << "Vehicle 기본 생성자" << endl;
        brand = "Unknown";
        year = 0;
    }
    
    Vehicle(string b, int y) : brand(b), year(y) {
        cout << "Vehicle 매개변수 생성자: " << brand << ", " << year << endl;
    }
    
    virtual ~Vehicle() {  // 가상 소멸자
        cout << "Vehicle 소멸자: " << brand << endl;
    }
    
    void startEngine() {
        cout << brand << " 엔진을 시동합니다." << endl;
    }
    
    virtual void displayInfo() {
        cout << "브랜드: " << brand << ", 연식: " << year << endl;
    }
};

class Car : public Vehicle {
private:
    int doors;
    string fuelType;
    
public:
    // 기본 생성자
    Car() : Vehicle(), doors(4), fuelType("Gasoline") {
        cout << "Car 기본 생성자" << endl;
    }
    
    // 매개변수 생성자
    Car(string b, int y, int d, string f) : Vehicle(b, y), doors(d), fuelType(f) {
        cout << "Car 매개변수 생성자: " << doors << "도어, " << fuelType << endl;
    }
    
    // 복사 생성자
    Car(const Car& other) : Vehicle(other.brand, other.year), doors(other.doors), fuelType(other.fuelType) {
        cout << "Car 복사 생성자" << endl;
    }
    
    ~Car() {
        cout << "Car 소멸자: " << brand << endl;
    }
    
    void displayInfo() override {
        Vehicle::displayInfo();  // 부모 클래스 메서드 호출
        cout << "도어 수: " << doors << ", 연료: " << fuelType << endl;
    }
    
    void openTrunk() {
        cout << brand << "의 트렁크를 엽니다." << endl;
    }
};

class SportsCar : public Car {
private:
    int topSpeed;
    bool hasTurbo;
    
public:
    SportsCar() : Car(), topSpeed(200), hasTurbo(false) {
        cout << "SportsCar 기본 생성자" << endl;
    }
    
    SportsCar(string b, int y, int d, string f, int speed, bool turbo) 
        : Car(b, y, d, f), topSpeed(speed), hasTurbo(turbo) {
        cout << "SportsCar 매개변수 생성자: " << speed << "km/h, 터보: " << turbo << endl;
    }
    
    ~SportsCar() {
        cout << "SportsCar 소멸자: " << brand << endl;
    }
    
    void displayInfo() override {
        Car::displayInfo();  // 부모 클래스 메서드 호출
        cout << "최고속도: " << topSpeed << "km/h, 터보: " << (hasTurbo ? "있음" : "없음") << endl;
    }
    
    void activateTurbo() {
        if (hasTurbo) {
            cout << brand << "의 터보를 가동합니다!" << endl;
        } else {
            cout << brand << "에는 터보가 없습니다." << endl;
        }
    }
};

void demonstrateLifetime() {
    cout << "\n=== 객체 생명주기 데모 ===" << endl;
    cout << "SportsCar 객체 생성 시작:" << endl;
    
    SportsCar ferrari("Ferrari", 2023, 2, "Gasoline", 320, true);
    
    cout << "\n객체 정보:" << endl;
    ferrari.displayInfo();
    ferrari.startEngine();
    ferrari.activateTurbo();
    
    cout << "\n스코프 종료 - 소멸자 호출 순서:" << endl;
    // 스코프 종료시 소멸자 호출: SportsCar → Car → Vehicle 순서
}

int main() {
    cout << "=== 생성자와 소멸자 상속 ===" << endl;
    
    cout << "1. 기본 생성자 테스트:" << endl;
    Car basicCar;
    cout << endl;
    
    cout << "2. 매개변수 생성자 테스트:" << endl;
    Car bmw("BMW", 2022, 4, "Gasoline");
    cout << endl;
    
    cout << "3. 복사 생성자 테스트:" << endl;
    Car bmwCopy = bmw;
    cout << endl;
    
    cout << "4. 다단계 상속 테스트:" << endl;
    demonstrateLifetime();
    
    cout << "\n5. 포인터를 통한 다형성 테스트:" << endl;
    Vehicle* vehiclePtr = new Car("Toyota", 2021, 4, "Hybrid");
    vehiclePtr->displayInfo();
    delete vehiclePtr;  // 가상 소멸자로 인해 올바른 소멸자 호출
    
    cout << "\n=== 생성자/소멸자 호출 규칙 ===" << endl;
    cout << "생성자: 부모 → 자식 순서" << endl;
    cout << "소멸자: 자식 → 부모 순서" << endl;
    cout << "초기화 리스트로 부모 생성자 호출" << endl;
    cout << "가상 소멸자로 다형성에서 안전한 소멸 보장" << endl;
    
    return 0;
}
```

---

## 4. 예제 04: 가상 함수 (04_virtual_function.cpp)

### 예제 정의
가상 함수의 개념과 동적 바인딩을 학습합니다.

```cpp
/*
주제: 가상 함수 (Virtual Functions)
정의: 런타임에 객체의 실제 타입에 따라 호출될 함수가 결정되는 함수로, 다형성의 핵심 메커니즘

핵심 개념: virtual 키워드, 동적 바인딩, 가상 함수 테이블, 정적 바인딩
정의:
- virtual 키워드: 함수를 가상 함수로 선언하는 키워드
- 동적 바인딩: 런타임에 실제 객체 타입에 따라 함수 호출이 결정되는 방식
- 가상 함수 테이블(vtable): 가상 함수들의 주소를 저장하는 테이블
- 정적 바인딩: 컴파일 타임에 함수 호출이 결정되는 방식
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
        cout << "Shape 생성: " << name << endl;
    }
    
    virtual ~Shape() {
        cout << "Shape 소멸: " << name << endl;
    }
    
    // 가상 함수들
    virtual double getArea() const {
        cout << "Shape::getArea() 호출 (기본 구현)" << endl;
        return 0.0;
    }
    
    virtual double getPerimeter() const {
        cout << "Shape::getPerimeter() 호출 (기본 구현)" << endl;
        return 0.0;
    }
    
    virtual void draw() const {
        cout << "Shape::draw() - 기본 도형 그리기" << endl;
    }
    
    // 비가상 함수
    void displayName() const {
        cout << "도형 이름: " << name << endl;
    }
    
    string getName() const { return name; }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("사각형"), width(w), height(h) {
        cout << "Rectangle 생성: " << width << " x " << height << endl;
    }
    
    ~Rectangle() {
        cout << "Rectangle 소멸" << endl;
    }
    
    // 가상 함수 오버라이딩
    double getArea() const override {
        cout << "Rectangle::getArea() 호출" << endl;
        return width * height;
    }
    
    double getPerimeter() const override {
        cout << "Rectangle::getPerimeter() 호출" << endl;
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "Rectangle::draw() - 사각형 그리기 (" << width << " x " << height << ")" << endl;
    }
    
    // Rectangle만의 고유 함수
    void setDimensions(double w, double h) {
        width = w;
        height = h;
    }
};

class Circle : public Shape {
private:
    double radius;
    static constexpr double PI = 3.14159;
    
public:
    Circle(double r) : Shape("원"), radius(r) {
        cout << "Circle 생성: 반지름 " << radius << endl;
    }
    
    ~Circle() {
        cout << "Circle 소멸" << endl;
    }
    
    double getArea() const override {
        cout << "Circle::getArea() 호출" << endl;
        return PI * radius * radius;
    }
    
    double getPerimeter() const override {
        cout << "Circle::getPerimeter() 호출" << endl;
        return 2 * PI * radius;
    }
    
    void draw() const override {
        cout << "Circle::draw() - 원 그리기 (반지름: " << radius << ")" << endl;
    }
    
    double getRadius() const { return radius; }
};

class Triangle : public Shape {
private:
    double base, height, side1, side2;
    
public:
    Triangle(double b, double h, double s1, double s2) 
        : Shape("삼각형"), base(b), height(h), side1(s1), side2(s2) {
        cout << "Triangle 생성: 밑변 " << base << ", 높이 " << height << endl;
    }
    
    ~Triangle() {
        cout << "Triangle 소멸" << endl;
    }
    
    double getArea() const override {
        cout << "Triangle::getArea() 호출" << endl;
        return 0.5 * base * height;
    }
    
    double getPerimeter() const override {
        cout << "Triangle::getPerimeter() 호출" << endl;
        return base + side1 + side2;
    }
    
    void draw() const override {
        cout << "Triangle::draw() - 삼각형 그리기 (밑변: " << base << ", 높이: " << height << ")" << endl;
    }
};

// 가상 함수와 비가상 함수 비교를 위한 클래스
class BaseDemo {
public:
    virtual void virtualFunc() {
        cout << "BaseDemo::virtualFunc() - 가상 함수" << endl;
    }
    
    void nonVirtualFunc() {
        cout << "BaseDemo::nonVirtualFunc() - 비가상 함수" << endl;
    }
};

class DerivedDemo : public BaseDemo {
public:
    void virtualFunc() override {
        cout << "DerivedDemo::virtualFunc() - 오버라이딩된 가상 함수" << endl;
    }
    
    void nonVirtualFunc() {  // 숨김 (hiding), 오버라이딩 아님
        cout << "DerivedDemo::nonVirtualFunc() - 숨겨진 함수" << endl;
    }
};

void demonstratePolymorphism() {
    cout << "\n=== 다형성 데모 ===" << endl;
    
    // 포인터 배열을 통한 다형성
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Rectangle>(5, 3));
    shapes.push_back(make_unique<Circle>(4));
    shapes.push_back(make_unique<Triangle>(6, 4, 5, 7));
    
    for (const auto& shape : shapes) {
        cout << "\n--- " << shape->getName() << " 처리 ---" << endl;
        shape->displayName();        // 비가상 함수
        shape->draw();              // 가상 함수 - 실제 타입에 따라 호출
        cout << "넓이: " << shape->getArea() << endl;
        cout << "둘레: " << shape->getPerimeter() << endl;
    }
}

void demonstrateVirtualVsNonVirtual() {
    cout << "\n=== 가상 함수 vs 비가상 함수 ===" << endl;
    
    DerivedDemo derived;
    BaseDemo* basePtr = &derived;
    
    cout << "포인터를 통한 호출:" << endl;
    basePtr->virtualFunc();     // DerivedDemo 버전 호출 (가상 함수)
    basePtr->nonVirtualFunc();  // BaseDemo 버전 호출 (비가상 함수)
    
    cout << "\n직접 호출:" << endl;
    derived.virtualFunc();      // DerivedDemo 버전 호출
    derived.nonVirtualFunc();   // DerivedDemo 버전 호출
}

int main() {
    cout << "=== 가상 함수 ===" << endl;
    
    // 1. 개별 객체 테스트
    cout << "1. 개별 객체 생성 및 호출:" << endl;
    Rectangle rect(10, 5);
    Circle circle(3);
    
    cout << "\n직접 호출:" << endl;
    rect.draw();
    circle.draw();
    
    cout << "\n포인터를 통한 호출:" << endl;
    Shape* shapePtr;
    
    shapePtr = &rect;
    shapePtr->draw();  // Rectangle::draw() 호출 (동적 바인딩)
    
    shapePtr = &circle;
    shapePtr->draw();  // Circle::draw() 호출 (동적 바인딩)
    
    // 2. 다형성 데모
    demonstratePolymorphism();
    
    // 3. 가상 함수 vs 비가상 함수
    demonstrateVirtualVsNonVirtual();
    
    cout << "\n=== 가상 함수 핵심 개념 ===" << endl;
    cout << "1. virtual 키워드로 가상 함수 선언" << endl;
    cout << "2. 자식 클래스에서 override로 재정의" << endl;
    cout << "3. 런타임에 실제 객체 타입에 따라 함수 결정" << endl;
    cout << "4. 포인터/참조를 통해 다형성 구현" << endl;
    cout << "5. 가상 소멸자로 안전한 메모리 관리" << endl;
    
    return 0;
}
```

---

## 5. 예제 05: 함수 오버라이딩 (05_function_overriding.cpp)

### 예제 정의
함수 오버라이딩과 override 키워드의 사용법을 학습합니다.

```cpp
/*
주제: 함수 오버라이딩 (Function Overriding)
정의: 자식 클래스에서 부모 클래스의 가상 함수를 재정의하여 다른 동작을 구현하는 기법

핵심 개념: override 키워드, 함수 시그니처, 가상 함수 재정의, 공변 반환 타입
정의:
- override 키워드: 함수가 부모 클래스의 가상 함수를 재정의함을 명시하는 C++11 키워드
- 함수 시그니처: 함수명, 매개변수 타입, const 여부 등 함수를 구분하는 요소
- 가상 함수 재정의: 부모의 가상 함수와 동일한 시그니처로 새로운 구현 제공
- 공변 반환 타입: 오버라이딩 시 반환 타입을 더 구체적인 타입으로 변경하는 것
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Employee {
protected:
    string name;
    int id;
    double baseSalary;
    
public:
    Employee(string n, int i, double salary) : name(n), id(i), baseSalary(salary) {
        cout << "Employee 생성: " << name << endl;
    }
    
    virtual ~Employee() {
        cout << "Employee 소멸: " << name << endl;
    }
    
    // 가상 함수들 (자식 클래스에서 오버라이딩 예정)
    virtual double calculateSalary() const {
        cout << "Employee::calculateSalary() 호출" << endl;
        return baseSalary;
    }
    
    virtual void displayInfo() const {
        cout << "Employee::displayInfo() - " << name << " (ID: " << id << ")" << endl;
    }
    
    virtual string getJobTitle() const {
        return "일반 직원";
    }
    
    virtual void work() const {
        cout << name << "가 일반적인 업무를 수행합니다." << endl;
    }
    
    // 비가상 함수
    void basicInfo() const {
        cout << "이름: " << name << ", ID: " << id << endl;
    }
    
    // 공변 반환 타입을 위한 가상 함수
    virtual Employee* clone() const {
        cout << "Employee::clone() 호출" << endl;
        return new Employee(name, id, baseSalary);
    }
    
    string getName() const { return name; }
    int getId() const { return id; }
};

class Manager : public Employee {
private:
    double bonus;
    int teamSize;
    
public:
    Manager(string n, int i, double salary, double b, int team) 
        : Employee(n, i, salary), bonus(b), teamSize(team) {
        cout << "Manager 생성: " << name << endl;
    }
    
    ~Manager() {
        cout << "Manager 소멸: " << name << endl;
    }
    
    // 올바른 오버라이딩 (override 키워드 사용)
    double calculateSalary() const override {
        cout << "Manager::calculateSalary() 호출" << endl;
        return baseSalary + bonus;
    }
    
    void displayInfo() const override {
        cout << "Manager::displayInfo() - " << name << " (ID: " << id 
             << ", 팀원: " << teamSize << "명)" << endl;
    }
    
    string getJobTitle() const override {
        return "매니저";
    }
    
    void work() const override {
        cout << name << "가 팀을 관리하고 있습니다. (팀원 " << teamSize << "명)" << endl;
    }
    
    // 공변 반환 타입 (Employee* → Manager*)
    Manager* clone() const override {
        cout << "Manager::clone() 호출" << endl;
        return new Manager(name, id, baseSalary, bonus, teamSize);
    }
    
    // Manager만의 고유 함수
    void manageTeam() const {
        cout << name << "가 " << teamSize << "명의 팀원을 관리합니다." << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, int i, double salary, string lang, int projects) 
        : Employee(n, i, salary), programmingLanguage(lang), projectsCompleted(projects) {
        cout << "Developer 생성: " << name << endl;
    }
    
    ~Developer() {
        cout << "Developer 소멸: " << name << endl;
    }
    
    double calculateSalary() const override {
        cout << "Developer::calculateSalary() 호출" << endl;
        return baseSalary + (projectsCompleted * 50000);  // 프로젝트당 보너스
    }
    
    void displayInfo() const override {
        cout << "Developer::displayInfo() - " << name << " (ID: " << id 
             << ", 언어: " << programmingLanguage << ", 프로젝트: " << projectsCompleted << "개)" << endl;
    }
    
    string getJobTitle() const override {
        return "개발자";
    }
    
    void work() const override {
        cout << name << "가 " << programmingLanguage << "로 개발하고 있습니다." << endl;
    }
    
    Developer* clone() const override {
        cout << "Developer::clone() 호출" << endl;
        return new Developer(name, id, baseSalary, programmingLanguage, projectsCompleted);
    }
    
    void code() const {
        cout << name << "가 " << programmingLanguage << "로 코딩 중입니다." << endl;
    }
};

// 잘못된 오버라이딩 예제 (컴파일 오류 방지를 위해 주석)
class Intern : public Employee {
public:
    Intern(string n, int i) : Employee(n, i, 0) {}
    
    // 올바른 오버라이딩
    double calculateSalary() const override {
        cout << "Intern::calculateSalary() 호출" << endl;
        return 0;  // 인턴은 무급
    }
    
    string getJobTitle() const override {
        return "인턴";
    }
    
    void work() const override {
        cout << name << "가 열심히 배우고 있습니다." << endl;
    }
    
    // 잘못된 오버라이딩 시도들 (주석 처리)
    /*
    // 1. 매개변수가 다름 - 오버라이딩 아님, 오버로딩도 아님
    void displayInfo(int extra) const override {  // 오류!
        cout << "Intern displayInfo with extra" << endl;
    }
    
    // 2. const가 다름 - 오버라이딩 아님
    void work() override {  // 오류! 부모는 const, 자식은 non-const
        cout << "Intern work without const" << endl;
    }
    
    // 3. 반환 타입이 다름 (공변이 아닌 경우) - 오버라이딩 아님
    int getJobTitle() const override {  // 오류! string이 아닌 int 반환
        return 0;
    }
    */
};

void demonstrateOverriding() {
    cout << "\n=== 오버라이딩 데모 ===" << endl;
    
    vector<unique_ptr<Employee>> employees;
    employees.push_back(make_unique<Employee>("김기본", 1001, 3000000));
    employees.push_back(make_unique<Manager>("이매니저", 2001, 5000000, 1000000, 5));
    employees.push_back(make_unique<Developer>("박개발", 3001, 4000000, "C++", 3));
    employees.push_back(make_unique<Intern>("최인턴", 4001));
    
    for (const auto& employee : employees) {
        cout << "\n--- " << employee->getName() << " ---" << endl;
        cout << "직책: " << employee->getJobTitle() << endl;
        employee->displayInfo();
        employee->work();
        cout << "급여: " << employee->calculateSalary() << "원" << endl;
    }
}

void demonstrateCovarianceReturn() {
    cout << "\n=== 공변 반환 타입 데모 ===" << endl;
    
    Manager manager("김관리", 5001, 6000000, 1500000, 10);
    Developer developer("이코딩", 6001, 4500000, "Python", 5);
    
    // 공변 반환 타입: Employee* → Manager*, Developer*
    Employee* empClone = manager.clone();
    Manager* mgrlone = manager.clone();  // 더 구체적인 타입으로 반환
    Developer* devClone = developer.clone();
    
    cout << "복제된 객체들:" << endl;
    empClone->displayInfo();
    mgrlone->displayInfo();
    devClone->displayInfo();
    
    // 메모리 해제
    delete empClone;
    delete mgrlone;
    delete devClone;
}

int main() {
    cout << "=== 함수 오버라이딩 ===" << endl;
    
    // 1. 기본 오버라이딩 테스트
    cout << "1. 기본 오버라이딩:" << endl;
    Manager mgr("홍관리", 1001, 4000000, 800000, 8);
    Developer dev("김개발", 2001, 3500000, "Java", 4);
    
    Employee* empPtr;
    
    empPtr = &mgr;
    cout << "Manager 포인터로 호출:" << endl;
    empPtr->work();        // Manager::work() 호출
    empPtr->displayInfo(); // Manager::displayInfo() 호출
    
    empPtr = &dev;
    cout << "\nDeveloper 포인터로 호출:" << endl;
    empPtr->work();        // Developer::work() 호출
    empPtr->displayInfo(); // Developer::displayInfo() 호출
    
    // 2. 다형성을 통한 오버라이딩
    demonstrateOverriding();
    
    // 3. 공변 반환 타입
    demonstrateCovarianceReturn();
    
    cout << "\n=== 오버라이딩 규칙 요약 ===" << endl;
    cout << "1. 부모 클래스의 함수가 virtual이어야 함" << endl;
    cout << "2. 함수 시그니처가 정확히 일치해야 함" << endl;
    cout << "3. override 키워드로 의도를 명확히 표현" << endl;
    cout << "4. 공변 반환 타입은 허용됨" << endl;
    cout << "5. 접근 지정자는 같거나 더 관대할 수 있음" << endl;
    
    return 0;
}
```

---

## 6. 예제 06: 순수 가상 함수 (06_pure_virtual_function.cpp)

### 예제 정의
순수 가상 함수와 추상 클래스의 개념을 학습합니다.

```cpp
/*
주제: 순수 가상 함수 (Pure Virtual Functions)
정의: 구현부가 없고 자식 클래스에서 반드시 재정의해야 하는 가상 함수로, 추상 클래스를 만드는 핵심 요소

핵심 개념: = 0, 추상 클래스, 인터페이스, 강제 구현
정의:
- = 0: 순수 가상 함수를 선언하는 구문
- 추상 클래스: 하나 이상의 순수 가상 함수를 가진 클래스로 인스턴스 생성 불가
- 인터페이스: 모든 함수가 순수 가상 함수인 추상 클래스
- 강제 구현: 자식 클래스가 반드시 순수 가상 함수를 구현해야 하는 제약
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

// 추상 기본 클래스 (Abstract Base Class)
class Shape {
protected:
    string name;
    
public:
    Shape(string n) : name(n) {
        cout << "Shape 생성: " << name << endl;
    }
    
    virtual ~Shape() {
        cout << "Shape 소멸: " << name << endl;
    }
    
    // 순수 가상 함수들 (= 0으로 선언)
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void draw() const = 0;
    
    // 일반 가상 함수 (기본 구현 제공, 오버라이딩 선택적)
    virtual void displayInfo() const {
        cout << "도형: " << name << ", 넓이: " << getArea() 
             << ", 둘레: " << getPerimeter() << endl;
    }
    
    // 비가상 함수 (모든 자식이 공통으로 사용)
    string getName() const {
        return name;
    }
};

// 구체적인 파생 클래스 1
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("사각형"), width(w), height(h) {
        cout << "Rectangle 생성: " << width << " x " << height << endl;
    }
    
    ~Rectangle() {
        cout << "Rectangle 소멸" << endl;
    }
    
    // 순수 가상 함수들을 반드시 구현
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "□ 사각형 그리기 (" << width << " x " << height << ")" << endl;
    }
    
    // Rectangle만의 고유 메서드
    void resize(double w, double h) {
        width = w;
        height = h;
        cout << "사각형 크기 변경: " << width << " x " << height << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    static constexpr double PI = 3.14159;
    
public:
    Circle(double r) : Shape("원"), radius(r) {
        cout << "Circle 생성: 반지름 " << radius << endl;
    }
    
    ~Circle() {
        cout << "Circle 소멸" << endl;
    }
    
    double getArea() const override {
        return PI * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * PI * radius;
    }
    
    void draw() const override {
        cout << "○ 원 그리기 (반지름: " << radius << ")" << endl;
    }
    
    double getRadius() const { return radius; }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;
    
public:
    Triangle(double s1, double s2, double s3) 
        : Shape("삼각형"), side1(s1), side2(s2), side3(s3) {
        cout << "Triangle 생성: " << s1 << ", " << s2 << ", " << s3 << endl;
    }
    
    ~Triangle() {
        cout << "Triangle 소멸" << endl;
    }
    
    double getArea() const override {
        // 헤론의 공식 사용
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
    
    double getPerimeter() const override {
        return side1 + side2 + side3;
    }
    
    void draw() const override {
        cout << "△ 삼각형 그리기 (" << side1 << ", " << side2 << ", " << side3 << ")" << endl;
    }
};

// 미완성 구현 클래스 (순수 가상 함수를 모두 구현하지 않음)
class IncompleteShape : public Shape {
public:
    IncompleteShape() : Shape("미완성") {}
    
    // getArea()만 구현하고 getPerimeter()와 draw()는 구현하지 않음
    double getArea() const override {
        return 0.0;
    }
    
    // getPerimeter()와 draw()가 구현되지 않아서 여전히 추상 클래스
};

// 인터페이스 예제 (모든 함수가 순수 가상 함수)
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
    virtual void setColor(string color) = 0;
    virtual string getColor() const = 0;
};

class Movable {
public:
    virtual ~Movable() = default;
    virtual void move(double x, double y) = 0;
    virtual void getPosition(double& x, double& y) const = 0;
};

// 다중 인터페이스 구현
class DrawableCircle : public Shape, public Drawable, public Movable {
private:
    double radius;
    string color;
    double posX, posY;
    static constexpr double PI = 3.14159;
    
public:
    DrawableCircle(double r, string c = "black") 
        : Shape("그리기 가능한 원"), radius(r), color(c), posX(0), posY(0) {}
    
    // Shape의 순수 가상 함수 구현
    double getArea() const override {
        return PI * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * PI * radius;
    }
    
    void draw() const override {
        cout << "● " << color << " 원 그리기 (반지름: " << radius 
             << ", 위치: " << posX << ", " << posY << ")" << endl;
    }
    
    // Drawable 인터페이스 구현
    void setColor(string c) override {
        color = c;
    }
    
    string getColor() const override {
        return color;
    }
    
    // Movable 인터페이스 구현
    void move(double x, double y) override {
        posX = x;
        posY = y;
        cout << "원을 (" << x << ", " << y << ")로 이동" << endl;
    }
    
    void getPosition(double& x, double& y) const override {
        x = posX;
        y = posY;
    }
};

void demonstrateAbstractClass() {
    cout << "\n=== 추상 클래스 데모 ===" << endl;
    
    // Shape는 추상 클래스이므로 인스턴스 생성 불가
    // Shape shape("테스트");  // 컴파일 오류!
    
    // 구체적인 클래스들은 인스턴스 생성 가능
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Rectangle>(5, 3));
    shapes.push_back(make_unique<Circle>(4));
    shapes.push_back(make_unique<Triangle>(3, 4, 5));
    
    cout << "도형들 처리:" << endl;
    for (const auto& shape : shapes) {
        shape->draw();
        shape->displayInfo();
        cout << "---" << endl;
    }
}

void demonstrateInterface() {
    cout << "\n=== 인터페이스 데모 ===" << endl;
    
    DrawableCircle circle(3, "red");
    
    // Shape 인터페이스 사용
    Shape* shapePtr = &circle;
    shapePtr->draw();
    shapePtr->displayInfo();
    
    // Drawable 인터페이스 사용
    Drawable* drawablePtr = &circle;
    drawablePtr->setColor("blue");
    cout << "색상 변경: " << drawablePtr->getColor() << endl;
    drawablePtr->draw();
    
    // Movable 인터페이스 사용
    Movable* movablePtr = &circle;
    movablePtr->move(10, 20);
    
    double x, y;
    movablePtr->getPosition(x, y);
    cout << "현재 위치: (" << x << ", " << y << ")" << endl;
}

// 팩토리 패턴에서 추상 클래스 활용
class ShapeFactory {
public:
    enum ShapeType { RECTANGLE, CIRCLE, TRIANGLE };
    
    static unique_ptr<Shape> createShape(ShapeType type) {
        switch (type) {
            case RECTANGLE:
                return make_unique<Rectangle>(4, 6);
            case CIRCLE:
                return make_unique<Circle>(5);
            case TRIANGLE:
                return make_unique<Triangle>(3, 4, 5);
            default:
                return nullptr;
        }
    }
};

int main() {
    cout << "=== 순수 가상 함수와 추상 클래스 ===" << endl;
    
    // 1. 추상 클래스 데모
    demonstrateAbstractClass();
    
    // 2. 인터페이스 데모
    demonstrateInterface();
    
    // 3. 팩토리 패턴과 추상 클래스
    cout << "\n=== 팩토리 패턴 ===" << endl;
    auto rect = ShapeFactory::createShape(ShapeFactory::RECTANGLE);
    auto circle = ShapeFactory::createShape(ShapeFactory::CIRCLE);
    
    if (rect) {
        rect->draw();
        rect->displayInfo();
    }
    
    if (circle) {
        circle->draw();
        circle->displayInfo();
    }
    
    cout << "\n=== 순수 가상 함수 핵심 개념 ===" << endl;
    cout << "1. 순수 가상 함수: virtual 함수명() = 0;" << endl;
    cout << "2. 추상 클래스: 순수 가상 함수를 가진 클래스" << endl;
    cout << "3. 인스턴스 생성 불가: 추상 클래스는 객체 생성 불가" << endl;
    cout << "4. 강제 구현: 자식 클래스가 반드시 구현해야 함" << endl;
    cout << "5. 인터페이스: 모든 함수가 순수 가상 함수인 클래스" << endl;
    cout << "6. 다형성 기반: 포인터/참조를 통한 일관된 인터페이스 제공" << endl;
    
    return 0;
}
```

---

## 7. 예제 07: 추상 클래스 (07_abstract_class.cpp)

### 예제 정의
추상 클래스를 활용한 디자인 패턴을 학습합니다.

```cpp
/*
주제: 추상 클래스 활용 (Abstract Class Applications)
정의: 추상 클래스를 활용하여 공통 인터페이스를 정의하고 구체적인 구현을 강제하는 설계 기법

핵심 개념: 템플릿 메서드 패턴, 전략 패턴, 팩토리 메서드 패턴, 공통 인터페이스
정의:
- 템플릿 메서드 패턴: 알고리즘의 구조를 정의하고 세부 단계를 자식 클래스에서 구현
- 전략 패턴: 알고리즘을 캡슐화하여 런타임에 교체 가능하게 하는 패턴
- 팩토리 메서드 패턴: 객체 생성을 자식 클래스에 위임하는 패턴
- 공통 인터페이스: 서로 다른 구현체들이 동일한 방식으로 사용될 수 있게 하는 인터페이스
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
using namespace std;

// 템플릿 메서드 패턴 예제
class DataProcessor {
protected:
    string fileName;
    
public:
    DataProcessor(string file) : fileName(file) {}
    virtual ~DataProcessor() = default;
    
    // 템플릿 메서드 - 전체 알고리즘 구조 정의
    void processData() {
        cout << "\n=== 데이터 처리 시작 ===" << endl;
        loadData();      // 1단계: 데이터 로드
        validateData();  // 2단계: 데이터 검증
        transformData(); // 3단계: 데이터 변환 (순수 가상)
        saveData();      // 4단계: 데이터 저장 (순수 가상)
        cleanup();       // 5단계: 정리 작업
        cout << "=== 데이터 처리 완료 ===" << endl;
    }
    
protected:
    // 공통 구현 (모든 자식이 동일하게 사용)
    virtual void loadData() {
        cout << "1. 파일에서 데이터 로드: " << fileName << endl;
    }
    
    virtual void validateData() {
        cout << "2. 데이터 유효성 검사" << endl;
    }
    
    virtual void cleanup() {
        cout << "5. 임시 파일 정리 및 리소스 해제" << endl;
    }
    
    // 순수 가상 함수 (자식 클래스에서 구체적 구현 필요)
    virtual void transformData() = 0;
    virtual void saveData() = 0;
};

class CSVProcessor : public DataProcessor {
public:
    CSVProcessor(string file) : DataProcessor(file) {}
    
protected:
    void transformData() override {
        cout << "3. CSV 데이터 변환: 쉼표 구분 → 구조화된 데이터" << endl;
    }
    
    void saveData() override {
        cout << "4. CSV 형식으로 저장: " << fileName << ".processed.csv" << endl;
    }
};

class JSONProcessor : public DataProcessor {
public:
    JSONProcessor(string file) : DataProcessor(file) {}
    
protected:
    void transformData() override {
        cout << "3. JSON 데이터 변환: JSON 파싱 → 객체 구조" << endl;
    }
    
    void saveData() override {
        cout << "4. JSON 형식으로 저장: " << fileName << ".processed.json" << endl;
    }
};

class XMLProcessor : public DataProcessor {
public:
    XMLProcessor(string file) : DataProcessor(file) {}
    
protected:
    void transformData() override {
        cout << "3. XML 데이터 변환: XML 파싱 → 트리 구조" << endl;
    }
    
    void saveData() override {
        cout << "4. XML 형식으로 저장: " << fileName << ".processed.xml" << endl;
    }
};

// 전략 패턴 예제
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(vector<int>& data) = 0;
    virtual string getName() const = 0;
};

class BubbleSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        cout << "버블 정렬 실행 중..." << endl;
        for (size_t i = 0; i < data.size() - 1; ++i) {
            for (size_t j = 0; j < data.size() - 1 - i; ++j) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }
    
    string getName() const override {
        return "버블 정렬";
    }
};

class QuickSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        cout << "퀵 정렬 실행 중..." << endl;
        std::sort(data.begin(), data.end());  // STL의 퀵 정렬 사용
    }
    
    string getName() const override {
        return "퀵 정렬";
    }
};

class MergeSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        cout << "병합 정렬 실행 중..." << endl;
        stable_sort(data.begin(), data.end());  // STL의 병합 정렬 사용
    }
    
    string getName() const override {
        return "병합 정렬";
    }
};

class SortContext {
private:
    unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(unique_ptr<SortStrategy> newStrategy) {
        strategy = move(newStrategy);
    }
    
    void executeSort(vector<int>& data) {
        if (strategy) {
            cout << "정렬 전략: " << strategy->getName() << endl;
            strategy->sort(data);
        } else {
            cout << "정렬 전략이 설정되지 않았습니다." << endl;
        }
    }
};

// 팩토리 메서드 패턴 예제
class Document {
protected:
    string content;
    
public:
    Document() = default;
    virtual ~Document() = default;
    
    virtual void create() = 0;
    virtual void open() = 0;
    virtual void save() = 0;
    virtual void close() = 0;
    
    void setContent(const string& text) {
        content = text;
    }
    
    string getContent() const {
        return content;
    }
};

class TextDocument : public Document {
public:
    void create() override {
        cout << "텍스트 문서 생성" << endl;
        content = "새 텍스트 문서";
    }
    
    void open() override {
        cout << "텍스트 문서 열기" << endl;
    }
    
    void save() override {
        cout << "텍스트 문서 저장: " << content << endl;
    }
    
    void close() override {
        cout << "PDF 문서 닫기" << endl;
    }
};

class WordDocument : public Document {
public:
    void create() override {
        cout << "Word 문서 생성" << endl;
        content = "새 Word 문서";
    }
    
    void open() override {
        cout << "Word 문서 열기" << endl;
    }
    
    void save() override {
        cout << "Word 문서 저장: " << content << endl;
    }
    
    void close() override {
        cout << "Word 문서 닫기" << endl;
    }
};

// 추상 팩토리
class DocumentFactory {
public:
    enum DocumentType { TEXT, PDF, WORD };
    
    virtual ~DocumentFactory() = default;
    virtual unique_ptr<Document> createDocument() = 0;
    virtual string getFactoryName() const = 0;
    
    // 팩토리 메서드
    static unique_ptr<DocumentFactory> getFactory(DocumentType type);
};

class TextDocumentFactory : public DocumentFactory {
public:
    unique_ptr<Document> createDocument() override {
        return make_unique<TextDocument>();
    }
    
    string getFactoryName() const override {
        return "텍스트 문서 팩토리";
    }
};

class PDFDocumentFactory : public DocumentFactory {
public:
    unique_ptr<Document> createDocument() override {
        return make_unique<PDFDocument>();
    }
    
    string getFactoryName() const override {
        return "PDF 문서 팩토리";
    }
};

class WordDocumentFactory : public DocumentFactory {
public:
    unique_ptr<Document> createDocument() override {
        return make_unique<WordDocument>();
    }
    
    string getFactoryName() const override {
        return "Word 문서 팩토리";
    }
};

// 정적 팩토리 메서드 구현
unique_ptr<DocumentFactory> DocumentFactory::getFactory(DocumentType type) {
    switch (type) {
        case TEXT:
            return make_unique<TextDocumentFactory>();
        case PDF:
            return make_unique<PDFDocumentFactory>();
        case WORD:
            return make_unique<WordDocumentFactory>();
        default:
            return nullptr;
    }
}

void demonstrateTemplateMethod() {
    cout << "\n=== 템플릿 메서드 패턴 ===" << endl;
    
    vector<unique_ptr<DataProcessor>> processors;
    processors.push_back(make_unique<CSVProcessor>("sales_data"));
    processors.push_back(make_unique<JSONProcessor>("user_data"));
    processors.push_back(make_unique<XMLProcessor>("config_data"));
    
    for (const auto& processor : processors) {
        processor->processData();
    }
}

void demonstrateStrategy() {
    cout << "\n=== 전략 패턴 ===" << endl;
    
    vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    SortContext context;
    
    cout << "원본 데이터: ";
    for (int num : data) cout << num << " ";
    cout << endl;
    
    // 버블 정렬 전략
    vector<int> data1 = data;
    context.setStrategy(make_unique<BubbleSort>());
    context.executeSort(data1);
    cout << "정렬 결과: ";
    for (int num : data1) cout << num << " ";
    cout << endl;
    
    // 퀵 정렬 전략
    vector<int> data2 = data;
    context.setStrategy(make_unique<QuickSort>());
    context.executeSort(data2);
    cout << "정렬 결과: ";
    for (int num : data2) cout << num << " ";
    cout << endl;
    
    // 병합 정렬 전략
    vector<int> data3 = data;
    context.setStrategy(make_unique<MergeSort>());
    context.executeSort(data3);
    cout << "정렬 결과: ";
    for (int num : data3) cout << num << " ";
    cout << endl;
}

void demonstrateFactoryMethod() {
    cout << "\n=== 팩토리 메서드 패턴 ===" << endl;
    
    vector<DocumentFactory::DocumentType> types = {
        DocumentFactory::TEXT,
        DocumentFactory::PDF,
        DocumentFactory::WORD
    };
    
    for (auto type : types) {
        auto factory = DocumentFactory::getFactory(type);
        if (factory) {
            cout << "\n" << factory->getFactoryName() << " 사용:" << endl;
            auto document = factory->createDocument();
            
            document->create();
            document->open();
            document->setContent("추상 클래스 예제 내용");
            document->save();
            document->close();
        }
    }
}

int main() {
    cout << "=== 추상 클래스 활용 ===" << endl;
    
    // 1. 템플릿 메서드 패턴
    demonstrateTemplateMethod();
    
    // 2. 전략 패턴
    demonstrateStrategy();
    
    // 3. 팩토리 메서드 패턴
    demonstrateFactoryMethod();
    
    cout << "\n=== 추상 클래스 활용 이점 ===" << endl;
    cout << "1. 공통 인터페이스 제공으로 일관성 보장" << endl;
    cout << "2. 코드 재사용성 증대" << endl;
    cout << "3. 확장성과 유지보수성 향상" << endl;
    cout << "4. 다형성을 통한 유연한 설계" << endl;
    cout << "5. 강제 구현으로 일관된 동작 보장" << endl;
    
    cout << "\n=== 디자인 패턴 요약 ===" << endl;
    cout << "템플릿 메서드: 알고리즘 구조 정의, 세부 구현은 자식에서" << endl;
    cout << "전략 패턴: 알고리즘을 캡슐화하여 런타임 교체 가능" << endl;
    cout << "팩토리 메서드: 객체 생성을 자식 클래스에 위임" << endl;
    
    return 0;
}
```

---

## 8. 예제 08: 다형성 기초 (08_polymorphism_basic.cpp)

### 예제 정의
다형성의 기본 개념과 활용법을 학습합니다.

```cpp
/*
주제: 다형성 기초 (Basic Polymorphism)
정의: 하나의 인터페이스를 통해 서로 다른 타입의 객체들을 동일한 방식으로 처리할 수 있는 객체지향의 핵심 특성

핵심 개념: 런타임 다형성, 컴파일타임 다형성, 가상 함수 테이블, 업캐스팅
정의:
- 런타임 다형성: 실행 시간에 실제 객체 타입에 따라 함수 호출이 결정되는 다형성
- 컴파일타임 다형성: 컴파일 시간에 함수 호출이 결정되는 다형성 (오버로딩, 템플릿)
- 가상 함수 테이블(vtable): 각 클래스의 가상 함수 주소를 저장하는 테이블
- 업캐스팅: 자식 클래스 객체를 부모 클래스 포인터/참조로 참조하는 것
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// 기본 클래스
class Instrument {
protected:
    string name;
    string type;
    
public:
    Instrument(string n, string t) : name(n), type(t) {
        cout << "Instrument 생성: " << name << endl;
    }
    
    virtual ~Instrument() {
        cout << "Instrument 소멸: " << name << endl;
    }
    
    // 가상 함수들 (다형성의 핵심)
    virtual void play() const {
        cout << "Instrument::play() - " << name << " 연주" << endl;
    }
    
    virtual void tune() const {
        cout << "Instrument::tune() - " << name << " 조율" << endl;
    }
    
    virtual string getSound() const {
        return "일반적인 악기 소리";
    }
    
    virtual double getVolume() const {
        return 50.0;  // 기본 볼륨
    }
    
    // 비가상 함수
    void displayInfo() const {
        cout << "악기 정보 - 이름: " << name << ", 종류: " << type << endl;
    }
    
    string getName() const { return name; }
    string getType() const { return type; }
};

class Piano : public Instrument {
private:
    int keys;
    
public:
    Piano(int k = 88) : Instrument("피아노", "건반악기"), keys(k) {
        cout << "Piano 생성: " << keys << "개 건반" << endl;
    }
    
    ~Piano() {
        cout << "Piano 소멸" << endl;
    }
    
    void play() const override {
        cout << "Piano::play() - 피아노 건반을 누르며 연주합니다 ♪♪" << endl;
    }
    
    void tune() const override {
        cout << "Piano::tune() - 피아노 조율사가 " << keys << "개 건반을 조율합니다" << endl;
    }
    
    string getSound() const override {
        return "도레미파솔라시도~";
    }
    
    double getVolume() const override {
        return 70.0;  // 피아노는 큰 소리
    }
    
    // Piano만의 고유 메서드
    void pressKey(int keyNumber) const {
        cout << "피아노 " << keyNumber << "번 건반을 누릅니다" << endl;
    }
};

class Guitar : public Instrument {
private:
    int strings;
    bool isElectric;
    
public:
    Guitar(int s = 6, bool electric = false) 
        : Instrument("기타", electric ? "전기기타" : "어쿠스틱기타"), 
          strings(s), isElectric(electric) {
        cout << "Guitar 생성: " << strings << "줄 " << (electric ? "전기" : "어쿠스틱") << "기타" << endl;
    }
    
    ~Guitar() {
        cout << "Guitar 소멸" << endl;
    }
    
    void play() const override {
        cout << "Guitar::play() - " << strings << "줄 기타를 스트럼하며 연주합니다 ♫♫" << endl;
    }
    
    void tune() const override {
        cout << "Guitar::tune() - " << strings << "개 줄을 하나씩 조율합니다" << endl;
    }
    
    string getSound() const override {
        return isElectric ? "지잉~ 왕왕~" : "통통통 징징~";
    }
    
    double getVolume() const override {
        return isElectric ? 90.0 : 40.0;  // 전기기타가 더 큰 소리
    }
    
    void strum() const {
        cout << "기타 줄을 스트럼합니다" << endl;
    }
};

class Drum : public Instrument {
private:
    int pieces;
    
public:
    Drum(int p = 5) : Instrument("드럼", "타악기"), pieces(p) {
        cout << "Drum 생성: " << pieces << "피스 드럼세트" << endl;
    }
    
    ~Drum() {
        cout << "Drum 소멸" << endl;
    }
    
    void play() const override {
        cout << "Drum::play() - " << pieces << "피스 드럼을 두드리며 연주합니다 ♩♩" << endl;
    }
    
    void tune() const override {
        cout << "Drum::tune() - " << pieces << "개 드럼의 장력을 조절합니다" << endl;
    }
    
    string getSound() const override {
        return "쿵짝쿵짝 따다다~";
    }
    
    double getVolume() const override {
        return 100.0;  // 드럼이 가장 큰 소리
    }
    
    void hit() const {
        cout << "드럼을 힘차게 칩니다!" << endl;
    }
};

class Violin : public Instrument {
private:
    bool hasBow;
    
public:
    Violin(bool bow = true) : Instrument("바이올린", "현악기"), hasBow(bow) {
        cout << "Violin 생성: " << (bow ? "활 포함" : "활 없음") << endl;
    }
    
    ~Violin() {
        cout << "Violin 소멸" << endl;
    }
    
    void play() const override {
        if (hasBow) {
            cout << "Violin::play() - 활로 현을 그으며 우아하게 연주합니다 ♪♫♪" << endl;
        } else {
            cout << "Violin::play() - 활이 없어서 현을 뜯어서 연주합니다" << endl;
        }
    }
    
    void tune() const override {
        cout << "Violin::tune() - 4개 현을 세밀하게 조율합니다" << endl;
    }
    
    string getSound() const override {
        return "미~레~도~시~";
    }
    
    double getVolume() const override {
        return 60.0;
    }
    
    void bow() const {
        if (hasBow) {
            cout << "활로 현을 그어 연주합니다" << endl;
        } else {
            cout << "활이 없습니다!" << endl;
        }
    }
};

// 다형성을 활용하는 오케스트라 클래스
class Orchestra {
private:
    vector<unique_ptr<Instrument>> instruments;
    string name;
    
public:
    Orchestra(string n) : name(n) {
        cout << "오케스트라 '" << name << "' 창단" << endl;
    }
    
    ~Orchestra() {
        cout << "오케스트라 '" << name << "' 해산" << endl;
    }
    
    void addInstrument(unique_ptr<Instrument> instrument) {
        cout << instrument->getName() << "를 오케스트라에 추가" << endl;
        instruments.push_back(move(instrument));
    }
    
    void tuneAllInstruments() const {
        cout << "\n=== " << name << " 조율 시간 ===" << endl;
        for (const auto& instrument : instruments) {
            instrument->tune();  // 다형성: 각 악기의 tune() 호출
        }
    }
    
    void performConcert() const {
        cout << "\n=== " << name << " 연주회 시작 ===" << endl;
        for (const auto& instrument : instruments) {
            instrument->displayInfo();
            instrument->play();    // 다형성: 각 악기의 play() 호출
            cout << "소리: " << instrument->getSound() << endl;
            cout << "볼륨: " << instrument->getVolume() << endl;
            cout << "---" << endl;
        }
        cout << "=== 연주회 종료 ===" << endl;
    }
    
    void getVolumeStatistics() const {
        if (instruments.empty()) return;
        
        double totalVolume = 0;
        double maxVolume = 0;
        double minVolume = 1000;
        string loudest, quietest;
        
        for (const auto& instrument : instruments) {
            double volume = instrument->getVolume();
            totalVolume += volume;
            
            if (volume > maxVolume) {
                maxVolume = volume;
                loudest = instrument->getName();
            }
            
            if (volume < minVolume) {
                minVolume = volume;
                quietest = instrument->getName();
            }
        }
        
        cout << "\n=== 볼륨 통계 ===" << endl;
        cout << "평균 볼륨: " << totalVolume / instruments.size() << endl;
        cout << "가장 큰 소리: " << loudest << " (" << maxVolume << ")" << endl;
        cout << "가장 작은 소리: " << quietest << " (" << minVolume << ")" << endl;
    }
    
    size_t getInstrumentCount() const {
        return instruments.size();
    }
};

void demonstrateBasicPolymorphism() {
    cout << "\n=== 기본 다형성 데모 ===" << endl;
    
    // 업캐스팅 (자식 → 부모)
    Piano piano;
    Guitar guitar(6, true);  // 6줄 전기기타
    
    Instrument* instPtr;
    
    // 피아노를 악기 포인터로 참조
    instPtr = &piano;
    cout << "포인터를 통한 피아노 연주:" << endl;
    instPtr->play();     // Piano::play() 호출 (다형성)
    instPtr->tune();     // Piano::tune() 호출 (다형성)
    
    // 기타를 악기 포인터로 참조
    instPtr = &guitar;
    cout << "\n포인터를 통한 기타 연주:" << endl;
    instPtr->play();     // Guitar::play() 호출 (다형성)
    instPtr->tune();     // Guitar::tune() 호출 (다형성)
}

void demonstratePolymorphicArray() {
    cout << "\n=== 다형성 배열 데모 ===" << endl;
    
    // 다형성 배열 (부모 클래스 포인터 배열)
    vector<unique_ptr<Instrument>> band;
    band.push_back(make_unique<Piano>(61));        // 61건반 피아노
    band.push_back(make_unique<Guitar>(6, false)); // 어쿠스틱 기타
    band.push_back(make_unique<Drum>(7));          // 7피스 드럼
    band.push_back(make_unique<Violin>(true));     // 활 있는 바이올린
    
    cout << "밴드 연주:" << endl;
    for (const auto& instrument : band) {
        cout << "\n" << instrument->getName() << " 연주:" << endl;
        instrument->play();   // 각각의 play() 메서드 호출
        cout << "소리: " << instrument->getSound() << endl;
    }
}

int main() {
    cout << "=== 다형성 기초 ===" << endl;
    
    // 1. 기본 다형성
    demonstrateBasicPolymorphism();
    
    // 2. 다형성 배열
    demonstratePolymorphicArray();
    
    // 3. 오케스트라를 통한 종합 다형성
    cout << "\n=== 오케스트라 다형성 데모 ===" << endl;
    Orchestra orchestra("서울 심포니");
    
    orchestra.addInstrument(make_unique<Piano>(88));
    orchestra.addInstrument(make_unique<Guitar>(12, true));  // 12줄 전기기타
    orchestra.addInstrument(make_unique<Drum>(5));
    orchestra.addInstrument(make_unique<Violin>());
    orchestra.addInstrument(make_unique<Guitar>(6, false)); // 어쿠스틱 기타
    
    orchestra.tuneAllInstruments();
    orchestra.performConcert();
    orchestra.getVolumeStatistics();
    
    cout << "\n=== 다형성 핵심 개념 ===" << endl;
    cout << "1. 하나의 인터페이스, 여러 구현" << endl;
    cout << "2. 런타임에 실제 객체 타입에 따라 함수 결정" << endl;
    cout << "3. 가상 함수와 가상 함수 테이블(vtable) 활용" << endl;
    cout << "4. 업캐스팅을 통한 일관된 처리" << endl;
    cout << "5. 코드의 확장성과 유연성 제공" << endl;
    
    return 0;
}
```

---

## 9. 예제 09: 가상 소멸자 (09_virtual_destructor.cpp)

### 예제 정의
가상 소멸자의 필요성과 올바른 사용법을 학습합니다.

```cpp
/*
주제: 가상 소멸자 (Virtual Destructor)
정의: 다형성을 사용할 때 올바른 소멸자 호출을 보장하기 위해 부모 클래스에서 virtual로 선언된 소멸자

핵심 개념: 메모리 누수 방지, 올바른 소멸 순서, 다형성 안전성
정의:
- 메모리 누수 방지: 자식 클래스의 소멸자가 호출되지 않아 발생하는 메모리 누수 방지
- 올바른 소멸 순서: 자식 → 부모 순서로 소멸자가 호출되도록 보장
- 다형성 안전성: 부모 클래스 포인터로 자식 객체를 삭제할 때의 안전성 보장
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// 잘못된 예제 - 가상 소멸자가 없는 경우
class BadBase {
private:
    int* data;
    
public:
    BadBase() {
        data = new int[10];
        cout << "BadBase 생성자: 메모리 할당" << endl;
    }
    
    // 비가상 소멸자 (문제!)
    ~BadBase() {
        delete[] data;
        cout << "BadBase 소멸자: 메모리 해제" << endl;
    }
    
    virtual void show() {
        cout << "BadBase::show()" << endl;
    }
};

class BadDerived : public BadBase {
private:
    string* name;
    
public:
    BadDerived(string n) {
        name = new string(n);
        cout << "BadDerived 생성자: " << *name << " 메모리 할당" << endl;
    }
    
    ~BadDerived() {
        cout << "BadDerived 소멸자: " << *name << " 메모리 해제" << endl;
        delete name;
    }
    
    void show() override {
        cout << "BadDerived::show() - " << *name << endl;
    }
};

// 올바른 예제 - 가상 소멸자가 있는 경우
class GoodBase {
private:
    int* data;
    
public:
    GoodBase() {
        data = new int[10];
        cout << "GoodBase 생성자: 메모리 할당" << endl;
    }
    
    // 가상 소멸자 (올바름!)
    virtual ~GoodBase() {
        delete[] data;
        cout << "GoodBase 소멸자: 메모리 해제" << endl;
    }
    
    virtual void show() {
        cout << "GoodBase::show()" << endl;
    }
};

class GoodDerived : public GoodBase {
private:
    string* name;
    
public:
    GoodDerived(string n) {
        name = new string(n);
        cout << "GoodDerived 생성자: " << *name << " 메모리 할당" << endl;
    }
    
    ~GoodDerived() {
        cout << "GoodDerived 소멸자: " << *name << " 메모리 해제" << endl;
        delete name;
    }
    
    void show() override {
        cout << "GoodDerived::show() - " << *name << endl;
    }
};

// 리소스 관리 예제
class Resource {
private:
    static int resourceCount;
    int id;
    string type;
    
public:
    Resource(string t) : type(t) {
        id = ++resourceCount;
        cout << "Resource " << id << " (" << type << ") 할당" << endl;
    }
    
    virtual ~Resource() {
        cout << "Resource " << id << " (" << type << ") 해제" << endl;
    }
    
    virtual void use() = 0;
    
    int getId() const { return id; }
    string getType() const { return type; }
};

int Resource::resourceCount = 0;

class FileResource : public Resource {
private:
    string filename;
    bool isOpen;
    
public:
    FileResource(string fname) : Resource("File"), filename(fname), isOpen(false) {
        isOpen = true;
        cout << "파일 '" << filename << "' 열기" << endl;
    }
    
    ~FileResource() {
        if (isOpen) {
            cout << "파일 '" << filename << "' 닫기" << endl;
        }
    }
    
    void use() override {
        if (isOpen) {
            cout << "파일 '" << filename << "' 읽기/쓰기" << endl;
        }
    }
    
    void close() {
        if (isOpen) {
            isOpen = false;
            cout << "파일 '" << filename << "' 수동 닫기" << endl;
        }
    }
};

class NetworkResource : public Resource {
private:
    string address;
    bool isConnected;
    
public:
    NetworkResource(string addr) : Resource("Network"), address(addr), isConnected(false) {
        isConnected = true;
        cout << "네트워크 '" << address << "' 연결" << endl;
    }
    
    ~NetworkResource() {
        if (isConnected) {
            cout << "네트워크 '" << address << "' 연결 해제" << endl;
        }
    }
    
    void use() override {
        if (isConnected) {
            cout << "네트워크 '" << address << "'로 데이터 송수신" << endl;
        }
    }
    
    void disconnect() {
        if (isConnected) {
            isConnected = false;
            cout << "네트워크 '" << address << "' 수동 연결 해제" << endl;
        }
    }
};

class MemoryResource : public Resource {
private:
    size_t size;
    void* memory;
    
public:
    MemoryResource(size_t s) : Resource("Memory"), size(s) {
        memory = malloc(size);
        cout << size << " 바이트 메모리 할당" << endl;
    }
    
    ~MemoryResource() {
        if (memory) {
            cout << size << " 바이트 메모리 해제" << endl;
            free(memory);
        }
    }
    
    void use() override {
        if (memory) {
            cout << size << " 바이트 메모리 사용" << endl;
        }
    }
};

void demonstrateBadDestruction() {
    cout << "\n=== 잘못된 소멸자 예제 (가상 소멸자 없음) ===" << endl;
    cout << "주의: 이 예제는 메모리 누수를 보여주기 위한 것입니다!" << endl;
    
    BadBase* ptr = new BadDerived("문제있는객체");
    ptr->show();
    
    cout << "부모 클래스 포인터로 삭제 시도..." << endl;
    delete ptr;  // BadDerived의 소멸자가 호출되지 않음! (메모리 누수)
    cout << "BadDerived 소멸자가 호출되지 않았습니다! (메모리 누수 발생)" << endl;
}

void demonstrateGoodDestruction() {
    cout << "\n=== 올바른 소멸자 예제 (가상 소멸자 있음) ===" << endl;
    
    GoodBase* ptr = new GoodDerived("올바른객체");
    ptr->show();
    
    cout << "부모 클래스 포인터로 삭제 시도..." << endl;
    delete ptr;  // GoodDerived의 소멸자가 먼저 호출됨! (올바른 소멸)
    cout << "올바른 순서로 소멸자가 호출되었습니다!" << endl;
}

void demonstrateResourceManagement() {
    cout << "\n=== 리소스 관리 예제 ===" << endl;
    
    vector<unique_ptr<Resource>> resources;
    
    resources.push_back(make_unique<FileResource>("data.txt"));
    resources.push_back(make_unique<NetworkResource>("192.168.1.1"));
    resources.push_back(make_unique<MemoryResource>(1024));
    
    cout << "\n리소스 사용:" << endl;
    for (const auto& resource : resources) {
        resource->use();
    }
    
    cout << "\n스코프 종료로 인한 자동 리소스 해제:" << endl;
    // 벡터가 소멸되면서 unique_ptr들이 자동으로 삭제
    // 가상 소멸자 덕분에 올바른 순서로 리소스 해제
}

void demonstratePolymorphicDestruction() {
    cout << "\n=== 다형성과 소멸자 ===" << endl;
    
    // 다양한 타입의 객체를 기본 클래스 포인터로 관리
    vector<Resource*> rawResources;
    rawResources.push_back(new FileResource("temp.dat"));
    rawResources.push_back(new NetworkResource("server.com"));
    rawResources.push_back(new MemoryResource(512));
    
    cout << "\n다형성을 통한 리소스 사용:" << endl;
    for (Resource* resource : rawResources) {
        cout << "리소스 " << resource->getId() << " (" << resource->getType() << "): ";
        resource->use();
    }
    
    cout << "\n가상 소멸자를 통한 올바른 정리:" << endl;
    for (Resource* resource : rawResources) {
        delete resource;  // 가상 소멸자 덕분에 올바른 소멸자 호출
    }
    rawResources.clear();
}

// 소멸자 호출 순서 확인
class Base1 {
public:
    Base1() { cout << "Base1 생성자" << endl; }
    virtual ~Base1() { cout << "Base1 소멸자" << endl; }
};

class Derived1 : public Base1 {
public:
    Derived1() { cout << "Derived1 생성자" << endl; }
    ~Derived1() { cout << "Derived1 소멸자" << endl; }
};

class FinalDerived : public Derived1 {
public:
    FinalDerived() { cout << "FinalDerived 생성자" << endl; }
    ~FinalDerived() { cout << "FinalDerived 소멸자" << endl; }
};

void demonstrateDestructionOrder() {
    cout << "\n=== 소멸자 호출 순서 확인 ===" << endl;
    
    cout << "객체 생성:" << endl;
    Base1* ptr = new FinalDerived();
    
    cout << "\n객체 삭제:" << endl;
    delete ptr;  // FinalDerived → Derived1 → Base1 순서로 소멸
}

int main() {
    cout << "=== 가상 소멸자 ===" << endl;
    
    // 1. 잘못된 예제 (메모리 누수 발생)
    demonstrateBadDestruction();
    
    // 2. 올바른 예제 (정상적인 메모리 해제)
    demonstrateGoodDestruction();
    
    // 3. 리소스 관리
    demonstrateResourceManagement();
    
    // 4. 다형성과 소멸자
    demonstratePolymorphicDestruction();
    
    // 5. 소멸자 호출 순서
    demonstrateDestructionOrder();
    
    cout << "\n=== 가상 소멸자 핵심 규칙 ===" << endl;
    cout << "1. 다형성을 사용하는 기본 클래스는 반드시 가상 소멸자 선언" << endl;
    cout << "2. virtual ~ClassName() = default; 또는 구체적 구현" << endl;
    cout << "3. 가상 소멸자는 자식 → 부모 순서로 호출 보장" << endl;
    cout << "4. 기본 클래스 포인터로 자식 객체 삭제 시 안전성 제공" << endl;
    cout << "5. 스마트 포인터 사용 시에도 가상 소멸자 필요" << endl;
    
    cout << "\n=== 가상 소멸자 없을 때의 문제점 ===" << endl;
    cout << "1. 자식 클래스 소멸자 호출 안됨" << endl;
    cout << "2. 메모리 누수 발생 가능" << endl;
    cout << "3. 리소스 해제 실패" << endl;
    cout << "4. 정의되지 않은 동작 (Undefined Behavior)" << endl;
    
    return 0;
}
```

---

## 10. 예제 10: 다중 상속 (10_multiple_inheritance.cpp)

### 예제 정의
다중 상속의 개념과 발생할 수 있는 문제점들을 학습합니다.

```cpp
/*
주제: 다중 상속 (Multiple Inheritance)
정의: 하나의 클래스가 두 개 이상의 부모 클래스로부터 상속받는 C++의 고급 기능

핵심 개념: 다이아몬드 문제, 가상 상속, 이름 충돌, 모호성 해결
정의:
- 다이아몬드 문제: 공통 조상을 가진 두 클래스를 다중 상속할 때 발생하는 모호성 문제
- 가상 상속: virtual 키워드를 사용하여 다이아몬드 문제를 해결하는 방법
- 이름 충돌: 여러 부모 클래스에 동일한 이름의 멤버가 있을 때 발생하는 충돌
- 모호성 해결: 범위 지정 연산자(::)를 사용하여 어떤 부모의 멤버인지 명시
*/

#include <iostream>
#include <string>
using namespace std;

// 기본 다중 상속 예제
class Flyable {
protected:
    double altitude;
    
public:
    Flyable() : altitude(0) {
        cout << "Flyable 생성자" << endl;
    }
    
    virtual ~Flyable() {
        cout << "Flyable 소멸자" << endl;
    }
    
    virtual void fly() {
        cout << "Flyable::fly() - 고도 " << altitude << "m에서 비행" << endl;
    }
    
    void setAltitude(double alt) {
        altitude = alt;
    }
    
    double getAltitude() const {
        return altitude;
    }
};

class Swimmable {
protected:
    double depth;
    
public:
    Swimmable() : depth(0) {
        cout << "Swimmable 생성자" << endl;
    }
    
    virtual ~Swimmable() {
        cout << "Swimmable 소멸자" << endl;
    }
    
    virtual void swim() {
        cout << "Swimmable::swim() - 수심 " << depth << "m에서 수영" << endl;
    }
    
    void setDepth(double d) {
        depth = d;
    }
    
    double getDepth() const {
        return depth;
    }
};

// 다중 상속 클래스
class Duck : public Flyable, public Swimmable {
private:
    string name;
    
public:
    Duck(string n) : name(n) {
        cout << "Duck 생성자: " << name << endl;
    }
    
    ~Duck() {
        cout << "Duck 소멸자: " << name << endl;
    }
    
    // 두 부모의 메서드를 모두 오버라이딩
    void fly() override {
        cout << "Duck::fly() - " << name << "가 물 위에서 날아오릅니다!" << endl;
    }
    
    void swim() override {
        cout << "Duck::swim() - " << name << "가 물에서 헤엄칩니다!" << endl;
    }
    
    // Duck만의 고유 메서드
    void quack() {
        cout << name << "가 꽥꽥 웁니다!" << endl;
    }
    
    string getName() const {
        return name;
    }
};

// 이름 충돌 문제 예제
class Engine {
protected:
    int power;
    
public:
    Engine(int p) : power(p) {
        cout << "Engine 생성자: " << power << "마력" << endl;
    }
    
    virtual ~Engine() {
        cout << "Engine 소멸자" << endl;
    }
    
    void start() {
        cout << "Engine::start() - 엔진 시동 (" << power << "마력)" << endl;
    }
    
    void stop() {
        cout << "Engine::stop() - 엔진 정지" << endl;
    }
    
    int getPower() const {
        return power;
    }
};

class ElectricMotor {
protected:
    int power;  // Engine과 같은 이름의 멤버
    
public:
    ElectricMotor(int p) : power(p) {
        cout << "ElectricMotor 생성자: " << power << "W" << endl;
    }
    
    virtual ~ElectricMotor() {
        cout << "ElectricMotor 소멸자" << endl;
    }
    
    void start() {  // Engine과 같은 이름의 메서드
        cout << "ElectricMotor::start() - 전기모터 시작 (" << power << "W)" << endl;
    }
    
    void charge() {
        cout << "ElectricMotor::charge() - 배터리 충전" << endl;
    }
    
    int getPower() const {
        return power;
    }
};

// 이름 충돌이 있는 다중 상속
class HybridCar : public Engine, public ElectricMotor {
private:
    string model;
    
public:
    HybridCar(string m, int enginePower, int motorPower) 
        : Engine(enginePower), ElectricMotor(motorPower), model(m) {
        cout << "HybridCar 생성자: " << model << endl;
    }
    
    ~HybridCar() {
        cout << "HybridCar 소멸자: " << model << endl;
    }
    
    // 모호성 해결을 위한 명시적 호출
    void startEngine() {
        Engine::start();  // Engine의 start() 호출
    }
    
    void startMotor() {
        ElectricMotor::start();  // ElectricMotor의 start() 호출
    }
    
    void startBoth() {
        cout << model << " 하이브리드 시동:" << endl;
        Engine::start();
        ElectricMotor::start();
    }
    
    void displayPowerInfo() {
        cout << model << " 출력 정보:" << endl;
        cout << "엔진 출력: " << Engine::getPower() << "마력" << endl;
        cout << "모터 출력: " << ElectricMotor::getPower() << "W" << endl;
        cout << "총 출력: " << Engine::getPower() << "마력 + " 
             << ElectricMotor::getPower() << "W" << endl;
    }
    
    string getModel() const {
        return model;
    }
};

// 다이아몬드 문제 예제
class Vehicle {
protected:
    string brand;
    int year;
    
public:
    Vehicle(string b, int y) : brand(b), year(y) {
        cout << "Vehicle 생성자: " << brand << " (" << year << ")" << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle 소멸자: " << brand << endl;
    }
    
    virtual void start() {
        cout << "Vehicle::start() - " << brand << " 시동" << endl;
    }
    
    void displayInfo() {
        cout << "차량 정보: " << brand << " " << year << "년형" << endl;
    }
    
    string getBrand() const { return brand; }
    int getYear() const { return year; }
};

class LandVehicle : public Vehicle {
protected:
    int wheels;
    
public:
    LandVehicle(string b, int y, int w) : Vehicle(b, y), wheels(w) {
        cout << "LandVehicle 생성자: " << wheels << "바퀴" << endl;
    }
    
    virtual ~LandVehicle() {
        cout << "LandVehicle 소멸자" << endl;
    }
    
    void drive() {
        cout << "LandVehicle::drive() - " << wheels << "바퀴로 달립니다" << endl;
    }
};

class WaterVehicle : public Vehicle {
protected:
    string propulsion;
    
public:
    WaterVehicle(string b, int y, string p) : Vehicle(b, y), propulsion(p) {
        cout << "WaterVehicle 생성자: " << propulsion << " 추진" << endl;
    }
    
    virtual ~WaterVehicle() {
        cout << "WaterVehicle 소멸자" << endl;
    }
    
    void sail() {
        cout << "WaterVehicle::sail() - " << propulsion << "으로 항해합니다" << endl;
    }
};

// 다이아몬드 문제 발생 (Vehicle이 두 번 상속됨)
class AmphibiousVehicle : public LandVehicle, public WaterVehicle {
private:
    bool isWaterMode;
    
public:
    AmphibiousVehicle(string b, int y, int w, string p) 
        : LandVehicle(b, y, w), WaterVehicle(b, y, p), isWaterMode(false) {
        cout << "AmphibiousVehicle 생성자" << endl;
    }
    
    ~AmphibiousVehicle() {
        cout << "AmphibiousVehicle 소멸자" << endl;
    }
    
    void switchMode() {
        isWaterMode = !isWaterMode;
        cout << "모드 전환: " << (isWaterMode ? "수상 모드" : "육상 모드") << endl;
    }
    
    void move() {
        if (isWaterMode) {
            WaterVehicle::sail();
        } else {
            LandVehicle::drive();
        }
    }
    
    // Vehicle의 멤버에 접근할 때 모호성 발생
    void showBrand() {
        // cout << getBrand();  // 오류! 모호함 - LandVehicle::getBrand()? WaterVehicle::getBrand()?
        cout << "브랜드 (LandVehicle 경로): " << LandVehicle::getBrand() << endl;
        cout << "브랜드 (WaterVehicle 경로): " << WaterVehicle::getBrand() << endl;
    }
};

// 가상 상속으로 다이아몬드 문제 해결
class VirtualVehicle {
protected:
    string brand;
    int year;
    
public:
    VirtualVehicle(string b, int y) : brand(b), year(y) {
        cout << "VirtualVehicle 생성자: " << brand << " (" << year << ")" << endl;
    }
    
    virtual ~VirtualVehicle() {
        cout << "VirtualVehicle 소멸자: " << brand << endl;
    }
    
    virtual void start() {
        cout << "VirtualVehicle::start() - " << brand << " 시동" << endl;
    }
    
    void displayInfo() {
        cout << "차량 정보: " << brand << " " << year << "년형" << endl;
    }
    
    string getBrand() const { return brand; }
    int getYear() const { return year; }
};

class VirtualLandVehicle : virtual public VirtualVehicle {  // virtual 상속
protected:
    int wheels;
    
public:
    VirtualLandVehicle(string b, int y, int w) : VirtualVehicle(b, y), wheels(w) {
        cout << "VirtualLandVehicle 생성자: " << wheels << "바퀴" << endl;
    }
    
    virtual ~VirtualLandVehicle() {
        cout << "VirtualLandVehicle 소멸자" << endl;
    }
    
    void drive() {
        cout << "VirtualLandVehicle::drive() - " << wheels << "바퀴로 달립니다" << endl;
    }
};

class VirtualWaterVehicle : virtual public VirtualVehicle {  // virtual 상속
protected:
    string propulsion;
    
public:
    VirtualWaterVehicle(string b, int y, string p) : VirtualVehicle(b, y), propulsion(p) {
        cout << "VirtualWaterVehicle 생성자: " << propulsion << " 추진" << endl;
    }
    
    virtual ~VirtualWaterVehicle() {
        cout << "VirtualWaterVehicle 소멸자" << endl;
    }
    
    void sail() {
        cout << "VirtualWaterVehicle::sail() - " << propulsion << "으로 항해합니다" << endl;
    }
};

// 가상 상속으로 다이아몬드 문제 해결
class FixedAmphibiousVehicle : public VirtualLandVehicle, public VirtualWaterVehicle {
private:
    bool isWaterMode;
    
public:
    FixedAmphibiousVehicle(string b, int y, int w, string p) 
        : VirtualVehicle(b, y),  // 가상 기본 클래스는 직접 초기화
          VirtualLandVehicle(b, y, w), 
          VirtualWaterVehicle(b, y, p), 
          isWaterMode(false) {
        cout << "FixedAmphibiousVehicle 생성자" << endl;
    }
    
    ~FixedAmphibiousVehicle() {
        cout << "FixedAmphibiousVehicle 소멸자" << endl;
    }
    
    void switchMode() {
        isWaterMode = !isWaterMode;
        cout << "모드 전환: " << (isWaterMode ? "수상 모드" : "육상 모드") << endl;
    }
    
    void move() {
        if (isWaterMode) {
            VirtualWaterVehicle::sail();
        } else {
            VirtualLandVehicle::drive();
        }
    }
    
    // 가상 상속으로 모호성 해결
    void showBrand() {
        cout << "브랜드: " << getBrand() << endl;  // 모호성 없음!
    }
};

int main() {
    cout << "=== 다중 상속 ===" << endl;
    
    // 1. 기본 다중 상속
    cout << "\n--- 기본 다중 상속 (Duck) ---" << endl;
    Duck duck("도널드");
    duck.fly();
    duck.swim();
    duck.quack();
    duck.setAltitude(100);
    duck.setDepth(5);
    cout << "고도: " << duck.getAltitude() << "m, 수심: " << duck.getDepth() << "m" << endl;
    
    // 2. 이름 충돌 문제
    cout << "\n--- 이름 충돌 문제 (HybridCar) ---" << endl;
    HybridCar hybrid("프리우스", 150, 50000);
    
    // hybrid.start();  // 오류! 모호함 - Engine::start()? ElectricMotor::start()?
    hybrid.startEngine();  // 명시적 호출
    hybrid.startMotor();   // 명시적 호출
    hybrid.startBoth();    // 둘 다 호출
    hybrid.displayPowerInfo();
    
    // 3. 다이아몬드 문제 (해결되지 않은 버전)
    cout << "\n--- 다이아몬드 문제 (해결 안됨) ---" << endl;
    AmphibiousVehicle amphibious("DUKW", 1943, 6, "프로펠러");
    amphibious.switchMode();
    amphibious.move();
    amphibious.switchMode();
    amphibious.move();
    amphibious.showBrand();  // 모호성으로 인한 명시적 호출 필요
    
    // 4. 가상 상속으로 다이아몬드 문제 해결
    cout << "\n--- 가상 상속으로 다이아몬드 문제 해결 ---" << endl;
    FixedAmphibiousVehicle fixedAmphibious("개선된DUKW", 2023, 8, "워터젯");
    fixedAmphibious.switchMode();
    fixedAmphibious.move();
    fixedAmphibious.switchMode();
    fixedAmphibious.move();
    fixedAmphibious.showBrand();  // 모호성 없음!
    fixedAmphibious.displayInfo();
    
    cout << "\n=== 다중 상속 핵심 개념 ===" << endl;
    cout << "1. 여러 부모 클래스로부터 동시에 상속" << endl;
    cout << "2. 이름 충돌 시 범위 지정 연산자(::) 사용" << endl;
    cout << "3. 다이아몬드 문제: 공통 조상의 중복 상속" << endl;
    cout << "4. 가상 상속(virtual): 다이아몬드 문제 해결" << endl;
    cout << "5. 생성자 호출 순서: 왼쪽부터 오른쪽, 깊이 우선" << endl;
    cout << "6. 소멸자 호출 순서: 생성자의 역순" << endl;
    
    cout << "\n=== 다중 상속 주의사항 ===" << endl;
    cout << "1. 복잡성 증가로 인한 설계 어려움" << endl;
    cout << "2. 이름 충돌과 모호성 문제" << endl;
    cout << "3. 가상 상속 시 성능 오버헤드" << endl;
    cout << "4. 대안: 구성(Composition)과 인터페이스 활용" << endl;
    
    return 0;
} {
        cout << "텍스트 문서 닫기" << endl;
    }
};

class PDFDocument : public Document {
public:
    void create() override {
        cout << "PDF 문서 생성" << endl;
        content = "새 PDF 문서";
    }
    
    void open() override {
        cout << "PDF 문서 열기" << endl;
    }
    
    void save() override {
        cout << "PDF 문서 저장: " << content << endl;
    }
    
    void close() override
