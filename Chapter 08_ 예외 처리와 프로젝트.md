# Chapter 08: 예외 처리와 프로젝트 (예제 01~10)

## 1. 예제 01: 기본 예외 처리 (01_basic_exception.cpp)

### 예제 정의
try-catch 구문을 사용한 기본적인 예외 처리를 학습합니다.

```cpp
/*
주제: 기본 예외 처리 (Basic Exception Handling)
정의: try-catch 구문을 사용하여 런타임 오류를 안전하게 처리
*/

#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
    if (b == 0) {
        throw invalid_argument("0으로 나눌 수 없습니다!");
    }
    return a / b;
}

int getArrayElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("배열 인덱스가 범위를 벗어났습니다!");
    }
    return arr[index];
}

int main() {
    cout << "=== 기본 예외 처리 ===" << endl;
    
    // 나누기 예외 처리
    try {
        cout << "10 / 2 = " << divide(10, 2) << endl;
        cout << "10 / 0 = " << divide(10, 0) << endl;  // 예외 발생
    }
    catch (const invalid_argument& e) {
        cout << "오류 발생: " << e.what() << endl;
    }
    
    // 배열 접근 예외 처리
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    try {
        cout << "\n배열[2] = " << getArrayElement(numbers, size, 2) << endl;
        cout << "배열[10] = " << getArrayElement(numbers, size, 10) << endl;  // 예외 발생
    }
    catch (const out_of_range& e) {
        cout << "배열 오류: " << e.what() << endl;
    }
    
    // 여러 예외 처리
    try {
        cout << "\n5 / 1 = " << divide(5, 1) << endl;
        cout << "배열[0] = " << getArrayElement(numbers, size, 0) << endl;
        cout << "3 / 0 = " << divide(3, 0) << endl;  // 예외 발생
    }
    catch (const invalid_argument& e) {
        cout << "나누기 오류: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cout << "범위 오류: " << e.what() << endl;
    }
    catch (...) {  // 모든 예외 처리
        cout << "알 수 없는 오류가 발생했습니다." << endl;
    }
    
    cout << "\n프로그램이 정상적으로 계속됩니다." << endl;
    return 0;
}
```

---

## 2. 예제 02: 사용자 정의 예외 (02_custom_exception.cpp)

### 예제 정의
사용자 정의 예외 클래스를 만들어 특화된 예외 처리를 구현합니다.

```cpp
/*
주제: 사용자 정의 예외 (Custom Exception)
정의: 특정 상황에 맞는 예외 클래스를 직접 정의하여 사용
*/

#include <iostream>
#include <exception>
#include <string>
using namespace std;

// 사용자 정의 예외 클래스
class BankException : public exception {
private:
    string message;
    
public:
    BankException(const string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException(double requested, double available) 
        : BankException("잔액 부족: 요청금액 " + to_string(requested) + 
                       "원, 잔액 " + to_string(available) + "원") {}
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException() : BankException("유효하지 않은 금액입니다.") {}
};

class BankAccount {
private:
    double balance;
    
public:
    BankAccount(double initial) : balance(initial) {}
    
    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        balance += amount;
        cout << amount << "원 입금 완료. 잔액: " << balance << "원" << endl;
    }
    
    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        if (amount > balance) {
            throw InsufficientFundsException(amount, balance);
        }
        balance -= amount;
        cout << amount << "원 출금 완료. 잔액: " << balance << "원" << endl;
    }
    
    double getBalance() const { return balance; }
};

int main() {
    cout << "=== 사용자 정의 예외 ===" << endl;
    
    BankAccount account(100000);
    
    try {
        account.deposit(50000);
        account.withdraw(30000);
        account.withdraw(-1000);  // 잘못된 금액
    }
    catch (const InvalidAmountException& e) {
        cout << "금액 오류: " << e.what() << endl;
    }
    catch (const InsufficientFundsException& e) {
        cout << "잔액 오류: " << e.what() << endl;
    }
    catch (const BankException& e) {
        cout << "은행 오류: " << e.what() << endl;
    }
    
    try {
        account.withdraw(200000);  // 잔액 부족
    }
    catch (const BankException& e) {
        cout << "거래 실패: " << e.what() << endl;
    }
    
    cout << "\n최종 잔액: " << account.getBalance() << "원" << endl;
    
    return 0;
}
```

---

## 3. 예제 03: 예외 안전성 (03_exception_safety.cpp)

### 예제 정의
예외가 발생했을 때도 안전한 코드 작성 방법을 학습합니다.

```cpp
/*
주제: 예외 안전성 (Exception Safety)
정의: 예외가 발생해도 프로그램이 일관된 상태를 유지하도록 하는 프로그래밍 기법
*/

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Resource {
private:
    string name;
    
public:
    Resource(const string& n) : name(n) {
        cout << "자원 생성: " << name << endl;
    }
    
    ~Resource() {
        cout << "자원 해제: " << name << endl;
    }
    
    void process() {
        cout << "자원 처리: " << name << endl;
    }
};

// 예외 안전하지 않은 클래스
class UnsafeManager {
private:
    Resource* resource1;
    Resource* resource2;
    
public:
    UnsafeManager() : resource1(nullptr), resource2(nullptr) {}
    
    void initialize() {
        resource1 = new Resource("자원1");
        // 여기서 예외가 발생하면 resource1이 누수됨
        resource2 = new Resource("자원2");
        
        // 강제로 예외 발생
        throw runtime_error("초기화 중 오류 발생!");
    }
    
    ~UnsafeManager() {
        delete resource1;
        delete resource2;
    }
};

// 예외 안전한 클래스 (RAII 사용)
class SafeManager {
private:
    unique_ptr<Resource> resource1;
    unique_ptr<Resource> resource2;
    
public:
    void initialize() {
        resource1 = make_unique<Resource>("안전자원1");
        resource2 = make_unique<Resource>("안전자원2");
        
        // 예외가 발생해도 스마트 포인터가 자동으로 정리
        throw runtime_error("초기화 중 오류 발생!");
    }
    
    void process() {
        if (resource1 && resource2) {
            resource1->process();
            resource2->process();
        }
    }
};

// 강한 예외 안전성을 보장하는 함수
void strongExceptionSafety() {
    vector<int> data = {1, 2, 3, 4, 5};
    vector<int> backup = data;  // 백업 생성
    
    try {
        // 위험한 작업 시뮬레이션
        data.push_back(6);
        data.push_back(7);
        
        // 예외 발생 시뮬레이션
        if (data.size() > 6) {
            throw runtime_error("데이터 처리 오류!");
        }
        
        cout << "작업 성공!" << endl;
    }
    catch (...) {
        data = backup;  // 원래 상태로 복원 (강한 예외 안전성)
        cout << "오류 발생, 원래 상태로 복원" << endl;
        throw;  // 예외 재발생
    }
}

int main() {
    cout << "=== 예외 안전하지 않은 코드 ===" << endl;
    try {
        UnsafeManager unsafe;
        unsafe.initialize();
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
    }
    
    cout << "\n=== 예외 안전한 코드 ===" << endl;
    try {
        SafeManager safe;
        safe.initialize();
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
        cout << "하지만 자원은 안전하게 해제됨" << endl;
    }
    
    cout << "\n=== 강한 예외 안전성 ===" << endl;
    try {
        strongExceptionSafety();
    }
    catch (const exception& e) {
        cout << "최종 오류: " << e.what() << endl;
    }
    
    return 0;
}
```

---

## 4. 예제 04: RAII와 예외 (04_raii_exception.cpp)

### 예제 정의
RAII 패턴을 활용하여 예외 상황에서도 안전한 자원 관리를 구현합니다.

