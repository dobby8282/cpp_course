# Chapter 05: 클래스와 객체지향 II

## 학습 목표
- 정적 멤버와 const 멤버의 고급 활용법 습득
- 연산자 오버로딩의 심화 기법 학습
- 프렌드 함수와 프렌드 클래스의 활용
- 이동 의미론과 완벽한 전달의 개념 이해
- 현대 C++의 고급 객체 관리 기법 습득
- RAII 패턴과 자원 관리 전략 학습

---

## 1. 예제 01: 정적 멤버 고급 활용 (01_static_members_advanced.cpp)

### 예제 정의
정적 멤버를 활용한 싱글톤 패턴과 팩토리 패턴을 구현합니다.

```cpp
/*
주제: 정적 멤버 고급 활용 (Advanced Static Members)
정의: 정적 멤버를 활용하여 디자인 패턴을 구현하고 클래스 레벨의 기능을 제공하는 기법

핵심 개념: 싱글톤 패턴, 팩토리 패턴, 정적 초기화, 클래스 유틸리티
정의:
- 싱글톤 패턴: 클래스의 인스턴스가 오직 하나만 존재하도록 보장하는 디자인 패턴
- 팩토리 패턴: 객체 생성을 캡슐화하여 생성 로직을 분리하는 패턴
- 정적 초기화: 프로그램 시작 시 정적 멤버가 초기화되는 과정
- 클래스 유틸리티: 인스턴스 없이도 사용할 수 있는 유틸리티 함수들
*/

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
using namespace std;

// 싱글톤 패턴 구현
class Logger {
private:
    static unique_ptr<Logger> instance;
    static mutex instanceMutex;
    string logLevel;
    
    // private 생성자로 외부 생성 방지
    Logger(string level = "INFO") : logLevel(level) {
        cout << "Logger 인스턴스 생성 (레벨: " << logLevel << ")" << endl;
    }
    
public:
    // 복사 생성자와 대입 연산자 삭제
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    static Logger& getInstance() {
        lock_guard<mutex> lock(instanceMutex);
        if (!instance) {
            instance = unique_ptr<Logger>(new Logger());
        }
        return *instance;
    }
    
    void log(const string& message) {
        cout << "[" << logLevel << "] " << message << endl;
    }
    
    void setLogLevel(const string& level) {
        logLevel = level;
    }
};

// 정적 멤버 초기화
unique_ptr<Logger> Logger::instance = nullptr;
mutex Logger::instanceMutex;

// 정적 멤버를 활용한 카운터 클래스
class ObjectCounter {
private:
    static int totalObjects;
    static int activeObjects;
    int objectId;
    
public:
    ObjectCounter() : objectId(++totalObjects) {
        activeObjects++;
        cout << "객체 " << objectId << " 생성 (활성: " << activeObjects << ")" << endl;
    }
    
    ~ObjectCounter() {
        activeObjects--;
        cout << "객체 " << objectId << " 소멸 (활성: " << activeObjects << ")" << endl;
    }
    
    // 정적 멤버 함수들
    static int getTotalObjects() { return totalObjects; }
    static int getActiveObjects() { return activeObjects; }
    
    static void printStatistics() {
        cout << "총 생성된 객체: " << totalObjects 
             << ", 현재 활성 객체: " << activeObjects << endl;
    }
    
    int getId() const { return objectId; }
};

int ObjectCounter::totalObjects = 0;
int ObjectCounter::activeObjects = 0;

// 팩토리 패턴 구현
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual string getType() const = 0;
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "원을 그립니다." << endl;
    }
    
    string getType() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "사각형을 그립니다." << endl;
    }
    
    string getType() const override {
        return "Rectangle";
    }
};

class ShapeFactory {
public:
    static unique_ptr<Shape> createShape(const string& type) {
        if (type == "circle") {
            return make_unique<Circle>();
        } else if (type == "rectangle") {
            return make_unique<Rectangle>();
        }
        return nullptr;
    }
    
    static void printAvailableShapes() {
        cout << "사용 가능한 도형: circle, rectangle" << endl;
    }
};

int main() {
    cout << "=== 정적 멤버 고급 활용 ===" << endl;
    
    // 싱글톤 패턴 테스트
    cout << "\n--- 싱글톤 패턴 ---" << endl;
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    
    cout << "같은 인스턴스인가? " << (&logger1 == &logger2) << endl;
    
    logger1.log("첫 번째 로그 메시지");
    logger2.setLogLevel("DEBUG");
    logger1.log("두 번째 로그 메시지");
    
    // 객체 카운터 테스트
    cout << "\n--- 객체 카운터 ---" << endl;
    ObjectCounter::printStatistics();
    
    {
        ObjectCounter obj1, obj2, obj3;
        ObjectCounter::printStatistics();
    }
    
    ObjectCounter::printStatistics();
    
    // 팩토리 패턴 테스트
    cout << "\n--- 팩토리 패턴 ---" << endl;
    ShapeFactory::printAvailableShapes();
    
    auto circle = ShapeFactory::createShape("circle");
    auto rectangle = ShapeFactory::createShape("rectangle");
    
    if (circle) {
        cout << circle->getType() << ": ";
        circle->draw();
    }
    
    if (rectangle) {
        cout << rectangle->getType() << ": ";
        rectangle->draw();
    }
    
    return 0;
}
```

---

## 2. 예제 02: const 멤버 심화 (02_const_members_advanced.cpp)

### 예제 정의
const 정확성과 mutable의 고급 사용법을 학습합니다.

