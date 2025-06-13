# Chapter 08: 예외 처리와 프로젝트

## 학습 목표
- 예외 처리의 기본 개념과 try-catch 구문 습득
- 사용자 정의 예외 클래스 작성법 학습
- 예외 안전성과 RAII 패턴 이해
- 자원 관리와 메모리 안전성 확보 기법 습득
- 프로젝트 구조화와 모듈 분리 방법 학습
- C++ 코딩 표준과 모범 사례 적용
- 디버깅 기법과 성능 최적화 방법 이해
- 종합 프로젝트를 통한 실무 역량 강화

---

## 1. 예제 01: 예외 처리 기초 (01_exception_basic.cpp)

### 예제 정의
C++의 기본적인 예외 처리 메커니즘을 학습합니다.

```cpp
/*
주제: 예외 처리 (Exception Handling)
정의: 프로그램 실행 중 발생하는 예상치 못한 오류나 예외 상황을 체계적으로 처리하는 메커니즘

핵심 개념: exception, 예외 안전성, 오류 처리 패턴
정의:
- exception: 프로그램 실행 중 발생하는 예외적인 상황이나 오류를 나타내는 객체
- 예외 안전성: 예외가 발생해도 프로그램이 일관된 상태를 유지하는 특성
- 오류 처리 패턴: 예외 상황을 체계적으로 감지하고 대응하는 프로그래밍 방법론

예외 처리의 필요성:
- 견고한 프로그램: 예상치 못한 상황에서도 안정적으로 동작
- 디버깅 용이성: 오류 발생 지점과 원인을 명확하게 파악
- 사용자 경험 향상: 프로그램 비정상 종료 방지
- 자원 누수 방지: 예외 발생 시에도 적절한 정리 작업 수행
*/

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// 간단한 나눗셈 함수 (예외 발생 가능)
double divide(double a, double b) {
    if (b == 0) {
        throw invalid_argument("0으로 나눌 수 없습니다!");
    }
    return a / b;
}

// 배열 접근 함수 (범위 검사)
int getArrayElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("배열 인덱스가 범위를 벗어났습니다!");
    }
    return arr[index];
}

int main() {
    cout << "=== 예외 처리 기초 ===" << endl;
    
    // 예외 없는 정상적인 경우
    cout << "1. 정상적인 계산:" << endl;
    try {
        double result = divide(10, 2);
        cout << "10 / 2 = " << result << endl;
    }
    catch (const exception& e) {
        cout << "예외 발생: " << e.what() << endl;
    }
    
    // 예외 발생 케이스
    cout << "\n2. 예외 발생 케이스:" << endl;
    try {
        double result = divide(10, 0);  // 0으로 나누기 시도
        cout << "결과: " << result << endl;  // 이 줄은 실행되지 않음
    }
    catch (const invalid_argument& e) {
        cout << "잘못된 인수 예외: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "일반 예외: " << e.what() << endl;
    }
    
    // 배열 접근 예외
    cout << "\n3. 배열 접근 예외:" << endl;
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    try {
        cout << "정상 접근: numbers[2] = " << getArrayElement(numbers, size, 2) << endl;
        cout << "비정상 접근: numbers[10] = " << getArrayElement(numbers, size, 10) << endl;
    }
    catch (const out_of_range& e) {
        cout << "범위 초과 예외: " << e.what() << endl;
    }
    
    cout << "\n4. 프로그램은 예외에도 불구하고 계속 실행됩니다." << endl;
    
    return 0;
}
```

---

## 2. 예제 02: try-catch 구문 상세 (02_try_catch.cpp)

### 예제 정의
다양한 형태의 try-catch 구문과 예외 처리 패턴을 학습합니다.

```cpp
/*
주제: try-catch 구문 (try-catch Statement)
정의: 예외가 발생할 수 있는 코드를 실행하고, 발생한 예외를 적절히 처리하는 C++의 예외 처리 구문

핵심 개념: try 블록, catch 블록, throw, 예외 전파
정의:
- try 블록: 예외가 발생할 수 있는 코드를 감싸는 영역
- catch 블록: 특정 타입의 예외를 잡아서 처리하는 영역
- throw: 예외를 명시적으로 발생시키는 키워드
- 예외 전파: 예외가 호출 스택을 따라 상위로 전달되는 과정

catch 블록의 순서 규칙:
- 더 구체적인 예외 타입을 먼저 catch
- 상속 관계에서 자식 클래스를 부모 클래스보다 먼저
- catch(...) 는 모든 예외를 잡는 마지막 수단
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// 복합적인 예외 상황을 시뮬레이션하는 함수
void processData(int value) {
    if (value < 0) {
        throw invalid_argument("음수는 처리할 수 없습니다");
    }
    else if (value == 0) {
        throw runtime_error("런타임 오류: 0은 특별한 값입니다");
    }
    else if (value > 100) {
        throw out_of_range("값이 허용 범위(1-100)를 초과했습니다");
    }
    else if (value == 13) {
        throw logic_error("논리 오류: 13은 불길한 숫자입니다");
    }
    
    cout << "데이터 처리 성공: " << value << endl;
}

// 메모리 할당 예외 시뮬레이션
void memoryIntensiveOperation() {
    try {
        // 매우 큰 메모리 할당 시도
        size_t hugeSIze = SIZE_MAX / 2;
        vector<int> hugeVector(hugeSIze);
    }
    catch (const bad_alloc& e) {
        cout << "메모리 할당 실패: " << e.what() << endl;
        throw;  // 예외를 다시 던짐 (re-throw)
    }
}

int main() {
    cout << "=== try-catch 구문 상세 ===" << endl;
    
    // 1. 다중 catch 블록
    cout << "1. 다중 catch 블록 테스트:" << endl;
    vector<int> testValues = {50, -5, 0, 150, 13, 25};
    
    for (int value : testValues) {
        try {
            cout << "처리 중: " << value << " -> ";
            processData(value);
        }
        catch (const invalid_argument& e) {
            cout << "인수 오류: " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "범위 오류: " << e.what() << endl;
        }
        catch (const logic_error& e) {
            cout << "논리 오류: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "런타임 오류: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "일반 예외: " << e.what() << endl;
        }
        catch (...) {
            cout << "알 수 없는 예외 발생" << endl;
        }
    }
    
    // 2. 예외 재던지기 (re-throw)
    cout << "\n2. 예외 재던지기 테스트:" << endl;
    try {
        try {
            memoryIntensiveOperation();
        }
        catch (const bad_alloc& e) {
            cout << "내부에서 메모리 예외를 잡았지만 다시 던집니다" << endl;
            throw;  // 예외를 상위로 재던지기
        }
    }
    catch (const bad_alloc& e) {
        cout << "외부에서 재던져진 메모리 예외를 처리: " << e.what() << endl;
    }
    
    // 3. 중첩된 try-catch
    cout << "\n3. 중첩된 try-catch:" << endl;
    try {
        cout << "외부 try 블록 시작" << endl;
        
        try {
            cout << "내부 try 블록에서 예외 발생" << endl;
            throw runtime_error("내부 예외");
        }
        catch (const runtime_error& e) {
            cout << "내부 catch에서 처리: " << e.what() << endl;
            cout << "내부에서 새로운 예외 발생" << endl;
            throw logic_error("외부로 전달할 예외");
        }
        
        cout << "이 줄은 실행되지 않음" << endl;
    }
    catch (const logic_error& e) {
        cout << "외부 catch에서 처리: " << e.what() << endl;
    }
    
    // 4. 예외 없이 정상 실행
    cout << "\n4. 예외 없는 정상 케이스:" << endl;
    try {
        processData(42);
        cout << "모든 처리가 성공적으로 완료되었습니다" << endl;
    }
    catch (...) {
        cout << "예외가 발생했습니다" << endl;
    }
    
    cout << "\n=== try-catch 사용 팁 ===" << endl;
    cout << "1. 구체적인 예외부터 잡기 (상속 순서 고려)" << endl;
    cout << "2. const 참조로 예외 객체 받기 (복사 비용 절약)" << endl;
    cout << "3. 필요시 throw; 로 예외 재던지기" << endl;
    cout << "4. catch(...) 는 최후의 수단으로만 사용" << endl;
    
    return 0;
}
```

---

## 3. 예제 03: 사용자 정의 예외 (03_custom_exceptions.cpp)

### 예제 정의
자신만의 예외 클래스를 정의하고 활용하는 방법을 학습합니다.

```cpp
/*
주제: 사용자 정의 예외 (Custom Exceptions)
정의: 표준 예외 클래스를 상속받아 특정 상황에 맞는 예외 클래스를 직접 정의하는 기법

핵심 개념: exception 상속, what() 오버라이드, 예외 계층구조
정의:
- exception 상속: std::exception 또는 그 하위 클래스를 상속받아 새로운 예외 클래스 생성
- what() 오버라이드: 예외 메시지를 반환하는 가상 함수를 재정의
- 예외 계층구조: 관련된 예외들을 상속 관계로 체계화하여 관리하는 구조

사용자 정의 예외의 장점:
- 도메인 특화: 애플리케이션 영역에 특화된 의미 있는 예외
- 정보 풍부: 예외 상황에 대한 더 자세하고 구체적인 정보 제공  
- 처리 세분화: 예외 타입에 따른 세밀한 처리 로직 구현 가능
- 유지보수성: 예외 관련 코드의 가독성과 유지보수성 향상
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

// 기본 사용자 정의 예외 클래스
class BankException : public exception {
protected:
    string message;
    
public:
    explicit BankException(const string& msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    
    virtual ~BankException() = default;
};

// 계좌 관련 예외들
class InsufficientFundsException : public BankException {
private:
    double currentBalance;
    double requestedAmount;
    
public:
    InsufficientFundsException(double balance, double requested) 
        : BankException("잔액 부족"), currentBalance(balance), requestedAmount(requested) {
        
        ostringstream oss;
        oss << "잔액 부족: 현재 잔액 " << currentBalance 
            << "원, 요청 금액 " << requestedAmount << "원";
        message = oss.str();
    }
    
    double getCurrentBalance() const { return currentBalance; }
    double getRequestedAmount() const { return requestedAmount; }
};

class InvalidAccountException : public BankException {
private:
    string accountNumber;
    
public:
    explicit InvalidAccountException(const string& accNum) 
        : BankException("잘못된 계좌"), accountNumber(accNum) {
        message = "잘못된 계좌 번호: " + accountNumber;
    }
    
    const string& getAccountNumber() const { return accountNumber; }
};

class NegativeAmountException : public BankException {
private:
    double amount;
    
public:
    explicit NegativeAmountException(double amt) 
        : BankException("음수 금액"), amount(amt) {
        ostringstream oss;
        oss << "음수 금액은 허용되지 않습니다: " << amount << "원";
        message = oss.str();
    }
    
    double getAmount() const { return amount; }
};

// 게임 관련 예외 클래스들
class GameException : public exception {
protected:
    string message;
    
public:
    explicit GameException(const string& msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class PlayerNotFoundException : public GameException {
private:
    string playerName;
    
public:
    explicit PlayerNotFoundException(const string& name) 
        : GameException("플레이어를 찾을 수 없음"), playerName(name) {
        message = "플레이어 '" + playerName + "'을(를) 찾을 수 없습니다";
    }
    
    const string& getPlayerName() const { return playerName; }
};

class InvalidMoveException : public GameException {
private:
    int x, y;
    
public:
    InvalidMoveException(int posX, int posY) 
        : GameException("잘못된 이동"), x(posX), y(posY) {
        ostringstream oss;
        oss << "잘못된 이동: (" << x << ", " << y << ")";
        message = oss.str();
    }
    
    int getX() const { return x; }
    int getY() const { return y; }
};

// 은행 계좌 클래스
class BankAccount {
private:
    string accountNumber;
    double balance;
    
public:
    BankAccount(const string& accNum, double initialBalance) 
        : accountNumber(accNum), balance(initialBalance) {
        if (initialBalance < 0) {
            throw NegativeAmountException(initialBalance);
        }
    }
    
    void withdraw(double amount) {
        if (amount < 0) {
            throw NegativeAmountException(amount);
        }
        if (amount > balance) {
            throw InsufficientFundsException(balance, amount);
        }
        balance -= amount;
        cout << amount << "원 출금 완료. 잔액: " << balance << "원" << endl;
    }
    
    void deposit(double amount) {
        if (amount < 0) {
            throw NegativeAmountException(amount);
        }
        balance += amount;
        cout << amount << "원 입금 완료. 잔액: " << balance << "원" << endl;
    }
    
    double getBalance() const { return balance; }
    const string& getAccountNumber() const { return accountNumber; }
};

// 게임 플레이어 클래스
class GamePlayer {
private:
    string name;
    int x, y;
    
public:
    GamePlayer(const string& playerName, int startX = 0, int startY = 0) 
        : name(playerName), x(startX), y(startY) {}
    
    void move(int newX, int newY) {
        if (newX < 0 || newX > 10 || newY < 0 || newY > 10) {
            throw InvalidMoveException(newX, newY);
        }
        x = newX;
        y = newY;
        cout << name << " 이동: (" << x << ", " << y << ")" << endl;
    }
    
    const string& getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
};

int main() {
    cout << "=== 사용자 정의 예외 ===" << endl;
    
    // 1. 은행 계좌 예외 테스트
    cout << "1. 은행 계좌 예외 테스트:" << endl;
    
    try {
        BankAccount account("123-456-789", 10000);
        
        account.deposit(5000);
        account.withdraw(3000);
        account.withdraw(20000);  // 잔액 부족 예외 발생
    }
    catch (const InsufficientFundsException& e) {
        cout << "잔액 부족 예외: " << e.what() << endl;
        cout << "현재 잔액: " << e.getCurrentBalance() << "원" << endl;
        cout << "요청 금액: " << e.getRequestedAmount() << "원" << endl;
    }
    catch (const NegativeAmountException& e) {
        cout << "음수 금액 예외: " << e.what() << endl;
        cout << "문제 금액: " << e.getAmount() << "원" << endl;
    }
    catch (const BankException& e) {
        cout << "은행 예외: " << e.what() << endl;
    }
    
    // 2. 음수 금액 예외 테스트
    cout << "\n2. 음수 금액 예외 테스트:" << endl;
    try {
        BankAccount account2("987-654-321", 5000);
        account2.deposit(-1000);  // 음수 입금 시도
    }
    catch (const NegativeAmountException& e) {
        cout << "예외 처리: " << e.what() << endl;
    }
    
    // 3. 게임 예외 테스트
    cout << "\n3. 게임 예외 테스트:" << endl;
    try {
        GamePlayer player("용사", 5, 5);
        
        player.move(3, 7);  // 정상 이동
        player.move(15, 20);  // 범위 초과 이동
    }
    catch (const InvalidMoveException& e) {
        cout << "잘못된 이동 예외: " << e.what() << endl;
        cout << "시도한 위치: (" << e.getX() << ", " << e.getY() << ")" << endl;
    }
    catch (const GameException& e) {
        cout << "게임 예외: " << e.what() << endl;
    }
    
    // 4. 예외 계층구조 테스트
    cout << "\n4. 예외 계층구조 테스트:" << endl;
    try {
        // 다양한 예외를 순서대로 발생시켜 catch 순서 확인
        throw InsufficientFundsException(1000, 2000);
    }
    catch (const InsufficientFundsException& e) {
        cout << "구체적인 예외: " << e.what() << endl;
    }
    catch (const BankException& e) {
        cout << "일반 은행 예외: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "표준 예외: " << e.what() << endl;
    }
    
    cout << "\n=== 사용자 정의 예외 설계 팁 ===" << endl;
    cout << "1. std::exception을 상속받아 표준 인터페이스 유지" << endl;
    cout << "2. what() 함수를 오버라이드하여 의미 있는 메시지 제공" << endl;
    cout << "3. 예외 상황에 대한 추가 정보를 멤버 변수로 저장" << endl;
    cout << "4. 도메인별로 예외 계층구조 설계" << endl;
    cout << "5. const char* what() const noexcept 시그니처 준수" << endl;
    
    return 0;
}
```

---

## 4. 예제 04: 예외 안전성 (04_exception_safety.cpp)

### 예제 정의
예외 안전성의 다양한 레벨과 안전한 코드 작성 기법을 학습합니다.

