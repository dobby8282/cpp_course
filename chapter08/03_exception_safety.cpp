/*
 * 예외 안전성
 * 파일명: 03_exception_safety.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 03_exception_safety 03_exception_safety.cpp
 * 실행: ./03_exception_safety (Linux/Mac) 또는 03_exception_safety.exe (Windows)
 */

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