```cpp
/*
주제: const 멤버 심화 (Advanced const Members)
정의: const 정확성을 통해 프로그램의 안전성을 높이고 의도를 명확히 표현하는 고급 기법

핵심 개념: const 정확성, mutable, const 오버로딩, 논리적 상수성
정의:
- const 정확성: 변경되지 않아야 하는 것은 const로 선언하여 컴파일 시점에 보장하는 원칙
- mutable: const 객체에서도 수정 가능한 멤버를 지정하는 키워드
- const 오버로딩: const 버전과 non-const 버전의 함수를 따로 제공하는 기법
- 논리적 상수성: 객체의 논리적 상태는 변하지 않으나 내부 구현상 일부 데이터가 변할 수 있는 개념
*/

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

class CachedCalculator {
private:
    mutable double cachedResult;
    mutable bool resultCached;
    mutable int accessCount;  // 논리적으로는 객체 상태와 무관
    
    vector<double> data;
    
public:
    CachedCalculator(vector<double> d) : data(d), cachedResult(0), resultCached(false), accessCount(0) {}
    
    // const 함수이지만 캐시 관련 멤버는 수정 가능
    double getAverage() const {
        accessCount++;  // mutable이므로 const 함수에서도 수정 가능
        
        if (!resultCached) {
            cout << "평균 계산 중..." << endl;
            double sum = 0;
            for (double value : data) {
                sum += value;
            }
            cachedResult = sum / data.size();
            resultCached = true;
        } else {
            cout << "캐시된 결과 반환" << endl;
        }
        
        return cachedResult;
    }
    
    void addData(double value) {
        data.push_back(value);
        resultCached = false;  // 캐시 무효화
    }
    
    int getAccessCount() const {
        return accessCount;
    }
    
    // const 오버로딩 예제
    double& operator[](size_t index) {
        resultCached = false;  // 데이터 변경 가능성으로 캐시 무효화
        return data[index];
    }
    
    const double& operator[](size_t index) const {
        accessCount++;  // 읽기 전용 접근도 카운트
        return data[index];
    }
    
    size_t size() const { return data.size(); }
};

// const 매개변수와 반환값
class StringProcessor {
private:
    string text;
    mutable string lastProcessed;
    mutable bool processed;
    
public:
    explicit StringProcessor(const string& str) : text(str), processed(false) {}
    
    // const 문자열 참조를 받아 const 문자열 참조를 반환
    const string& getUpperCase() const {
        if (!processed) {
            lastProcessed = text;
            for (char& c : lastProcessed) {
                if (c >= 'a' && c <= 'z') {
                    c = c - 'a' + 'A';
                }
            }
            processed = true;
        }
        return lastProcessed;
    }
    
    void setText(const string& newText) {
        text = newText;
        processed = false;
    }
    
    // const 함수와 non-const 함수의 차이
    char& charAt(size_t index) {
        processed = false;  // 수정 가능성
        return text[index];
    }
    
    const char& charAt(size_t index) const {
        return text[index];
    }
};

// const 객체 전용 인터페이스
class ReadOnlyData {
private:
    vector<int> data;
    mutable size_t readCount;
    
public:
    ReadOnlyData(vector<int> d) : data(d), readCount(0) {}
    
    // const 전용 인터페이스
    int getValue(size_t index) const {
        if (index < data.size()) {
            readCount++;
            return data[index];
        }
        return -1;
    }
    
    size_t getSize() const { return data.size(); }
    size_t getReadCount() const { return readCount; }
    
    // const 반복자 제공
    vector<int>::const_iterator begin() const { return data.begin(); }
    vector<int>::const_iterator end() const { return data.end(); }
};

int main() {
    cout << "=== const 멤버 심화 ===" << endl;
    
    // 캐시 계산기 테스트
    cout << "\n--- 캐시 계산기 ---" << endl;
    CachedCalculator calc({1.0, 2.0, 3.0, 4.0, 5.0});
    
    cout << "첫 번째 평균 계산: " << calc.getAverage() << endl;
    cout << "두 번째 평균 계산: " << calc.getAverage() << endl;
    cout << "접근 횟수: " << calc.getAccessCount() << endl;
    
    // const 오버로딩 테스트
    cout << "\n--- const 오버로딩 ---" << endl;
    const CachedCalculator constCalc({10, 20, 30});
    
    cout << "const 객체 인덱스 접근: " << constCalc[1] << endl;
    cout << "const 객체 접근 횟수: " << constCalc.getAccessCount() << endl;
    
    // 일반 객체의 수정
    calc[0] = 100;  // non-const 버전 호출
    cout << "수정 후 평균: " << calc.getAverage() << endl;
    
    // 문자열 프로세서 테스트
    cout << "\n--- 문자열 프로세서 ---" << endl;
    StringProcessor processor("Hello World");
    
    cout << "원본: " << processor.charAt(0) << endl;
    cout << "대문자 변환: " << processor.getUpperCase() << endl;
    cout << "다시 대문자 변환: " << processor.getUpperCase() << endl;
    
    // 읽기 전용 데이터 테스트
    cout << "\n--- 읽기 전용 데이터 ---" << endl;
    const ReadOnlyData readOnlyData({100, 200, 300, 400});
    
    cout << "데이터 크기: " << readOnlyData.getSize() << endl;
    cout << "인덱스 1의 값: " << readOnlyData.getValue(1) << endl;
    cout << "인덱스 2의 값: " << readOnlyData.getValue(2) << endl;
    cout << "읽기 횟수: " << readOnlyData.getReadCount() << endl;
    
    // const 반복자 사용
    cout << "모든 데이터: ";
    for (auto it = readOnlyData.begin(); it != readOnlyData.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

---

## 3. 예제 03: 연산자 오버로딩 심화 (03_operator_overloading_advanced.cpp)

### 예제 정의
복합 대입 연산자, 증감 연산자, 함수 호출 연산자 등을 구현합니다.

```cpp
/*
주제: 연산자 오버로딩 심화 (Advanced Operator Overloading)
정의: 다양한 연산자를 오버로딩하여 사용자 정의 타입이 내장 타입처럼 자연스럽게 동작하도록 하는 기법

핵심 개념: 복합 대입 연산자, 전위/후위 증감, 함수 호출 연산자, 변환 연산자
정의:
- 복합 대입 연산자: +=, -=, *=, /= 등의 연산자 오버로딩
- 전위/후위 증감: ++obj와 obj++의 차이를 구현하는 방법
- 함수 호출 연산자: operator()를 오버로딩하여 객체를 함수처럼 사용
- 변환 연산자: 객체를 다른 타입으로 암시적 변환하는 연산자
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    
public:
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // 기본 산술 연산자
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    
    // 복합 대입 연산자들
    Vector3D& operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    
    Vector3D& operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    
    Vector3D& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    
    // 전위 증가 연산자
    Vector3D& operator++() {
        ++x; ++y; ++z;
        cout << "전위 증가 연산자 호출" << endl;
        return *this;
    }
    
    // 후위 증가 연산자 (int 매개변수로 구분)
    Vector3D operator++(int) {
        cout << "후위 증가 연산자 호출" << endl;
        Vector3D temp = *this;
        ++x; ++y; ++z;
        return temp;
    }
    
    // 배열 접근 연산자
    double& operator[](int index) {
        switch(index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw out_of_range("잘못된 인덱스");
        }
    }
    
    const double& operator[](int index) const {
        switch(index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw out_of_range("잘못된 인덱스");
        }
    }
    
    // 비교 연산자
    bool operator==(const Vector3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    
    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }
    
    // 출력 연산자 (friend 함수)
    friend ostream& operator<<(ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    
    // 입력 연산자 (friend 함수)
    friend istream& operator>>(istream& is, Vector3D& v) {
        is >> v.x >> v.y >> v.z;
        return is;
    }
    
    // 변환 연산자 - double로 암시적 변환 (벡터의 크기)
    operator double() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    // 명시적 변환 연산자 - string으로 변환
    explicit operator string() const {
        ostringstream oss;
        oss << "Vector3D(" << x << ", " << y << ", " << z << ")";
        return oss.str();
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

// 함수 객체 (Functor) 예제
class Multiplier {
private:
    double factor;
    
public:
    Multiplier(double f) : factor(f) {}
    
    // 함수 호출 연산자
    double operator()(double value) const {
        return value * factor;
    }
    
    // 다중 매개변수 함수 호출 연산자
    Vector3D operator()(const Vector3D& v) const {
        return Vector3D(v.getX() * factor, v.getY() * factor, v.getZ() * factor);
    }
};

// 스마트 포인터 스타일 클래스
template<typename T>
class SimpleSmartPtr {
private:
    T* ptr;
    
public:
    explicit SimpleSmartPtr(T* p = nullptr) : ptr(p) {}
    
    ~SimpleSmartPtr() {
        delete ptr;
    }
    
    // 복사 방지
    SimpleSmartPtr(const SimpleSmartPtr&) = delete;
    SimpleSmartPtr& operator=(const SimpleSmartPtr&) = delete;
    
    // 이동 생성자와 이동 대입 연산자
    SimpleSmartPtr(SimpleSmartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    SimpleSmartPtr& operator=(SimpleSmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // 역참조 연산자
    T& operator*() const {
        return *ptr;
    }
    
    // 멤버 접근 연산자
    T* operator->() const {
        return ptr;
    }
    
    // bool 변환 연산자
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    T* get() const { return ptr; }
};

int main() {
    cout << "=== 연산자 오버로딩 심화 ===" << endl;
    
    // Vector3D 테스트
    cout << "\n--- Vector3D 연산자 ---" << endl;
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    
    // 복합 대입 연산자
    v1 += v2;
    cout << "v1 += v2: " << v1 << endl;
    
    v1 *= 2;
    cout << "v1 *= 2: " << v1 << endl;
    
    // 증감 연산자 테스트
    cout << "\n--- 증감 연산자 ---" << endl;
    Vector3D v3(1, 1, 1);
    cout << "v3 = " << v3 << endl;
    
    Vector3D v4 = ++v3;  // 전위
    cout << "++v3, v3 = " << v3 << ", v4 = " << v4 << endl;
    
    Vector3D v5 = v3++;  // 후위
    cout << "v3++, v3 = " << v3 << ", v5 = " << v5 << endl;
    
    // 배열 접근 연산자
    cout << "\n--- 배열 접근 ---" << endl;
    cout << "v3[0] = " << v3[0] << ", v3[1] = " << v3[1] << ", v3[2] = " << v3[2] << endl;
    
    v3[0] = 10;
    cout << "v3[0] = 10 후: " << v3 << endl;
    
    // 변환 연산자
    cout << "\n--- 변환 연산자 ---" << endl;
    double magnitude = v3;  // 암시적 변환
    cout << "v3의 크기: " << magnitude << endl;
    
    string strRep = static_cast<string>(v3);  // 명시적 변환
    cout << "v3의 문자열 표현: " << strRep << endl;
    
    // 함수 객체 테스트
    cout << "\n--- 함수 객체 ---" << endl;
    Multiplier doubler(2.0);
    Multiplier tripler(3.0);
    
    cout << "doubler(5) = " << doubler(5) << endl;
    cout << "tripler(v1) = " << tripler(v1) << endl;
    
    // 스마트 포인터 테스트
    cout << "\n--- 스마트 포인터 ---" << endl;
    SimpleSmartPtr<Vector3D> smartPtr(new Vector3D(7, 8, 9));
    
    if (smartPtr) {
        cout << "스마트 포인터가 유효한 객체를 가리킴" << endl;
        cout << "*smartPtr = " << *smartPtr << endl;
        cout << "smartPtr->getX() = " << smartPtr->getX() << endl;
    }
    
    return 0;
}
```

---

## 4. 예제 04: 프렌드 클래스 (04_friend_classes.cpp)

### 예제 정의
프렌드 클래스를 활용한 밀접한 협력 관계의 클래스들을 구현합니다.

```cpp
/*
주제: 프렌드 클래스 (Friend Classes)
정의: 한 클래스가 다른 클래스의 private 및 protected 멤버에 접근할 수 있도록 허용하는 관계

핵심 개념: 클래스 간 협력, 캡슐화 완화, 상호 의존성, 접근 권한 부여
정의:
- 클래스 간 협력: 두 클래스가 밀접하게 연동하여 작업을 수행하는 관계
- 캡슐화 완화: 특정 클래스에 대해서만 private 접근을 허용하는 예외적 상황
- 상호 의존성: 클래스들이 서로의 내부 구현에 의존하는 관계
- 접근 권한 부여: friend 키워드를 통해 특별한 접근 권한을 부여하는 것
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 전방 선언
class BankAccount;
class TransactionLogger;

// 은행 계좌 클래스
class BankAccount {
    friend class BankManager;     // BankManager가 모든 private 멤버에 접근 가능
    friend class AuditSystem;     // AuditSystem도 접근 가능
    
private:
    string accountNumber;
    string ownerName;
    double balance;
    vector<string> transactionHistory;
    bool isActive;
    
public:
    BankAccount(string accNum, string name, double initialBalance) 
        : accountNumber(accNum), ownerName(name), balance(initialBalance), isActive(true) {
        transactionHistory.push_back("계좌 개설: " + to_string(initialBalance));
    }
    
    // 공개 인터페이스
    bool deposit(double amount) {
        if (!isActive || amount <= 0) return false;
        
        balance += amount;
        transactionHistory.push_back("입금: +" + to_string(amount));
        return true;
    }
    
    bool withdraw(double amount) {
        if (!isActive || amount <= 0 || amount > balance) return false;
        
        balance -= amount;
        transactionHistory.push_back("출금: -" + to_string(amount));
        return true;
    }
    
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
    string getOwnerName() const { return ownerName; }
    bool getStatus() const { return isActive; }
};

// 은행 매니저 클래스 (friend)
class BankManager {
private:
    string managerId;
    vector<BankAccount*> managedAccounts;
    
public:
    BankManager(string id) : managerId(id) {}
    
    void addAccount(BankAccount* account) {
        managedAccounts.push_back(account);
    }
    
    // friend이므로 private 멤버에 직접 접근 가능
    void freezeAccount(BankAccount* account) {
        account->isActive = false;  // private 멤버 직접 수정
        account->transactionHistory.push_back("계좌 동결 by " + managerId);
        cout << "계좌 " << account->accountNumber << " 동결됨" << endl;
    }
    
    void unfreezeAccount(BankAccount* account) {
        account->isActive = true;
        account->transactionHistory.push_back("계좌 해제 by " + managerId);
        cout << "계좌 " << account->accountNumber << " 동결 해제됨" << endl;
    }
    
    // 강제 입출금 (수수료, 이자 등)
    void forceTransaction(BankAccount* account, double amount, string reason) {
        account->balance += amount;  // private 멤버 직접 수정
        account->transactionHistory.push_back("매니저 거래: " + to_string(amount) + " (" + reason + ")");
        cout << "강제 거래 실행: " << amount << " (" << reason << ")" << endl;
    }
    
    void printAccountDetails(const BankAccount* account) {
        cout << "\n=== 계좌 상세 정보 ===" << endl;
        cout << "계좌번호: " << account->accountNumber << endl;
        cout << "소유자: " << account->ownerName << endl;
        cout << "잔액: " << account->balance << endl;
        cout << "상태: " << (account->isActive ? "활성" : "비활성") << endl;
        
        cout << "거래 내역:" << endl;
        for (const string& transaction : account->transactionHistory) {
            cout << "  - " << transaction << endl;
        }
    }
};

// 감사 시스템 클래스 (friend)
class AuditSystem {
private:
    string systemId;
    
public:
    AuditSystem(string id) : systemId(id) {}
    
    // 계좌 검증 (private 멤버 접근)
    bool auditAccount(const BankAccount* account) {
        cout << "\n[감사] 계좌 " << account->accountNumber << " 검사 중..." << endl;
        
        // private 멤버에 직접 접근하여 검증
        bool hasIssues = false;
        
        if (account->balance < 0) {
            cout << "[경고] 음수 잔액 발견: " << account->balance << endl;
            hasIssues = true;
        }
        
        if (account->transactionHistory.empty()) {
            cout << "[경고] 거래 내역이 없음" << endl;
            hasIssues = true;
        }
        
        if (account->ownerName.empty()) {
            cout << "[경고] 소유자 이름이 없음" << endl;
            hasIssues = true;
        }
        
        if (!hasIssues) {
            cout << "[정상] 계좌에 문제없음" << endl;
        }
        
        return !hasIssues;
    }
    
    // 모든 거래 내역 분석
    void analyzeTransactions(const BankAccount* account) {
        cout << "\n[분석] 거래 패턴 분석..." << endl;
        
        int deposits = 0, withdrawals = 0;
        for (const string& transaction : account->transactionHistory) {
            if (transaction.find("입금") != string::npos) deposits++;
            if (transaction.find("출금") != string::npos) withdrawals++;
        }
        
        cout << "총 거래 수: " << account->transactionHistory.size() << endl;
        cout << "입금 횟수: " << deposits << endl;
        cout << "출금 횟수: " << withdrawals << endl;
    }
};

// 일반 클래스 (friend가 아님)
class CustomerService {
public:
    // public 인터페이스만 사용 가능
    void checkBalance(const BankAccount* account) {
        cout << "\n[고객 서비스] 잔액 조회" << endl;
        cout << "계좌번호: " << account->getAccountNumber() << endl;
        cout << "잔액: " << account->getBalance() << endl;
        // cout << account->balance;  // 오류! private 멤버에 접근 불가
    }
    
    bool helpDeposit(BankAccount* account, double amount) {
        cout << "[고객 서비스] 입금 도움" << endl;
        return account->deposit(amount);  // public 함수만 사용
    }
};

int main() {
    cout << "=== 프렌드 클래스 활용 ===" << endl;
    
    // 계좌 생성
    BankAccount account("123-456-789", "김고객", 100000);
    
    // 매니저 생성 및 계좌 관리
    BankManager manager("MGR001");
    manager.addAccount(&account);
    
    // 일반 거래
    cout << "\n--- 일반 거래 ---" << endl;
    account.deposit(50000);
    account.withdraw(30000);
    
    manager.printAccountDetails(&account);
    
    // 매니저 권한 사용 (friend 클래스)
    cout << "\n--- 매니저 권한 사용 ---" << endl;
    manager.forceTransaction(&account, -1000, "계좌 관리 수수료");
    manager.forceTransaction(&account, 2000, "이자 지급");
    
    manager.freezeAccount(&account);
    
    // 동결된 계좌에서 거래 시도
    cout << "\n--- 동결된 계좌 거래 시도 ---" << endl;
    bool result = account.deposit(10000);
    cout << "입금 결과: " << (result ? "성공" : "실패") << endl;
    
    manager.unfreezeAccount(&account);
    
    // 감사 시스템 (friend 클래스)
    cout << "\n--- 감사 시스템 ---" << endl;
    AuditSystem auditor("AUDIT001");
    auditor.auditAccount(&account);
    auditor.analyzeTransactions(&account);
    
    // 고객 서비스 (friend가 아님)
    cout << "\n--- 고객 서비스 ---" << endl;
    CustomerService cs;
    cs.checkBalance(&account);
    cs.helpDeposit(&account, 25000);
    
    manager.printAccountDetails(&account);
    
    return 0;
}
```

---

## 5. 예제 05: 이동 의미론 심화 (05_move_semantics_advanced.cpp)

### 예제 정의
이동 생성자와 이동 대입 연산자의 고급 구현을 학습합니다.

```cpp
/*
주제: 이동 의미론 심화 (Advanced Move Semantics)
정의: 불필요한 복사를 피하고 자원을 효율적으로 이동시키는 C++11의 핵심 기능

핵심 개념: 이동 생성자, 이동 대입, noexcept, 우측값 참조, std::move
정의:
- 이동 생성자: 임시 객체나 이동 가능한 객체에서 자원을 빼앗아 새 객체를 생성
- 이동 대입: 기존 객체에 다른 객체의 자원을 이동시키는 대입 연산
- noexcept: 함수가 예외를 던지지 않음을 보장하는 키워드
- 우측값 참조(&&): 이동 가능한 객체를 참조하는 새로운 참조 타입
- std::move: 좌측값을 우측값으로 변환하여 이동을 강제하는 함수
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
using namespace std;

class BigResource {
private:
    size_t size;
    int* data;
    string name;
    
public:
    // 생성자
    BigResource(size_t s, string n) : size(s), name(n) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
        cout << "생성자: " << name << " (크기: " << size << ")" << endl;
    }
    
    // 복사 생성자
    BigResource(const BigResource& other) 
        : size(other.size), name(other.name + "_copy") {
        data = new int[size];
        copy(other.data, other.data + size, data);
        cout << "복사 생성자: " << name << " (크기: " << size << ")" << endl;
    }
    
    // 이동 생성자
    BigResource(BigResource&& other) noexcept
        : size(other.size), data(other.data), name(other.name + "_moved") {
        other.data = nullptr;
        other.size = 0;
        cout << "이동 생성자: " << name << " (자원 이동)" << endl;
    }
    
    // 복사 대입 연산자
    BigResource& operator=(const BigResource& other) {
        if (this != &other) {
            delete[] data;
            
            size = other.size;
            name = other.name + "_assigned";
            data = new int[size];
            copy(other.data, other.data + size, data);
            cout << "복사 대입: " << name << " (크기: " << size << ")" << endl;
        }
        return *this;
    }
    
    // 이동 대입 연산자
    BigResource& operator=(BigResource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            size = other.size;
            data = other.data;
            name = other.name + "_move_assigned";
            
            other.data = nullptr;
            other.size = 0;
            cout << "이동 대입: " << name << " (자원 이동)" << endl;
        }
        return *this;
    }
    
    // 소멸자
    ~BigResource() {
        if (data) {
            cout << "소멸자: " << name << " 해제" << endl;
            delete[] data;
        } else {
            cout << "소멸자: " << name << " (이미 이동됨)" << endl;
        }
    }
    
    void display() const {
        if (data && size > 0) {
            cout << name << ": 첫 번째 요소 = " << data[0] 
                 << ", 크기 = " << size << endl;
        } else {
            cout << name << ": 자원 없음" << endl;
        }
    }
    
    size_t getSize() const { return size; }
    string getName() const { return name; }
};

// 이동 전용 클래스 (복사 불가)
class MoveOnlyResource {
private:
    unique_ptr<int[]> data;
    size_t size;
    string identifier;
    
public:
    // 생성자
    explicit MoveOnlyResource(size_t s, string id = "MoveOnly") 
        : data(make_unique<int[]>(s)), size(s), identifier(id) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i * 2);
        }
        cout << "MoveOnly 생성: " << identifier << " (크기: " << size << ")" << endl;
    }
    
    // 복사 생성자와 복사 대입 연산자 삭제
    MoveOnlyResource(const MoveOnlyResource&) = delete;
    MoveOnlyResource& operator=(const MoveOnlyResource&) = delete;
    
    // 이동 생성자
    MoveOnlyResource(MoveOnlyResource&& other) noexcept
        : data(move(other.data)), size(other.size), 
          identifier(other.identifier + "_moved") {
        other.size = 0;
        cout << "MoveOnly 이동 생성: " << identifier << endl;
    }
    
    // 이동 대입 연산자
    MoveOnlyResource& operator=(MoveOnlyResource&& other) noexcept {
        if (this != &other) {
            data = move(other.data);
            size = other.size;
            identifier = other.identifier + "_move_assigned";
            other.size = 0;
            cout << "MoveOnly 이동 대입: " << identifier << endl;
        }
        return *this;
    }
    
    void display() const {
        if (data && size > 0) {
            cout << identifier << ": 첫 번째 요소 = " << data[0] 
                 << ", 크기 = " << size << endl;
        } else {
            cout << identifier << ": 자원 없음" << endl;
        }
    }
    
    size_t getSize() const { return size; }
};

// 팩토리 함수 (이동 반환)
BigResource createBigResource(size_t size, string name) {
    return BigResource(size, name);  // 이동 반환
}

MoveOnlyResource createMoveOnlyResource(size_t size) {
    return MoveOnlyResource(size, "Factory");  // 이동 반환
}

// 이동을 활용하는 컨테이너 클래스
template<typename T>
class SimpleVector {
private:
    T* data;
    size_t capacity;
    size_t count;
    
public:
    SimpleVector() : data(nullptr), capacity(0), count(0) {}
    
    explicit SimpleVector(size_t cap) : capacity(cap), count(0) {
        data = static_cast<T*>(operator new(sizeof(T) * capacity));
    }
    
    ~SimpleVector() {
        clear();
        operator delete(data);
    }
    
    // 복사 생성자
    SimpleVector(const SimpleVector& other) : capacity(other.capacity), count(other.count) {
        data = static_cast<T*>(operator new(sizeof(T) * capacity));
        for (size_t i = 0; i < count; ++i) {
            new (data + i) T(other.data[i]);
        }
    }
    
    // 이동 생성자
    SimpleVector(SimpleVector&& other) noexcept
        : data(other.data), capacity(other.capacity), count(other.count) {
        other.data = nullptr;
        other.capacity = 0;
        other.count = 0;
    }
    
    // 완벽한 전달을 사용한 emplace_back
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (count >= capacity) {
            resize();
        }
        new (data + count) T(forward<Args>(args)...);
        ++count;
    }
    
    // 이동을 사용한 push_back
    void push_back(T&& item) {
        if (count >= capacity) {
            resize();
        }
        new (data + count) T(move(item));
        ++count;
    }
    
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
    
    size_t size() const { return count; }
    
private:
    void clear() {
        for (size_t i = 0; i < count; ++i) {
            data[i].~T();
        }
        count = 0;
    }
    
    void resize() {
        size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
        T* newData = static_cast<T*>(operator new(sizeof(T) * newCapacity));
        
        for (size_t i = 0; i < count; ++i) {
            new (newData + i) T(move(data[i]));
            data[i].~T();
        }
        
        operator delete(data);
        data = newData;
        capacity = newCapacity;
    }
};

int main() {
    cout << "=== 이동 의미론 심화 ===" << endl;
    
    // 기본 이동 테스트
    cout << "\n--- 기본 이동 테스트 ---" << endl;
    BigResource res1(5, "Resource1");
    
    BigResource res2 = move(res1);  // 이동 생성자
    res1.display();
    res2.display();
    
    // 팩토리 함수 이동 반환
    cout << "\n--- 팩토리 함수 ---" << endl;
    BigResource res3 = createBigResource(3, "Factory");
    res3.display();
    
    // 이동 대입
    cout << "\n--- 이동 대입 ---" << endl;
    BigResource res4(2, "Resource4");
    res4 = createBigResource(4, "NewResource");
    res4.display();
    
    // 이동 전용 클래스
    cout << "\n--- 이동 전용 클래스 ---" << endl;
    MoveOnlyResource moveRes1(3, "MoveRes1");
    moveRes1.display();
    
    MoveOnlyResource moveRes2 = move(moveRes1);
    moveRes1.display();
    moveRes2.display();
    
    // 이동을 활용하는 컨테이너
    cout << "\n--- 이동 활용 컨테이너 ---" << endl;
    SimpleVector<BigResource> vec(2);
    
    vec.emplace_back(3, "VecItem1");  // 완벽한 전달로 생성
    vec.push_back(createBigResource(2, "VecItem2"));  // 이동으로 추가
    
    cout << "벡터 내용:" << endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i].display();
    }
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 6. 예제 06: 완벽한 전달 (06_perfect_forwarding.cpp)

### 예제 정의
템플릿과 우측값 참조를 활용한 완벽한 전달을 구현합니다.

```cpp
/*
주제: 완벽한 전달 (Perfect Forwarding)
정의: 함수 템플릿에서 매개변수를 원래의 값 범주(좌측값/우측값)를 보존하며 다른 함수에 전달하는 기법

핵심 개념: 유니버설 참조, std::forward, 참조 축약, 값 범주 보존
정의:
- 유니버설 참조: T&& 형태로 좌측값과 우측값을 모두 받을 수 있는 참조
- std::forward: 매개변수의 원래 값 범주를 보존하여 전달하는 함수
- 참조 축약: 참조의 참조가 하나의 참조로 축약되는 규칙
- 값 범주 보존: 좌측값은 좌측값으로, 우측값은 우측값으로 전달하는 것
*/

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