```cpp
/*
주제: 예외 안전성 (Exception Safety)
정의: 예외가 발생하더라도 프로그램이 일관되고 안전한 상태를 유지하는 프로그래밍 설계 원칙

핵심 개념: 안전성 레벨, 강한 보장, 기본 보장, 무던짐 보장
정의:
- 무던짐 보장(No-throw guarantee): 예외를 절대 던지지 않는 함수 (noexcept)
- 강한 보장(Strong guarantee): 예외 발생 시 함수 호출 이전 상태로 완전히 복원
- 기본 보장(Basic guarantee): 예외 발생 시 객체는 유효한 상태이지만 원래 상태와 다를 수 있음
- 보장 없음(No guarantee): 예외 발생 시 프로그램 상태를 예측할 수 없음

예외 안전성 설계 원칙:
- RAII(Resource Acquisition Is Initialization): 자원 관리를 객체 생명주기에 연결
- Copy-and-swap idiom: 임시 복사본에서 작업 후 성공 시 교체
- Two-phase construction: 생성과 초기화를 분리하여 예외 안전성 확보
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// 예외 안전성 레벨별 예제 클래스들

// 1. 무던짐 보장 (No-throw guarantee)
class NoThrowExample {
private:
    int value;
    
public:
    explicit NoThrowExample(int v) noexcept : value(v) {}
    
    // noexcept 명시로 예외를 던지지 않음을 보장
    void setValue(int v) noexcept {
        value = v;
    }
    
    int getValue() const noexcept {
        return value;
    }
    
    // 이동 생성자는 일반적으로 noexcept
    NoThrowExample(NoThrowExample&& other) noexcept : value(other.value) {
        other.value = 0;
    }
    
    // 소멸자는 기본적으로 noexcept
    ~NoThrowExample() noexcept = default;
};

// 2. 기본 보장 (Basic guarantee)
class BasicSafetyExample {
private:
    vector<string> data;
    string name;
    
public:
    BasicSafetyExample(const string& n) : name(n) {}
    
    // 기본 보장: 예외 발생 시에도 객체는 유효한 상태
    void addData(const string& item) {
        data.push_back(item);  // 메모리 부족 시 예외 가능
        // 예외 발생해도 data는 여전히 유효한 상태
    }
    
    void clearData() noexcept {
        data.clear();  // 예외 없이 실행됨
    }
    
    size_t getDataCount() const noexcept {
        return data.size();
    }
    
    const string& getName() const noexcept {
        return name;
    }
};

// 3. 강한 보장 (Strong guarantee)
class StrongSafetyExample {
private:
    vector<int> numbers;
    string description;
    
public:
    StrongSafetyExample() = default;
    
    // Copy-and-swap idiom을 사용한 강한 보장
    void setData(const vector<int>& newNumbers, const string& newDesc) {
        // 임시 객체에서 모든 작업 수행
        vector<int> tempNumbers = newNumbers;  // 복사 중 예외 가능
        string tempDesc = newDesc;             // 복사 중 예외 가능
        
        // 모든 작업이 성공하면 원본 데이터 교체 (무던짐 보장)
        numbers.swap(tempNumbers);  // noexcept
        description.swap(tempDesc); // noexcept
    }
    
    // 강한 보장을 제공하는 추가 함수
    void addNumber(int num) {
        vector<int> temp = numbers;  // 현재 상태 백업
        temp.push_back(num);         // 새 데이터로 작업
        numbers.swap(temp);          // 성공 시에만 교체
    }
    
    const vector<int>& getNumbers() const noexcept {
        return numbers;
    }
    
    const string& getDescription() const noexcept {
        return description;
    }
};

// 4. 보장 없음 (No guarantee) - 안 좋은 예제
class UnsafeExample {
private:
    int* data;
    size_t size;
    
public:
    UnsafeExample(size_t s) : size(s) {
        data = new int[size];
    }
    
    // 위험한 함수: 예외 발생 시 메모리 누수 가능
    void dangerousResize(size_t newSize) {
        delete[] data;           // 기존 메모리 해제
        data = new int[newSize]; // 여기서 예외 발생 시 data는 댕글링 포인터
        size = newSize;
    }
    
    // 안전한 버전
    void safeResize(size_t newSize) {
        int* newData = new int[newSize];  // 새 메모리 할당
        delete[] data;                    // 성공 후 기존 메모리 해제
        data = newData;                   // 포인터 업데이트
        size = newSize;
    }
    
    ~UnsafeExample() {
        delete[] data;
    }
};

// RAII를 활용한 안전한 자원 관리
class FileManager {
private:
    string filename;
    bool isOpen;
    
public:
    explicit FileManager(const string& fname) : filename(fname), isOpen(false) {
        // 파일 열기 시뮬레이션
        if (filename.empty()) {
            throw invalid_argument("파일명이 비어있습니다");
        }
        isOpen = true;
        cout << "파일 열기: " << filename << endl;
    }
    
    // 복사 방지 (자원 관리 객체는 일반적으로 복사 금지)
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    
    // 이동은 허용 (소유권 이전)
    FileManager(FileManager&& other) noexcept 
        : filename(move(other.filename)), isOpen(other.isOpen) {
        other.isOpen = false;
    }
    
    void writeData(const string& data) {
        if (!isOpen) {
            throw runtime_error("파일이 열려있지 않습니다");
        }
        if (data.empty()) {
            throw invalid_argument("빈 데이터는 쓸 수 없습니다");
        }
        cout << "데이터 쓰기: " << data << endl;
    }
    
    // 소멸자에서 자동 정리 (RAII)
    ~FileManager() noexcept {
        if (isOpen) {
            cout << "파일 닫기: " << filename << endl;
        }
    }
};

int main() {
    cout << "=== 예외 안전성 레벨 ===" << endl;
    
    // 1. 무던짐 보장 테스트
    cout << "1. 무던짐 보장 (No-throw guarantee):" << endl;
    NoThrowExample nothrow(42);
    nothrow.setValue(100);  // 예외 없음이 보장됨
    cout << "값: " << nothrow.getValue() << endl;
    
    // 2. 기본 보장 테스트
    cout << "\n2. 기본 보장 (Basic guarantee):" << endl;
    BasicSafetyExample basic("테스트");
    try {
        basic.addData("데이터1");
        basic.addData("데이터2");
        cout << "데이터 개수: " << basic.getDataCount() << endl;
        
        // 메모리 부족 시뮬레이션은 어려우므로 다른 예외로 대체
        cout << "기본 보장: 예외 발생해도 객체는 유효 상태 유지" << endl;
    }
    catch (const exception& e) {
        cout << "예외 발생했지만 객체는 여전히 유효: " << basic.getName() << endl;
    }
    
    // 3. 강한 보장 테스트
    cout << "\n3. 강한 보장 (Strong guarantee):" << endl;
    StrongSafetyExample strong;
    
    try {
        vector<int> data1 = {1, 2, 3};
        strong.setData(data1, "첫 번째 데이터");
        cout << "데이터 설정 성공" << endl;
        
        strong.addNumber(4);
        cout << "숫자 추가 성공" << endl;
        
        // 원본 데이터는 변경되거나 완전히 원래 상태로 복원됨
        cout << "현재 데이터 크기: " << strong.getNumbers().size() << endl;
    }
    catch (const exception& e) {
        cout << "예외 발생 시 원래 상태로 복원됨" << endl;
    }
    
    // 4. RAII 패턴 테스트
    cout << "\n4. RAII 패턴 (자동 자원 관리):" << endl;
    try {
        FileManager file("test.txt");
        file.writeData("중요한 데이터");
        
        // 예외 발생 상황 시뮬레이션
        throw runtime_error("예상치 못한 오류");
        
    } // 여기서 FileManager 소멸자가 자동 호출되어 파일 닫기
    catch (const exception& e) {
        cout << "예외 처리: " << e.what() << endl;
        cout << "RAII로 인해 파일은 자동으로 닫힘" << endl;
    }
    
    // 5. 예외 안전성이 없는 코드의 문제점
    cout << "\n5. 예외 안전하지 않은 코드의 위험성:" << endl;
    cout << "UnsafeExample의 dangerousResize()는 메모리 누수 위험이 있음" << endl;
    cout << "safeResize()는 예외 발생 시에도 안전함" << endl;
    
    cout << "\n=== 예외 안전성 설계 가이드라인 ===" << endl;
    cout << "1. RAII 패턴으로 자원 관리 자동화" << endl;
    cout << "2. noexcept로 예외 없음을 명시" << endl;
    cout << "3. Copy-and-swap idiom으로 강한 보장 제공" << endl;
    cout << "4. 스마트 포인터로 메모리 안전성 확보" << endl;
    cout << "5. 예외 발생 시점을 최소화하는 설계" << endl;
    
    return 0;
}
```

---

## 5. 예제 05: RAII 패턴 (05_raii_pattern.cpp)

### 예제 정의
RAII(자원 획득이 초기화) 패턴을 활용한 안전한 자원 관리를 학습합니다.

```cpp
/*
주제: RAII 패턴 (Resource Acquisition Is Initialization)
정의: 자원의 획득과 해제를 객체의 생성과 소멸에 연결하여 자동으로 관리하는 C++의 핵심 프로그래밍 패턴

핵심 개념: 자원 관리, 소멸자 보장, 스코프 기반 해제, 예외 안전성
정의:
- 자원 관리: 메모리, 파일, 네트워크 연결 등의 시스템 자원을 체계적으로 관리
- 소멸자 보장: C++은 스코프를 벗어날 때 반드시 소멸자를 호출
- 스코프 기반 해제: 객체가 생성된 스코프를 벗어나면 자동으로 자원 해제
- 예외 안전성: 예외가 발생해도 자원이 적절히 해제되는 것을 보장

RAII의 핵심 원칙:
1. 자원 획득은 객체 생성 시점 (생성자)
2. 자원 해제는 객체 소멸 시점 (소멸자)  
3. 복사/이동 의미론을 통한 소유권 관리
4. 예외 발생 시에도 자동 정리 보장
*/

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <mutex>
#include <chrono>
#include <thread>
using namespace std;

// 1. 파일 자원 관리 RAII 클래스
class FileRAII {
private:
    string filename;
    unique_ptr<ofstream> file;
    
public:
    explicit FileRAII(const string& fname) : filename(fname) {
        file = make_unique<ofstream>(filename);
        if (!file->is_open()) {
            throw runtime_error("파일을 열 수 없습니다: " + filename);
        }
        cout << "[FILE] 파일 열기: " << filename << endl;
    }
    
    // 복사 방지 (자원은 고유하게 소유)
    FileRAII(const FileRAII&) = delete;
    FileRAII& operator=(const FileRAII&) = delete;
    
    // 이동 허용 (소유권 이전)
    FileRAII(FileRAII&& other) noexcept 
        : filename(move(other.filename)), file(move(other.file)) {
        cout << "[FILE] 파일 소유권 이동: " << filename << endl;
    }
    
    void write(const string& data) {
        if (file && file->is_open()) {
            *file << data << endl;
            cout << "[FILE] 데이터 쓰기: " << data << endl;
        } else {
            throw runtime_error("파일이 열려있지 않습니다");
        }
    }
    
    // RAII: 소멸자에서 자동 자원 해제
    ~FileRAII() {
        if (file && file->is_open()) {
            file->close();
            cout << "[FILE] 파일 자동 닫기: " << filename << endl;
        }
    }
};

// 2. 뮤텍스 락 RAII 클래스 (lock_guard와 유사)
class MutexRAII {
private:
    mutex& mtx;
    bool isLocked;
    
public:
    explicit MutexRAII(mutex& m) : mtx(m), isLocked(true) {
        mtx.lock();
        cout << "[MUTEX] 뮤텍스 잠금 획득" << endl;
    }
    
    // 복사와 대입 방지
    MutexRAII(const MutexRAII&) = delete;
    MutexRAII& operator=(const MutexRAII&) = delete;
    
    // 수동 해제 기능
    void unlock() {
        if (isLocked) {
            mtx.unlock();
            isLocked = false;
            cout << "[MUTEX] 뮤텍스 수동 해제" << endl;
        }
    }
    
    ~MutexRAII() {
        if (isLocked) {
            mtx.unlock();
            cout << "[MUTEX] 뮤텍스 자동 해제" << endl;
        }
    }
};

// 3. 시간 측정 RAII 클래스
class TimerRAII {
private:
    string name;
    chrono::high_resolution_clock::time_point start;
    
public:
    explicit TimerRAII(const string& timerName) : name(timerName) {
        start = chrono::high_resolution_clock::now();
        cout << "[TIMER] 타이머 시작: " << name << endl;
    }
    
    ~TimerRAII() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "[TIMER] 타이머 종료: " << name 
             << " (" << duration.count() << "ms)" << endl;
    }
};

// 4. 메모리 풀 RAII 관리
class MemoryPoolRAII {
private:
    size_t poolSize;
    unique_ptr<char[]> pool;
    
public:
    explicit MemoryPoolRAII(size_t size) : poolSize(size) {
        pool = make_unique<char[]>(poolSize);
        cout << "[MEMORY] 메모리 풀 할당: " << poolSize << " 바이트" << endl;
    }
    
    char* getMemory(size_t offset) {
        if (offset >= poolSize) {
            throw out_of_range("메모리 풀 범위 초과");
        }
        return pool.get() + offset;
    }
    
    ~MemoryPoolRAII() {
        cout << "[MEMORY] 메모리 풀 자동 해제: " << poolSize << " 바이트" << endl;
    }
};

// 5. 네트워크 연결 시뮬레이션 RAII
class NetworkConnectionRAII {
private:
    string serverAddress;
    bool isConnected;
    
public:
    explicit NetworkConnectionRAII(const string& address) 
        : serverAddress(address), isConnected(false) {
        
        // 연결 시뮬레이션
        cout << "[NETWORK] 서버 연결 시도: " << serverAddress << endl;
        
        // 연결 실패 시뮬레이션
        if (serverAddress == "invalid_server") {
            throw runtime_error("서버 연결 실패: " + serverAddress);
        }
        
        isConnected = true;
        cout << "[NETWORK] 서버 연결 성공: " << serverAddress << endl;
    }
    
    void sendData(const string& data) {
        if (!isConnected) {
            throw runtime_error("연결되지 않은 상태");
        }
        cout << "[NETWORK] 데이터 전송: " << data << endl;
    }
    
    ~NetworkConnectionRAII() {
        if (isConnected) {
            cout << "[NETWORK] 연결 자동 해제: " << serverAddress << endl;
        }
    }
};

// 복합 RAII 클래스 (여러 자원을 한 번에 관리)
class DatabaseTransactionRAII {
private:
    string transactionId;
    bool isActive;
    
public:
    explicit DatabaseTransactionRAII(const string& txId) 
        : transactionId(txId), isActive(true) {
        cout << "[DB] 트랜잭션 시작: " << transactionId << endl;
    }
    
    void executeQuery(const string& query) {
        if (!isActive) {
            throw runtime_error("트랜잭션이 활성화되지 않음");
        }
        cout << "[DB] 쿼리 실행: " << query << endl;
    }
    
    void commit() {
        if (isActive) {
            cout << "[DB] 트랜잭션 커밋: " << transactionId << endl;
            isActive = false;
        }
    }
    
    void rollback() {
        if (isActive) {
            cout << "[DB] 트랜잭션 롤백: " << transactionId << endl;
            isActive = false;
        }
    }
    
    ~DatabaseTransactionRAII() {
        if (isActive) {
            cout << "[DB] 트랜잭션 자동 롤백: " << transactionId << endl;
        }
    }
};

// RAII 활용 예제 함수들
void fileOperationExample() {
    cout << "\n=== 파일 연산 예제 ===" << endl;
    
    try {
        FileRAII file1("output1.txt");
        file1.write("첫 번째 라인");
        file1.write("두 번째 라인");
        
        // 예외 발생 시뮬레이션
        if (true) {  // 조건을 바꿔서 테스트
            throw runtime_error("파일 처리 중 오류 발생");
        }
        
        file1.write("세 번째 라인");  // 이 줄은 실행되지 않음
    }
    catch (const exception& e) {
        cout << "예외 처리: " << e.what() << endl;
        cout << "RAII로 인해 파일은 자동으로 닫힘" << endl;
    }
}

void mutexExample() {
    cout << "\n=== 뮤텍스 예제 ===" << endl;
    
    mutex sharedMutex;
    
    try {
        MutexRAII lock(sharedMutex);
        
        cout << "임계 영역에서 작업 수행 중..." << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        
        // 예외 발생 가능 영역
        throw logic_error("뮤텍스 보호 영역에서 오류");
        
    } // MutexRAII 소멸자에서 자동으로 뮤텍스 해제
    catch (const exception& e) {
        cout << "예외 처리: " << e.what() << endl;
        cout << "뮤텍스는 자동으로 해제됨" << endl;
    }
}

void performanceTimingExample() {
    cout << "\n=== 성능 측정 예제 ===" << endl;
    
    {
        TimerRAII timer("복잡한 계산");
        
        // 시간이 걸리는 작업 시뮬레이션
        int sum = 0;
        for (int i = 0; i < 1000000; ++i) {
            sum += i;
        }
        
        cout << "계산 결과: " << sum << endl;
    } // TimerRAII 소멸자에서 자동으로 시간 측정 종료
}

int main() {
    cout << "=== RAII 패턴 활용 ===" << endl;
    
    // 1. 파일 연산 RAII
    fileOperationExample();
    
    // 2. 뮤텍스 RAII
    mutexExample();
    
    // 3. 성능 측정 RAII
    performanceTimingExample();
    
    // 4. 메모리 풀 RAII
    cout << "\n=== 메모리 풀 예제 ===" << endl;
    try {
        MemoryPoolRAII memPool(1024);
        char* ptr = memPool.getMemory(100);
        cout << "메모리 풀에서 주소 획득: " << static_cast<void*>(ptr) << endl;
    } // 자동으로 메모리 풀 해제
    catch (const exception& e) {
        cout << "메모리 풀 예외: " << e.what() << endl;
    }
    
    // 5. 네트워크 연결 RAII
    cout << "\n=== 네트워크 연결 예제 ===" << endl;
    try {
        NetworkConnectionRAII conn("server.example.com");
        conn.sendData("Hello Server!");
        conn.sendData("Important Data");
    } // 자동으로 연결 해제
    catch (const exception& e) {
        cout << "네트워크 예외: " << e.what() << endl;
    }
    
    // 6. 데이터베이스 트랜잭션 RAII
    cout << "\n=== 데이터베이스 트랜잭션 예제 ===" << endl;
    try {
        DatabaseTransactionRAII tx("TX_001");
        tx.executeQuery("INSERT INTO users...");
        tx.executeQuery("UPDATE accounts...");
        
        // 성공 시 커밋
        tx.commit();
    } // 커밋되지 않으면 자동 롤백
    catch (const exception& e) {
        cout << "DB 예외: " << e.what() << endl;
    }
    
    // 7. 예외 발생 시 자동 롤백 테스트
    cout << "\n=== 자동 롤백 테스트 ===" << endl;
    try {
        DatabaseTransactionRAII tx("TX_002");
        tx.executeQuery("DELETE FROM logs...");
        
        throw runtime_error("트랜잭션 중 오류 발생");
        
        tx.commit();  // 이 줄은 실행되지 않음
    }
    catch (const exception& e) {
        cout << "예외로 인한 자동 롤백: " << e.what() << endl;
    }
    
    cout << "\n=== RAII 패턴의 장점 ===" << endl;
    cout << "1. 자동 자원 관리: 수동 해제 코드 불필요" << endl;
    cout << "2. 예외 안전성: 예외 발생 시에도 자원 해제 보장" << endl;
    cout << "3. 코드 간소화: try-finally 블록 불필요" << endl;
    cout << "4. 실수 방지: 자원 해제 누락 가능성 제거" << endl;
    cout << "5. 스코프 기반: 직관적이고 예측 가능한 자원 관리" << endl;
    
    return 0;
}
```

