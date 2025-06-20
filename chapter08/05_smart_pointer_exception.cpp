/*
 * 스마트 포인터와 예외
 * 파일명: 05_smart_pointer_exception.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 05_smart_pointer_exception 05_smart_pointer_exception.cpp
 * 실행: ./05_smart_pointer_exception (Linux/Mac) 또는 05_smart_pointer_exception.exe (Windows)
 */

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