// 테스트용 클래스
class TestObject {
private:
    string name;
    int value;
    
public:
    // 다양한 생성자
    TestObject() : name("default"), value(0) {
        cout << "TestObject 기본 생성자: " << name << endl;
    }
    
    TestObject(const string& n) : name(n), value(0) {
        cout << "TestObject 생성자(const string&): " << name << endl;
    }
    
    TestObject(string&& n) : name(move(n)), value(0) {
        cout << "TestObject 생성자(string&&): " << name << endl;
    }
    
    TestObject(const string& n, int v) : name(n), value(v) {
        cout << "TestObject 생성자(const string&, int): " << name << ", " << value << endl;
    }
    
    TestObject(string&& n, int v) : name(move(n)), value(v) {
        cout << "TestObject 생성자(string&&, int): " << name << ", " << value << endl;
    }
    
    // 복사 생성자
    TestObject(const TestObject& other) : name(other.name), value(other.value) {
        cout << "TestObject 복사 생성자: " << name << endl;
    }
    
    // 이동 생성자
    TestObject(TestObject&& other) noexcept : name(move(other.name)), value(other.value) {
        cout << "TestObject 이동 생성자: " << name << endl;
    }
    
    ~TestObject() {
        cout << "TestObject 소멸자: " << name << endl;
    }
    