---

## 6. 예제 06: 자원 관리 (06_resource_management.cpp)

### 예제 정의
다양한 자원(메모리, 파일, 네트워크 등)의 안전한 관리 기법을 학습합니다.

```cpp
/*
주제: 자원 관리 (Resource Management)
정의: 프로그램에서 사용하는 시스템 자원(메모리, 파일, 네트워크 연결 등)을 안전하고 효율적으로 할당, 사용, 해제하는 종합적인 기법

핵심 개념: 스마트 포인터, 컨테이너, 자원 래퍼, 소유권 관리
정의:
- 스마트 포인터: 자동 메모리 관리를 제공하는 포인터 래퍼 클래스
- 컨테이너: STL 컨테이너를 활용한 안전한 데이터 구조 관리
- 자원 래퍼: 시스템 자원을 객체로 래핑하여 RAII 패턴 적용
- 소유권 관리: 자원의 소유권을 명확히 하여 중복 해제나 누수 방지

모던 C++ 자원 관리 전략:
1. Raw 포인터 대신 스마트 포인터 사용
2. 수동 메모리 관리 대신 컨테이너 사용  
3. RAII 패턴으로 모든 자원 관리
4. 소유권 의미론을 명확히 하는 타입 설계
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

// 1. 스마트 포인터를 활용한 메모리 관리
class SmartMemoryExample {
public:
    static void demonstrateUniquePtr() {
        cout << "\n--- unique_ptr 활용 ---" << endl;
        
        // unique_ptr로 단일 객체 관리
        auto ptr1 = make_unique<string>("Hello Smart Pointer");
        cout << "unique_ptr 값: " << *ptr1 << endl;
        
        // unique_ptr로 배열 관리
        auto arrayPtr = make_unique<int[]>(5);
        for (int i = 0; i < 5; ++i) {
            arrayPtr[i] = i * 10;
        }
        
        cout << "배열 내용: ";
        for (int i = 0; i < 5; ++i) {
            cout << arrayPtr[i] << " ";
        }
        cout << endl;
        
        // 소유권 이전
        auto ptr2 = move(ptr1);
        cout << "소유권 이전 후 ptr1: " << (ptr1 ? "유효" : "nullptr") << endl;
        cout << "소유권 이전 후 ptr2: " << *ptr2 << endl;
    }
    
    static void demonstrateSharedPtr() {
        cout << "\n--- shared_ptr 활용 ---" << endl;
        
        auto shared1 = make_shared<vector<int>>(initializer_list<int>{1, 2, 3, 4, 5});
        cout << "shared1 참조 카운트: " << shared1.use_count() << endl;
        
        {
            auto shared2 = shared1;  // 참조 카운트 증가
            auto shared3 = shared1;  // 참조 카운트 증가
            
            cout << "shared_ptr 공유 후 참조 카운트: " << shared1.use_count() << endl;
            
            shared2->push_back(6);
            cout << "shared2를 통한 수정 후 shared1 크기: " << shared1->size() << endl;
        } // shared2, shared3 소멸
        
        cout << "내부 스코프 종료 후 참조 카운트: " << shared1.use_count() << endl;
    }
    
    static void demonstrateWeakPtr() {
        cout << "\n--- weak_ptr 활용 (순환 참조 방지) ---" << endl;
        
        auto shared = make_shared<string>("Weak Pointer Example");
        weak_ptr<string> weak = shared;
        
        cout << "shared_ptr 참조 카운트: " << shared.use_count() << endl;
        cout << "weak_ptr 만료 여부: " << (weak.expired() ? "만료됨" : "유효함") << endl;
        
        // weak_ptr에서 shared_ptr 생성
        if (auto locked = weak.lock()) {
            cout << "weak_ptr로부터 접근한 값: " << *locked << endl;
        }
        
        shared.reset();  // shared_ptr 해제
        cout << "shared_ptr 해제 후 weak_ptr 만료 여부: " << (weak.expired() ? "만료됨" : "유효함") << endl;
    }
};

// 2. 컨테이너 기반 자원 관리
class ContainerResourceExample {
private:
    vector<unique_ptr<string>> stringPtrs;
    map<string, shared_ptr<vector<int>>> dataMap;
    
public:
    void addString(const string& str) {
        stringPtrs.push_back(make_unique<string>(str));
    }
    
    void addDataVector(const string& key, const vector<int>& data) {
        dataMap[key] = make_shared<vector<int>>(data);
    }
    
    void displayContents() const {
        cout << "문자열 컨테이너:" << endl;
        for (const auto& ptr : stringPtrs) {
            cout << "  " << *ptr << endl;
        }
        
        cout << "데이터 맵:" << endl;
        for (const auto& [key, value] : dataMap) {
            cout << "  " << key << ": ";
            for (int num : *value) {
                cout << num << " ";
            }
            cout << endl;
        }
    }
    
    // 자동 정리: 소멸자에서 모든 스마트 포인터가 자동 해제됨
};

// 3. 커스텀 자원 관리 클래스
class CustomResourceManager {
private:
    struct Resource {
        string name;
        size_t size;
        unique_ptr<char[]> data;
        
        Resource(const string& n, size_t s) : name(n), size(s) {
            data = make_unique<char[]>(size);
            cout << "자원 할당: " << name << " (" << size << " 바이트)" << endl;
        }
        
        ~Resource() {
            cout << "자원 해제: " << name << " (" << size << " 바이트)" << endl;
        }
    };
    
    map<string, unique_ptr<Resource>> resources;
    
public:
    bool allocateResource(const string& name, size_t size) {
        if (resources.find(name) != resources.end()) {
            cout << "이미 존재하는 자원: " << name << endl;
            return false;
        }
        
        try {
            resources[name] = make_unique<Resource>(name, size);
            return true;
        }
        catch (const bad_alloc& e) {
            cout << "자원 할당 실패: " << e.what() << endl;
            return false;
        }
    }
    
    bool deallocateResource(const string& name) {
        auto it = resources.find(name);
        if (it != resources.end()) {
            resources.erase(it);  // unique_ptr 자동 해제
            return true;
        }
        return false;
    }
    
    void listResources() const {
        cout << "현재 관리 중인 자원:" << endl;
        for (const auto& [name, resource] : resources) {
            cout << "  " << name << " (" << resource->size << " 바이트)" << endl;
        }
    }
    
    size_t getTotalMemoryUsage() const {
        size_t total = 0;
        for (const auto& [name, resource] : resources) {
            total += resource->size;
        }
        return total;
    }
    
    // 소멸자에서 모든 자원 자동 해제
    ~CustomResourceManager() {
        cout << "자원 관리자 종료: 모든 자원 자동 해제" << endl;
    }
};

// 4. 파일 시스템 자원 관리
class FileSystemManager {
private:
    map<string, unique_ptr<fstream>> openFiles;
    
public:
    bool openFile(const string& filename, ios::openmode mode) {
        if (openFiles.find(filename) != openFiles.end()) {
            cout << "파일이 이미 열려있음: " << filename << endl;
            return false;
        }
        
        auto file = make_unique<fstream>(filename, mode);
        if (file->is_open()) {
            openFiles[filename] = move(file);
            cout << "파일 열기 성공: " << filename << endl;
            return true;
        } else {
            cout << "파일 열기 실패: " << filename << endl;
            return false;
        }
    }
    
    bool writeToFile(const string& filename, const string& data) {
        auto it = openFiles.find(filename);
        if (it != openFiles.end() && it->second->is_open()) {
            *(it->second) << data << endl;
            cout << "파일 쓰기: " << filename << " <- " << data << endl;
            return true;
        }
        cout << "파일에 쓰기 실패: " << filename << endl;
        return false;
    }
    
    bool closeFile(const string& filename) {
        auto it = openFiles.find(filename);
        if (it != openFiles.end()) {
            it->second->close();
            openFiles.erase(it);
            cout << "파일 닫기: " << filename << endl;
            return true;
        }
        return false;
    }
    
    void listOpenFiles() const {
        cout << "열린 파일 목록:" << endl;
        for (const auto& [filename, file] : openFiles) {
            cout << "  " << filename << (file->is_open() ? " (열림)" : " (닫힘)") << endl;
        }
    }
    
    // 소멸자에서 모든 파일 자동 닫기
    ~FileSystemManager() {
        cout << "파일 시스템 관리자 종료: 모든 파일 자동 닫기" << endl;
        for (auto& [filename, file] : openFiles) {
            if (file->is_open()) {
                file->close();
                cout << "  자동 닫기: " << filename << endl;
            }
        }
    }
};

// 5. 함수 객체와 콜백 관리
class CallbackManager {
private:
    map<string, function<void()>> callbacks;
    
public:
    void registerCallback(const string& name, function<void()> callback) {
        callbacks[name] = callback;
        cout << "콜백 등록: " << name << endl;
    }
    
    bool executeCallback(const string& name) {
        auto it = callbacks.find(name);
        if (it != callbacks.end()) {
            try {
                it->second();
                cout << "콜백 실행 성공: " << name << endl;
                return true;
            }
            catch (const exception& e) {
                cout << "콜백 실행 중 예외: " << name << " - " << e.what() << endl;
                return false;
            }
        }
        cout << "콜백을 찾을 수 없음: " << name << endl;
        return false;
    }
    
    void removeCallback(const string& name) {
        callbacks.erase(name);
        cout << "콜백 제거: " << name << endl;
    }
    
    void executeAllCallbacks() {
        cout << "모든 콜백 실행:" << endl;
        for (const auto& [name, callback] : callbacks) {
            try {
                callback();
                cout << "  " << name << ": 성공" << endl;
            }
            catch (const exception& e) {
                cout << "  " << name << ": 실패 - " << e.what() << endl;
            }
        }
    }
};

int main() {
    cout << "=== 자원 관리 종합 예제 ===" << endl;
    
    // 1. 스마트 포인터 활용
    cout << "\n1. 스마트 포인터 활용:" << endl;
    SmartMemoryExample::demonstrateUniquePtr();
    SmartMemoryExample::demonstrateSharedPtr();
    SmartMemoryExample::demonstrateWeakPtr();
    
    // 2. 컨테이너 기반 자원 관리
    cout << "\n2. 컨테이너 기반 자원 관리:" << endl;
    {
        ContainerResourceExample container;
        container.addString("첫 번째 문자열");
        container.addString("두 번째 문자열");
        container.addDataVector("데이터1", {1, 2, 3, 4});
        container.addDataVector("데이터2", {10, 20, 30});
        
        container.displayContents();
    } // 스코프 종료 시 모든 자원 자동 해제
    cout << "컨테이너 자원 자동 해제 완료" << endl;
    
    // 3. 커스텀 자원 관리
    cout << "\n3. 커스텀 자원 관리:" << endl;
    {
        CustomResourceManager manager;
        
        manager.allocateResource("버퍼1", 1024);
        manager.allocateResource("버퍼2", 2048);
        manager.allocateResource("캐시", 4096);
        
        manager.listResources();
        cout << "총 메모리 사용량: " << manager.getTotalMemoryUsage() << " 바이트" << endl;
        
        manager.deallocateResource("버퍼1");
        manager.listResources();
        cout << "버퍼1 해제 후 메모리 사용량: " << manager.getTotalMemoryUsage() << " 바이트" << endl;
    } // 관리자 소멸 시 모든 자원 자동 해제
    
    // 4. 파일 시스템 자원 관리
    cout << "\n4. 파일 시스템 자원 관리:" << endl;
    {
        FileSystemManager fsManager;
        
        fsManager.openFile("test1.txt", ios::out);
        fsManager.openFile("test2.txt", ios::out);
        
        fsManager.writeToFile("test1.txt", "Hello File System");
        fsManager.writeToFile("test2.txt", "Resource Management");
        
        fsManager.listOpenFiles();
        
        fsManager.closeFile("test1.txt");
        fsManager.listOpenFiles();
    } // 관리자 소멸 시 열린 파일들 자동 닫기
    
    // 5. 콜백 관리
    cout << "\n5. 콜백 관리:" << endl;
    {
        CallbackManager callbackMgr;
        
        // 람다를 이용한 콜백 등록
        callbackMgr.registerCallback("greeting", []() {
            cout << "    안녕하세요!" << endl;
        });
        
        callbackMgr.registerCallback("calculation", []() {
            int result = 10 + 20;
            cout << "    계산 결과: " << result << endl;
        });
        
        callbackMgr.registerCallback("error_callback", []() {
            throw runtime_error("의도적인 오류");
        });
        
        // 개별 콜백 실행
        callbackMgr.executeCallback("greeting");
        callbackMgr.executeCallback("calculation");
        callbackMgr.executeCallback("error_callback");
        
        // 모든 콜백 실행
        callbackMgr.executeAllCallbacks();
    }
    
    cout << "\n=== 자원 관리 모범 사례 ===" << endl;
    cout << "1. Raw 포인터 대신 스마트 포인터 사용" << endl;
    cout << "2. 수동 메모리 관리 대신 STL 컨테이너 활용" << endl;
    cout << "3. RAII 패턴으로 모든 자원을 객체로 래핑" << endl;
    cout << "4. 소유권 의미론을 명확히 하는 타입 설계" << endl;
    cout << "5. 예외 안전성을 고려한 자원 해제 보장" << endl;
    cout << "6. 스코프 기반 자원 관리로 누수 방지" << endl;
    
    return 0;
}
```

---

## 7. 예제 07: 프로젝트 구조화 (07_project_structure.cpp)