```cpp
/*
주제: RAII와 예외 (RAII & Exception)
정의: RAII 패턴으로 예외 발생 시에도 자원이 안전하게 해제되도록 보장
*/

#include <iostream>
#include <fstream>
#include <memory>
#include <mutex>
using namespace std;

// 파일 자원 관리 RAII 클래스
class FileHandler {
private:
    ofstream file;
    string filename;
    
public:
    FileHandler(const string& fname) : filename(fname) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("파일을 열 수 없습니다: " + filename);
        }
        cout << "파일 열기 성공: " << filename << endl;
    }
    
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
            cout << "파일 자동 닫기: " << filename << endl;
        }
    }
    
    void write(const string& content) {
        if (!file.is_open()) {
            throw runtime_error("파일이 열려있지 않습니다.");
        }
        file << content << endl;
    }
    
    void forceError() {
        throw runtime_error("강제 오류 발생!");
    }
};

// 뮤텍스 RAII 클래스
class LockGuard {
private:
    mutex& mtx;
    
public:
    LockGuard(mutex& m) : mtx(m) {
        mtx.lock();
        cout << "뮤텍스 잠금" << endl;
    }
    
    ~LockGuard() {
        mtx.unlock();
        cout << "뮤텍스 해제" << endl;
    }
};

mutex globalMutex;

void processData() {
    LockGuard lock(globalMutex);  // RAII로 뮤텍스 관리
    
    cout << "중요한 작업 수행 중..." << endl;
    
    // 예외 발생 시뮬레이션
    throw runtime_error("작업 중 오류 발생!");
    
    cout << "작업 완료" << endl;  // 실행되지 않음
}

int main() {
    cout << "=== RAII와 예외 처리 ===" << endl;
    
    cout << "\n1. 파일 처리 중 예외 발생" << endl;
    try {
        FileHandler file("test.txt");
        file.write("첫 번째 줄");
        file.write("두 번째 줄");
        file.forceError();  // 예외 발생
        file.write("세 번째 줄");  // 실행되지 않음
    }
    catch (const exception& e) {
        cout << "파일 처리 오류: " << e.what() << endl;
    }
    // FileHandler 소멸자가 자동으로 파일을 닫음
    
    cout << "\n2. 뮤텍스 처리 중 예외 발생" << endl;
    try {
        processData();
    }
    catch (const exception& e) {
        cout << "데이터 처리 오류: " << e.what() << endl;
    }
    // LockGuard 소멸자가 자동으로 뮤텍스를 해제
    
    cout << "\n3. 스마트 포인터와 예외" << endl;
    try {
        auto ptr1 = make_unique<int>(42);
        auto ptr2 = make_unique<string>("Hello");
        
        cout << "*ptr1 = " << *ptr1 << endl;
        cout << "*ptr2 = " << *ptr2 << endl;
        
        throw runtime_error("스마트 포인터 테스트 오류!");
    }
    catch (const exception& e) {
        cout << "스마트 포인터 오류: " << e.what() << endl;
    }
    // 스마트 포인터들이 자동으로 메모리 해제
    
    cout << "\n모든 자원이 안전하게 해제되었습니다." << endl;
    return 0;
}
```

---

## 5. 예제 05: 스마트 포인터와 예외 (05_smart_pointer_exception.cpp)

### 예제 정의
스마트 포인터를 활용하여 예외 안전한 메모리 관리를 구현합니다.

```cpp
/*
주제: 스마트 포인터와 예외 (Smart Pointer & Exception)
정의: unique_ptr, shared_ptr을 사용하여 예외 상황에서도 메모리 누수 방지
*/

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
using namespace std;

class Resource {
public:
    int value;
    
    Resource(int v) : value(v) {
        cout << "Resource 생성: " << value << endl;
    }
    
    ~Resource() {
        cout << "Resource 소멸: " << value << endl;
    }
    
    void process() {
        if (value < 0) {
            throw invalid_argument("음수 값은 처리할 수 없습니다.");
        }
        cout << "Resource 처리: " << value << endl;
    }
};

// 위험한 방식 (raw pointer)
void dangerousFunction() {
    cout << "\n=== 위험한 방식 (Raw Pointer) ===" << endl;
    
    Resource* res1 = new Resource(10);
    Resource* res2 = new Resource(20);
    
    try {
        res1->process();
        res2->process();
        
        // 예외 발생 시뮬레이션
        throw runtime_error("처리 중 오류 발생!");
        
        // 아래 코드는 실행되지 않음 -> 메모리 누수!
        delete res1;
        delete res2;
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
        // 예외 처리에서 수동으로 정리해야 함
        delete res1;
        delete res2;
    }
}

// 안전한 방식 (unique_ptr)
void safeFunction() {
    cout << "\n=== 안전한 방식 (unique_ptr) ===" << endl;
    
    auto res1 = make_unique<Resource>(30);
    auto res2 = make_unique<Resource>(40);
    
    try {
        res1->process();
        res2->process();
        
        // 예외 발생 시뮬레이션
        throw runtime_error("처리 중 오류 발생!");
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
    }
    // unique_ptr이 자동으로 메모리 해제
}

// shared_ptr 사용
void sharedPtrExample() {
    cout << "\n=== shared_ptr 예제 ===" << endl;
    
    vector<shared_ptr<Resource>> resources;
    
    try {
        resources.push_back(make_shared<Resource>(50));
        resources.push_back(make_shared<Resource>(60));
        resources.push_back(make_shared<Resource>(-10));  // 문제가 될 값
        
        for (auto& res : resources) {
            res->process();  // -10에서 예외 발생
        }
    }
    catch (const exception& e) {
        cout << "처리 오류: " << e.what() << endl;
    }
    // shared_ptr들이 자동으로 메모리 해제
}

// 팩토리 함수와 예외 안전성
unique_ptr<Resource> createResource(int value) {
    if (value == 0) {
        throw invalid_argument("0은 유효하지 않은 값입니다.");
    }
    return make_unique<Resource>(value);
}

int main() {
    cout << "=== 스마트 포인터와 예외 안전성 ===" << endl;
    
    // 위험한 방식 시연
    try {
        dangerousFunction();
    }
    catch (...) {
        cout << "dangerousFunction에서 예외 발생" << endl;
    }
    
    // 안전한 방식 시연
    try {
        safeFunction();
    }
    catch (...) {
        cout << "safeFunction에서 예외 발생" << endl;
    }
    
    // shared_ptr 시연
    sharedPtrExample();
    
    cout << "\n=== 팩토리 함수와 예외 ===" << endl;
    try {
        auto res1 = createResource(100);
        auto res2 = createResource(0);  // 예외 발생
        auto res3 = createResource(200);
    }
    catch (const exception& e) {
        cout << "팩토리 오류: " << e.what() << endl;
    }
    
    cout << "\n프로그램 종료 - 모든 자원이 안전하게 해제되었습니다." << endl;
    return 0;
}
```

---

## 6. 예제 06: 파일 I/O와 예외 (06_file_io_exception.cpp)

### 예제 정의
파일 입출력 작업에서의 예외 처리와 안전한 파일 관리를 학습합니다.