    void display() const {
        cout << "TestObject: " << name << ", value: " << value << endl;
    }
    
    const string& getName() const { return name; }
    int getValue() const { return value; }
};

// 완벽한 전달을 사용하지 않는 경우 (문제가 있는 구현)
template<typename T>
unique_ptr<T> makeUniqueOld(const T& obj) {
    return make_unique<T>(obj);  // 항상 복사 생성자 호출
}

// 완벽한 전달을 사용하는 make_unique 구현
template<typename T, typename... Args>
unique_ptr<T> makeUniquePerfect(Args&&... args) {
    return make_unique<T>(forward<Args>(args)...);
}

// 완벽한 전달을 사용하는 팩토리 함수
template<typename T, typename... Args>
T createObject(Args&&... args) {
    cout << "createObject 호출" << endl;
    return T(forward<Args>(args)...);
}

// 함수 오버로딩으로 값 범주 확인
void processValue(const string& s) {
    cout << "processValue(const string&): " << s << endl;
}

void processValue(string&& s) {
    cout << "processValue(string&&): " << s << endl;
}

// 완벽한 전달을 사용하는 래퍼 함수
template<typename T>
void forwardToProcess(T&& value) {
    cout << "forwardToProcess 호출 - ";
    processValue(forward<T>(value));
}

// 가변 인자 완벽한 전달
template<typename Func, typename... Args>
auto callFunction(Func&& func, Args&&... args) -> decltype(func(forward<Args>(args)...)) {
    cout << "callFunction: 함수 호출 전달" << endl;
    return func(forward<Args>(args)...);
}

// 테스트 함수들
int multiply(int a, int b) {
    cout << "multiply(" << a << ", " << b << ") = " << (a * b) << endl;
    return a * b;
}

string concatenate(const string& a, const string& b) {
    string result = a + b;
    cout << "concatenate(\"" << a << "\", \"" << b << "\") = \"" << result << "\"" << endl;
    return result;
}

// 컨테이너에 완벽한 전달로 요소 추가
template<typename Container, typename... Args>
void emplaceBack(Container& container, Args&&... args) {
    container.emplace_back(forward<Args>(args)...);
}