### 예제 정의
대규모 C++ 프로젝트의 구조화와 모듈 분리 기법을 학습합니다.

```cpp
/*
주제: 프로젝트 구조화 (Project Structure)
정의: 대규모 C++ 프로젝트를 유지보수하기 쉽고 확장 가능하도록 체계적으로 조직화하는 소프트웨어 아키텍처 기법

핵심 개념: 모듈화, 헤더 분리, 네임스페이스 활용, 의존성 관리
정의:
- 모듈화: 기능별로 코드를 분리하여 독립적인 모듈로 구성하는 설계 원칙
- 헤더 분리: 인터페이스(헤더)와 구현(소스)을 분리하여 컴파일 의존성 감소
- 네임스페이스 활용: 논리적 그룹핑과 이름 충돌 방지를 위한 명명 공간 설계
- 의존성 관리: 모듈 간 의존 관계를 최소화하고 명확히 정의하는 전략

프로젝트 구조 예시:
Project/
├── include/           # 공개 헤더 파일들
│   ├── core/         # 핵심 모듈 헤더
│   ├── utils/        # 유틸리티 헤더
│   └── config/       # 설정 관련 헤더
├── src/              # 구현 파일들
│   ├── core/         # 핵심 모듈 구현
│   ├── utils/        # 유틸리티 구현
│   └── main.cpp      # 메인 파일
├── tests/            # 테스트 코드
├── docs/             # 문서
└── CMakeLists.txt    # 빌드 설정
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>
using namespace std;

// =================================================================
// 1. Core 모듈 (핵심 비즈니스 로직)
// =================================================================

namespace Core {
    // 추상 인터페이스 정의
    class IDataProcessor {
    public:
        virtual ~IDataProcessor() = default;
        virtual void processData(const string& data) = 0;
        virtual string getResult() const = 0;
    };
    
    // 구체적인 구현
    class TextProcessor : public IDataProcessor {
    private:
        string processedText;
        
    public:
        void processData(const string& data) override {
            processedText = "[PROCESSED] " + data;
            cout << "Core::TextProcessor 처리 완료" << endl;
        }
        
        string getResult() const override {
            return processedText;
        }
    };
    
    class NumberProcessor : public IDataProcessor {
    private:
        string result;
        
    public:
        void processData(const string& data) override {
            // 간단한 숫자 합계 계산 시뮬레이션
            int sum = 0;
            for (char c : data) {
                if (isdigit(c)) {
                    sum += (c - '0');
                }
            }
            result = "숫자 합계: " + to_string(sum);
            cout << "Core::NumberProcessor 처리 완료" << endl;
        }
        
        string getResult() const override {
            return result;
        }
    };
    
    // 팩토리 패턴
    class ProcessorFactory {
    public:
        enum class ProcessorType { TEXT, NUMBER };
        
        static unique_ptr<IDataProcessor> createProcessor(ProcessorType type) {
            switch (type) {
                case ProcessorType::TEXT:
                    return make_unique<TextProcessor>();
                case ProcessorType::NUMBER:
                    return make_unique<NumberProcessor>();
                default:
                    return nullptr;
            }
        }
    };
}

// =================================================================
// 2. Utils 모듈 (유틸리티 함수들)
// =================================================================

namespace Utils {
    // 로깅 시스템
    class Logger {
    private:
        vector<string> logs;
        bool isEnabled;
        
    public:
        Logger() : isEnabled(true) {}
        
        void log(const string& message) {
            if (isEnabled) {
                string logEntry = "[LOG] " + message;
                logs.push_back(logEntry);
                cout << logEntry << endl;
            }
        }
        
        void error(const string& message) {
            string errorEntry = "[ERROR] " + message;
            logs.push_back(errorEntry);
            cout << errorEntry << endl;
        }
        
        void setEnabled(bool enabled) {
            isEnabled = enabled;
        }
        
        vector<string> getAllLogs() const {
            return logs;
        }
        
        void clearLogs() {
            logs.clear();
        }
    };
    
    // 문자열 유틸리티
    class StringUtils {
    public:
        static string toUpper(const string& str) {
            string result = str;
            transform(result.begin(), result.end(), result.begin(), ::toupper);
            return result;
        }
        
        static string toLower(const string& str) {
            string result = str;
            transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }
        
        static vector<string> split(const string& str, char delimiter) {
            vector<string> tokens;
            string token;
            for (char c : str) {
                if (c == delimiter) {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token.clear();
                    }
                } else {
                    token += c;
                }
            }
            if (!token.empty()) {
                tokens.push_back(token);
            }
            return tokens;
        }
        
        static string join(const vector<string>& strings, const string& separator) {
            string result;
            for (size_t i = 0; i < strings.size(); ++i) {
                result += strings[i];
                if (i < strings.size() - 1) {
                    result += separator;
                }
            }
            return result;
        }
    };
    
    // 성능 측정 유틸리티
    class PerformanceTimer {
    private:
        map<string, chrono::high_resolution_clock::time_point> startTimes;
        map<string, long long> durations;
        
    public:
        void startTimer(const string& name) {
            startTimes[name] = chrono::high_resolution_clock::now();
        }
        
        void stopTimer(const string& name) {
            auto it = startTimes.find(name);
            if (it != startTimes.end()) {
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - it->second);
                durations[name] = duration.count();
                startTimes.erase(it);
            }
        }
        
        long long getDuration(const string& name) const {
            auto it = durations.find(name);
            return (it != durations.end()) ? it->second : -1;
        }
        
        void printAllTimers() const {
            cout << "=== 성능 측정 결과 ===" << endl;
            for (const auto& [name, duration] : durations) {
                cout << name << ": " << duration << " 마이크로초" << endl;
            }
        }
    };
}

// =================================================================
// 3. Config 모듈 (설정 관리)
// =================================================================

namespace Config {
    class ApplicationConfig {
    private:
        map<string, string> settings;
        static unique_ptr<ApplicationConfig> instance;
        
        ApplicationConfig() {
            // 기본 설정 로드
            loadDefaultSettings();
        }
        
    public:
        static ApplicationConfig& getInstance() {
            if (!instance) {
                instance = unique_ptr<ApplicationConfig>(new ApplicationConfig());
            }
            return *instance;
        }
        
        void setSetting(const string& key, const string& value) {
            settings[key] = value;
        }
        
        string getSetting(const string& key, const string& defaultValue = "") const {
            auto it = settings.find(key);
            return (it != settings.end()) ? it->second : defaultValue;
        }
        
        void loadDefaultSettings() {
            settings["app_name"] = "C++ Project Example";
            settings["version"] = "1.0.0";
            settings["debug_mode"] = "true";
            settings["max_threads"] = "4";
            settings["log_level"] = "INFO";
        }
        
        void printAllSettings() const {
            cout << "=== 애플리케이션 설정 ===" << endl;
            for (const auto& [key, value] : settings) {
                cout << key << " = " << value << endl;
            }
        }
    };
    
    // 정적 멤버 정의
    unique_ptr<ApplicationConfig> ApplicationConfig::instance = nullptr;
}

// =================================================================
// 4. Service 모듈 (비즈니스 서비스)
// =================================================================

namespace Service {
    class DataProcessingService {
    private:
        Utils::Logger& logger;
        Utils::PerformanceTimer timer;
        vector<unique_ptr<Core::IDataProcessor>> processors;
        
    public:
        explicit DataProcessingService(Utils::Logger& log) : logger(log) {}
        
        void addProcessor(unique_ptr<Core::IDataProcessor> processor) {
            processors.push_back(move(processor));
            logger.log("프로세서 추가됨");
        }
        
        vector<string> processAllData(const vector<string>& dataList) {
            logger.log("데이터 처리 시작");
            timer.startTimer("total_processing");
            
            vector<string> results;
            
            for (const auto& data : dataList) {
                timer.startTimer("single_process");
                
                for (auto& processor : processors) {
                    processor->processData(data);
                    results.push_back(processor->getResult());
                }
                
                timer.stopTimer("single_process");
                logger.log("데이터 처리 완료: " + data);
            }
            
            timer.stopTimer("total_processing");
            logger.log("모든 데이터 처리 완료");
            
            return results;
        }
        
        void printPerformanceStats() {
            timer.printAllTimers();
        }
    };
    
    class ReportService {
    private:
        Utils::Logger& logger;
        
    public:
        explicit ReportService(Utils::Logger& log) : logger(log) {}
        
        void generateReport(const vector<string>& results) {
            logger.log("리포트 생성 시작");
            
            cout << "\n=== 처리 결과 리포트 ===" << endl;
            cout << "총 결과 수: " << results.size() << endl;
            
            for (size_t i = 0; i < results.size(); ++i) {
                cout << (i + 1) << ". " << results[i] << endl;
            }
            
            // 통계 정보
            cout << "\n=== 통계 정보 ===" << endl;
            cout << "평균 결과 길이: " << calculateAverageLength(results) << " 문자" << endl;
            
            logger.log("리포트 생성 완료");
        }
        
    private:
        double calculateAverageLength(const vector<string>& results) const {
            if (results.empty()) return 0.0;
            
            size_t totalLength = 0;
            for (const auto& result : results) {
                totalLength += result.length();
            }
            
            return static_cast<double>(totalLength) / results.size();
        }
    };
}

// =================================================================
// 5. Application 모듈 (애플리케이션 진입점)
// =================================================================

namespace Application {
    class MainApplication {
    private:
        Utils::Logger logger;
        Config::ApplicationConfig& config;
        unique_ptr<Service::DataProcessingService> dataService;
        unique_ptr<Service::ReportService> reportService;
        
    public:
        MainApplication() : config(Config::ApplicationConfig::getInstance()) {
            dataService = make_unique<Service::DataProcessingService>(logger);
            reportService = make_unique<Service::ReportService>(logger);
        }
        
        void initialize() {
            logger.log("애플리케이션 초기화");
            
            // 설정 로드
            config.printAllSettings();
            
            // 프로세서 등록
            dataService->addProcessor(
                Core::ProcessorFactory::createProcessor(Core::ProcessorFactory::ProcessorType::TEXT)
            );
            dataService->addProcessor(
                Core::ProcessorFactory::createProcessor(Core::ProcessorFactory::ProcessorType::NUMBER)
            );
            
            logger.log("초기화 완료");
        }
        
        void run() {
            logger.log("애플리케이션 실행 시작");
            
            // 테스트 데이터
            vector<string> testData = {
                "Hello World 123",
                "C++ Programming 456",
                "Exception Handling 789"
            };
            
            // 데이터 처리
            auto results = dataService->processAllData(testData);
            
            // 리포트 생성
            reportService->generateReport(results);
            
            // 성능 통계
            dataService->printPerformanceStats();
            
            logger.log("애플리케이션 실행 완료");
        }
        
        void shutdown() {
            logger.log("애플리케이션 종료");
            
            // 정리 작업
            dataService.reset();
            reportService.reset();
            
            // 로그 요약
            auto allLogs = logger.getAllLogs();
            cout << "\n=== 로그 요약 ===" << endl;
            cout << "총 로그 수: " << allLogs.size() << endl;
            
            logger.log("종료 완료");
        }
    };
}

int main() {
    cout << "=== 프로젝트 구조화 예제 ===" << endl;
    
    try {
        // 애플리케이션 생성 및 실행
        Application::MainApplication app;
        
        app.initialize();
        app.run();
        app.shutdown();
        
    } catch (const exception& e) {
        cout << "애플리케이션 오류: " << e.what() << endl;
        return 1;
    }
    
    cout << "\n=== 프로젝트 구조화 원칙 ===" << endl;
    cout << "1. 네임스페이스로 논리적 모듈 분리" << endl;
    cout << "2. 인터페이스와 구현 분리 (추상화)" << endl;
    cout << "3. 팩토리 패턴으로 객체 생성 관리" << endl;
    cout << "4. 싱글톤 패턴으로 전역 설정 관리" << endl;
    cout << "5. 의존성 주입으로 결합도 감소" << endl;
    cout << "6. RAII 패턴으로 자원 관리 자동화" << endl;
    
    return 0;
}
```

---

## 8. 예제 08: 코딩 표준 (08_coding_standards.cpp)

### 예제 정의
C++ 코딩 표준과 모범 사례를 적용한 고품질 코드 작성법을 학습합니다.