```cpp
/*
주제: 파일 I/O와 예외 (File I/O & Exception)
정의: 파일 작업 시 발생할 수 있는 예외를 안전하게 처리
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class FileManager {
public:
    static void writeFile(const string& filename, const vector<string>& lines) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("파일을 생성할 수 없습니다: " + filename);
        }
        
        for (const auto& line : lines) {
            file << line << endl;
            if (file.fail()) {
                throw runtime_error("파일 쓰기 중 오류가 발생했습니다.");
            }
        }
        
        cout << "파일 쓰기 완료: " << filename << endl;
    }
    
    static vector<string> readFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("파일을 열 수 없습니다: " + filename);
        }
        
        vector<string> lines;
        string line;
        
        while (getline(file, line)) {
            lines.push_back(line);
        }
        
        if (file.bad()) {
            throw runtime_error("파일 읽기 중 오류가 발생했습니다.");
        }
        
        cout << "파일 읽기 완료: " << filename << " (" << lines.size() << "줄)" << endl;
        return lines;
    }
    
    static void copyFile(const string& source, const string& destination) {
        try {
            auto content = readFile(source);
            writeFile(destination, content);
            cout << "파일 복사 완료: " << source << " -> " << destination << endl;
        }
        catch (const exception& e) {
            throw runtime_error("파일 복사 실패: " + string(e.what()));
        }
    }
};

// RAII를 사용한 안전한 파일 클래스
class SafeFile {
private:
    fstream file;
    string filename;
    
public:
    SafeFile(const string& fname, ios::openmode mode) : filename(fname) {
        file.open(filename, mode);
        if (!file.is_open()) {
            throw runtime_error("파일 열기 실패: " + filename);
        }
        cout << "파일 열기: " << filename << endl;
    }
    
    ~SafeFile() {
        if (file.is_open()) {
            file.close();
            cout << "파일 닫기: " << filename << endl;
        }
    }
    
    void writeLine(const string& line) {
        file << line << endl;
        if (file.fail()) {
            throw runtime_error("쓰기 오류: " + filename);
        }
    }
    
    string readLine() {
        string line;
        if (!getline(file, line)) {
            if (file.eof()) {
                throw runtime_error("파일 끝에 도달했습니다.");
            } else {
                throw runtime_error("읽기 오류: " + filename);
            }
        }
        return line;
    }
};

int main() {
    cout << "=== 파일 I/O 예외 처리 ===" << endl;
    
    // 1. 기본 파일 작업
    try {
        vector<string> testData = {
            "첫 번째 줄",
            "두 번째 줄",
            "세 번째 줄"
        };
        
        FileManager::writeFile("test.txt", testData);
        auto readData = FileManager::readFile("test.txt");
        
        cout << "읽은 내용:" << endl;
        for (const auto& line : readData) {
            cout << "  " << line << endl;
        }
        
    }
    catch (const exception& e) {
        cout << "파일 작업 오류: " << e.what() << endl;
    }
    
    // 2. 존재하지 않는 파일 읽기
    try {
        FileManager::readFile("nonexistent.txt");
    }
    catch (const exception& e) {
        cout << "예상된 오류: " << e.what() << endl;
    }
    
    // 3. 파일 복사
    try {
        FileManager::copyFile("test.txt", "backup.txt");
    }
    catch (const exception& e) {
        cout << "복사 오류: " << e.what() << endl;
    }
    
    // 4. RAII 파일 클래스 사용
    cout << "\n=== RAII 파일 클래스 ===" << endl;
    try {
        {
            SafeFile outFile("safe_test.txt", ios::out);
            outFile.writeLine("RAII로 안전하게 관리되는 파일");
            outFile.writeLine("예외가 발생해도 파일이 닫힙니다");
            // 강제 예외 발생
            // throw runtime_error("테스트 예외");
        } // 여기서 SafeFile 소멸자가 자동으로 파일을 닫음
        
        SafeFile inFile("safe_test.txt", ios::in);
        cout << "읽은 줄: " << inFile.readLine() << endl;
        cout << "읽은 줄: " << inFile.readLine() << endl;
        
    }
    catch (const exception& e) {
        cout << "RAII 파일 오류: " << e.what() << endl;
    }
    
    return 0;
}
```

---

## 7. 예제 07: 디버깅과 로깅 (07_debugging_logging.cpp)

### 예제 정의
디버깅을 위한 로깅 시스템과 assert를 활용한 개발 도구를 학습합니다.

```cpp
/*
주제: 디버깅과 로깅 (Debugging & Logging)
정의: 프로그램의 실행 상태를 추적하고 문제를 진단하는 도구들
*/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>
#include <sstream>
using namespace std;

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    static ofstream logFile;
    static LogLevel currentLevel;
    
    static string getCurrentTime() {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        auto tm = *localtime(&time_t);
        
        stringstream ss;
        ss << "[" << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << "]";
        return ss.str();
    }
    
    static string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
    
public:
    static void initialize(const string& filename, LogLevel level = LogLevel::INFO) {
        logFile.open(filename, ios::app);
        currentLevel = level;
        log(LogLevel::INFO, "로그 시스템 초기화");
    }
    
    static void log(LogLevel level, const string& message) {
        if (level < currentLevel) return;
        
        string logMessage = getCurrentTime() + " [" + levelToString(level) + "] " + message;
        
        cout << logMessage << endl;  // 콘솔 출력
        if (logFile.is_open()) {
            logFile << logMessage << endl;  // 파일 출력
            logFile.flush();
        }
    }
    
    static void debug(const string& message) { log(LogLevel::DEBUG, message); }
    static void info(const string& message) { log(LogLevel::INFO, message); }
    static void warning(const string& message) { log(LogLevel::WARNING, message); }
    static void error(const string& message) { log(LogLevel::ERROR, message); }
    
    static void close() {
        log(LogLevel::INFO, "로그 시스템 종료");
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

// 정적 멤버 초기화
ofstream Logger::logFile;
LogLevel Logger::currentLevel = LogLevel::INFO;

// 디버깅용 매크로
#ifdef _DEBUG
    #define DEBUG_LOG(msg) Logger::debug(msg)
    #define ASSERT_MSG(condition, msg) assert((condition) && (msg))
#else
    #define DEBUG_LOG(msg)
    #define ASSERT_MSG(condition, msg)
#endif

class Calculator {
private:
    double lastResult;
    
public:
    Calculator() : lastResult(0) {
        Logger::info("Calculator 객체 생성");
    }
    
    double add(double a, double b) {
        DEBUG_LOG("덧셈 연산: " + to_string(a) + " + " + to_string(b));
        
        lastResult = a + b;
        Logger::info("덧셈 완료: " + to_string(lastResult));
        return lastResult;
    }
    
    double divide(double a, double b) {
        DEBUG_LOG("나눗셈 연산: " + to_string(a) + " / " + to_string(b));
        
        if (b == 0) {
            Logger::error("0으로 나누기 시도!");
            throw invalid_argument("0으로 나눌 수 없습니다.");
        }
        
        // assert를 사용한 조건 검사
        ASSERT_MSG(b != 0, "나누는 수가 0이 아니어야 합니다");
        
        lastResult = a / b;
        Logger::info("나눗셈 완료: " + to_string(lastResult));
        return lastResult;
    }
    
    double getLastResult() const {
        DEBUG_LOG("마지막 결과 조회: " + to_string(lastResult));
        return lastResult;
    }
    
    ~Calculator() {
        Logger::info("Calculator 객체 소멸");
    }
};

int main() {
    // 로그 시스템 초기화
    Logger::initialize("app.log", LogLevel::DEBUG);
    
    cout << "=== 디버깅과 로깅 시스템 ===" << endl;
    
    try {
        Calculator calc;
        
        Logger::info("프로그램 시작");
        
        double result1 = calc.add(10, 5);
        Logger::info("첫 번째 계산 결과: " + to_string(result1));
        
        double result2 = calc.divide(20, 4);
        Logger::info("두 번째 계산 결과: " + to_string(result2));
        
        // 경고 상황
        Logger::warning("0으로 나누기를 시도합니다.");
        
        // 오류 발생 시뮬레이션
        double result3 = calc.divide(10, 0);  // 예외 발생
        
    }
    catch (const exception& e) {
        Logger::error("예외 발생: " + string(e.what()));
        cout << "프로그램에서 오류가 발생했지만 로그에 기록되었습니다." << endl;
    }
    
    // 디버그 정보
    DEBUG_LOG("메인 함수 종료 준비");
    
    Logger::info("프로그램 정상 종료");
    Logger::close();
    
    cout << "\n로그가 'app.log' 파일에 저장되었습니다." << endl;
    
    return 0;
}
```

---

## 8. 예제 08: 코딩 표준과 스타일 (08_coding_standards.cpp)

### 예제 정의
일관된 코딩 스타일과 모범 사례를 적용한 코드 작성법을 학습합니다.