int main() {
    cout << "=== 완벽한 전달 ===" << endl;
    
    // 값 범주 보존 테스트
    cout << "\n--- 값 범주 보존 ---" << endl;
    string lvalue = "좌측값";
    
    cout << "좌측값 전달:" << endl;
    forwardToProcess(lvalue);
    
    cout << "우측값 전달:" << endl;
    forwardToProcess(string("우측값"));
    forwardToProcess(move(lvalue));
    
    // 완벽한 전달을 사용한 객체 생성
    cout << "\n--- 완벽한 전달 객체 생성 ---" << endl;
    
    // 문제가 있는 구현 (항상 복사)
    cout << "기존 방식 (복사 발생):" << endl;
    TestObject obj1("Original");
    auto ptr1 = makeUniqueOld(obj1);
    
    // 완벽한 전달 구현
    cout << "\n완벽한 전달 방식:" << endl;
    auto ptr2 = makeUniquePerfect<TestObject>("Perfect", 42);
    auto ptr3 = makeUniquePerfect<TestObject>(string("Moved"), 99);
    
    ptr2->display();
    ptr3->display();
    
    // createObject 함수 테스트
    cout << "\n--- createObject 테스트 ---" << endl;
    TestObject obj2 = createObject<TestObject>("Created", 123);
    obj2.display();
    
    string temp = "Temporary";
    TestObject obj3 = createObject<TestObject>(move(temp));
    obj3.display();
    
    // 함수 호출 전달
    cout << "\n--- 함수 호출 전달 ---" << endl;
    int result1 = callFunction(multiply, 6, 7);
    string result2 = callFunction(concatenate, string("Hello"), string(" World"));
    
    // 컨테이너 완벽한 전달
    cout << "\n--- 컨테이너 완벽한 전달 ---" << endl;
    vector<TestObject> vec;
    
    cout << "emplace_back으로 직접 생성:" << endl;
    emplaceBack(vec, "Vector1", 10);
    emplaceBack(vec, string("Vector2"), 20);
    
    cout << "\n벡터 내용:" << endl;
    for (const auto& item : vec) {
        item.display();
    }
    
    // 람다와 완벽한 전달
    cout << "\n--- 람다와 완벽한 전달 ---" << endl;
    auto lambda = [](auto&&... args) {
        cout << "람다 함수: 매개변수 개수 = " << sizeof...(args) << endl;
        return createObject<TestObject>(forward<decltype(args)>(args)...);
    };
    
    TestObject lambdaObj = lambda("Lambda", 999);
    lambdaObj.display();
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 7. 예제 07: 우측값 참조 심화 (07_rvalue_reference_advanced.cpp)

### 예제 정의
우측값 참조의 고급 사용법과 참조 축약 규칙을 학습합니다.

```cpp
/*
주제: 우측값 참조 심화 (Advanced Rvalue References)
정의: 임시 객체와 이동 가능한 객체를 효율적으로 처리하기 위한 C++11의 고급 참조 시스템

핵심 개념: 우측값 참조, 참조 축약, 값 범주, 이동 캡처
정의:
- 우측값 참조(&&): 우측값(임시 객체)을 참조할 수 있는 새로운 참조 타입
- 참조 축약: T& &, T& &&, T&& & 등이 모두 T&가 되는 규칙
- 값 범주: 좌측값(lvalue), 우측값(rvalue), xvalue 등의 표현식 분류
- 이동 캡처: 람다에서 외부 변수를 이동으로 캡처하는 기법
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <functional>
using namespace std;

// 값 범주를 확인하는 유틸리티
class ValueCategoryTester {
private:
    string name;
    
public:
    ValueCategoryTester(string n) : name(n) {
        cout << "생성자: " << name << endl;
    }
    
    ValueCategoryTester(const ValueCategoryTester& other) : name(other.name + "_copy") {
        cout << "복사 생성자: " << name << endl;
    }
    
    ValueCategoryTester(ValueCategoryTester&& other) noexcept : name(other.name + "_moved") {
        cout << "이동 생성자: " << name << endl;
    }
    
    ValueCategoryTester& operator=(const ValueCategoryTester& other) {
        name = other.name + "_assigned";
        cout << "복사 대입: " << name << endl;
        return *this;
    }
    
    ValueCategoryTester& operator=(ValueCategoryTester&& other) noexcept {
        name = other.name + "_move_assigned";
        cout << "이동 대입: " << name << endl;
        return *this;
    }
    
    ~ValueCategoryTester() {
        cout << "소멸자: " << name << endl;
    }
    
    const string& getName() const { return name; }
};

// 함수 오버로딩으로 값 범주 구분
void testValueCategory(const ValueCategoryTester& obj) {
    cout << "좌측값(const&): " << obj.getName() << endl;
}

void testValueCategory(ValueCategoryTester&& obj) {
    cout << "우측값(&&): " << obj.getName() << endl;
}

// 템플릿으로 유니버설 참조 테스트
template<typename T>
void universalReference(T&& param) {
    cout << "유니버설 참조 호출" << endl;
    testValueCategory(forward<T>(param));
}

// 참조 축약 규칙 시연
template<typename T>
void referenceCollapsing() {
    cout << "\n=== 참조 축약 규칙 ===" << endl;
    
    // T가 int&일 때: T&& = int& && = int& (참조 축약)
    // T가 int일 때: T&& = int&&
    if (is_lvalue_reference_v<T&&>) {
        cout << "T&&는 좌측값 참조입니다." << endl;
    } else {
        cout << "T&&는 우측값 참조입니다." << endl;
    }
}

// 이동 의미론을 활용한 빌더 패턴
class StringBuilder {
private:
    string content;
    
public:
    StringBuilder() = default;
    
    // 좌측값 참조 버전
    StringBuilder& append(const string& str) & {
        content += str;
        cout << "좌측값 append: \"" << str << "\"" << endl;
        return *this;
    }
    
    // 우측값 참조 버전 (체이닝 최적화)
    StringBuilder&& append(const string& str) && {
        content += str;
        cout << "우측값 append: \"" << str << "\"" << endl;
        return move(*this);
    }
    
    string build() && {
        cout << "build() 호출 (이동)" << endl;
        return move(content);
    }
    
    const string& build() const & {
        cout << "build() 호출 (복사)" << endl;
        return content;
    }
};

// 조건부 이동 클래스
template<bool ShouldMove>
class ConditionalMover {
private:
    vector<string> data;
    
public:
    template<typename T>
    void addData(T&& item) {
        if constexpr (ShouldMove) {
            data.emplace_back(forward<T>(item));
            cout << "이동으로 추가" << endl;
        } else {
            data.emplace_back(item);
            cout << "복사로 추가" << endl;
        }
    }
    
    void printData() const {
        cout << "저장된 데이터: ";
        for (const auto& item : data) {
            cout << "\"" << item << "\" ";
        }
        cout << endl;
    }
};

// 이동 캡처를 사용하는 함수
auto createMoveCaptureLambda(ValueCategoryTester obj) {
    cout << "람다 생성 중..." << endl;
    
    // C++14 이동 캡처
    return [captured = move(obj)](const string& suffix) mutable {
        cout << "람다 실행: " << captured.getName() << suffix << endl;
        return move(captured);
    };
}

// 완벽한 전달과 우측값 참조 조합
template<typename Container, typename... Args>
auto emplaceAndReturn(Container& container, Args&&... args) -> decltype(auto) {
    container.emplace_back(forward<Args>(args)...);
    return container.back();
}

int main() {
    cout << "=== 우측값 참조 심화 ===" << endl;
    
    // 기본 값 범주 테스트
    cout << "\n--- 값 범주 기본 테스트 ---" << endl;
    ValueCategoryTester obj1("Object1");
    
    testValueCategory(obj1);                              // 좌측값
    testValueCategory(ValueCategoryTester("Temporary")); // 우측값
    testValueCategory(move(obj1));                       // xvalue (우측값)
    
    // 유니버설 참조 테스트
    cout << "\n--- 유니버설 참조 테스트 ---" << endl;
    ValueCategoryTester obj2("Object2");
    
    universalReference(obj2);                              // T = ValueCategoryTester&
    universalReference(ValueCategoryTester("Universal")); // T = ValueCategoryTester
    
    // 참조 축약 규칙
    cout << "\n--- 참조 축약 규칙 ---" << endl;
    int x = 42;
    int& lref = x;
    
    referenceCollapsing<int>();    // T = int, T&& = int&&
    referenceCollapsing<int&>();   // T = int&, T&& = int& && = int&
    
    // 빌더 패턴 테스트
    cout << "\n--- 빌더 패턴 ---" << endl;
    StringBuilder builder;
    
    // 좌측값에 대한 체이닝
    string result1 = builder.append("Hello").append(" ").append("World").build();
    cout << "결과1: \"" << result1 << "\"" << endl;
    
    // 우측값에 대한 체이닝 (최적화됨)
    string result2 = StringBuilder()
        .append("Fast")
        .append(" ")
        .append("Builder")
        .build();
    cout << "결과2: \"" << result2 << "\"" << endl;
    
    // 조건부 이동 테스트
    cout << "\n--- 조건부 이동 ---" << endl;
    ConditionalMover<true> mover;
    ConditionalMover<false> copier;
    
    string data = "TestData";
    
    cout << "이동 버전:" << endl;
    mover.addData(data);
    mover.addData(string("TempData"));
    mover.printData();
    
    cout << "복사 버전:" << endl;
    copier.addData(data);
    copier.addData(string("TempData"));
    copier.printData();
    
    // 이동 캡처 람다
    cout << "\n--- 이동 캡처 람다 ---" << endl;
    ValueCategoryTester objForCapture("CaptureMe");
    auto lambda = createMoveCaptureLambda(move(objForCapture));
    
    cout << "람다 호출:" << endl;
    ValueCategoryTester result = lambda("_executed");
    
    // 완벽한 전달과 참조 조합
    cout << "\n--- 완벽한 전달 조합 ---" << endl;
    vector<ValueCategoryTester> container;
    
    cout << "좌측값으로 추가:" << endl;
    ValueCategoryTester obj3("ContainerItem");
    auto& ref1 = emplaceAndReturn(container, obj3);
    cout << "반환된 참조: " << ref1.getName() << endl;
    
    cout << "우측값으로 추가:" << endl;
    auto& ref2 = emplaceAndReturn(container, ValueCategoryTester("DirectAdd"));
    cout << "반환된 참조: " << ref2.getName() << endl;
    
    // 이동 전용 스마트 포인터 이동
    cout << "\n--- 스마트 포인터 이동 ---" << endl;
    auto ptr1 = make_unique<ValueCategoryTester>("SmartPtr1");
    cout << "포인터1 생성 완료" << endl;
    
    auto ptr2 = move(ptr1);  // 소유권 이동
    cout << "포인터2로 이동 완료" << endl;
    
    if (!ptr1) {
        cout << "포인터1은 nullptr" << endl;
    }
    if (ptr2) {
        cout << "포인터2는 유효: " << ptr2->getName() << endl;
    }
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 10. 예제 10: 종합 실습 - 스마트 포인터 구현 (10_smart_pointer_implementation.cpp)

### 예제 정의
unique_ptr과 shared_ptr의 간단한 버전을 직접 구현하여 스마트 포인터의 동작 원리를 이해합니다.

```cpp
/*
주제: 스마트 포인터 구현 (Smart Pointer Implementation)
정의: 자동 메모리 관리를 제공하는 스마트 포인터를 직접 구현하여 RAII와 이동 의미론을 종합적으로 활용

핵심 개념: 독점 소유권, 공유 소유권, 참조 카운팅, 자동 해제
정의:
- 독점 소유권: unique_ptr처럼 하나의 포인터만이 객체를 소유하는 방식
- 공유 소유권: shared_ptr처럼 여러 포인터가 객체를 공유하는 방식
- 참조 카운팅: 객체를 참조하는 포인터의 개수를 추적하는 메커니즘
- 자동 해제: 더 이상 참조되지 않을 때 자동으로 메모리를 해제하는 기능
*/

#include <iostream>
#include <string>
#include <utility>
#include <atomic>
using namespace std;

// 간단한 unique_ptr 구현
template<typename T>
class SimpleUniquePtr {
private:
    T* ptr;
    
public:
    // 생성자
    explicit SimpleUniquePtr(T* p = nullptr) : ptr(p) {
        cout << "SimpleUniquePtr 생성: " << ptr << endl;
    }
    
    // 소멸자
    ~SimpleUniquePtr() {
        if (ptr) {
            cout << "SimpleUniquePtr 소멸: " << ptr << endl;
            delete ptr;
        }
    }
    
    // 복사 생성자와 복사 대입 연산자 삭제
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;
    
    // 이동 생성자
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
        cout << "SimpleUniquePtr 이동 생성: " << ptr << endl;
    }
    
    // 이동 대입 연산자
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
            cout << "SimpleUniquePtr 이동 대입: " << ptr << endl;
        }
        return *this;
    }
    
    // 역참조 연산자
    T& operator*() const {
        return *ptr;
    }
    
    // 멤버 접근 연산자
    T* operator->() const {
        return ptr;
    }
    
    // bool 변환 연산자
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    // get 함수
    T* get() const {
        return ptr;
    }
    
    // release 함수 (소유권 포기)
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        cout << "SimpleUniquePtr 소유권 해제: " << temp << endl;
        return temp;
    }
    
    // reset 함수
    void reset(T* newPtr = nullptr) {
        if (ptr != newPtr) {
            delete ptr;
            ptr = newPtr;
            cout << "SimpleUniquePtr 재설정: " << ptr << endl;
        }
    }
};