```cpp
/*
주제: 코딩 표준 (Coding Standards)
정의: 일관성 있고 읽기 쉬우며 유지보수하기 좋은 코드를 작성하기 위한 규칙과 관례의 집합

핵심 개념: 네이밍 컨벤션, 코드 포맷팅, 주석 작성, 오류 처리
정의:
- 네이밍 컨벤션: 변수, 함수, 클래스 등의 이름을 일관성 있게 짓는 규칙
- 코드 포맷팅: 들여쓰기, 중괄호 위치, 공백 등의 코드 레이아웃 규칙
- 주석 작성: 코드의 의도와 설명을 명확히 전달하는 주석 작성 가이드라인
- 오류 처리: 예외 상황을 일관성 있게 처리하는 방법론

Google C++ Style Guide 주요 원칙:
1. 명확성: 코드는 명확하고 이해하기 쉬워야 함
2. 일관성: 프로젝트 전체에서 일관된 스타일 유지
3. 간결성: 불필요한 복잡성 피하기
4. 안전성: 버그와 보안 취약점 최소화
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <cassert>

/**
 * @brief 학생 정보를 관리하는 클래스
 * 
 * 이 클래스는 학생의 기본 정보(이름, ID, 점수)를 저장하고
 * 관련된 연산들을 제공합니다.
 * 
 * @author C++ Development Team
 * @version 1.0
 * @since 2024-01-01
 */
class StudentRecord {
private:
    // 멤버 변수는 소문자로 시작하고 언더스코어 사용
    std::string student_name_;
    int student_id_;
    std::vector<double> test_scores_;
    
    // 상수는 k로 시작하는 카멜케이스
    static constexpr int kMaxStudentId = 999999;
    static constexpr double kMinValidScore = 0.0;
    static constexpr double kMaxValidScore = 100.0;
    
public:
    /**
     * @brief StudentRecord 생성자
     * @param name 학생 이름 (비어있으면 안됨)
     * @param id 학생 ID (1 이상 999999 이하)
     * @throws std::invalid_argument 잘못된 매개변수가 전달된 경우
     */
    explicit StudentRecord(const std::string& name, int id) 
        : student_name_(name), student_id_(id) {
        
        // 입력 검증은 생성자에서 수행
        if (name.empty()) {
            throw std::invalid_argument("학생 이름은 비어있을 수 없습니다");
        }
        
        if (id <= 0 || id > kMaxStudentId) {
            throw std::invalid_argument(
                "학생 ID는 1부터 " + std::to_string(kMaxStudentId) + " 사이여야 합니다"
            );
        }
    }
    
    // 복사 방지 (Rule of Five 적용)
    StudentRecord(const StudentRecord&) = delete;
    StudentRecord& operator=(const StudentRecord&) = delete;
    
    // 이동은 허용
    StudentRecord(StudentRecord&&) = default;
    StudentRecord& operator=(StudentRecord&&) = default;
    
    // 가상 소멸자 (상속 가능성 고려)
    virtual ~StudentRecord() = default;
    
    /**
     * @brief 시험 점수를 추가합니다
     * @param score 추가할 점수 (0.0 이상 100.0 이하)
     * @throws std::out_of_range 점수가 유효 범위를 벗어난 경우
     */
    void AddTestScore(double score) {
        // 사전 조건 검사
        if (score < kMinValidScore || score > kMaxValidScore) {
            throw std::out_of_range(
                "점수는 " + std::to_string(kMinValidScore) + "점부터 " + 
                std::to_string(kMaxValidScore) + "점 사이여야 합니다"
            );
        }
        
        test_scores_.push_back(score);
    }
    
    /**
     * @brief 평균 점수를 계산합니다
     * @return 평균 점수 (점수가 없으면 0.0)
     */
    double CalculateAverageScore() const noexcept {
        if (test_scores_.empty()) {
            return 0.0;
        }
        
        double sum = 0.0;
        for (size_t i = 0; i < history_.size(); ++i) {
            sum += history_.at(i);
        }
        
        double average = sum / static_cast<double>(history_.size());
        LOG_DEBUG(logger_, "평균 계산 완료: " + to_string(average));
        
        return average;
    }
    
    void PrintHistory() {
        LOG_INFO(logger_, "계산 히스토리 출력");
        history_.PrintDebugInfo();
    }
    
    void SimulateBug() {
        LOG_WARNING(logger_, "의도적 버그 시뮬레이션 시작");
        
        try {
            // 버그 1: 0으로 나누기
            double result1 = Divide(10.0, 0.0);
            LOG_INFO(logger_, "버그 1 결과: " + to_string(result1));
            
        } catch (const exception& e) {
            LOG_ERROR(logger_, "버그 1 예외: " + string(e.what()));
        }
        
        // 버그 2: 빈 히스토리에서 평균 계산
        DebugVector<double> empty_history("empty", logger_);
        // double avg = GetAverage();  // 이 줄의 주석을 해제하면 단언문 실패
    }
};

void DemonstrateDebuggingTechniques() {
    cout << "=== 디버깅 기법 종합 예제 ===" << endl;
    
    // 1. 로깅 시스템 설정
    DebugLogger logger(LogLevel::DEBUG, true, true, "debug_demo.log");
    PerformanceProfiler profiler(logger);
    MemoryDebugger memory_debugger(logger);
    
    LOG_INFO(logger, "디버깅 세션 시작");
    
    // 2. 메모리 디버깅
    {
        LOG_INFO(logger, "메모리 디버깅 테스트");
        
        void* ptr1 = memory_debugger.Allocate(1024);
        void* ptr2 = memory_debugger.Allocate(2048);
        
        memory_debugger.Deallocate(ptr1);
        // ptr2는 의도적으로 해제하지 않음 (메모리 누수 시뮬레이션)
        
        memory_debugger.PrintMemoryReport();
    }
    
    // 3. 성능 프로파일링
    {
        LOG_INFO(logger, "성능 프로파일링 테스트");
        
        // 무거운 작업 시뮬레이션
        for (int i = 0; i < 3; ++i) {
            PROFILE_SCOPE(profiler, "heavy_computation");
            
            // 시간이 걸리는 작업 시뮬레이션
            volatile int sum = 0;
            for (int j = 0; j < 100000; ++j) {
                sum += j;
            }
        }
        
        profiler.PrintStatistics();
    }
    
    // 4. 컨테이너 디버깅
    {
        LOG_INFO(logger, "컨테이너 디버깅 테스트");
        
        DebugVector<string> debug_vec("test_vector", logger);
        debug_vec.push_back("첫 번째");
        debug_vec.push_back("두 번째");
        debug_vec.push_back("세 번째");
        
        debug_vec.PrintDebugInfo();
        
        // 범위 검사 테스트
        try {
            string& item = debug_vec.at(1);  // 정상
            LOG_INFO(logger, "정상 접근: " + item);
            
            // string& invalid = debug_vec.at(10);  // 단언문 실패 (주석 해제하면 프로그램 종료)
        } catch (const exception& e) {
            LOG_ERROR(logger, "예외 발생: " + string(e.what()));
        }
    }
    
    // 5. 통합 버그 시뮬레이션
    {
        LOG_INFO(logger, "통합 버그 시뮬레이션");
        
        BuggyCalculator calc(logger, profiler);
        
        // 정상적인 연산
        calc.Divide(10.0, 2.0);
        calc.Divide(15.0, 3.0);
        calc.Divide(20.0, 4.0);
        
        double avg = calc.GetAverage();
        LOG_INFO(logger, "평균: " + to_string(avg));
        
        calc.PrintHistory();
        
        // 버그 시뮬레이션 (주의: 일부는 프로그램을 종료시킬 수 있음)
        // calc.SimulateBug();
    }
    
    LOG_INFO(logger, "디버깅 세션 완료");
}

// =================================================================
// 7. 단위 테스트 프레임워크 (간단한 버전)
// =================================================================

class SimpleTestFramework {
private:
    int total_tests_;
    int passed_tests_;
    DebugLogger& logger_;
    
public:
    explicit SimpleTestFramework(DebugLogger& logger) 
        : total_tests_(0), passed_tests_(0), logger_(logger) {}
    
    template<typename T>
    void AssertEqual(const T& expected, const T& actual, const string& test_name) {
        total_tests_++;
        
        if (expected == actual) {
            passed_tests_++;
            LOG_INFO(logger_, "✓ PASS: " + test_name);
        } else {
            stringstream ss;
            ss << "✗ FAIL: " << test_name << " (예상: " << expected << ", 실제: " << actual << ")";
            LOG_ERROR(logger_, ss.str());
        }
    }
    
    void AssertTrue(bool condition, const string& test_name) {
        total_tests_++;
        
        if (condition) {
            passed_tests_++;
            LOG_INFO(logger_, "✓ PASS: " + test_name);
        } else {
            LOG_ERROR(logger_, "✗ FAIL: " + test_name + " (조건이 거짓)");
        }
    }
    
    void AssertThrows(function<void()> func, const string& test_name) {
        total_tests_++;
        
        try {
            func();
            LOG_ERROR(logger_, "✗ FAIL: " + test_name + " (예외가 발생하지 않음)");
        } catch (...) {
            passed_tests_++;
            LOG_INFO(logger_, "✓ PASS: " + test_name + " (예상된 예외 발생)");
        }
    }
    
    void PrintSummary() {
        LOG_INFO(logger_, "=== 테스트 결과 요약 ===");
        LOG_INFO(logger_, "총 테스트: " + to_string(total_tests_));
        LOG_INFO(logger_, "통과: " + to_string(passed_tests_));
        LOG_INFO(logger_, "실패: " + to_string(total_tests_ - passed_tests_));
        
        double success_rate = (total_tests_ > 0) ? 
            (static_cast<double>(passed_tests_) / total_tests_ * 100.0) : 0.0;
        
        stringstream ss;
        ss << "성공률: " << fixed << setprecision(1) << success_rate << "%";
        LOG_INFO(logger_, ss.str());
    }
};

void RunUnitTests() {
    cout << "\n=== 단위 테스트 실행 ===" << endl;
    
    DebugLogger test_logger(LogLevel::INFO);
    SimpleTestFramework test_framework(test_logger);
    PerformanceProfiler test_profiler(test_logger);
    
    // 계산기 테스트
    BuggyCalculator calc(test_logger, test_profiler);
    
    // 정상 케이스 테스트
    test_framework.AssertEqual(5.0, calc.Divide(10.0, 2.0), "정상 나눗셈");
    test_framework.AssertEqual(3.0, calc.Divide(9.0, 3.0), "또 다른 정상 나눗셈");
    
    double avg = calc.GetAverage();
    test_framework.AssertEqual(4.0, avg, "평균 계산");
    
    // 예외 상황 테스트
    test_framework.AssertThrows([&calc]() {
        calc.Divide(1.0, 0.0);  // 0으로 나누기
    }, "0으로 나누기 예외");
    
    test_framework.PrintSummary();
}

int main() {
    cout << "=== C++ 디버깅 기법 종합 ===" << endl;
    
    // 메인 디버깅 데모
    DemonstrateDebuggingTechniques();
    
    // 단위 테스트 실행
    RunUnitTests();
    
    cout << "\n=== 디버깅 모범 사례 ===" << endl;
    cout << "1. 체계적인 로깅 시스템 구축" << endl;
    cout << "2. 단언문으로 프로그램 가정 검증" << endl;
    cout << "3. 성능 프로파일링으로 병목 지점 식별" << endl;
    cout << "4. 메모리 디버깅으로 누수 방지" << endl;
    cout << "5. 단위 테스트로 회귀 방지" << endl;
    cout << "6. IDE 디버거 활용한 단계별 실행" << endl;
    cout << "7. 재현 가능한 최소 예제 작성" << endl;
    
    return 0;
}
```

---

## 10. 예제 10: 종합 프로젝트 (10_final_project.cpp)

### 예제 정의
지금까지 학습한 모든 내용을 종합하여 완전한 애플리케이션을 구현합니다.

