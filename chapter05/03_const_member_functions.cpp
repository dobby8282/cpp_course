/*
 * const 멤버 함수
 * 파일명: 03_const_member_functions.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 03_const_member_functions 03_const_member_functions.cpp
 * 실행: ./03_const_member_functions (Linux/Mac) 또는 03_const_member_functions.exe (Windows)
 */

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