```cpp
/*
주제: 코딩 표준과 스타일 (Coding Standards & Style)
정의: 일관되고 읽기 쉬운 코드를 작성하기 위한 규칙과 관례
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// 네임스페이스 사용 (글로벌 using namespace std는 피하기)
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace MyProject {
    
    // 상수는 대문자와 언더스코어 사용
    const int MAX_STUDENTS = 100;
    const double PI = 3.14159;
    
    // 열거형은 class 사용 (scoped enum)
    enum class Grade {
        A_PLUS,
        A,
        B_PLUS,
        B,
        C_PLUS,
        C,
        D,
        F
    };
    
    // 클래스명은 PascalCase
    class StudentManager {
    private:
        // 멤버 변수는 camelCase 또는 snake_case (일관성 유지)
        vector<string> studentNames;
        vector<double> studentScores;
        int maxCapacity;
        
        // private 헬퍼 함수
        bool isValidScore(double score) const {
            return score >= 0.0 && score <= 100.0;
        }
        
        Grade calculateGrade(double score) const {
            if (score >= 97.0) return Grade::A_PLUS;
            if (score >= 93.0) return Grade::A;
            if (score >= 90.0) return Grade::B_PLUS;
            if (score >= 87.0) return Grade::B;
            if (score >= 83.0) return Grade::C_PLUS;
            if (score >= 80.0) return Grade::C;
            if (score >= 70.0) return Grade::D;
            return Grade::F;
        }
        
    public:
        // 생성자는 명시적 초기화 리스트 사용
        explicit StudentManager(int capacity = MAX_STUDENTS) 
            : maxCapacity(capacity) {
            studentNames.reserve(maxCapacity);
            studentScores.reserve(maxCapacity);
        }
        
        // 복사 방지 (필요한 경우에만)
        StudentManager(const StudentManager&) = delete;
        StudentManager& operator=(const StudentManager&) = delete;
        
        // 이동 생성자는 noexcept
        StudentManager(StudentManager&& other) noexcept 
            : studentNames(std::move(other.studentNames)),
              studentScores(std::move(other.studentScores)),
              maxCapacity(other.maxCapacity) {}
        
        // 함수명은 camelCase
        bool addStudent(const string& name, double score) {
            // 매개변수 검증
            if (name.empty()) {
                cout << "오류: 학생 이름이 비어있습니다." << endl;
                return false;
            }
            
            if (!isValidScore(score)) {
                cout << "오류: 점수는 0-100 사이여야 합니다." << endl;
                return false;
            }
            
            if (studentNames.size() >= static_cast<size_t>(maxCapacity)) {
                cout << "오류: 최대 수용 인원을 초과했습니다." << endl;
                return false;
            }
            
            // 중복 검사
            auto it = std::find(studentNames.begin(), studentNames.end(), name);
            if (it != studentNames.end()) {
                cout << "경고: 이미 존재하는 학생입니다: " << name << endl;
                return false;
            }
            
            studentNames.push_back(name);
            studentScores.push_back(score);
            return true;
        }
        
        void displayAllStudents() const {
            cout << "\n=== 학생 목록 (" << studentNames.size() << "명) ===" << endl;
            
            for (size_t i = 0; i < studentNames.size(); ++i) {
                Grade grade = calculateGrade(studentScores[i]);
                cout << (i + 1) << ". " << studentNames[i] 
                     << " - 점수: " << studentScores[i] 
                     << ", 등급: " << gradeToString(grade) << endl;
            }
        }
        
        // const 멤버 함수 적극 활용
        double getAverageScore() const {
            if (studentScores.empty()) {
                return 0.0;
            }
            
            double sum = 0.0;
            for (double score : studentScores) {
                sum += score;
            }
            return sum / studentScores.size();
        }
        
        size_t getStudentCount() const {
            return studentNames.size();
        }
        
        // 정적 유틸리티 함수
        static string gradeToString(Grade grade) {
            switch (grade) {
                case Grade::A_PLUS: return "A+";
                case Grade::A:      return "A";
                case Grade::B_PLUS: return "B+";
                case Grade::B:      return "B";
                case Grade::C_PLUS: return "C+";
                case Grade::C:      return "C";
                case Grade::D:      return "D";
                case Grade::F:      return "F";
                default:            return "Unknown";
            }
        }
    };
    
} // namespace MyProject

// 함수는 camelCase
void demonstrateBestPractices() {
    using namespace MyProject;
    
    cout << "=== C++ 코딩 표준 데모 ===" << endl;
    
    // auto 키워드 적극 활용
    auto manager = std::make_unique<StudentManager>(5);
    
    // 명확한 변수명 사용
    const vector<std::pair<string, double>> testStudents = {
        {"김철수", 95.5},
        {"이영희", 87.3},
        {"박민수", 92.0},
        {"최정화", 78.8}
    };
    
    // range-based for loop 사용
    for (const auto& [name, score] : testStudents) {
        manager->addStudent(name, score);
    }
    
    manager->displayAllStudents();
    
    cout << "\n평균 점수: " << manager->getAverageScore() << endl;
    cout << "총 학생 수: " << manager->getStudentCount() << "명" << endl;
    
    // 잘못된 입력 테스트
    cout << "\n=== 오류 처리 테스트 ===" << endl;
    manager->addStudent("", 90);        // 빈 이름
    manager->addStudent("홍길동", 150); // 잘못된 점수
    manager->addStudent("김철수", 80);  // 중복 이름
}

int main() {
    try {
        demonstrateBestPractices();
    }
    catch (const std::exception& e) {
        cout << "예외 발생: " << e.what() << endl;
        return 1;
    }
    
    cout << "\n=== 코딩 표준 정리 ===" << endl;
    cout << "1. 일관된 네이밍 컨벤션 (camelCase, PascalCase)" << endl;
    cout << "2. const 정확성 유지" << endl;
    cout << "3. RAII 패턴 활용" << endl;
    cout << "4. 스마트 포인터 사용" << endl;
    cout << "5. 예외 안전성 보장" << endl;
    cout << "6. 명확한 함수와 변수명" << endl;
    cout << "7. 적절한 주석과 문서화" << endl;
    
    return 0;
}
```

---

## 9. 예제 09: 프로젝트 구조화 (파일 분리)

### ProjectStructure.h
```cpp
/*
주제: 프로젝트 구조화 - 도서관 관리 시스템 (헤더 파일)
정의: 큰 프로젝트를 모듈로 나누어 관리하는 방법
*/

#ifndef PROJECT_STRUCTURE_H
#define PROJECT_STRUCTURE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace Library {
    
    // 전방 선언
    class Book;
    class Member;
    class LibrarySystem;
    
    // 열거형
    enum class BookStatus {
        AVAILABLE,
        BORROWED,
        RESERVED,
        DAMAGED
    };
    
    // 예외 클래스들
    class LibraryException : public std::exception {
    protected:
        std::string message;
    public:
        explicit LibraryException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };
    
    class BookNotFoundException : public LibraryException {
    public:
        BookNotFoundException(const std::string& title) 
            : LibraryException("책을 찾을 수 없습니다: " + title) {}
    };
    
    class MemberNotFoundException : public LibraryException {
    public:
        MemberNotFoundException(int id) 
            : LibraryException("회원을 찾을 수 없습니다: ID " + std::to_string(id)) {}
    };
    
    // Book 클래스
    class Book {
    private:
        std::string title;
        std::string author;
        std::string isbn;
        BookStatus status;
        static int nextId;
        int bookId;
        
    public:
        Book(const std::string& t, const std::string& a, const std::string& i);
        
        // Getter 함수들
        int getId() const { return bookId; }
        std::string getTitle() const { return title; }
        std::string getAuthor() const { return author; }
        std::string getIsbn() const { return isbn; }
        BookStatus getStatus() const { return status; }
        
        // 상태 변경
        void setStatus(BookStatus newStatus) { status = newStatus; }
        
        // 출력
        void display() const;
        static std::string statusToString(BookStatus status);
    };
    
    // Member 클래스
    class Member {
    private:
        int memberId;
        std::string name;
        std::string email;
        std::vector<int> borrowedBooks;
        static int nextMemberId;
        
    public:
        Member(const std::string& n, const std::string& e);
        
        // Getter 함수들
        int getId() const { return memberId; }
        std::string getName() const { return name; }
        std::string getEmail() const { return email; }
        const std::vector<int>& getBorrowedBooks() const { return borrowedBooks; }
        
        // 도서 관리
        void borrowBook(int bookId);
        void returnBook(int bookId);
        bool hasBorrowed(int bookId) const;
        
        void display() const;
    };
    
    // LibrarySystem 클래스
    class LibrarySystem {
    private:
        std::vector<std::unique_ptr<Book>> books;
        std::vector<std::unique_ptr<Member>> members;
        
        Book* findBookById(int id);
        Member* findMemberById(int id);
        
    public:
        // 도서 관리
        void addBook(const std::string& title, const std::string& author, const std::string& isbn);
        void removeBook(int bookId);
        Book* findBook(const std::string& title);
        void displayAllBooks();
        
        // 회원 관리
        void addMember(const std::string& name, const std::string& email);
        void removeMember(int memberId);
        Member* findMember(int memberId);
        void displayAllMembers();
        
        // 대출/반납
        void borrowBook(int memberId, int bookId);
        void returnBook(int memberId, int bookId);
        
        // 통계
        void displayStatistics();
        
        // 소멸자
        ~LibrarySystem() = default;
    };
    
} // namespace Library

#endif
```