```cpp
/*
주제: 종합 프로젝트 (Comprehensive Final Project)
정의: C++의 모든 핵심 개념을 통합하여 실제 사용 가능한 완전한 애플리케이션을 구현하는 최종 프로젝트

프로젝트 개요: 도서관 관리 시스템
- 객체지향 설계 (클래스, 상속, 다형성)
- 예외 처리 및 안전성 보장
- STL 컨테이너와 알고리즘 활용
- 스마트 포인터를 통한 메모리 관리
- 파일 I/O와 데이터 영속성
- 모던 C++ 기능 활용

시스템 요구사항:
1. 도서 및 회원 정보 관리
2. 대출/반납 기능
3. 검색 및 필터링
4. 데이터 저장/로드
5. 예외 처리 및 로깅
6. 성능 최적화
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <functional>
#include <stdexcept>
using namespace std;

// =================================================================
// 1. 기본 데이터 모델 (Model Layer)
// =================================================================

namespace Model {
    // 기본 엔티티 인터페이스
    class IEntity {
    public:
        virtual ~IEntity() = default;
        virtual string GetId() const = 0;
        virtual string ToString() const = 0;
        virtual void FromString(const string& data) = 0;
    };
    
    // 도서 클래스
    class Book : public IEntity {
    private:
        string isbn_;
        string title_;
        string author_;
        string category_;
        bool is_available_;
        chrono::system_clock::time_point publication_date_;
        
    public:
        Book() : is_available_(true) {}
        
        Book(const string& isbn, const string& title, const string& author, 
             const string& category = "일반") 
            : isbn_(isbn), title_(title), author_(author), category_(category), 
              is_available_(true), publication_date_(chrono::system_clock::now()) {
            
            if (isbn.empty() || title.empty() || author.empty()) {
                throw invalid_argument("도서 정보가 불완전합니다");
            }
        }
        
        // IEntity 구현
        string GetId() const override { return isbn_; }
        
        string ToString() const override {
            stringstream ss;
            auto time_t = chrono::system_clock::to_time_t(publication_date_);
            ss << isbn_ << "|" << title_ << "|" << author_ << "|" << category_ 
               << "|" << (is_available_ ? "1" : "0") << "|" 
               << put_time(localtime(&time_t), "%Y-%m-%d");
            return ss.str();
        }
        
        void FromString(const string& data) override {
            stringstream ss(data);
            string available_str, date_str;
            
            getline(ss, isbn_, '|');
            getline(ss, title_, '|');
            getline(ss, author_, '|');
            getline(ss, category_, '|');
            getline(ss, available_str, '|');
            getline(ss, date_str);
            
            is_available_ = (available_str == "1");
            
            // 날짜 파싱 (간단히 구현)
            publication_date_ = chrono::system_clock::now();
        }
        
        // Getters
        const string& GetISBN() const { return isbn_; }
        const string& GetTitle() const { return title_; }
        const string& GetAuthor() const { return author_; }
        const string& GetCategory() const { return category_; }
        bool IsAvailable() const { return is_available_; }
        
        // Setters
        void SetAvailable(bool available) { is_available_ = available; }
        void SetCategory(const string& category) { category_ = category; }
        
        // 검색 지원
        bool MatchesKeyword(const string& keyword) const {
            string lower_keyword = keyword;
            transform(lower_keyword.begin(), lower_keyword.end(), 
                     lower_keyword.begin(), ::tolower);
            
            auto contains = [&lower_keyword](const string& text) {
                string lower_text = text;
                transform(lower_text.begin(), lower_text.end(), 
                         lower_text.begin(), ::tolower);
                return lower_text.find(lower_keyword) != string::npos;
            };
            
            return contains(title_) || contains(author_) || contains(category_);
        }
    };
    
    // 회원 클래스
    class Member : public IEntity {
    private:
        string member_id_;
        string name_;
        string email_;
        chrono::system_clock::time_point join_date_;
        set<string> borrowed_books_;
        
        static constexpr size_t kMaxBorrowLimit = 3;
        
    public:
        Member() : join_date_(chrono::system_clock::now()) {}
        
        Member(const string& id, const string& name, const string& email)
            : member_id_(id), name_(name), email_(email), 
              join_date_(chrono::system_clock::now()) {
            
            if (id.empty() || name.empty()) {
                throw invalid_argument("회원 정보가 불완전합니다");
            }
        }
        
        // IEntity 구현
        string GetId() const override { return member_id_; }
        
        string ToString() const override {
            stringstream ss;
            auto time_t = chrono::system_clock::to_time_t(join_date_);
            ss << member_id_ << "|" << name_ << "|" << email_ << "|"
               << put_time(localtime(&time_t), "%Y-%m-%d") << "|";
            
            // 대출 도서 목록
            bool first = true;
            for (const auto& isbn : borrowed_books_) {
                if (!first) ss << ",";
                ss << isbn;
                first = false;
            }
            
            return ss.str();
        }
        
        void FromString(const string& data) override {
            stringstream ss(data);
            string date_str, books_str;
            
            getline(ss, member_id_, '|');
            getline(ss, name_, '|');
            getline(ss, email_, '|');
            getline(ss, date_str, '|');
            getline(ss, books_str);
            
            // 대출 도서 파싱
            if (!books_str.empty()) {
                stringstream books_ss(books_str);
                string isbn;
                while (getline(books_ss, isbn, ',')) {
                    borrowed_books_.insert(isbn);
                }
            }
            
            join_date_ = chrono::system_clock::now();
        }
        
        // 대출 관리
        bool CanBorrow() const {
            return borrowed_books_.size() < kMaxBorrowLimit;
        }
        
        bool BorrowBook(const string& isbn) {
            if (!CanBorrow()) return false;
            return borrowed_books_.insert(isbn).second;
        }
        
        bool ReturnBook(const string& isbn) {
            return borrowed_books_.erase(isbn) > 0;
        }
        
        bool HasBorrowed(const string& isbn) const {
            return borrowed_books_.find(isbn) != borrowed_books_.end();
        }
        
        // Getters
        const string& GetName() const { return name_; }
        const string& GetEmail() const { return email_; }
        const set<string>& GetBorrowedBooks() const { return borrowed_books_; }
        size_t GetBorrowedCount() const { return borrowed_books_.size(); }
        size_t GetMaxBorrowLimit() const { return kMaxBorrowLimit; }
    };
    
    // 대출 기록 클래스
    class LoanRecord {
    private:
        string record_id_;
        string member_id_;
        string isbn_;
        chrono::system_clock::time_point borrow_date_;
        chrono::system_clock::time_point due_date_;
        chrono::system_clock::time_point return_date_;
        bool is_returned_;
        
        static constexpr int kLoanPeriodDays = 14;
        
    public:
        LoanRecord(const string& member_id, const string& isbn)
            : member_id_(member_id), isbn_(isbn), 
              borrow_date_(chrono::system_clock::now()), is_returned_(false) {
            
            // 대출 ID 생성 (간단히 구현)
            record_id_ = member_id + "_" + isbn + "_" + to_string(
                chrono::duration_cast<chrono::seconds>(
                    borrow_date_.time_since_epoch()).count());
            
            // 반납 예정일 계산
            due_date_ = borrow_date_ + chrono::hours(24 * kLoanPeriodDays);
        }
        
        void ReturnBook() {
            return_date_ = chrono::system_clock::now();
            is_returned_ = true;
        }
        
        bool IsOverdue() const {
            if (is_returned_) return false;
            return chrono::system_clock::now() > due_date_;
        }
        
        int GetOverdueDays() const {
            if (!IsOverdue()) return 0;
            
            auto now = chrono::system_clock::now();
            auto overdue_duration = now - due_date_;
            return chrono::duration_cast<chrono::hours>(overdue_duration).count() / 24;
        }
        
        // Getters
        const string& GetRecordId() const { return record_id_; }
        const string& GetMemberId() const { return member_id_; }
        const string& GetISBN() const { return isbn_; }
        bool IsReturned() const { return is_returned_; }
        chrono::system_clock::time_point GetBorrowDate() const { return borrow_date_; }
        chrono::system_clock::time_point GetDueDate() const { return due_date_; }
    };
}

// =================================================================
// 2. 예외 처리 시스템 (Exception Layer)
// =================================================================

namespace Exception {
    class LibraryException : public exception {
    protected:
        string message_;
        
    public:
        explicit LibraryException(const string& msg) : message_(msg) {}
        const char* what() const noexcept override { return message_.c_str(); }
    };
    
    class BookNotFoundException : public LibraryException {
    public:
        explicit BookNotFoundException(const string& isbn) 
            : LibraryException("도서를 찾을 수 없습니다: " + isbn) {}
    };
    
    class MemberNotFoundException : public LibraryException {
    public:
        explicit MemberNotFoundException(const string& member_id) 
            : LibraryException("회원을 찾을 수 없습니다: " + member_id) {}
    };
    
    class BookNotAvailableException : public LibraryException {
    public:
        explicit BookNotAvailableException(const string& isbn) 
            : LibraryException("도서가 대출 중입니다: " + isbn) {}
    };
    
    class BorrowLimitExceededException : public LibraryException {
    public:
        explicit BorrowLimitExceededException(const string& member_id) 
            : LibraryException("대출 한도를 초과했습니다: " + member_id) {}
    };
    
    class FileOperationException : public LibraryException {
    public:
        explicit FileOperationException(const string& operation) 
            : LibraryException("파일 작업 실패: " + operation) {}
    };
}

// =================================================================
// 3. 서비스 레이어 (Service Layer)
// =================================================================

namespace Service {
    // 데이터 저장소 인터페이스
    template<typename T>
    class IRepository {
    public:
        virtual ~IRepository() = default;
        virtual void Add(unique_ptr<T> entity) = 0;
        virtual T* FindById(const string& id) = 0;
        virtual vector<T*> FindAll() = 0;
        virtual bool Remove(const string& id) = 0;
        virtual void Clear() = 0;
        virtual size_t Count() const = 0;
    };
    
    // 메모리 기반 저장소 구현
    template<typename T>
    class MemoryRepository : public IRepository<T> {
    private:
        map<string, unique_ptr<T>> entities_;
        
    public:
        void Add(unique_ptr<T> entity) override {
            if (!entity) throw invalid_argument("null 엔티티는 추가할 수 없습니다");
            
            string id = entity->GetId();
            entities_[id] = move(entity);
        }
        
        T* FindById(const string& id) override {
            auto it = entities_.find(id);
            return (it != entities_.end()) ? it->second.get() : nullptr;
        }
        
        vector<T*> FindAll() override {
            vector<T*> result;
            for (auto& [id, entity] : entities_) {
                result.push_back(entity.get());
            }
            return result;
        }
        
        bool Remove(const string& id) override {
            return entities_.erase(id) > 0;
        }
        
        void Clear() override {
            entities_.clear();
        }
        
        size_t Count() const override {
            return entities_.size();
        }
        
        // 조건부 검색
        template<typename Predicate>
        vector<T*> FindWhere(Predicate pred) {
            vector<T*> result;
            for (auto& [id, entity] : entities_) {
                if (pred(*entity)) {
                    result.push_back(entity.get());
                }
            }
            return result;
        }
    };
    
    // 파일 I/O 서비스
    class FileService {
    public:
        template<typename T>
        static void SaveToFile(const string& filename, const vector<T*>& entities) {
            ofstream file(filename);
            if (!file.is_open()) {
                throw Exception::FileOperationException("파일 저장: " + filename);
            }
            
            for (const auto& entity : entities) {
                file << entity->ToString() << endl;
            }
        }
        
        template<typename T>
        static void LoadFromFile(const string& filename, 
                                function<unique_ptr<T>()> factory,
                                function<void(unique_ptr<T>)> callback) {
            ifstream file(filename);
            if (!file.is_open()) {
                throw Exception::FileOperationException("파일 로드: " + filename);
            }
            
            string line;
            while (getline(file, line)) {
                if (!line.empty()) {
                    auto entity = factory();
                    entity->FromString(line);
                    callback(move(entity));
                }
            }
        }
    };
    
    // 도서관 관리 서비스
    class LibraryService {
    private:
        unique_ptr<IRepository<Model::Book>> book_repo_;
        unique_ptr<IRepository<Model::Member>> member_repo_;
        vector<unique_ptr<Model::LoanRecord>> loan_records_;
        
    public:
        LibraryService() {
            book_repo_ = make_unique<MemoryRepository<Model::Book>>();
            member_repo_ = make_unique<MemoryRepository<Model::Member>>();
        }
        
        // 도서 관리
        void AddBook(const string& isbn, const string& title, 
                    const string& author, const string& category = "일반") {
            auto book = make_unique<Model::Book>(isbn, title, author, category);
            book_repo_->Add(move(book));
        }
        
        Model::Book* FindBook(const string& isbn) {
            return book_repo_->FindById(isbn);
        }
        
        vector<Model::Book*> SearchBooks(const string& keyword) {
            auto memory_repo = dynamic_cast<MemoryRepository<Model::Book>*>(book_repo_.get());
            if (memory_repo) {
                return memory_repo->FindWhere([&keyword](const Model::Book& book) {
                    return book.MatchesKeyword(keyword);
                });
            }
            return {};
        }
        
        vector<Model::Book*> GetAllBooks() {
            return book_repo_->FindAll();
        }
        
        // 회원 관리
        void AddMember(const string& id, const string& name, const string& email) {
            auto member = make_unique<Model::Member>(id, name, email);
            member_repo_->Add(move(member));
        }
        
        Model::Member* FindMember(const string& id) {
            return member_repo_->FindById(id);
        }
        
        vector<Model::Member*> GetAllMembers() {
            return member_repo_->FindAll();
        }
        
        // 대출/반납 관리
        void BorrowBook(const string& member_id, const string& isbn) {
            Model::Member* member = FindMember(member_id);
            if (!member) {
                throw Exception::MemberNotFoundException(member_id);
            }
            
            Model::Book* book = FindBook(isbn);
            if (!book) {
                throw Exception::BookNotFoundException(isbn);
            }
            
            if (!book->IsAvailable()) {
                throw Exception::BookNotAvailableException(isbn);
            }
            
            if (!member->CanBorrow()) {
                throw Exception::BorrowLimitExceededException(member_id);
            }
            
            // 대출 처리
            book->SetAvailable(false);
            member->BorrowBook(isbn);
            
            auto loan_record = make_unique<Model::LoanRecord>(member_id, isbn);
            loan_records_.push_back(move(loan_record));
        }
        
        void ReturnBook(const string& member_id, const string& isbn) {
            Model::Member* member = FindMember(member_id);
            if (!member) {
                throw Exception::MemberNotFoundException(member_id);
            }
            
            Model::Book* book = FindBook(isbn);
            if (!book) {
                throw Exception::BookNotFoundException(isbn);
            }
            
            if (!member->HasBorrowed(isbn)) {
                throw Exception::LibraryException("회원이 해당 도서를 대출하지 않았습니다");
            }
            
            // 반납 처리
            book->SetAvailable(true);
            member->ReturnBook(isbn);
            
            // 대출 기록 업데이트
            auto it = find_if(loan_records_.begin(), loan_records_.end(),
                [&](const auto& record) {
                    return record->GetMemberId() == member_id && 
                           record->GetISBN() == isbn && 
                           !record->IsReturned();
                });
            
            if (it != loan_records_.end()) {
                (*it)->ReturnBook();
            }
        }
        
        // 통계 및 리포트
        vector<Model::LoanRecord*> GetOverdueLoans() {
            vector<Model::LoanRecord*> overdue;
            for (auto& record : loan_records_) {
                if (record->IsOverdue()) {
                    overdue.push_back(record.get());
                }
            }
            return overdue;
        }
        
        map<string, int> GetCategoryStatistics() {
            map<string, int> stats;
            for (auto* book : GetAllBooks()) {
                stats[book->GetCategory()]++;
            }
            return stats;
        }
        
        // 데이터 영속성
        void SaveData() {
            try {
                FileService::SaveToFile("books.txt", GetAllBooks());
                FileService::SaveToFile("members.txt", GetAllMembers());
                cout << "데이터 저장 완료" << endl;
            } catch (const Exception::FileOperationException& e) {
                cerr << "데이터 저장 실패: " << e.what() << endl;
                throw;
            }
        }
        
        void LoadData() {
            try {
                // 도서 데이터 로드
                FileService::LoadFromFile<Model::Book>("books.txt",
                    []() { return make_unique<Model::Book>(); },
                    [this](unique_ptr<Model::Book> book) {
                        book_repo_->Add(move(book));
                    });
                
                // 회원 데이터 로드
                FileService::LoadFromFile<Model::Member>("members.txt",
                    []() { return make_unique<Model::Member>(); },
                    [this](unique_ptr<Model::Member> member) {
                        member_repo_->Add(move(member));
                    });
                
                cout << "데이터 로드 완료" << endl;
            } catch (const Exception::FileOperationException& e) {
                cerr << "데이터 로드 실패: " << e.what() << endl;
                // 로드 실패는 치명적이지 않음 (새 데이터베이스로 시작)
            }
        }
    };
}

// =================================================================
// 4. 사용자 인터페이스 (UI Layer)
// =================================================================

namespace UI {
    class ConsoleInterface {
    private:
        Service::LibraryService& library_service_;
        
        void PrintHeader(const string& title) {
            cout << "\n" << string(50, '=') << endl;
            cout << "  " << title << endl;
            cout << string(50, '=') << endl;
        }
        
        void PrintMenu() {
            PrintHeader("도서관 관리 시스템");
            cout << "1. 도서 관리" << endl;
            cout << "2. 회원 관리" << endl;
            cout << "3. 대출/반납" << endl;
            cout << "4. 검색" << endl;
            cout << "5. 통계" << endl;
            cout << "6. 데이터 저장/로드" << endl;
            cout << "0. 종료" << endl;
            cout << "선택: ";
        }
        
        void BookManagementMenu() {
            while (true) {
                PrintHeader("도서 관리");
                cout << "1. 도서 추가" << endl;
                cout << "2. 도서 목록" << endl;
                cout << "3. 도서 정보" << endl;
                cout << "0. 이전 메뉴" << endl;
                cout << "선택: ";
                
                int choice;
                cin >> choice;
                cin.ignore();
                
                try {
                    switch (choice) {
                        case 1: AddBookInterface(); break;
                        case 2: ListBooksInterface(); break;
                        case 3: BookInfoInterface(); break;
                        case 0: return;
                        default: cout << "잘못된 선택입니다." << endl;
                    }
                } catch (const exception& e) {
                    cout << "오류: " << e.what() << endl;
                }
            }
        }
        
        void AddBookInterface() {
            string isbn, title, author, category;
            
            cout << "ISBN: ";
            getline(cin, isbn);
            cout << "제목: ";
            getline(cin, title);
            cout << "저자: ";
            getline(cin, author);
            cout << "카테고리 (선택사항): ";
            getline(cin, category);
            
            if (category.empty()) category = "일반";
            
            library_service_.AddBook(isbn, title, author, category);
            cout << "도서가 추가되었습니다." << endl;
        }
        
        void ListBooksInterface() {
            auto books = library_service_.GetAllBooks();
            
            if (books.empty()) {
                cout << "등록된 도서가 없습니다." << endl;
                return;
            }
            
            cout << "\n총 " << books.size() << "권의 도서:" << endl;
            cout << string(80, '-') << endl;
            cout << left << setw(15) << "ISBN" 
                 << setw(25) << "제목" 
                 << setw(15) << "저자" 
                 << setw(10) << "카테고리" 
                 << setw(8) << "상태" << endl;
            cout << string(80, '-') << endl;
            
            for (auto* book : books) {
                cout << left << setw(15) << book->GetISBN()
                     << setw(25) << book->GetTitle().substr(0, 22)
                     << setw(15) << book->GetAuthor().substr(0, 12)
                     << setw(10) << book->GetCategory()
                     << setw(8) << (book->IsAvailable() ? "대출가능" : "대출중") << endl;
            }
        }
        
        void BookInfoInterface() {
            string isbn;
            cout << "ISBN을 입력하세요: ";
            getline(cin, isbn);
            
            auto* book = library_service_.FindBook(isbn);
            if (!book) {
                cout << "도서를 찾을 수 없습니다." << endl;
                return;
            }
            
            cout << "\n도서 정보:" << endl;
            cout << "ISBN: " << book->GetISBN() << endl;
            cout << "제목: " << book->GetTitle() << endl;
            cout << "저자: " << book->GetAuthor() << endl;
            cout << "카테고리: " << book->GetCategory() << endl;
            cout << "상태: " << (book->IsAvailable() ? "대출 가능" : "대출 중") << endl;
        }
        
        void MemberManagementMenu() {
            while (true) {
                PrintHeader("회원 관리");
                cout << "1. 회원 등록" << endl;
                cout << "2. 회원 목록" << endl;
                cout << "3. 회원 정보" << endl;
                cout << "0. 이전 메뉴" << endl;
                cout << "선택: ";
                
                int choice;
                cin >> choice;
                cin.ignore();
                
                try {
                    switch (choice) {
                        case 1: AddMemberInterface(); break;
                        case 2: ListMembersInterface(); break;
                        case 3: MemberInfoInterface(); break;
                        case 0: return;
                        default: cout << "잘못된 선택입니다." << endl;
                    }
                } catch (const exception& e) {
                    cout << "오류: " << e.what() << endl;
                }
            }
        }
        
        void AddMemberInterface() {
            string id, name, email;
            
            cout << "회원 ID: ";
            getline(cin, id);
            cout << "이름: ";
            getline(cin, name);
            cout << "이메일: ";
            getline(cin, email);
            
            library_service_.AddMember(id, name, email);
            cout << "회원이 등록되었습니다." << endl;
        }
        
        void ListMembersInterface() {
            auto members = library_service_.GetAllMembers();
            
            if (members.empty()) {
                cout << "등록된 회원이 없습니다." << endl;
                return;
            }
            
            cout << "\n총 " << members.size() << "명의 회원:" << endl;
            cout << string(70, '-') << endl;
            cout << left << setw(15) << "회원 ID" 
                 << setw(20) << "이름" 
                 << setw(25) << "이메일" 
                 << setw(10) << "대출 수" << endl;
            cout << string(70, '-') << endl;
            
            for (auto* member : members) {
                cout << left << setw(15) << member->GetId()
                     << setw(20) << member->GetName()
                     << setw(25) << member->GetEmail()
                     << setw(10) << member->GetBorrowedCount() << endl;
            }
        }
        
        void MemberInfoInterface() {
            string member_id;
            cout << "회원 ID를 입력하세요: ";
            getline(cin, member_id);
            
            auto* member = library_service_.FindMember(member_id);
            if (!member) {
                cout << "회원을 찾을 수 없습니다." << endl;
                return;
            }
            
            cout << "\n회원 정보:" << endl;
            cout << "ID: " << member->GetId() << endl;
            cout << "이름: " << member->GetName() << endl;
            cout << "이메일: " << member->GetEmail() << endl;
            cout << "대출 도서 수: " << member->GetBorrowedCount() 
                 << "/" << member->GetMaxBorrowLimit() << endl;
            
            auto borrowed_books = member->GetBorrowedBooks();
            if (!borrowed_books.empty()) {
                cout << "대출 중인 도서:" << endl;
                for (const auto& isbn : borrowed_books) {
                    auto* book = library_service_.FindBook(isbn);
                    cout << "  - " << (book ? book->GetTitle() : isbn) << endl;
                }
            }
        }
        
        void LoanReturnMenu() {
            while (true) {
                PrintHeader("대출/반납");
                cout << "1. 도서 대출" << endl;
                cout << "2. 도서 반납" << endl;
                cout << "3. 연체 도서 조회" << endl;
                cout << "0. 이전 메뉴" << endl;
                cout << "선택: ";
                
                int choice;
                cin >> choice;
                cin.ignore();
                
                try {
                    switch (choice) {
                        case 1: BorrowBookInterface(); break;
                        case 2: ReturnBookInterface(); break;
                        case 3: OverdueListInterface(); break;
                        case 0: return;
                        default: cout << "잘못된 선택입니다." << endl;
                    }
                } catch (const exception& e) {
                    cout << "오류: " << e.what() << endl;
                }
            }
        }
        
        void BorrowBookInterface() {
            string member_id, isbn;
            
            cout << "회원 ID: ";
            getline(cin, member_id);
            cout << "도서 ISBN: ";
            getline(cin, isbn);
            
            library_service_.BorrowBook(member_id, isbn);
            cout << "도서 대출이 완료되었습니다." << endl;
        }
        
        void ReturnBookInterface() {
            string member_id, isbn;
            
            cout << "회원 ID: ";
            getline(cin, member_id);
            cout << "도서 ISBN: ";
            getline(cin, isbn);
            
            library_service_.ReturnBook(member_id, isbn);
            cout << "도서 반납이 완료되었습니다." << endl;
        }
        
        void OverdueListInterface() {
            auto overdue_loans = library_service_.GetOverdueLoans();
            
            if (overdue_loans.empty()) {
                cout << "연체된 도서가 없습니다." << endl;
                return;
            }
            
            cout << "\n연체 도서 목록:" << endl;
            cout << string(60, '-') << endl;
            
            for (auto* loan : overdue_loans) {
                auto* member = library_service_.FindMember(loan->GetMemberId());
                auto* book = library_service_.FindBook(loan->GetISBN());
                
                cout << "회원: " << (member ? member->GetName() : loan->GetMemberId()) << endl;
                cout << "도서: " << (book ? book->GetTitle() : loan->GetISBN()) << endl;
                cout << "연체일: " << loan->GetOverdueDays() << "일" << endl;
                cout << string(30, '-') << endl;
            }
        }
        
        void SearchInterface() {
            string keyword;
            cout << "검색어를 입력하세요: ";
            getline(cin, keyword);
            
            auto books = library_service_.SearchBooks(keyword);
            
            if (books.empty()) {
                cout << "검색 결과가 없습니다." << endl;
                return;
            }
            
            cout << "\n검색 결과 (" << books.size() << "건):" << endl;
            cout << string(80, '-') << endl;
            
            for (auto* book : books) {
                cout << "제목: " << book->GetTitle() << endl;
                cout << "저자: " << book->GetAuthor() << endl;
                cout << "ISBN: " << book->GetISBN() << endl;
                cout << "상태: " << (book->IsAvailable() ? "대출 가능" : "대출 중") << endl;
                cout << string(40, '-') << endl;
            }
        }
        
        void StatisticsInterface() {
            PrintHeader("통계 정보");
            
            auto books = library_service_.GetAllBooks();
            auto members = library_service_.GetAllMembers();
            auto category_stats = library_service_.GetCategoryStatistics();
            
            cout << "전체 도서 수: " << books.size() << endl;
            cout << "전체 회원 수: " << members.size() << endl;
            
            int available_books = count_if(books.begin(), books.end(),
                [](auto* book) { return book->IsAvailable(); });
            cout << "대출 가능 도서: " << available_books << endl;
            cout << "대출 중인 도서: " << (books.size() - available_books) << endl;
            
            cout << "\n카테고리별 통계:" << endl;
            for (const auto& [category, count] : category_stats) {
                cout << "  " << category << ": " << count << "권" << endl;
            }
        }
        
        void DataManagementInterface() {
            while (true) {
                PrintHeader("데이터 관리");
                cout << "1. 데이터 저장" << endl;
                cout << "2. 데이터 로드" << endl;
                cout << "0. 이전 메뉴" << endl;
                cout << "선택: ";
                
                int choice;
                cin >> choice;
                cin.ignore();
                
                try {
                    switch (choice) {
                        case 1: 
                            library_service_.SaveData();
                            break;
                        case 2: 
                            library_service_.LoadData();
                            break;
                        case 0: 
                            return;
                        default: 
                            cout << "잘못된 선택입니다." << endl;
                    }
                } catch (const exception& e) {
                    cout << "오류: " << e.what() << endl;
                }
            }
        }
        
    public:
        explicit ConsoleInterface(Service::LibraryService& service) 
            : library_service_(service) {}
        
        void Run() {
            // 시작 시 데이터 로드 시도
            try {
                library_service_.LoadData();
            } catch (...) {
                cout << "기존 데이터를 로드하지 못했습니다. 새로 시작합니다." << endl;
            }
            
            while (true) {
                PrintMenu();
                
                int choice;
                cin >> choice;
                cin.ignore();
                
                try {
                    switch (choice) {
                        case 1: BookManagementMenu(); break;
                        case 2: MemberManagementMenu(); break;
                        case 3: LoanReturnMenu(); break;
                        case 4: SearchInterface(); break;
                        case 5: StatisticsInterface(); break;
                        case 6: DataManagementInterface(); break;
                        case 0: 
                            cout << "프로그램을 종료합니다." << endl;
                            return;
                        default: 
                            cout << "잘못된 선택입니다." << endl;
                    }
                } catch (const exception& e) {
                    cout << "오류 발생: " << e.what() << endl;
                    cout << "계속하려면 Enter를 누르세요...";
                    cin.get();
                }
            }
        }
    };
}

// =================================================================
// 5. 애플리케이션 진입점
// =================================================================

void InitializeSampleData(Service::LibraryService& service) {
    cout << "샘플 데이터 초기화 중..." << endl;
    
    try {
        // 샘플 도서 추가
        service.AddBook("978-89-6626-171-4", "모던 C++ 입문", "김현정", "프로그래밍");
        service.AddBook("978-89-7914-285-0", "Clean Code", "Robert Martin", "프로그래밍");
        service.AddBook("978-89-6845-045-3", "알고리즘 문제 해결 전략", "구종만", "알고리즘");
        service.AddBook("978-89-7497-912-4", "객체지향의 사실과 오해", "조영호", "설계");
        service.AddBook("978-89-6626-135-6", "이것이 자바다", "신용권", "프로그래밍");
        
        // 샘플 회원 추가
        service.AddMember("M001", "김철수", "kim@email.com");
        service.AddMember("M002", "이영희", "lee@email.com");
        service.AddMember("M003", "박민수", "park@email.com");
        
        // 샘플 대출
        service.BorrowBook("M001", "978-89-6626-171-4");
        service.BorrowBook("M002", "978-89-7914-285-0");
        
        cout << "샘플 데이터 초기화 완료" << endl;
        
    } catch (const exception& e) {
        cout << "샘플 데이터 초기화 실패: " << e.what() << endl;
    }
}

int main() {
    cout << "=== C++ 종합 프로젝트: 도서관 관리 시스템 ===" << endl;
    cout << "이 시스템은 다음 기능들을 포함합니다:" << endl;
    cout << "- 객체지향 설계 (클래스, 상속, 다형성)" << endl;
    cout << "- 예외 처리 및 안전성 보장" << endl;
    cout << "- STL 컨테이너와 알고리즘 활용" << endl;
    cout << "- 스마트 포인터를 통한 메모리 관리" << endl;
    cout << "- 파일 I/O와 데이터 영속성" << endl;
    cout << "- 템플릿 및 제네릭 프로그래밍" << endl;
    cout << "- 모던 C++ 기능 (auto, 람다, 범위 기반 for 등)" << endl;
    cout << "\n계속하려면 Enter를 누르세요...";
    cin.get();
    
    try {
        // 서비스 초기화
        Service::LibraryService library_service;
        
        // 샘플 데이터 초기화
        InitializeSampleData(library_service);
        
        // UI 실행
        UI::ConsoleInterface ui(library_service);
        ui.Run();
        
        // 종료 시 데이터 저장
        cout << "프로그램 종료 전 데이터를 저장합니다..." << endl;
        library_service.SaveData();
        
    } catch (const exception& e) {
        cerr << "심각한 오류 발생: " << e.what() << endl;
        return 1;
    }
    
    cout << "\n=== 프로젝트 완료 ===" << endl;
    cout << "이 프로젝트에서 활용된 C++ 개념들:" << endl;
    cout << "1. 클래스와 객체지향 프로그래밍" << endl;
    cout << "2. 상속과 다형성" << endl;
    cout << "3. 예외 처리와 안전성" << endl;
    cout << "4. 스마트 포인터와 RAII" << endl;
    cout << "5. STL 컨테이너와 알고리즘" << endl;
    cout << "6. 템플릿과 제네릭 프로그래밍" << endl;
    cout << "7. 파일 I/O와 데이터 영속성" << endl;
    cout << "8. 모던 C++ 기능들" << endl;
    cout << "9. 코딩 표준과 모범 사례" << endl;
    cout << "10. 프로젝트 구조화와 모듈화" << endl;
    
    return 0;
}
```

