/*
 * 다형성과 동적 바인딩
 * 파일명: 09_polymorphism_dynamic_binding.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 09_polymorphism_dynamic_binding 09_polymorphism_dynamic_binding.cpp
 * 실행: ./09_polymorphism_dynamic_binding (Linux/Mac) 또는 09_polymorphism_dynamic_binding.exe (Windows)
 */

/*
주제: 다형성과 동적 바인딩 (Polymorphism & Dynamic Binding)
정의: 하나의 인터페이스로 다양한 타입의 객체를 처리하는 능력
*/

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Vehicle {
protected:
    string brand;

public:
    Vehicle(string b) : brand(b) {}
    virtual ~Vehicle() {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void getInfo() {
        cout << "브랜드: " << brand << endl;
    }
};

class Car : public Vehicle {
public:
    Car(string b) : Vehicle(b) {}

    void start() override {
        cout << brand << " 자동차 시동을 켭니다. 부릉부릉!" << endl;
    }

    void stop() override {
        cout << brand << " 자동차를 정지합니다." << endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(string b) : Vehicle(b) {}

    void start() override {
        cout << brand << " 오토바이 시동을 켭니다. 붕붕!" << endl;
    }

    void stop() override {
        cout << brand << " 오토바이를 정지합니다." << endl;
    }
};

// 다형성을 활용한 함수
void driveVehicle(Vehicle* vehicle) {
    vehicle->getInfo();
    vehicle->start();
    cout << "운전 중..." << endl;
    vehicle->stop();
    cout << endl;
}

int main() {
    // 스마트 포인터로 다형성 활용
    vector<unique_ptr<Vehicle>> garage;
    garage.push_back(make_unique<Car>("현대"));
    garage.push_back(make_unique<Motorcycle>("혼다"));
    garage.push_back(make_unique<Car>("BMW"));

    cout << "=== 차고의 모든 차량 운전 ===" << endl;
    for (auto& vehicle : garage) {
        driveVehicle(vehicle.get());
    }

    return 0;
}