// make_unique 구현
template<typename T, typename... Args>
SimpleUniquePtr<T> makeSimpleUnique(Args&&... args) {
    return SimpleUniquePtr<T>(new T(forward<Args>(args)...));
}

// 참조 카운팅을 위한 제어 블록
struct ControlBlock {
    atomic<int> refCount;
    
    ControlBlock() : refCount(1) {
        cout << "ControlBlock 생성, 참조 카운트: " << refCount.load() << endl;
    }
    
    ~ControlBlock() {
        cout << "ControlBlock 소멸" << endl;
    }
    
    void addRef() {
        refCount++;
        cout << "참조 추가, 현재 카운트: " << refCount.load() << endl;
    }
    
    bool removeRef() {
        int count = --refCount;
        cout << "참조 제거, 현재 카운트: " << count << endl;
        return count == 0;
    }
    
    int getCount() const {
        return refCount.load();
    }
};

// 간단한 shared_ptr 구현
template<typename T>
class SimpleSharedPtr {
private:
    T* ptr;
    ControlBlock* control;
    
    void release() {
        if (control && control->removeRef()) {
            delete ptr;
            delete control;
            cout << "SimpleSharedPtr: 객체와 제어 블록 삭제" << endl;
        }
        ptr = nullptr;
        control = nullptr;
    }
    
public:
    // 생성자
    explicit SimpleSharedPtr(T* p = nullptr) : ptr(p), control(nullptr) {
        if (ptr) {
            control = new ControlBlock();
        }
        cout << "SimpleSharedPtr 생성: " << ptr << endl;
    }
    
    // 소멸자
    ~SimpleSharedPtr() {
        cout << "SimpleSharedPtr 소멸자 호출: " << ptr << endl;
        release();
    }
    
    // 복사 생성자
    SimpleSharedPtr(const SimpleSharedPtr& other) : ptr(other.ptr), control(other.control) {
        if (control) {
            control->addRef();
        }
        cout << "SimpleSharedPtr 복사 생성: " << ptr << endl;
    }
    
    // 복사 대입 연산자
    SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            if (control) {
                control->addRef();
            }
            cout << "SimpleSharedPtr 복사 대입: " << ptr << endl;
        }
        return *this;
    }
    
    // 이동 생성자
    SimpleSharedPtr(SimpleSharedPtr&& other) noexcept : ptr(other.ptr), control(other.control) {
        other.ptr = nullptr;
        other.control = nullptr;
        cout << "SimpleSharedPtr 이동 생성: " << ptr << endl;
    }
    
    // 이동 대입 연산자
    SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
            cout << "SimpleSharedPtr 이동 대입: " << ptr << endl;
        }
        return *this;
    }
    
    // 역참조 연산자
    T& operator*() const {
        return *ptr;
    }
    
    // 멤버 접근 연산자
    T* operator->() const {
        return ptr;
    }
    
    // bool 변환 연산자
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    // get 함수
    T* get() const {
        return ptr;
    }
    
    // use_count 함수
    int use_count() const {
        return control ? control->getCount() : 0;
    }
    
    // reset 함수
    void reset(T* newPtr = nullptr) {
        release();
        ptr = newPtr;
        if (ptr) {
            control = new ControlBlock();
        }
    }
};

// make_shared 구현
template<typename T, typename... Args>
SimpleSharedPtr<T> makeSimpleShared(Args&&... args) {
    return SimpleSharedPtr<T>(new T(forward<Args>(args)...));
}

// 테스트용 클래스
class TestResource {
private:
    string name;
    int value;
    
public:
    TestResource(string n, int v) : name(move(n)), value(v) {
        cout << "TestResource 생성: " << name << " (" << value << ")" << endl;
    }
    
    ~TestResource() {
        cout << "TestResource 소멸: " << name << " (" << value << ")" << endl;
    }
    
    void display() const {
        cout << "TestResource: " << name << " = " << value << endl;
    }
    
    void setValue(int v) {
        value = v;
    }
    
    const string& getName() const { return name; }
    int getValue() const { return value; }
};

void testUniquePtr() {
    cout << "\n=== SimpleUniquePtr 테스트 ===" << endl;
    
    // 기본 사용
    {
        auto ptr1 = makeSimpleUnique<TestResource>("Unique1", 100);
        ptr1->display();
        ptr1->setValue(200);
        ptr1->display();
    } // 자동 소멸
    
    // 이동 의미론
    cout << "\n--- 이동 테스트 ---" << endl;
    auto ptr2 = makeSimpleUnique<TestResource>("Unique2", 300);
    auto ptr3 = move(ptr2);
    
    cout << "ptr2가 유효한가? " << static_cast<bool>(ptr2) << endl;
    cout << "ptr3가 유효한가? " << static_cast<bool>(ptr3) << endl;
    
    if (ptr3) {
        ptr3->display();
    }
    
    // release와 reset
    cout << "\n--- release/reset 테스트 ---" << endl;
    auto ptr4 = makeSimpleUnique<TestResource>("Unique4", 400);
    TestResource* rawPtr = ptr4.release();
    
    cout << "release 후 ptr4 유효성: " << static_cast<bool>(ptr4) << endl;
    cout << "원시 포인터로 접근: ";
    rawPtr->display();
    
    ptr4.reset(rawPtr);  // 다시 관리 시작
    ptr4->display();
}

void testSharedPtr() {
    cout << "\n=== SimpleSharedPtr 테스트 ===" << endl;
    
    // 기본 사용과 참조 카운팅
    {
        auto ptr1 = makeSimpleShared<TestResource>("Shared1", 500);
        cout << "ptr1 참조 카운트: " << ptr1.use_count() << endl;
        
        {
            auto ptr2 = ptr1;  // 복사
            cout << "복사 후 참조 카운트: " << ptr1.use_count() << endl;
            
            auto ptr3 = ptr1;  // 또 다른 복사
            cout << "두 번째 복사 후 참조 카운트: " << ptr1.use_count() << endl;
            
            ptr2->setValue(600);
            ptr1->display();
            ptr3->display();
            
        } // ptr2, ptr3 소멸
        
        cout << "내부 스코프 종료 후 참조 카운트: " << ptr1.use_count() << endl;
        ptr1->display();
        
    } // ptr1 소멸, 객체 해제
    
    // 이동 의미론
    cout << "\n--- 공유 포인터 이동 테스트 ---" << endl;
    auto ptr4 = makeSimpleShared<TestResource>("Shared2", 700);
    auto ptr5 = ptr4;
    cout << "이동 전 참조 카운트: " << ptr4.use_count() << endl;
    
    auto ptr6 = move(ptr4);
    cout << "이동 후 ptr4 참조 카운트: " << (ptr4 ? ptr4.use_count() : 0) << endl;
    cout << "이동 후 ptr5 참조 카운트: " << ptr5.use_count() << endl;
    cout << "이동 후 ptr6 참조 카운트: " << ptr6.use_count() << endl;
}

void testMixedUsage() {
    cout << "\n=== 혼합 사용 테스트 ===" << endl;
    
    // 벡터에 스마트 포인터 저장
    vector<SimpleUniquePtr<TestResource>> uniqueVec;
    vector<SimpleSharedPtr<TestResource>> sharedVec;
    
    // unique_ptr 벡터
    uniqueVec.push_back(makeSimpleUnique<TestResource>("Vec1", 800));
    uniqueVec.push_back(makeSimpleUnique<TestResource>("Vec2", 900));
    
    cout << "Unique 벡터 내용:" << endl;
    for (const auto& ptr : uniqueVec) {
        ptr->display();
    }
    
    // shared_ptr 벡터
    auto shared1 = makeSimpleShared<TestResource>("SharedVec1", 1000);
    auto shared2 = makeSimpleShared<TestResource>("SharedVec2", 1100);
    
    sharedVec.push_back(shared1);
    sharedVec.push_back(shared2);
    sharedVec.push_back(shared1);  // 같은 객체를 다시 추가
    
    cout << "\nShared 벡터 내용:" << endl;
    for (size_t i = 0; i < sharedVec.size(); ++i) {
        cout << "인덱스 " << i << " (참조 카운트: " << sharedVec[i].use_count() << "): ";
        sharedVec[i]->display();
    }
}

