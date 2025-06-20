/*
 * RAII와 예외
 * 파일명: 04_raii_exception.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 04_raii_exception 04_raii_exception.cpp
 * 실행: ./04_raii_exception (Linux/Mac) 또는 04_raii_exception.exe (Windows)
 */

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