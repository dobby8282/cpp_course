/*
 * 파일 I/O와 예외
 * 파일명: 06_file_io_exception.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 06_file_io_exception 06_file_io_exception.cpp
 * 실행: ./06_file_io_exception (Linux/Mac) 또는 06_file_io_exception.exe (Windows)
 */

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