/*
 * 사용자 정의 예외
 * 파일명: 02_custom_exception.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 02_custom_exception 02_custom_exception.cpp
 * 실행: ./02_custom_exception (Linux/Mac) 또는 02_custom_exception.exe (Windows)
 */

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