int main() {
    cout << "=== 스마트 포인터 구현 ===" << endl;
    
    testUniquePtr();
    testSharedPtr();
    testMixedUsage();
    
    cout << "\n=== 프로그램 종료 ===" << endl;
    
    return 0;
}
```

---

## 이번 챕터 요약

### 학습한 내용
**고급 정적 멤버**: 싱글톤 패턴, 팩토리 패턴, 객체 카운팅
**const 심화**: const 정확성, mutable, const 오버로딩
**연산자 오버로딩 고급**: 복합 대입, 증감, 함수 호출, 변환 연산자
**프렌드 관계**: 프렌드 클래스, 클래스 간 협력
**이동 의미론**: 이동 생성자, 이동 대입, 완벽한 전달
**현대 C++ 기능**: auto, 람다, constexpr, 스마트 포인터
**RAII 패턴**: 자원 관리, 예외 안전성, 스코프 기반 해제
**스마트 포인터 구현**: unique_ptr, shared_ptr 동작 원리

### 핵심 키워드
- 고급 기능: `static`, `mutable`, `friend`, `constexpr`
- 이동 의미론: `&&`, `std::move`, `std::forward`, `noexcept`
- 현대 C++: `auto`, `lambda`, `nullptr`, `스마트 포인터`
- 자원 관리: `RAII`, `unique_ptr`, `shared_ptr`, 예외 안전성

### 설계 원칙
1. **RAII**: 자원 획득은 초기화, 해제는 소멸자에서
2. **이동 우선**: 불필요한 복사 피하기
3. **const 정확성**: 변경되지 않는 것은 const로
4. **예외 안전성**: 예외 상황에서도 자원 누수 방지
5. **현대적 기법**: 원시 포인터 대신 스마트 포인터 사용

---

## 실습 과제

### 과제 1: 커스텀 스마트 포인터
weak_ptr 기능을 포함한 스마트 포인터 시스템을 구현하세요.

### 과제 2: 자원 관리 클래스
데이터베이스 연결, 네트워크 소켓 등을 관리하는 RAII 클래스를 구현하세요.

### 과제 3: 고급 연산자 오버로딩
행렬 연산을 지원하는 Matrix 클래스를 완전한 연산자 오버로딩과 함께 구현하세요.

### 과제 4: 팩토리 패턴 시스템
다양한 타입의 객체를 생성하고 관리하는 팩토리 시스템을 현대적 C++ 기능으로 구현하세요.

---

## 다음 챕터 예고
**Chapter 06: 상속과 다형성**에서는 객체지향의 핵심인 상속 관계와 다형성을 통한 유연한 설계 방법을 학습합니다.

### 예제 정의
자원 관리를 위한 RAII 패턴의 구현과 활용을 학습합니다.

```cpp
/*
주제: RAII 패턴 (Resource Acquisition Is Initialization)
정의: 자원의 획득과 해제를 객체의 생성과 소멸에 연결하여 자동으로 관리하는 C++의 핵심 패턴

핵심 개념: 자원 관리, 예외 안전성, 소멸자 보장, 스코프 기반 해제
정의:
- 자원 관리: 메모리, 파일, 네트워크 연결 등의 시스템 자원을 체계적으로 관리
- 예외 안전성: 예외가 발생해도 자원이 적절히 해제되는 것을 보장
- 소멸자 보장: C++은 스코프를 벗어날 때 반드시 소멸자를 호출
- 스코프 기반 해제: 객체가 생성된 스코프를 벗어나면 자동으로 자원 해제
*/

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <chrono>
#include <stdexcept>
using namespace std;

// 파일 자원 관리 RAII 클래스
class FileRAII {
private:
    string filename;
    fstream file;
    
public:
    FileRAII(const string& fname, ios::openmode mode) : filename(fname) {
        file.open(filename, mode);
        if (!file.is_open()) {
            throw runtime_error("파일을 열 수 없습니다: " + filename);
        }
        cout << "파일 열기: " << filename << endl;
    }
    
    ~FileRAII() {
        if (file.is_open()) {
            file.close();
            cout << "파일 닫기: " << filename << endl;
        }
    }
    
    // 복사 방지
    FileRAII(const FileRAII&) = delete;
    FileRAII& operator=(const FileRAII&) = delete;
    
    // 이동 허용
    FileRAII(FileRAII&& other) noexcept 
        : filename(move(other.filename)), file(move(other.file)) {}
    
    FileRAII& operator=(FileRAII&& other) noexcept {
        if (this != &other) {
            if (file.is_open()) {
                file.close();
            }
            filename = move(other.filename);
            file = move(other.file);
        }
        return *this;
    }
    
    template<typename T>
    FileRAII& write(const T& data) {
        file << data;
        return *this;
    }
    
    template<typename T>
    FileRAII& read(T& data) {
        file >> data;
        return *this;
    }
    
    bool isValid() const {
        return file.is_open() && file.good();
    }
};

// 시간 측정 RAII 클래스
class Timer {
private:
    string name;
    chrono::high_resolution_clock::time_point start;
    
public:
    explicit Timer(string n) : name(move(n)) {
        start = chrono::high_resolution_clock::now();
        cout << "[타이머 시작] " << name << endl;
    }
    
    ~Timer() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "[타이머 종료] " << name << ": " 
             << duration.count() << " 마이크로초" << endl;
    }
};

// 뮤텍스 락 RAII 시뮬레이션
class MockMutex {
private:
    string name;
    bool locked;
    
public:
    MockMutex(string n) : name(n), locked(false) {}
    
    void lock() {
        if (locked) {
            throw runtime_error("이미 잠긴 뮤텍스: " + name);
        }
        locked = true;
        cout << "뮤텍스 잠금: " << name << endl;
    }
    
    void unlock() {
        if (!locked) {
            throw runtime_error("잠기지 않은 뮤텍스 해제 시도: " + name);
        }
        locked = false;
        cout << "뮤텍스 해제: " << name << endl;
    }
    
    bool isLocked() const { return locked; }
};

class LockGuard {
private:
    MockMutex& mutex;
    
public:
    explicit LockGuard(MockMutex& m) : mutex(m) {
        mutex.lock();
    }
    
    ~LockGuard() {
        try {
            mutex.unlock();
        } catch (const exception& e) {
            cout << "소멸자에서 예외: " << e.what() << endl;
        }
    }
    
    // 복사와 이동 방지
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
    LockGuard(LockGuard&&) = delete;
    LockGuard& operator=(LockGuard&&) = delete;
};

// 메모리 풀 RAII 관리
class MemoryPool {
private:
    size_t blockSize;
    size_t poolSize;
    char* pool;
    vector<bool> allocated;
    
public:
    MemoryPool(size_t blockSz, size_t poolSz) 
        : blockSize(blockSz), poolSize(poolSz), allocated(poolSz, false) {
        pool = new char[blockSize * poolSize];
        cout << "메모리 풀 생성: " << (blockSize * poolSize) << " 바이트" << endl;
    }
    
    ~MemoryPool() {
        delete[] pool;
        cout << "메모리 풀 해제" << endl;
    }
    
    void* allocate() {
        for (size_t i = 0; i < poolSize; ++i) {
            if (!allocated[i]) {
                allocated[i] = true;
                cout << "블록 " << i << " 할당" << endl;
                return pool + (i * blockSize);
            }
        }
        throw bad_alloc();
    }
    
    void deallocate(void* ptr) {
        if (!ptr) return;
        
        char* charPtr = static_cast<char*>(ptr);
        size_t index = (charPtr - pool) / blockSize;
        
        if (index < poolSize && allocated[index]) {
            allocated[index] = false;
            cout << "블록 " << index << " 해제" << endl;
        }
    }
};

// 메모리 풀 사용을 위한 RAII 래퍼
class PooledMemory {
private:
    MemoryPool& pool;
    void* memory;
    
public:
    explicit PooledMemory(MemoryPool& p) : pool(p), memory(nullptr) {
        memory = pool.allocate();
    }
    
    ~PooledMemory() {
        if (memory) {
            pool.deallocate(memory);
        }
    }
    
    void* get() { return memory; }
    
    template<typename T>
    T* getAs() { return static_cast<T*>(memory); }
};

// 예외 안전성 테스트 함수들
void testExceptionSafety() {
    cout << "\n=== 예외 안전성 테스트 ===" << endl;
    
    MockMutex mutex("TestMutex");
    
    try {
        LockGuard guard(mutex);
        cout << "뮤텍스가 잠겨있나? " << mutex.isLocked() << endl;
        
        // 예외 발생 시뮬레이션
        throw runtime_error("테스트 예외");
        
    } catch (const exception& e) {
        cout << "예외 캐치: " << e.what() << endl;
        cout << "예외 후 뮤텍스 상태: " << mutex.isLocked() << endl;
    }
}

void testFileOperations() {
    cout << "\n=== 파일 작업 테스트 ===" << endl;
    
    try {
        // 파일 쓰기
        {
            FileRAII file("test.txt", ios::out);
            file.write("Hello ").write("RAII ").write("World!\n");
            file.write("자동 파일 관리\n");
        } // 파일 자동 닫힘
        
        // 파일 읽기
        {
            FileRAII file("test.txt", ios::in);
            string line;
            cout << "파일 내용:" << endl;
            while (getline(file.isValid() ? 
                          static_cast<ifstream&>(file) : ifstream(), line)) {
                cout << "  " << line << endl;
            }
        } // 파일 자동 닫힘
        
    } catch (const exception& e) {
        cout << "파일 작업 오류: " << e.what() << endl;
    }
}