---

## 이번 챕터 요약

### 학습한 내용
**예외 처리**: try-catch, 사용자 정의 예외, 예외 안전성
**자원 관리**: RAII 패턴, 스마트 포인터, 메모리 관리
**프로젝트 구조**: 모듈화, 네임스페이스, 의존성 관리
**코딩 표준**: 네이밍 컨벤션, 주석, 코드 품질
**디버깅**: 로깅, 단언문, 프로파일링, 테스트
**종합 프로젝트**: 실제 애플리케이션 구현

### 핵심 키워드
- 예외 처리: `try`, `catch`, `throw`, `exception`, `noexcept`
- 자원 관리: `unique_ptr`, `shared_ptr`, `RAII`, 스마트 포인터
- 모듈화: `namespace`, 헤더 분리, 인터페이스 설계
- 디버깅: `assert`, 로깅, 프로파일링, 단위 테스트

### C++ 마스터를 위한 원칙
1. **예외 안전성**: 항상 예외 상황을 고려한 코드 작성
2. **RAII 패턴**: 자원 관리를 객체 생명주기에 연결
3. **모던 C++ 활용**: 스마트 포인터, auto, 람다 등 적극 활용
4. **코드 품질**: 일관된 스타일과 명확한 의도 표현
5. **테스트**: 단위 테스트와 통합 테스트로 품질 보장
6. **성능**: 프로파일링을 통한 병목 지점 최적화

---

## 실습 과제

### 과제 1: 예외 안전한 스택 구현
예외 안전성을 보장하는 커스텀 스택 클래스를 구현하세요.

### 과제 2: 파일 관리 시스템
RAII 패턴을 활용한 안전한 파일 관리 시스템을 구현하세요.

### 과제 3: 성능 모니터링 도구
메모리 사용량과 실행 시간을 추적하는 성능 모니터링 도구를 작성하세요.

### 과제 4: 완전한 애플리케이션
자신만의 도메인에서 모든 C++ 개념을 활용한 완전한 애플리케이션을 설계하고 구현하세요.

---

## C++ 학습 여정 완료

축하합니다! 8개 챕터를 통해 C++의 핵심 개념들을 모두 학습했습니다:

1. **Chapter 01**: C++ 기초와 개발환경
2. **Chapter 02**: 변수, 데이터 타입, 연산자와 제어문
3. **Chapter 03**: 함수와 배열
4. **Chapter 04**: 클래스와 객체지향 I
5. **Chapter 05**: 클래스와 객체지향 II
6. **Chapter 06**: 상속과 다형성
7. **Chapter 07**: 템플릿과 STL
8. **Chapter 08**: 예외 처리와 프로젝트

이제 여러분은 실무에서 C++을 활용할 수 있는 견고한 기반을 갖추었습니다. 계속해서 실제 프로젝트를 통해 경험을 쌓아가시기 바랍니다!.0;
        for (double score : test_scores_) {
            sum += score;
        }
        
        return sum / static_cast<double>(test_scores_.size());
    }
    
    /**
     * @brief 최고 점수를 반환합니다
     * @return 최고 점수
     * @throws std::runtime_error 점수가 없는 경우
     */
    double GetHighestScore() const {
        if (test_scores_.empty()) {
            throw std::runtime_error("점수가 없어서 최고점을 계산할 수 없습니다");
        }
        
        return *std::max_element(test_scores_.begin(), test_scores_.end());
    }
    
    /**
     * @brief 학점을 계산합니다
     * @return 학점 문자열 (A, B, C, D, F)
     */
    std::string CalculateGrade() const {
        double average = CalculateAverageScore();
        
        // 범위 기반 조건문으로 가독성 향상
        if (average >= 90.0) return "A";
        if (average >= 80.0) return "B";
        if (average >= 70.0) return "C";
        if (average >= 60.0) return "D";
        return "F";
    }
    
    // Getter 함수들 (const 보장)
    const std::string& GetStudentName() const noexcept { return student_name_; }
    int GetStudentId() const noexcept { return student_id_; }
    size_t GetTestCount() const noexcept { return test_scores_.size(); }
    
    /**
     * @brief 학생 정보를 문자열로 변환합니다
     * @return 학생 정보 문자열
     */
    std::string ToString() const {
        std::string result = "학생: " + student_name_ + 
                           " (ID: " + std::to_string(student_id_) + ")";
        
        if (!test_scores_.empty()) {
            result += "\n  평균: " + std::to_string(CalculateAverageScore());
            result += "\n  학점: " + CalculateGrade();
            result += "\n  시험 수: " + std::to_string(test_scores_.size());
        } else {
            result += "\n  시험 점수 없음";
        }
        
        return result;
    }
    
    /**
     * @brief 두 학생의 평균 점수를 비교합니다
     * @param other 비교할 다른 학생
     * @return 이 학생의 평균이 더 높으면 true
     */
    bool HasHigherAverageThan(const StudentRecord& other) const noexcept {
        return CalculateAverageScore() > other.CalculateAverageScore();
    }
};

/**
 * @brief 학생 관리 시스템 클래스
 * 
 * 여러 학생의 정보를 관리하고 통계를 제공하는 클래스입니다.
 */
class StudentManagementSystem {
private:
    std::vector<std::unique_ptr<StudentRecord>> students_;
    
public:
    /**
     * @brief 새 학생을 추가합니다
     * @param name 학생 이름
     * @param id 학생 ID
     * @return 추가 성공 여부
     */
    bool AddStudent(const std::string& name, int id) noexcept {
        try {
            // ID 중복 검사
            if (FindStudentById(id) != nullptr) {
                std::cerr << "오류: 이미 존재하는 학생 ID입니다: " << id << std::endl;
                return false;
            }
            
            auto student = std::make_unique<StudentRecord>(name, id);
            students_.push_back(std::move(student));
            
            std::cout << "학생 추가 성공: " << name << " (ID: " << id << ")" << std::endl;
            return true;
            
        } catch (const std::exception& e) {
            std::cerr << "학생 추가 실패: " << e.what() << std::endl;
            return false;
        }
    }
    
    /**
     * @brief ID로 학생을 찾습니다
     * @param id 찾을 학생 ID
     * @return 학생 포인터 (없으면 nullptr)
     */
    StudentRecord* FindStudentById(int id) const noexcept {
        auto it = std::find_if(students_.begin(), students_.end(),
            [id](const auto& student) {
                return student->GetStudentId() == id;
            });
        
        return (it != students_.end()) ? it->get() : nullptr;
    }
    
    /**
     * @brief 특정 학생에게 점수를 추가합니다
     * @param id 학생 ID
     * @param score 점수
     * @return 추가 성공 여부
     */
    bool AddScoreToStudent(int id, double score) noexcept {
        try {
            StudentRecord* student = FindStudentById(id);
            if (student == nullptr) {
                std::cerr << "오류: 학생을 찾을 수 없습니다 (ID: " << id << ")" << std::endl;
                return false;
            }
            
            student->AddTestScore(score);
            std::cout << "점수 추가 성공: " << student->GetStudentName() 
                     << " -> " << score << "점" << std::endl;
            return true;
            
        } catch (const std::exception& e) {
            std::cerr << "점수 추가 실패: " << e.what() << std::endl;
            return false;
        }
    }
    