### ProjectStructure.cpp
```cpp
/*
구현 파일
*/

#include "ProjectStructure.h"

namespace Library {
    
    // Book 클래스 구현
    int Book::nextId = 1;
    
    Book::Book(const std::string& t, const std::string& a, const std::string& i)
        : title(t), author(a), isbn(i), status(BookStatus::AVAILABLE), bookId(nextId++) {}
    
    void Book::display() const {
        std::cout << "ID: " << bookId << ", 제목: " << title 
                  << ", 저자: " << author << ", 상태: " << statusToString(status) << std::endl;
    }
    
    std::string Book::statusToString(BookStatus status) {
        switch (status) {
            case BookStatus::AVAILABLE: return "대출가능";
            case BookStatus::BORROWED: return "대출중";
            case BookStatus::RESERVED: return "예약됨";
            case BookStatus::DAMAGED: return "손상됨";
            default: return "알수없음";
        }
    }
    
    // Member 클래스 구현
    int Member::nextMemberId = 1000;
    
    Member::Member(const std::string& n, const std::string& e)
        : memberId(nextMemberId++), name(n), email(e) {}
    
    void Member::borrowBook(int bookId) {
        if (!hasBorrowed(bookId)) {
            borrowedBooks.push_back(bookId);
        }
    }
    
    void Member::returnBook(int bookId) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }
    
    bool Member::hasBorrowed(int bookId) const {
        return std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) != borrowedBooks.end();
    }
    
    void Member::display() const {
        std::cout << "ID: " << memberId << ", 이름: " << name 
                  << ", 이메일: " << email << ", 대출도서: " << borrowedBooks.size() << "권" << std::endl;
    }
    
    // LibrarySystem 클래스 구현
    void LibrarySystem::addBook(const std::string& title, const std::string& author, const std::string& isbn) {
        books.push_back(std::make_unique<Book>(title, author, isbn));
        std::cout << "도서 추가 완료: " << title << std::endl;
    }
    
    void LibrarySystem::addMember(const std::string& name, const std::string& email) {
        members.push_back(std::make_unique<Member>(name, email));
        std::cout << "회원 등록 완료: " << name << std::endl;
    }
    
    Book* LibrarySystem::findBookById(int id) {
        auto it = std::find_if(books.begin(), books.end(),
            [id](const std::unique_ptr<Book>& book) {
                return book->getId() == id;
            });
        return (it != books.end()) ? it->get() : nullptr;
    }
    
    Member* LibrarySystem::findMemberById(int id) {
        auto it = std::find_if(members.begin(), members.end(),
            [id](const std::unique_ptr<Member>& member) {
                return member->getId() == id;
            });
        return (it != members.end()) ? it->get() : nullptr;
    }
    
    Book* LibrarySystem::findBook(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(),
            [&title](const std::unique_ptr<Book>& book) {
                return book->getTitle() == title;
            });
        return (it != books.end()) ? it->get() : nullptr;
    }
    
    Member* LibrarySystem::findMember(int memberId) {
        return findMemberById(memberId);
    }
    
    void LibrarySystem::borrowBook(int memberId, int bookId) {
        Member* member = findMemberById(memberId);
        if (!member) {
            throw MemberNotFoundException(memberId);
        }
        
        Book* book = findBookById(bookId);
        if (!book) {
            throw BookNotFoundException("ID " + std::to_string(bookId));
        }
        
        if (book->getStatus() != BookStatus::AVAILABLE) {
            throw LibraryException("도서가 대출 불가능한 상태입니다.");
        }
        
        book->setStatus(BookStatus::BORROWED);
        member->borrowBook(bookId);
        
        std::cout << member->getName() << "님이 '" << book->getTitle() << "' 도서를 대출했습니다." << std::endl;
    }
    
    void LibrarySystem::returnBook(int memberId, int bookId) {
        Member* member = findMemberById(memberId);
        if (!member) {
            throw MemberNotFoundException(memberId);
        }
        
        Book* book = findBookById(bookId);
        if (!book) {
            throw BookNotFoundException("ID " + std::to_string(bookId));
        }
        
        if (!member->hasBorrowed(bookId)) {
            throw LibraryException("해당 회원이 대출하지 않은 도서입니다.");
        }
        
        book->setStatus(BookStatus::AVAILABLE);
        member->returnBook(bookId);
        
        std::cout << member->getName() << "님이 '" << book->getTitle() << "' 도서를 반납했습니다." << std::endl;
    }
    
    void LibrarySystem::displayAllBooks() {
        std::cout << "\n=== 전체 도서 목록 ===" << std::endl;
        for (const auto& book : books) {
            book->display();
        }
    }
    
    void LibrarySystem::displayAllMembers() {
        std::cout << "\n=== 전체 회원 목록 ===" << std::endl;
        for (const auto& member : members) {
            member->display();
        }
    }
    
    void LibrarySystem::displayStatistics() {
        std::cout << "\n=== 도서관 통계 ===" << std::endl;
        std::cout << "총 도서 수: " << books.size() << "권" << std::endl;
        std::cout << "총 회원 수: " << members.size() << "명" << std::endl;
        
        int availableBooks = 0;
        int borrowedBooks = 0;
        
        for (const auto& book : books) {
            if (book->getStatus() == BookStatus::AVAILABLE) {
                availableBooks++;
            } else if (book->getStatus() == BookStatus::BORROWED) {
                borrowedBooks++;
            }
        }
        
        std::cout << "대출 가능 도서: " << availableBooks << "권" << std::endl;
        std::cout << "대출 중인 도서: " << borrowedBooks << "권" << std::endl;
    }
    
} // namespace Library
```

### main.cpp
```cpp
/*
메인 파일 - 프로젝트 구조화 데모
*/

#include "ProjectStructure.h"

int main() {
    using namespace Library;
    
    std::cout << "=== 도서관 관리 시스템 ===" << std::endl;
    
    try {
        LibrarySystem library;
        
        // 도서 추가
        library.addBook("C++ 프로그래밍", "김개발", "978-1234567890");
        library.addBook("자료구조와 알고리즘", "이알고", "978-1234567891");
        library.addBook("데이터베이스 설계", "박디비", "978-1234567892");
        
        // 회원 등록
        library.addMember("김철수", "kim@email.com");
        library.addMember("이영희", "lee@email.com");
        
        // 전체 목록 출력
        library.displayAllBooks();
        library.displayAllMembers();
        
        // 대출/반납 테스트
        std::cout << "\n=== 대출/반납 테스트 ===" << std::endl;
        library.borrowBook(1000, 1);  // 김철수가 C++ 프로그래밍 대출
        library.borrowBook(1001, 2);  // 이영희가 자료구조와 알고리즘 대출
        
        // 통계 출력
        library.displayStatistics();
        
        // 반납
        library.returnBook(1000, 1);
        
        // 오류 상황 테스트
        std::cout << "\n=== 오류 상황 테스트 ===" << std::endl;
        try {
            library.borrowBook(9999, 1);  // 존재하지 않는 회원
        } catch (const LibraryException& e) {
            std::cout << "예상된 오류: " << e.what() << std::endl;
        }
        
        try {
            library.borrowBook(1000, 9999);  // 존재하지 않는 도서
        } catch (const LibraryException& e) {
            std::cout << "예상된 오류: " << e.what() << std::endl;
        }
        
        // 최종 통계
        library.displayStatistics();
        
    } catch (const std::exception& e) {
        std::cout << "시스템 오류: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== 프로젝트 구조화의 장점 ===" << std::endl;
    std::cout << "1. 모듈화: 기능별로 파일 분리" << std::endl;
    std::cout << "2. 재사용성: 헤더 파일로 인터페이스 제공" << std::endl;
    std::cout << "3. 유지보수성: 각 클래스가 독립적" << std::endl;
    std::cout << "4. 가독성: 관련 기능이 함께 모여있음" << std::endl;
    std::cout << "5. 확장성: 새로운 기능 추가가 용이" << std::endl;
    
    return 0;
}
```

