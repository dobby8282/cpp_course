/*
 * 디버깅과 로깅
 * 파일명: 07_debugging_logging.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 07_debugging_logging 07_debugging_logging.cpp
 * 실행: ./07_debugging_logging (Linux/Mac) 또는 07_debugging_logging.exe (Windows)
 */

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