    /**
     * @brief 모든 학생의 정보를 출력합니다
     */
    void PrintAllStudents() const noexcept {
        if (students_.empty()) {
            std::cout << "등록된 학생이 없습니다." << std::endl;
            return;
        }
        
        std::cout << "\n=== 전체 학생 목록 ===" << std::endl;
        for (const auto& student : students_) {
            std::cout << student->ToString() << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
    
    /**
     * @brief 반 평균을 계산합니다
     * @return 반 평균 (학생이 없으면 0.0)
     */
    double CalculateClassAverage() const noexcept {
        if (students_.empty()) {
            return 0.0;
        }
        
        double total = 0.0;
        int count = 0;
        
        for (const auto& student : students_) {
            if (student->GetTestCount() > 0) {
                total += student->CalculateAverageScore();
                ++count;
            }
        }
        
        return (count > 0) ? total / static_cast<double>(count) : 0.0;
    }
    
    /**
     * @brief 최우수 학생을 찾습니다
     * @return 최우수 학생 포인터 (없으면 nullptr)
     */
    const StudentRecord* FindTopStudent() const noexcept {
        if (students_.empty()) {
            return nullptr;
        }
        
        const StudentRecord* topStudent = nullptr;
        double highestAverage = -1.0;
        
        for (const auto& student : students_) {
            if (student->GetTestCount() > 0) {
                double average = student->CalculateAverageScore();
                if (average > highestAverage) {
                    highestAverage = average;
                    topStudent = student.get();
                }
            }
        }
        
        return topStudent;
    }
    
    /**
     * @brief 통계 정보를 출력합니다
     */
    void PrintStatistics() const noexcept {
        std::cout << "\n=== 반 통계 ===" << std::endl;
        std::cout << "총 학생 수: " << students_.size() << std::endl;
        std::cout << "반 평균: " << CalculateClassAverage() << "점" << std::endl;
        
        const StudentRecord* topStudent = FindTopStudent();
        if (topStudent != nullptr) {
            std::cout << "최우수 학생: " << topStudent->GetStudentName() 
                     << " (" << topStudent->CalculateAverageScore() << "점)" << std::endl;
        } else {
            std::cout << "점수가 입력된 학생이 없습니다." << std::endl;
        }
    }
    
    size_t GetStudentCount() const noexcept { return students_.size(); }
};

/**
 * @brief 애플리케이션의 메인 컨트롤러 클래스
 */
class Application {
private:
    StudentManagementSystem system_;
    
public:
    /**
     * @brief 샘플 데이터를 초기화합니다
     */
    void InitializeSampleData() noexcept {
        std::cout << "=== 샘플 데이터 초기화 ===" << std::endl;
        
        // 학생 추가
        system_.AddStudent("김철수", 20240001);
        system_.AddStudent("이영희", 20240002);
        system_.AddStudent("박민수", 20240003);
        system_.AddStudent("최지연", 20240004);
        
        // 점수 추가
        system_.AddScoreToStudent(20240001, 85.5);
        system_.AddScoreToStudent(20240001, 92.0);
        system_.AddScoreToStudent(20240001, 78.5);
        
        system_.AddScoreToStudent(20240002, 95.0);
        system_.AddScoreToStudent(20240002, 88.5);
        system_.AddScoreToStudent(20240002, 96.5);
        
        system_.AddScoreToStudent(20240003, 76.0);
        system_.AddScoreToStudent(20240003, 82.5);
        
        system_.AddScoreToStudent(20240004, 98.0);
        system_.AddScoreToStudent(20240004, 94.5);
        system_.AddScoreToStudent(20240004, 97.0);
    }
    
    /**
     * @brief 애플리케이션을 실행합니다
     */
    void Run() noexcept {
        try {
            InitializeSampleData();
            
            system_.PrintAllStudents();
            system_.PrintStatistics();
            
            // 오류 처리 테스트
            std::cout << "\n=== 오류 처리 테스트 ===" << std::endl;
            system_.AddStudent("", 20240005);        // 빈 이름
            system_.AddStudent("test", 0);           // 잘못된 ID
            system_.AddScoreToStudent(99999, 85.0);  // 존재하지 않는 학생
            system_.AddScoreToStudent(20240001, 150.0); // 잘못된 점수
            
        } catch (const std::exception& e) {
            std::cerr << "애플리케이션 오류: " << e.what() << std::endl;
        }
    }
};

// 전역 함수들은 파스칼케이스 사용
void PrintCodingStandardsGuidelines() noexcept {
    std::cout << "\n=== C++ 코딩 표준 가이드라인 ===" << std::endl;
    std::cout << "1. 네이밍:" << std::endl;
    std::cout << "   - 클래스: PascalCase (StudentRecord)" << std::endl;
    std::cout << "   - 함수: PascalCase (CalculateAverage)" << std::endl;
    std::cout << "   - 변수: snake_case (student_name_)" << std::endl;
    std::cout << "   - 상수: k + PascalCase (kMaxSize)" << std::endl;
    
    std::cout << "\n2. 포맷팅:" << std::endl;
    std::cout << "   - 들여쓰기: 스페이스 4개" << std::endl;
    std::cout << "   - 중괄호: K&R 스타일" << std::endl;
    std::cout << "   - 한 줄 최대 80-100 문자" << std::endl;
    
    std::cout << "\n3. 주석:" << std::endl;
    std::cout << "   - Doxygen 스타일 문서화 주석" << std::endl;
    std::cout << "   - 복잡한 로직에는 설명 주석" << std::endl;
    std::cout << "   - TODO, FIXME, NOTE 등 특수 주석 활용" << std::endl;
    
    std::cout << "\n4. 예외 처리:" << std::endl;
    std::cout << "   - 생성자에서 입력 검증" << std::endl;
    std::cout << "   - noexcept 명시로 예외 안전성 표시" << std::endl;
    std::cout << "   - RAII 패턴으로 자원 관리" << std::endl;
    
    std::cout << "\n5. 현대 C++ 기능:" << std::endl;
    std::cout << "   - auto 키워드 적절히 사용" << std::endl;
    std::cout << "   - 스마트 포인터로 메모리 관리" << std::endl;
    std::cout << "   - 범위 기반 for 루프 활용" << std::endl;
    std::cout << "   - constexpr, noexcept 적극 활용" << std::endl;
}

int main() {
    std::cout << "=== C++ 코딩 표준 예제 ===" << std::endl;
    
    // 애플리케이션 실행
    Application app;
    app.Run();
    
    // 코딩 표준 가이드라인 출력
    PrintCodingStandardsGuidelines();
    
    return 0;
}
```

---

## 9. 예제 09: 디버깅 기법 (09_debugging_techniques.cpp)

### 예제 정의
효과적인 디버깅 기법과 도구 활용법을 학습합니다.

```cpp
/*
주제: 디버깅 기법 (Debugging Techniques)
정의: 프로그램의 오류를 체계적으로 찾아내고 수정하는 방법론과 도구 활용 기법

핵심 개념: 단계별 디버깅, 로깅, 단언문, 프로파일링
정의:
- 단계별 디버깅: IDE 디버거를 활용한 중단점 설정과 스텝 실행
- 로깅: 프로그램 실행 과정을 기록하여 문제점 추적
- 단언문(assert): 프로그램의 가정을 검증하여 논리적 오류 발견
- 프로파일링: 성능 병목 지점을 분석하여 최적화 대상 식별

디버깅 전략:
1. 재현 가능한 최소 예제 작성
2. 이진 탐색을 통한 오류 범위 축소
3. 로그 기반 상태 추적
4. 단위 테스트를 통한 격리된 검증
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

// =================================================================
// 1. 로깅 시스템 (디버깅의 핵심 도구)
// =================================================================

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class DebugLogger {
private:
    LogLevel min_level_;
    bool console_output_;
    bool file_output_;
    string log_filename_;
    ofstream log_file_;
    
    string GetCurrentTime() const {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        stringstream ss;
        ss << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << "." << setfill('0') << setw(3) << ms.count();
        return ss.str();
    }
    
    string LogLevelToString(LogLevel level) const {
        switch (level) {
            case LogLevel::DEBUG:   return "DEBUG";
            case LogLevel::INFO:    return "INFO ";
            case LogLevel::WARNING: return "WARN ";
            case LogLevel::ERROR:   return "ERROR";
            default:                return "UNKN ";
        }
    }
    
public:
    DebugLogger(LogLevel level = LogLevel::DEBUG, 
                bool console = true, 
                bool file = false,
                const string& filename = "debug.log") 
        : min_level_(level), console_output_(console), file_output_(file), log_filename_(filename) {
        
        if (file_output_) {
            log_file_.open(log_filename_, ios::app);
        }
    }
    
    ~DebugLogger() {
        if (log_file_.is_open()) {
            log_file_.close();
        }
    }
    
    void Log(LogLevel level, const string& message, 
             const string& function = "", int line = 0) {
        
        if (level < min_level_) return;
        
        stringstream log_entry;
        log_entry << "[" << GetCurrentTime() << "] "
                  << "[" << LogLevelToString(level) << "] ";
        
        if (!function.empty()) {
            log_entry << "[" << function << ":" << line << "] ";
        }
        
        log_entry << message;
        
        string final_message = log_entry.str();
        
        if (console_output_) {
            cout << final_message << endl;
        }
        
        if (file_output_ && log_file_.is_open()) {
            log_file_ << final_message << endl;
            log_file_.flush();
        }
    }
    
    void SetLevel(LogLevel level) { min_level_ = level; }
};

// 편의 매크로
#define LOG_DEBUG(logger, msg) logger.Log(LogLevel::DEBUG, msg, __FUNCTION__, __LINE__)
#define LOG_INFO(logger, msg) logger.Log(LogLevel::INFO, msg, __FUNCTION__, __LINE__)
#define LOG_WARNING(logger, msg) logger.Log(LogLevel::WARNING, msg, __FUNCTION__, __LINE__)
#define LOG_ERROR(logger, msg) logger.Log(LogLevel::ERROR, msg, __FUNCTION__, __LINE__)

// =================================================================
// 2. 단언문 활용 (프로그램 가정 검증)
// =================================================================

// 커스텀 단언문 (릴리즈 빌드에서도 동작)
#define DEBUG_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            cerr << "단언문 실패: " << #condition << endl; \
            cerr << "메시지: " << message << endl; \
            cerr << "파일: " << __FILE__ << ":" << __LINE__ << endl; \
            cerr << "함수: " << __FUNCTION__ << endl; \
            abort(); \
        } \
    } while (0)

// 범위 검사 단언문
#define ASSERT_RANGE(value, min_val, max_val) \
    DEBUG_ASSERT((value) >= (min_val) && (value) <= (max_val), \
                 "값이 허용 범위를 벗어남: " + to_string(value))

// =================================================================
// 3. 디버깅 가능한 컨테이너 클래스
// =================================================================

template<typename T>
class DebugVector {
private:
    vector<T> data_;
    DebugLogger& logger_;
    string name_;
    
public:
    DebugVector(const string& name, DebugLogger& logger) 
        : logger_(logger), name_(name) {
        LOG_DEBUG(logger_, "DebugVector '" + name_ + "' 생성됨");
    }
    
    ~DebugVector() {
        LOG_DEBUG(logger_, "DebugVector '" + name_ + "' 소멸됨 (크기: " + to_string(data_.size()) + ")");
    }
    
    void push_back(const T& value) {
        data_.push_back(value);
        LOG_DEBUG(logger_, name_ + ".push_back() - 새 크기: " + to_string(data_.size()));
    }
    
    T& at(size_t index) {
        LOG_DEBUG(logger_, name_ + ".at(" + to_string(index) + ") 호출");
        
        // 범위 검사 단언문
        DEBUG_ASSERT(index < data_.size(), 
                     "인덱스 " + to_string(index) + "가 크기 " + to_string(data_.size()) + "를 초과");
        
        return data_.at(index);
    }
    
    const T& at(size_t index) const {
        LOG_DEBUG(logger_, name_ + ".at(" + to_string(index) + ") const 호출");
        
        DEBUG_ASSERT(index < data_.size(), 
                     "인덱스 " + to_string(index) + "가 크기 " + to_string(data_.size()) + "를 초과");
        
        return data_.at(index);
    }
    
    size_t size() const noexcept { 
        return data_.size(); 
    }
    
    bool empty() const noexcept { 
        return data_.empty(); 
    }
    
    void clear() {
        size_t old_size = data_.size();
        data_.clear();
        LOG_INFO(logger_, name_ + ".clear() - " + to_string(old_size) + "개 요소 제거됨");
    }
    
    // 디버깅용 상태 출력
    void PrintDebugInfo() const {
        LOG_INFO(logger_, name_ + " 상태: 크기=" + to_string(data_.size()) + 
                          ", 용량=" + to_string(data_.capacity()));
        
        for (size_t i = 0; i < data_.size(); ++i) {
            stringstream ss;
            ss << data_[i];
            LOG_DEBUG(logger_, "  [" + to_string(i) + "] = " + ss.str());
        }
    }
};

// =================================================================
// 4. 성능 프로파일링 도구
// =================================================================

class PerformanceProfiler {
private:
    map<string, chrono::high_resolution_clock::time_point> start_times_;
    map<string, vector<long long>> measurements_;
    DebugLogger& logger_;
    
public:
    explicit PerformanceProfiler(DebugLogger& logger) : logger_(logger) {}
    
    void StartMeasurement(const string& name) {
        start_times_[name] = chrono::high_resolution_clock::now();
        LOG_DEBUG(logger_, "성능 측정 시작: " + name);
    }
    
    void EndMeasurement(const string& name) {
        auto it = start_times_.find(name);
        if (it != start_times_.end()) {
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end_time - it->second);
            
            measurements_[name].push_back(duration.count());
            start_times_.erase(it);
            
            LOG_DEBUG(logger_, "성능 측정 완료: " + name + " (" + to_string(duration.count()) + " μs)");
        }
    }
    
    void PrintStatistics() const {
        LOG_INFO(logger_, "=== 성능 통계 ===");
        
        for (const auto& [name, times] : measurements_) {
            if (!times.empty()) {
                long long total = 0;
                long long min_time = times[0];
                long long max_time = times[0];
                
                for (long long time : times) {
                    total += time;
                    min_time = min(min_time, time);
                    max_time = max(max_time, time);
                }
                
                double average = static_cast<double>(total) / times.size();
                
                stringstream stats;
                stats << name << ": "
                      << "평균=" << fixed << setprecision(2) << average << "μs, "
                      << "최소=" << min_time << "μs, "
                      << "최대=" << max_time << "μs, "
                      << "호출=" << times.size() << "회";
                
                LOG_INFO(logger_, stats.str());
            }
        }
    }
};

// RAII 기반 자동 성능 측정
class ScopedProfiler {
private:
    PerformanceProfiler& profiler_;
    string name_;
    
public:
    ScopedProfiler(PerformanceProfiler& profiler, const string& name) 
        : profiler_(profiler), name_(name) {
        profiler_.StartMeasurement(name_);
    }
    
    ~ScopedProfiler() {
        profiler_.EndMeasurement(name_);
    }
};

#define PROFILE_SCOPE(profiler, name) ScopedProfiler _prof(profiler, name)

// =================================================================
// 5. 메모리 디버깅 도구
// =================================================================

class MemoryDebugger {
private:
    map<void*, size_t> allocations_;
    size_t total_allocated_;
    size_t peak_usage_;
    DebugLogger& logger_;
    
public:
    explicit MemoryDebugger(DebugLogger& logger) 
        : total_allocated_(0), peak_usage_(0), logger_(logger) {}
    
    void* Allocate(size_t size) {
        void* ptr = malloc(size);
        if (ptr) {
            allocations_[ptr] = size;
            total_allocated_ += size;
            peak_usage_ = max(peak_usage_, total_allocated_);
            
            LOG_DEBUG(logger_, "메모리 할당: " + to_string(size) + " 바이트 (총: " + 
                               to_string(total_allocated_) + " 바이트)");
        }
        return ptr;
    }
    
    void Deallocate(void* ptr) {
        auto it = allocations_.find(ptr);
        if (it != allocations_.end()) {
            size_t size = it->second;
            total_allocated_ -= size;
            allocations_.erase(it);
            
            LOG_DEBUG(logger_, "메모리 해제: " + to_string(size) + " 바이트 (총: " + 
                               to_string(total_allocated_) + " 바이트)");
            
            free(ptr);
        } else {
            LOG_ERROR(logger_, "잘못된 메모리 해제 시도");
        }
    }
    
    void PrintMemoryReport() const {
        LOG_INFO(logger_, "=== 메모리 리포트 ===");
        LOG_INFO(logger_, "현재 할당량: " + to_string(total_allocated_) + " 바이트");
        LOG_INFO(logger_, "최대 사용량: " + to_string(peak_usage_) + " 바이트");
        LOG_INFO(logger_, "미해제 블록: " + to_string(allocations_.size()) + " 개");
        
        if (!allocations_.empty()) {
            LOG_WARNING(logger_, "메모리 누수 감지됨!");
            for (const auto& [ptr, size] : allocations_) {
                stringstream ss;
                ss << "  누수: " << ptr << " (" << size << " 바이트)";
                LOG_WARNING(logger_, ss.str());
            }
        }
    }
    
    ~MemoryDebugger() {
        if (!allocations_.empty()) {
            LOG_ERROR(logger_, "프로그램 종료 시 메모리 누수 발견!");
        }
    }
};

// =================================================================
// 6. 통합 디버깅 예제
// =================================================================

class BuggyCalculator {
private:
    DebugLogger& logger_;
    PerformanceProfiler& profiler_;
    DebugVector<double> history_;
    
public:
    BuggyCalculator(DebugLogger& logger, PerformanceProfiler& profiler) 
        : logger_(logger), profiler_(profiler), history_("calculation_history", logger) {
        LOG_INFO(logger_, "BuggyCalculator 생성됨");
    }
    
    double Divide(double a, double b) {
        PROFILE_SCOPE(profiler_, "Divide");
        LOG_DEBUG(logger_, "나눗셈 연산: " + to_string(a) + " / " + to_string(b));
        
        // 의도적인 버그: 0으로 나누기 검사 누락
        // DEBUG_ASSERT(b != 0.0, "0으로 나눌 수 없습니다");
        
        double result = a / b;  // 버그: b가 0일 때 문제 발생
        history_.push_back(result);
        
        LOG_DEBUG(logger_, "결과: " + to_string(result));
        return result;
    }
    
    double GetAverage() {
        PROFILE_SCOPE(profiler_, "GetAverage");
        LOG_DEBUG(logger_, "평균 계산 시작 (히스토리 크기: " + to_string(history_.size()) + ")");
        
        // 의도적인 버그: 빈 히스토리 검사 누락
        DEBUG_ASSERT(!history_.empty(), "히스토리가 비어있어 평균을 계산할 수 없습니다");
        
        double sum = 0