---

## 10. 예제 10: 종합 프로젝트 - 게임 엔진 (10_game_engine.cpp)

### 예제 정의
모든 C++ 개념을 통합한 실용적인 게임 엔진을 구현합니다.

### GameEngine.h
```cpp
/*
주제: 종합 프로젝트 - 간단한 게임 엔진 (헤더 파일)
정의: 모든 C++ 개념을 통합한 실용적인 게임 엔진
*/

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <random>
#include <functional>

namespace GameEngine {
    
    // 게임 상태 열거형
    enum class GameState {
        MENU,
        PLAYING,
        PAUSED,
        GAME_OVER
    };
    
    // 2D 벡터 클래스
    struct Vector2D {
        float x, y;
        
        Vector2D(float x = 0, float y = 0) : x(x), y(y) {}
        
        Vector2D operator+(const Vector2D& other) const {
            return Vector2D(x + other.x, y + other.y);
        }
        
        Vector2D& operator+=(const Vector2D& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        
        Vector2D operator*(float scalar) const {
            return Vector2D(x * scalar, y * scalar);
        }
        
        float distance(const Vector2D& other) const {
            float dx = x - other.x;
            float dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }
        
        void normalize() {
            float magnitude = sqrt(x * x + y * y);
            if (magnitude > 0) {
                x /= magnitude;
                y /= magnitude;
            }
        }
    };
    
    // 게임 예외 클래스들
    class GameException : public std::exception {
    protected:
        std::string message;
    public:
        explicit GameException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };
    
    class InvalidPositionException : public GameException {
    public:
        InvalidPositionException(float x, float y) 
            : GameException("잘못된 위치: (" + std::to_string(x) + ", " + std::to_string(y) + ")") {}
    };
    
    class GameObjectNotFoundException : public GameException {
    public:
        GameObjectNotFoundException(const std::string& name) 
            : GameException("게임 오브젝트를 찾을 수 없음: " + name) {}
    };
    
    // 이벤트 시스템
    template<typename T>
    class EventSystem {
    private:
        std::vector<std::function<void(const T&)>> listeners;
        
    public:
        void addListener(std::function<void(const T&)> listener) {
            listeners.push_back(listener);
        }
        
        void broadcast(const T& event) {
            for (auto& listener : listeners) {
                try {
                    listener(event);
                } catch (const std::exception& e) {
                    std::cout << "이벤트 처리 오류: " << e.what() << std::endl;
                }
            }
        }
    };
    
    // 게임 이벤트 타입들
    struct CollisionEvent {
        std::string object1, object2;
        Vector2D position;
    };
    
    struct ScoreEvent {
        int score;
        std::string playerName;
    };
    
    // 게임 객체 기본 클래스 (추상 클래스)
    class GameObject {
    protected:
        Vector2D position;
        Vector2D velocity;
        std::string name;
        bool active;
        static int nextId;
        int id;
        
    public:
        GameObject(const std::string& n, Vector2D pos = Vector2D());
        virtual ~GameObject() = default;
        
        // 순수 가상 함수
        virtual void update(float deltaTime) = 0;
        virtual void render() const = 0;
        
        // 가상 함수
        virtual void onCollision(GameObject* other) {}
        virtual void onDestroy() {}
        
        // Getter/Setter
        const Vector2D& getPosition() const { return position; }
        const Vector2D& getVelocity() const { return velocity; }
        const std::string& getName() const { return name; }
        int getId() const { return id; }
        bool isActive() const { return active; }
        
        void setPosition(const Vector2D& pos) { position = pos; }
        void setVelocity(const Vector2D& vel) { velocity = vel; }
        void setActive(bool isActive) { active = isActive; }
        
        // 충돌 검사
        virtual bool checkCollision(const GameObject* other) const;
        
        // 이동
        void move(const Vector2D& direction, float speed, float deltaTime);
    };
    
    // 플레이어 클래스
    class Player : public GameObject {
    private:
        int health;
        int score;
        float speed;
        
    public:
        Player(const std::string& name, Vector2D pos = Vector2D(0, 0));
        
        void update(float deltaTime) override;
        void render() const override;
        void onCollision(GameObject* other) override;
        
        // 플레이어 전용 메서드
        void takeDamage(int damage);
        void addScore(int points);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);
        void moveLeft(float deltaTime);
        void moveRight(float deltaTime);
        
        // Getter
        int getHealth() const { return health; }
        int getScore() const { return score; }
        float getSpeed() const { return speed; }
    };
    
    // 적 클래스
    class Enemy : public GameObject {
    private:
        int damage;
        float speed;
        Vector2D targetPosition;
        
    public:
        Enemy(const std::string& name, Vector2D pos = Vector2D(0, 0));
        
        void update(float deltaTime) override;
        void render() const override;
        void onCollision(GameObject* other) override;
        
        void setTarget(const Vector2D& target) { targetPosition = target; }
        int getDamage() const { return damage; }
    };
    
    // 아이템 클래스
    class Item : public GameObject {
    private:
        int value;
        std::string itemType;
        
    public:
        Item(const std::string& name, const std::string& type, int val, Vector2D pos = Vector2D(0, 0));
        
        void update(float deltaTime) override;
        void render() const override;
        void onCollision(GameObject* other) override;
        
        int getValue() const { return value; }
        const std::string& getType() const { return itemType; }
    };
    
    // 게임 월드 관리자
    class GameWorld {
    private:
        std::vector<std::unique_ptr<GameObject>> gameObjects;
        std::unique_ptr<Player> player;
        GameState currentState;
        float worldWidth, worldHeight;
        
        // 이벤트 시스템
        EventSystem<CollisionEvent> collisionEvents;
        EventSystem<ScoreEvent> scoreEvents;
        
        // 랜덤 생성기
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> posDist;
        
    public:
        GameWorld(float width = 800, float height = 600);
        ~GameWorld() = default;
        
        // 게임 오브젝트 관리
        void addGameObject(std::unique_ptr<GameObject> obj);
        void removeGameObject(const std::string& name);
        GameObject* findGameObject(const std::string& name);
        
        // 플레이어 관리
        void setPlayer(std::unique_ptr<Player> p);
        Player* getPlayer() const { return player.get(); }
        
        // 게임 루프
        void update(float deltaTime);
        void render() const;
        
        // 충돌 검사
        void checkCollisions();
        
        // 게임 상태 관리
        void setState(GameState state) { currentState = state; }
        GameState getState() const { return currentState; }
        
        // 월드 경계 검사
        bool isInBounds(const Vector2D& position) const;
        void clampToBounds(Vector2D& position) const;
        
        // 적과 아이템 생성
        void spawnEnemy();
        void spawnItem();
        
        // 이벤트 리스너 등록
        void addCollisionListener(std::function<void(const CollisionEvent&)> listener);
        void addScoreListener(std::function<void(const ScoreEvent&)> listener);
        
        // 게임 통계
        void displayStatistics() const;
        
        // 게임 초기화 및 정리
        void initialize();
        void cleanup();
    };
    
    // 게임 엔진 메인 클래스
    class Game {
    private:
        std::unique_ptr<GameWorld> world;
        bool running;
        std::chrono::high_resolution_clock::time_point lastFrameTime;
        
        // 성능 측정
        int frameCount;
        float totalTime;
        float averageFPS;
        
    public:
        Game();
        ~Game() = default;
        
        // 게임 생명주기
        void initialize();
        void run();
        void shutdown();
        
        // 게임 루프 구성요소
        void handleInput();
        void update(float deltaTime);
        void render();
        
        // 유틸리티
        float calculateDeltaTime();
        void updateFPS(float deltaTime);
        void displayFPS() const;
        
        bool isRunning() const { return running; }
        void stop() { running = false; }
    };
    
} // namespace GameEngine

#endif
```