int main() {
    cout << "=== RAII 패턴 ===" << endl;
    
    // 타이머 RAII 테스트
    {
        Timer timer("전체 프로그램");
        
        // 파일 작업 테스트
        testFileOperations();
        
        // 예외 안전성 테스트
        testExceptionSafety();
        
        // 메모리 풀 테스트
        cout << "\n--- 메모리 풀 테스트 ---" << endl;
        {
            MemoryPool pool(sizeof(int), 5);
            
            vector<unique_ptr<PooledMemory>> allocatedBlocks;
            
            // 여러 블록 할당
            for (int i = 0; i < 3; ++i) {
                auto block = make_unique<PooledMemory>(pool);
                *block->getAs<int>() = i * 10;
                allocatedBlocks.push_back(move(block));
            }
            
            // 사용
            for (size_t i = 0; i < allocatedBlocks.size(); ++i) {
                cout << "블록 " << i << " 값: " 
                     << *allocatedBlocks[i]->getAs<int>() << endl;
            }
            
            // 스코프 종료시 자동 해제
        }
        
        // 중첩된 타이머
        {
            Timer innerTimer("내부 작업");
            
            // 시간이 걸리는 작업 시뮬레이션
            int sum = 0;
            for (int i = 0; i < 1000000; ++i) {
                sum += i;
            }
            cout << "계산 결과: " << sum << endl;
        }
        
    } // 전체 타이머 종료
    
    cout << "\n=== RAII 패턴 완료 ===" << endl;
    
    return 0;
}

### 예제 정의
C++11/14/17의 현대적 기능들을 종합적으로 활용합니다.

```cpp
/*
주제: 현대 C++ 기능 (Modern C++ Features)
정의: C++11부터 도입된 현대적 언어 기능들을 활용하여 더 안전하고 효율적인 코드를 작성하는 방법

핵심 개념: auto, 범위 기반 for, 람다, constexpr, nullptr, 스마트 포인터
정의:
- auto: 컴파일러가 타입을 자동으로 추론하는 키워드
- 범위 기반 for: 컨테이너의 모든 요소를 간단히 순회하는 반복문
- 람다: 익명 함수를 정의하는 C++11 기능
- constexpr: 컴파일 시간에 계산 가능한 함수나 변수를 지정하는 키워드
- nullptr: 타입 안전한 널 포인터 상수
- 스마트 포인터: 자동 메모리 관리를 제공하는 포인터 래퍼
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <map>
#include <type_traits>
using namespace std;

// constexpr 함수들
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr double pi() {
    return 3.14159265358979323846;
}

constexpr double circleArea(double radius) {
    return pi() * radius * radius;
}

// 현대적 클래스 설계
class ModernClass {
private:
    string name;
    vector<int> data;
    unique_ptr<string> description;
    
public:
    // 위임 생성자
    ModernClass() : ModernClass("default", {}) {}
    
    ModernClass(string n, vector<int> d) 
        : name(move(n)), data(move(d)), description(make_unique<string>("A modern class")) {}
    
    // 복사 방지, 이동 허용
    ModernClass(const ModernClass&) = delete;
    ModernClass& operator=(const ModernClass&) = delete;
    
    ModernClass(ModernClass&&) = default;
    ModernClass& operator=(ModernClass&&) = default;
    
    // auto 반환 타입 추론
    auto getName() const -> const string& {
        return name;
    }
    
    // decltype과 후행 반환 타입
    template<typename T>
    auto addToData(T&& value) -> decltype(data.emplace_back(forward<T>(value))) {
        return data.emplace_back(forward<T>(value));
    }
    
    // 범위 기반 for 지원을 위한 begin/end
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
    
    void display() const {
        cout << "ModernClass: " << name << endl;
        cout << "Description: " << *description << endl;
        cout << "Data: ";
        for (const auto& item : data) {  // 범위 기반 for
            cout << item << " ";
        }
        cout << endl;
    }
};

// 가변 인자 템플릿을 활용한 팩토리
template<typename T, typename... Args>
auto makeObject(Args&&... args) {
    return make_unique<T>(forward<Args>(args)...);
}

// 람다와 함수 객체 활용
class LambdaDemo {
public:
    static void demonstrateLambdas() {
        cout << "\n=== 람다 표현식 데모 ===" << endl;
        
        vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // 기본 람다
        auto isEven = [](int n) { return n % 2 == 0; };
        
        // 캡처를 사용하는 람다
        int threshold = 5;
        auto greaterThanThreshold = [threshold](int n) { return n > threshold; };
        
        // 제네릭 람다 (C++14)
        auto multiply = [](auto a, auto b) { return a * b; };
        
        // 복사된 숫자들
        vector<int> evenNumbers;
        copy_if(numbers.begin(), numbers.end(), back_inserter(evenNumbers), isEven);
        
        cout << "짝수: ";
        for (auto n : evenNumbers) cout << n << " ";
        cout << endl;
        
        // 변환
        vector<int> doubled;
        transform(numbers.begin(), numbers.end(), back_inserter(doubled), 
                 [](int n) { return n * 2; });
        
        cout << "두 배: ";
        for (auto n : doubled) cout << n << " ";
        cout << endl;
        
        // 집계
        int sum = accumulate(numbers.begin(), numbers.end(), 0,
                           [](int a, int b) { return a + b; });
        cout << "합계: " << sum << endl;
        
        // 조건부 카운트
        int count = count_if(numbers.begin(), numbers.end(), greaterThanThreshold);
        cout << threshold << "보다 큰 수의 개수: " << count << endl;
        
        // 제네릭 람다 테스트
        cout << "multiply(3, 4) = " << multiply(3, 4) << endl;
        cout << "multiply(2.5, 3.0) = " << multiply(2.5, 3.0) << endl;
    }
};

// SFINAE와 타입 특성 활용
template<typename T>
enable_if_t<is_arithmetic_v<T>, void>
printValue(const T& value) {
    cout << "산술 타입 값: " << value << endl;
}

template<typename T>
enable_if_t<!is_arithmetic_v<T>, void>
printValue(const T& value) {
    cout << "비산술 타입 값: " << value << endl;
}

// 초기화 리스트 활용
class InitializerListDemo {
private:
    vector<string> words;
    
public:
    InitializerListDemo(initializer_list<string> list) : words(list) {}
    
    void addWords(initializer_list<string> newWords) {
        words.insert(words.end(), newWords);
    }
    
    void display() const {
        cout << "단어들: ";
        for (const auto& word : words) {
            cout << "\"" << word << "\" ";
        }
        cout << endl;
    }
};

int main() {
    cout << "=== 현대 C++ 기능 종합 ===" << endl;
    
    // constexpr 테스트
    cout << "\n--- constexpr 계산 ---" << endl;
    constexpr int fact5 = factorial(5);
    constexpr double area = circleArea(3.0);
    
    cout << "5! = " << fact5 << endl;
    cout << "반지름 3인 원의 넓이 = " << area << endl;
    
    // auto와 타입 추론
    cout << "\n--- auto 타입 추론 ---" << endl;
    auto integer = 42;
    auto floating = 3.14;
    auto text = string("Hello");
    auto lambda = [](int x) { return x * x; };
    
    cout << "정수: " << integer << endl;
    cout << "실수: " << floating << endl;
    cout << "문자열: " << text << endl;
    cout << "람다 결과: " << lambda(5) << endl;
    
    // 현대적 클래스 사용
    cout << "\n--- 현대적 클래스 ---" << endl;
    auto obj = makeObject<ModernClass>("Modern", vector<int>{1, 2, 3, 4, 5});
    obj->addToData(6);
    obj->addToData(7);
    obj->display();
    
    // 범위 기반 for로 직접 순회
    cout << "직접 순회: ";
    for (auto value : *obj) {
        cout << value << " ";
    }
    cout << endl;
    
    // 람다 데모
    LambdaDemo::demonstrateLambdas();
    
    // 스마트 포인터와 자동 메모리 관리
    cout << "\n--- 스마트 포인터 ---" << endl;
    {
        auto ptr1 = make_unique<string>("Unique");
        auto ptr2 = make_shared<string>("Shared");
        auto ptr3 = ptr2;  // 참조 카운트 증가
        
        cout << "*ptr1: " << *ptr1 << endl;
        cout << "*ptr2: " << *ptr2 << endl;
        cout << "ptr2 참조 카운트: " << ptr2.use_count() << endl;
    } // 자동으로 메모리 해제
    
    // nullptr 사용
    cout << "\n--- nullptr 사용 ---" << endl;
    unique_ptr<int> nullPtr = nullptr;
    if (!nullPtr) {
        cout << "포인터가 nullptr입니다." << endl;
    }
    
    nullPtr = make_unique<int>(100);
    if (nullPtr) {
        cout << "포인터 값: " << *nullPtr << endl;
    }
    
    // 타입 특성과 SFINAE
    cout << "\n--- 타입 특성 ---" << endl;
    printValue(42);
    printValue(3.14);
    printValue(string("Hello"));
    
    // 초기화 리스트
    cout << "\n--- 초기화 리스트 ---" << endl;
    InitializerListDemo demo{"hello", "world", "cpp"};
    demo.display();
    
    demo.addWords({"modern", "features"});
    demo.display();
    
    // 통일 초기화 구문
    cout << "\n--- 통일 초기화 ---" << endl;
    vector<int> vec1{1, 2, 3, 4, 5};
    map<string, int> myMap{
        {"one", 1},
        {"two", 2},
        {"three", 3}
    };
    
    cout << "벡터: ";
    for (auto val : vec1) cout << val << " ";
    cout << endl;
    
    cout << "맵: ";
    for (const auto& [key, value] : myMap) {  // 구조화된 바인딩 (C++17)
        cout << key << "=" << value << " ";
    }
    cout << endl;
    
    cout << "\n=== 현대 C++ 기능 완료 ===" << endl;
    
    return 0;
}