### GameEngine.cpp
```cpp
/*
게임 엔진 구현 파일
*/

#include "GameEngine.h"
#include <iostream>
#include <iomanip>
#include <cmath>

namespace GameEngine {
    
    // GameObject 구현
    int GameObject::nextId = 1;
    
    GameObject::GameObject(const std::string& n, Vector2D pos) 
        : position(pos), velocity(0, 0), name(n), active(true), id(nextId++) {}
    
    bool GameObject::checkCollision(const GameObject* other) const {
        if (!other || !other->isActive() || !this->isActive()) {
            return false;
        }
        
        float distance = position.distance(other->getPosition());
        return distance < 20.0f; // 간단한 원형 충돌 검사
    }
    
    void GameObject::move(const Vector2D& direction, float speed, float deltaTime) {
        Vector2D normalizedDir = direction;
        normalizedDir.normalize();
        velocity = normalizedDir * speed;
        position += velocity * deltaTime;
    }
    
    // Player 구현
    Player::Player(const std::string& name, Vector2D pos) 
        : GameObject(name, pos), health(100), score(0), speed(200.0f) {}
    
    void Player::update(float deltaTime) {
        // 플레이어 업데이트 로직
        if (health <= 0) {
            setActive(false);
        }
    }
    
    void Player::render() const {
        std::cout << "플레이어 " << name << " 위치: (" 
                  << std::fixed << std::setprecision(1) 
                  << position.x << ", " << position.y << ") "
                  << "체력: " << health << " 점수: " << score << std::endl;
    }
    
    void Player::onCollision(GameObject* other) {
        if (auto enemy = dynamic_cast<Enemy*>(other)) {
            takeDamage(enemy->getDamage());
            std::cout << name << "이(가) 적과 충돌! 데미지: " << enemy->getDamage() << std::endl;
        }
        else if (auto item = dynamic_cast<Item*>(other)) {
            if (item->getType() == "coin") {
                addScore(item->getValue());
                std::cout << name << "이(가) 코인 획득! +" << item->getValue() << "점" << std::endl;
            }
            else if (item->getType() == "health") {
                health = std::min(100, health + item->getValue());
                std::cout << name << "이(가) 체력 회복! +" << item->getValue() << " HP" << std::endl;
            }
            item->setActive(false);
        }
    }
    
    void Player::takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }
    
    void Player::addScore(int points) {
        score += points;
    }
    
    void Player::moveUp(float deltaTime) {
        move(Vector2D(0, -1), speed, deltaTime);
    }
    
    void Player::moveDown(float deltaTime) {
        move(Vector2D(0, 1), speed, deltaTime);
    }
    
    void Player::moveLeft(float deltaTime) {
        move(Vector2D(-1, 0), speed, deltaTime);
    }
    
    void Player::moveRight(float deltaTime) {
        move(Vector2D(1, 0), speed, deltaTime);
    }
    
    // Enemy 구현
    Enemy::Enemy(const std::string& name, Vector2D pos) 
        : GameObject(name, pos), damage(10), speed(100.0f), targetPosition(0, 0) {}
    
    void Enemy::update(float deltaTime) {
        // 타겟을 향해 이동
        Vector2D direction = Vector2D(targetPosition.x - position.x, targetPosition.y - position.y);
        move(direction, speed, deltaTime);
    }
    
    void Enemy::render() const {
        std::cout << "적 " << name << " 위치: (" 
                  << std::fixed << std::setprecision(1) 
                  << position.x << ", " << position.y << ")" << std::endl;
    }
    
    void Enemy::onCollision(GameObject* other) {
        if (dynamic_cast<Player*>(other)) {
            // 플레이어와 충돌 시 사라짐
            setActive(false);
        }
    }
    
    // Item 구현
    Item::Item(const std::string& name, const std::string& type, int val, Vector2D pos) 
        : GameObject(name, pos), value(val), itemType(type) {}
    
    void Item::update(float deltaTime) {
        // 아이템은 기본적으로 정적
    }
    
    void Item::render() const {
        std::cout << "아이템 " << name << "(" << itemType << ") 위치: (" 
                  << std::fixed << std::setprecision(1) 
                  << position.x << ", " << position.y << ") 가치: " << value << std::endl;
    }
    
    void Item::onCollision(GameObject* other) {
        if (dynamic_cast<Player*>(other)) {
            // 플레이어가 수집하면 사라짐
            setActive(false);
        }
    }
    
    // GameWorld 구현
    GameWorld::GameWorld(float width, float height) 
        : currentState(GameState::MENU), worldWidth(width), worldHeight(height),
          gen(rd()), posDist(0.0f, 1.0f) {}
    
    void GameWorld::addGameObject(std::unique_ptr<GameObject> obj) {
        if (!obj) {
            throw std::invalid_argument("null 게임 오브젝트를 추가할 수 없습니다.");
        }
        gameObjects.push_back(std::move(obj));
    }
    
    void GameWorld::removeGameObject(const std::string& name) {
        auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
            [&name](const std::unique_ptr<GameObject>& obj) {
                return obj->getName() == name;
            });
        
        if (it != gameObjects.end()) {
            (*it)->onDestroy();
            gameObjects.erase(it);
        }
    }
    
    GameObject* GameWorld::findGameObject(const std::string& name) {
        auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
            [&name](const std::unique_ptr<GameObject>& obj) {
                return obj->getName() == name;
            });
        
        return (it != gameObjects.end()) ? it->get() : nullptr;
    }
    
    void GameWorld::setPlayer(std::unique_ptr<Player> p) {
        player = std::move(p);
    }
    
    void GameWorld::update(float deltaTime) {
        if (currentState != GameState::PLAYING) {
            return;
        }
        
        // 플레이어 업데이트
        if (player && player->isActive()) {
            player->update(deltaTime);
            clampToBounds(const_cast<Vector2D&>(player->getPosition()));
        }
        
        // 모든 게임 오브젝트 업데이트
        for (auto& obj : gameObjects) {
            if (obj->isActive()) {
                obj->update(deltaTime);
                clampToBounds(const_cast<Vector2D&>(obj->getPosition()));
            }
        }
        
        // 충돌 검사
        checkCollisions();
        
        // 비활성 오브젝트 제거
        gameObjects.erase(
            std::remove_if(gameObjects.begin(), gameObjects.end(),
                [](const std::unique_ptr<GameObject>& obj) {
                    return !obj->isActive();
                }),
            gameObjects.end()
        );
        
        // 게임 종료 조건 확인
        if (player && !player->isActive()) {
            currentState = GameState::GAME_OVER;
        }
    }
    
    void GameWorld::render() const {
        std::cout << "\n===== 게임 화면 =====" << std::endl;
        std::cout << "상태: ";
        switch (currentState) {
            case GameState::MENU: std::cout << "메뉴"; break;
            case GameState::PLAYING: std::cout << "플레이 중"; break;
            case GameState::PAUSED: std::cout << "일시정지"; break;
            case GameState::GAME_OVER: std::cout << "게임 오버"; break;
        }
        std::cout << std::endl;
        
        if (player) {
            player->render();
        }
        
        for (const auto& obj : gameObjects) {
            if (obj->isActive()) {
                obj->render();
            }
        }
        
        std::cout << "===================" << std::endl;
    }
    
    void GameWorld::checkCollisions() {
        if (!player || !player->isActive()) return;
        
        // 플레이어와 다른 오브젝트간 충돌 검사
        for (auto& obj : gameObjects) {
            if (obj->isActive() && player->checkCollision(obj.get())) {
                // 충돌 이벤트 발생
                CollisionEvent event;
                event.object1 = player->getName();
                event.object2 = obj->getName();
                event.position = player->getPosition();
                
                collisionEvents.broadcast(event);
                
                // 충돌 처리
                player->onCollision(obj.get());
                obj->onCollision(player.get());
            }
        }
    }
    
    bool GameWorld::isInBounds(const Vector2D& position) const {
        return position.x >= 0 && position.x <= worldWidth &&
               position.y >= 0 && position.y <= worldHeight;
    }
    
    void GameWorld::clampToBounds(Vector2D& position) const {
        position.x = std::max(0.0f, std::min(worldWidth, position.x));
        position.y = std::max(0.0f, std::min(worldHeight, position.y));
    }
    
    void GameWorld::spawnEnemy() {
        static int enemyCount = 1;
        auto enemy = std::make_unique<Enemy>("Enemy_" + std::to_string(enemyCount++));
        
        // 랜덤 위치에 생성
        Vector2D spawnPos(posDist(gen) * worldWidth, posDist(gen) * worldHeight);
        enemy->setPosition(spawnPos);
        
        // 플레이어를 타겟으로 설정
        if (player) {
            enemy->setTarget(player->getPosition());
        }
        
        addGameObject(std::move(enemy));
    }
    
    void GameWorld::spawnItem() {
        static int itemCount = 1;
        
        // 랜덤으로 아이템 타입 결정
        std::string itemType = (posDist(gen) > 0.5f) ? "coin" : "health";
        int value = (itemType == "coin") ? 10 : 20;
        
        auto item = std::make_unique<Item>("Item_" + std::to_string(itemCount++), itemType, value);
        
        // 랜덤 위치에 생성
        Vector2D spawnPos(posDist(gen) * worldWidth, posDist(gen) * worldHeight);
        item->setPosition(spawnPos);
        
        addGameObject(std::move(item));
    }
    
    void GameWorld::addCollisionListener(std::function<void(const CollisionEvent&)> listener) {
        collisionEvents.addListener(listener);
    }
    
    void GameWorld::addScoreListener(std::function<void(const ScoreEvent&)> listener) {
        scoreEvents.addListener(listener);
    }
    
    void GameWorld::displayStatistics() const {
        std::cout << "\n=== 게임 통계 ===" << std::endl;
        std::cout << "활성 오브젝트 수: " << gameObjects.size() << std::endl;
        if (player) {
            std::cout << "플레이어 체력: " << player->getHealth() << std::endl;
            std::cout << "플레이어 점수: " << player->getScore() << std::endl;
        }
        std::cout << "월드 크기: " << worldWidth << " x " << worldHeight << std::endl;
    }
    
    void GameWorld::initialize() {
        gameObjects.clear();
        currentState = GameState::PLAYING;
        
        // 이벤트 리스너 등록
        addCollisionListener([](const CollisionEvent& event) {
            std::cout << "충돌 발생: " << event.object1 << " vs " << event.object2 << std::endl;
        });
        
        std::cout << "게임 월드 초기화 완료" << std::endl;
    }
    
    void GameWorld::cleanup() {
        gameObjects.clear();
        player.reset();
        std::cout << "게임 월드 정리 완료" << std::endl;
    }
    
    // Game 구현
    Game::Game() : running(false), frameCount(0), totalTime(0.0f), averageFPS(0.0f) {
        world = std::make_unique<GameWorld>();
    }
    
    void Game::initialize() {
        std::cout << "=== 게임 엔진 초기화 ===" << std::endl;
        
        try {
            world->initialize();
            
            // 플레이어 생성
            auto player = std::make_unique<Player>("Hero", Vector2D(400, 300));
            world->setPlayer(std::move(player));
            
            // 초기 적과 아이템 생성
            for (int i = 0; i < 3; ++i) {
                world->spawnEnemy();
                world->spawnItem();
            }
            
            running = true;
            lastFrameTime = std::chrono::high_resolution_clock::now();
            
            std::cout << "게임 초기화 완료!" << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "게임 초기화 실패: " << e.what() << std::endl;
            throw;
        }
    }
    
    void Game::run() {
        if (!running) {
            throw std::runtime_error("게임이 초기화되지 않았습니다.");
        }
        
        std::cout << "\n=== 게임 시작 ===" << std::endl;
        
        int frameLimit = 60; // 시뮬레이션을 위한 프레임 제한
        int currentFrame = 0;
        
        try {
            while (running && currentFrame < frameLimit) {
                float deltaTime = calculateDeltaTime();
                
                handleInput();
                update(deltaTime);
                render();
                
                updateFPS(deltaTime);
                
                if (currentFrame % 10 == 0) { // 10프레임마다 출력
                    displayFPS();
                }
                
                // 시뮬레이션을 위한 자동 이벤트
                if (currentFrame % 15 == 0) {
                    world->spawnEnemy();
                }
                
                if (currentFrame % 20 == 0) {
                    world->spawnItem();
                }
                
                currentFrame++;
                
                // 게임 오버 확인
                if (world->getState() == GameState::GAME_OVER) {
                    std::cout << "\n게임 오버!" << std::endl;
                    break;
                }
            }
            
        } catch (const std::exception& e) {
            std::cout << "게임 실행 중 오류 발생: " << e.what() << std::endl;
        }
        
        std::cout << "\n게임 종료" << std::endl;
        world->displayStatistics();
    }
    
    void Game::shutdown() {
        std::cout << "\n=== 게임 엔진 종료 ===" << std::endl;
        
        try {
            world->cleanup();
            running = false;
            
            std::cout << "최종 평균 FPS: " << std::fixed << std::setprecision(1) << averageFPS << std::endl;
            std::cout << "총 렌더링된 프레임: " << frameCount << std::endl;
            std::cout << "게임 엔진 종료 완료" << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "게임 종료 중 오류 발생: " << e.what() << std::endl;
        }
    }
    
    void Game::handleInput() {
        // 시뮬레이션을 위한 자동 입력
        if (world->getPlayer()) {
            static int inputCounter = 0;
            float deltaTime = 0.016f; // 60 FPS 기준
            
            switch (inputCounter % 8) {
                case 0: case 1: world->getPlayer()->moveRight(deltaTime); break;
                case 2: case 3: world->getPlayer()->moveDown(deltaTime); break;
                case 4: case 5: world->getPlayer()->moveLeft(deltaTime); break;
                case 6: case 7: world->getPlayer()->moveUp(deltaTime); break;
            }
            inputCounter++;
        }
    }
    
    void Game::update(float deltaTime) {
        world->update(deltaTime);
    }
    
    void Game::render() {
        world->render();
    }
    
    float Game::calculateDeltaTime() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastFrameTime);
        lastFrameTime = currentTime;
        
        return duration.count() / 1000000.0f; // 초 단위로 변환
    }
    
    void Game::updateFPS(float deltaTime) {
        frameCount++;
        totalTime += deltaTime;
        
        if (totalTime > 0.0f) {
            averageFPS = frameCount / totalTime;
        }
    }
    
    void Game::displayFPS() const {
        std::cout << "FPS: " << std::fixed << std::setprecision(1) << averageFPS 
                  << " | 프레임: " << frameCount << std::endl;
    }
    
} // namespace GameEngine
```

### main.cpp
```cpp
/*
게임 엔진 메인 파일
*/

#include "GameEngine.h"
#include <iostream>

int main() {
    std::cout << "=== C++ 게임 엔진 종합 프로젝트 ===" << std::endl;
    
    try {
        // 게임 생성 및 초기화
        GameEngine::Game game;
        game.initialize();
        
        // 게임 실행
        game.run();
        
        // 게임 종료
        game.shutdown();
        
    } catch (const std::exception& e) {
        std::cout << "치명적 오류: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== 게임 엔진 프로젝트에서 사용된 C++ 개념들 ===" << std::endl;
    std::cout << "1. 객체지향 프로그래밍 (클래스, 상속, 다형성)" << std::endl;
    std::cout << "2. 예외 처리 (try-catch, 사용자 정의 예외)" << std::endl;
    std::cout << "3. 스마트 포인터 (unique_ptr, 자동 메모리 관리)" << std::endl;
    std::cout << "4. STL 컨테이너 (vector, map)" << std::endl;
    std::cout << "5. 알고리즘 (find_if, remove_if)" << std::endl;
    std::cout << "6. 템플릿 (EventSystem 클래스)" << std::endl;
    std::cout << "7. 람다 함수 (이벤트 리스너)" << std::endl;
    std::cout << "8. 함수 객체 (std::function)" << std::endl;
    std::cout << "9. 네임스페이스 (GameEngine)" << std::endl;
    std::cout << "10. RAII 패턴 (자원 관리)" << std::endl;
    std::cout << "11. 이동 의미론 (std::move)" << std::endl;
    std::cout << "12. 강력한 타입 시스템 (enum class)" << std::endl;
    std::cout << "13. 컴파일 타임 최적화" << std::endl;
    std::cout << "14. 모던 C++ 기능들" << std::endl;
    
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

이제 여러분은 실무에서 C++을 활용할 수 있는 견고한 기반을 갖추었습니다. 계속해서 더 깊이 있는 학습과 실제 프로젝트 경험을 통해 전문가 수준으로 발전해 나가시기 바랍니다!
