# Chapter 06: 상속과 다형성 (예제 01~10)

## 1. 예제 01: 기본 상속 (01_basic_inheritance.cpp)

### 예제 정의
클래스 상속의 기본 개념을 학습합니다.

```cpp
/*
주제: 기본 상속 (Basic Inheritance)
정의: 기존 클래스의 기능을 확장하여 새로운 클래스를 만드는 기법
*/

#include <iostream>
#include <string>
using namespace std;

// 기본 클래스 (부모 클래스)
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "동물 생성: " << name << endl;
    }
    
    void eat() {
        cout << name << "이(가) 먹이를 먹습니다." << endl;
    }
    
    void sleep() {
        cout << name << "이(가) 잠을 잡니다." << endl;
    }
};

// 파생 클래스 (자식 클래스)
class Dog : public Animal {
public:
    Dog(string n, int a) : Animal(n, a) {
        cout << "개 생성: " << name << endl;
    }
    
    void bark() {
        cout << name << "이(가) 멍멍 짖습니다." << endl;
    }
};

int main() {
    Dog dog("바둑이", 3);
    
    dog.eat();    // 부모 클래스의 메서드
    dog.sleep();  // 부모 클래스의 메서드
    dog.bark();   // 자식 클래스의 메서드
    
    return 0;
}
```
---

## 2. 예제 02: 접근 지정자 (02_access_specifiers.cpp)

### 예제 정의
상속에서 public, protected, private 접근 지정자의 차이를 학습합니다.

```cpp
/*
주제: 접근 지정자 (Access Specifiers in Inheritance)
정의: 상속 시 멤버들의 접근 권한을 제어하는 키워드
*/

#include <iostream>
using namespace std;

class Base {
public:
    int publicVar;
protected:
    int protectedVar;
private:
    int privateVar;
    
public:
    Base() : publicVar(1), protectedVar(2), privateVar(3) {}
    
    void showBase() {
        cout << "Base - public: " << publicVar 
             << ", protected: " << protectedVar 
             << ", private: " << privateVar << endl;
    }
};

class Derived : public Base {
public:
    void showDerived() {
        cout << "Derived - public: " << publicVar << endl;      // OK
        cout << "Derived - protected: " << protectedVar << endl; // OK
        // cout << "Derived - private: " << privateVar << endl;  // 오류!
    }
    
    void setProtected(int value) {
        protectedVar = value;  // protected는 자식에서 접근 가능
    }
};

int main() {
    Derived d;
    d.publicVar = 10;        // OK: public 멤버
    // d.protectedVar = 20;  // 오류: protected는 외부에서 접근 불가
    
    d.showBase();
    d.showDerived();
    d.setProtected(99);
    d.showDerived();
    
    return 0;
}
```

---

## 3. 예제 03: 생성자/소멸자 호출 순서 (03_constructor_destructor_order.cpp)

### 예제 정의
상속에서 생성자와 소멸자의 호출 순서를 학습합니다.

```cpp
/*
주제: 생성자/소멸자 호출 순서
정의: 상속 관계에서 생성자는 부모→자식, 소멸자는 자식→부모 순으로 호출
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base 생성자" << endl;
    }
    
    ~Base() {
        cout << "Base 소멸자" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived 생성자" << endl;
    }
    
    ~Derived() {
        cout << "Derived 소멸자" << endl;
    }
};

class GrandChild : public Derived {
public:
    GrandChild() {
        cout << "GrandChild 생성자" << endl;
    }
    
    ~GrandChild() {
        cout << "GrandChild 소멸자" << endl;
    }
};

int main() {
    cout << "=== 객체 생성 ===" << endl;
    {
        GrandChild gc;
    } // 여기서 소멸
    cout << "=== 객체 소멸 완료 ===" << endl;
    
    return 0;
}
```

---

## 4. 예제 04: 함수 오버라이딩 (04_function_overriding.cpp)

### 예제 정의
자식 클래스에서 부모 클래스의 함수를 재정의하는 방법을 학습합니다.

```cpp
/*
주제: 함수 오버라이딩 (Function Overriding)
정의: 자식 클래스에서 부모 클래스의 함수를 재정의하는 것
*/

#include <iostream>
using namespace std;

class Shape {
protected:
    string name;
    
public:
    Shape(string n) : name(n) {}
    
    void display() {
        cout << "도형: " << name << endl;
    }
    
    double getArea() {
        cout << "기본 도형의 넓이" << endl;
        return 0;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("원"), radius(r) {}
    
    // 부모 클래스의 함수 오버라이딩
    double getArea() {
        cout << "원의 넓이 계산" << endl;
        return 3.14159 * radius * radius;
    }
    
    // 부모 함수 호출하기
    void showInfo() {
        Shape::display();  // 부모 클래스의 display() 호출
        cout << "반지름: " << radius << ", 넓이: " << getArea() << endl;
    }
};

int main() {
    Circle circle(5.0);
    
    circle.showInfo();
    
    // 부모 클래스 포인터로 자식 객체 참조
    Shape* shape = &circle;
    shape->display();     // 부모 클래스의 display()
    shape->getArea();     // 어떤 getArea()가 호출될까?
    
    return 0;
}
```

---

## 5. 예제 05: 가상 함수 기초 (05_virtual_function_basic.cpp)

### 예제 정의
가상 함수를 통한 동적 바인딩의 개념을 학습합니다.

```cpp
/*
주제: 가상 함수 기초 (Virtual Function Basics)
정의: 런타임에 실제 객체 타입에 따라 호출될 함수가 결정되는 함수
*/

#include <iostream>
using namespace std;

class Animal {
public:
    // 가상 함수
    virtual void makeSound() {
        cout << "동물이 소리를 냅니다." << endl;
    }
    
    // 일반 함수
    void move() {
        cout << "동물이 움직입니다." << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {  // override 키워드 사용 권장
        cout << "멍멍!" << endl;
    }
    
    void move() {
        cout << "개가 뛰어다닙니다." << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "야옹!" << endl;
    }
    
    void move() {
        cout << "고양이가 조용히 걷습니다." << endl;
    }
};

int main() {
    Dog dog;
    Cat cat;
    
    cout << "=== 직접 호출 ===" << endl;
    dog.makeSound();  // 멍멍!
    cat.makeSound();  // 야옹!
    
    cout << "\n=== 포인터로 호출 ===" << endl;
    Animal* animals[] = {&dog, &cat};
    
    for (Animal* animal : animals) {
        animal->makeSound();  // 가상 함수: 실제 타입의 함수 호출
        animal->move();       // 일반 함수: Animal의 함수 호출
    }
    
    return 0;
}
```

---

## 6. 예제 06: 가상 소멸자 (06_virtual_destructor.cpp)

### 예제 정의
가상 소멸자의 필요성과 사용법을 학습합니다.

```cpp
/*
주제: 가상 소멸자 (Virtual Destructor)
정의: 상속 관계에서 올바른 소멸자 호출을 보장하는 가상 소멸자
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base 생성자" << endl;
    }
    
    // 가상 소멸자 - 중요!
    virtual ~Base() {
        cout << "Base 소멸자" << endl;
    }
    
    virtual void display() {
        cout << "Base 클래스" << endl;
    }
};

class Derived : public Base {
private:
    int* data;
    
public:
    Derived() {
        data = new int[10];
        cout << "Derived 생성자 (메모리 할당)" << endl;
    }
    
    ~Derived() {
        delete[] data;
        cout << "Derived 소멸자 (메모리 해제)" << endl;
    }
    
    void display() override {
        cout << "Derived 클래스" << endl;
    }
};

int main() {
    cout << "=== 직접 객체 생성 ===" << endl;
    {
        Derived d;
        d.display();
    }
    
    cout << "\n=== 포인터를 통한 동적 할당 ===" << endl;
    {
        Base* ptr = new Derived();  // 업캐스팅
        ptr->display();             // 가상 함수
        virtual void onCollision(GameObject* other) {}
        
        // Getter/Setter
        Vector2D getPosition() const { return position; }
        void setPosition(const Vector2D& pos) { position = pos; }
        Vector2D getVelocity() const { return velocity; }
        void setVelocity(const Vector2D& vel) { velocity = vel; }
        bool isActive() const { return active; }
        void setActive(bool a) { active = a; }
        int getId() const { return id; }
        std::string getName() const { return name; }
    };
    
    // 플레이어 클래스
    class Player : public GameObject {
    private:
        int health;
        int score;
        
    public:
        Player(Vector2D pos = Vector2D(50, 50));
        
        void update(float deltaTime) override;
        void render() override;
        void onCollision(GameObject* other) override;
        
        void takeDamage(int damage);
        void addScore(int points);
        
        int getHealth() const { return health; }
        int getScore() const { return score; }
    };
    
    // 적 클래스
    class Enemy : public GameObject {
    private:
        int damage;
        float speed;
        
    public:
        Enemy(Vector2D pos, int dmg = 10);
        
        void update(float deltaTime) override;
        void render() override;
        void onCollision(GameObject* other) override;
        
        int getDamage() const { return damage; }
    };
    
    // 파워업 클래스
    class PowerUp : public GameObject {
    private:
        int healAmount;
        
    public:
        PowerUp(Vector2D pos, int heal = 20);
        
        void update(float deltaTime) override;
        void render() override;
        void onCollision(GameObject* other) override;
        
        int getHealAmount() const { return healAmount; }
    };
    
    // 게임 예외 클래스
    class GameException : public std::exception {
    private:
        std::string message;
        
    public:
        GameException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };
    
    // 게임 엔진 메인 클래스
    class Game {
    private:
        GameState currentState;
        std::vector<std::unique_ptr<GameObject>> gameObjects;
        std::unique_ptr<Player> player;
        
        // 게임 통계
        int enemiesDestroyed;
        float gameTime;
        bool gameRunning;
        
        // 프라이빗 헬퍼 함수들
        void updateGameObjects(float deltaTime);
        void renderGameObjects();
        void checkCollisions();
        void spawnEnemy();
        void spawnPowerUp();
        void cleanupInactiveObjects();
        
    public:
        Game();
        ~Game() = default;
        
        // 게임 생명주기
        void initialize();
        void run();
        void update(float deltaTime);
        void render();
        void shutdown();
        
        // 게임 상태 관리
        void setState(GameState state) { currentState = state; }
        GameState getState() const { return currentState; }
        
        // 게임 오브젝트 관리
        void addGameObject(std::unique_ptr<GameObject> obj);
        void removeGameObject(int id);
        
        // 입력 처리 (간단한 시뮬레이션)
        void processInput(char input);
        
        // 통계
        void displayStats();
        
        // 게임 로직
        void restartGame();
        bool isGameOver() const;
    };
    
    // 유틸리티 함수들
    namespace Utils {
        float randomFloat(float min, float max);
        int randomInt(int min, int max);
        bool checkCollision(const GameObject* obj1, const GameObject* obj2, float radius = 10.0f);
        std::string stateToString(GameState state);
    }
    
} // namespace GameEngine

#endif함수 호출
        delete ptr;                 // 가상 소멸자 덕분에 Derived 소멸자도 호출
    }
    
    return 0;
}
```

---

## 7. 예제 07: 순수 가상 함수 (07_pure_virtual_function.cpp)

### 예제 정의
순수 가상 함수의 개념과 사용법을 학습합니다.

```cpp
/*
주제: 순수 가상 함수 (Pure Virtual Function)
정의: 구현이 없는 가상 함수로, 자식 클래스에서 반드시 구현해야 함
*/

#include <iostream>
using namespace std;

// 추상 클래스 (순수 가상 함수를 가진 클래스)
class Shape {
protected:
    string name;
    
public:
    Shape(string n) : name(n) {}
    
    // 순수 가상 함수 (= 0으로 선언)
    virtual double getArea() = 0;
    virtual void draw() = 0;
    
    // 일반 함수는 구현 가능
    void displayName() {
        cout << "도형 이름: " << name << endl;
    }
    
    virtual ~Shape() {}  // 가상 소멸자
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("사각형"), width(w), height(h) {}
    
    // 순수 가상 함수 구현 (필수)
    double getArea() override {
        return width * height;
    }
    
    void draw() override {
        cout << "사각형을 그립니다 (" << width << "x" << height << ")" << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("원"), radius(r) {}
    
    double getArea() override {
        return 3.14159 * radius * radius;
    }
    
    void draw() override {
        cout << "원을 그립니다 (반지름: " << radius << ")" << endl;
    }
};

int main() {
    // Shape shape;  // 오류: 추상 클래스는 인스턴스화 불가
    
    Rectangle rect(4, 5);
    Circle circle(3);
    
    Shape* shapes[] = {&rect, &circle};
    
    for (Shape* shape : shapes) {
        shape->displayName();
        shape->draw();
        cout << "넓이: " << shape->getArea() << endl << endl;
    }
    
    return 0;
}
```

---

## 8. 예제 08: 추상 클래스 (08_abstract_class.cpp)

### 예제 정의
추상 클래스를 활용한 인터페이스 설계를 학습합니다.

```cpp
/*
주제: 추상 클래스 (Abstract Class)
정의: 하나 이상의 순수 가상 함수를 가진 클래스로, 인터페이스 역할
*/

#include <iostream>
#include <vector>
using namespace std;

// 추상 클래스 - 게임 캐릭터 인터페이스
class GameCharacter {
protected:
    string name;
    int health;
    
public:
    GameCharacter(string n, int h) : name(n), health(h) {}
    
    // 순수 가상 함수들 (인터페이스)
    virtual void attack() = 0;
    virtual void defend() = 0;
    virtual void useSkill() = 0;
    
    // 공통 기능
    void takeDamage(int damage) {
        health -= damage;
        cout << name << "이(가) " << damage << " 피해를 받았습니다. (체력: " << health << ")" << endl;
    }
    
    bool isAlive() { return health > 0; }
    virtual ~GameCharacter() {}
};

class Warrior : public GameCharacter {
public:
    Warrior(string n) : GameCharacter(n, 100) {}
    
    void attack() override {
        cout << name << " 전사가 검으로 공격합니다!" << endl;
    }
    
    void defend() override {
        cout << name << " 전사가 방패로 방어합니다!" << endl;
    }
    
    void useSkill() override {
        cout << name << " 전사가 강력한 베기를 사용합니다!" << endl;
    }
};

class Mage : public GameCharacter {
public:
    Mage(string n) : GameCharacter(n, 80) {}
    
    void attack() override {
        cout << name << " 마법사가 파이어볼을 시전합니다!" << endl;
    }
    
    void defend() override {
        cout << name << " 마법사가 마법 보호막을 생성합니다!" << endl;
    }
    
    void useSkill() override {
        cout << name << " 마법사가 번개 마법을 사용합니다!" << endl;
    }
};

int main() {
    vector<GameCharacter*> party;
    party.push_back(new Warrior("김전사"));
    party.push_back(new Mage("이마법사"));
    
    // 다형성을 활용한 일괄 처리
    for (GameCharacter* character : party) {
        character->attack();
        character->defend();
        character->useSkill();
        character->takeDamage(20);
        cout << endl;
    }
    
    // 메모리 해제
    for (GameCharacter* character : party) {
        delete character;
    }
    
    return 0;
}
```

---

## 9. 예제 09: 다형성과 동적 바인딩 (09_polymorphism_dynamic_binding.cpp)

### 예제 정의
다형성을 활용한 유연한 프로그램 설계를 학습합니다.

```cpp
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
```

---

## 10. 예제 10: 상속 종합 프로젝트 (파일 분리)

### Shape.h
```cpp
/*
주제: 상속 종합 프로젝트 - 도형 관리 시스템 (헤더 파일)
정의: 상속, 가상 함수, 다형성을 모두 활용한 실용적인 예제
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// 추상 기본 클래스
class Shape {
protected:
    string name;
    string color;
    static int totalShapes;
    
public:
    Shape(string n, string c);
    virtual ~Shape();
    
    // 순수 가상 함수
    virtual double getArea() = 0;
    virtual double getPerimeter() = 0;
    virtual void draw() = 0;
    
    // 공통 기능
    virtual void displayInfo();
    string getName() const { return name; }
    static int getTotalShapes() { return totalShapes; }
};

// 원 클래스
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r, string c = "빨간색");
    
    double getArea() override;
    double getPerimeter() override;
    void draw() override;
};

// 사각형 클래스
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h, string c = "파란색");
    
    double getArea() override;
    double getPerimeter() override;
    void draw() override;
};

// 도형 관리자 클래스
class ShapeManager {
private:
    vector<unique_ptr<Shape>> shapes;
    
public:
    void addShape(unique_ptr<Shape> shape);
    void displayAllShapes();
    double getTotalArea();
    void clearShapes();
    ~ShapeManager();
};

#endif
```

### GameEngine.cpp
```cpp
/*
구현 파일 - 게임 엔진
*/

#include "GameEngine.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace GameEngine {
    
    // GameObject 클래스 구현
    int GameObject::nextId = 1;
    
    GameObject::GameObject(const std::string& n, Vector2D pos) 
        : name(n), position(pos), velocity(0, 0), active(true), id(nextId++) {}
    
    // Player 클래스 구현
    Player::Player(Vector2D pos) : GameObject("Player", pos), health(100), score(0) {}
    
    void Player::update(float deltaTime) {
        // 플레이어 위치 업데이트
        position += velocity;
        
        // 화면 경계 처리 (간단한 래핑)
        if (position.x < 0) position.x = 100;
        if (position.x > 100) position.x = 0;
        if (position.y < 0) position.y = 100;
        if (position.y > 100) position.y = 0;
    }
    
    void Player::render() {
        std::cout << "P(" << static_cast<int>(position.x) << "," << static_cast<int>(position.y) << ") ";
    }
    
    void Player::onCollision(GameObject* other) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(other)) {
            takeDamage(enemy->getDamage());
        } else if (PowerUp* powerUp = dynamic_cast<PowerUp*>(other)) {
            health = std::min(100, health + powerUp->getHealAmount());
            addScore(50);
            other->setActive(false);
        }
    }
    
    void Player::takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << "플레이어 피해! 체력: " << health << std::endl;
    }
    
    void Player::addScore(int points) {
        score += points;
    }
    
    // Enemy 클래스 구현
    Enemy::Enemy(Vector2D pos, int dmg) 
        : GameObject("Enemy", pos), damage(dmg), speed(1.0f) {
        // 플레이어를 향한 간단한 AI 속도 설정
        velocity = Vector2D(Utils::randomFloat(-speed, speed), Utils::randomFloat(-speed, speed));
    }
    
    void Enemy::update(float deltaTime) {
        position += velocity;
        
        // 화면 밖으로 나가면 비활성화
        if (position.x < -10 || position.x > 110 || position.y < -10 || position.y > 110) {
            active = false;
        }
    }
    
    void Enemy::render() {
        std::cout << "E(" << static_cast<int>(position.x) << "," << static_cast<int>(position.y) << ") ";
    }
    
    void Enemy::onCollision(GameObject* other) {
        if (dynamic_cast<Player*>(other)) {
            active = false;  // 플레이어와 충돌하면 사라짐
        }
    }
    
    // PowerUp 클래스 구현
    PowerUp::PowerUp(Vector2D pos, int heal) 
        : GameObject("PowerUp", pos), healAmount(heal) {}
    
    void PowerUp::update(float deltaTime) {
        // 파워업은 정적
    }
    
    void PowerUp::render() {
        std::cout << "H(" << static_cast<int>(position.x) << "," << static_cast<int>(position.y) << ") ";
    }
    
    void PowerUp::onCollision(GameObject* other) {
        // Player::onCollision에서 처리
    }
    
    // Game 클래스 구현
    Game::Game() : currentState(GameState::MENU), enemiesDestroyed(0), gameTime(0), gameRunning(false) {
        srand(static_cast<unsigned>(time(nullptr)));
    }
    
    void Game::initialize() {
        std::cout << "=== 게임 엔진 초기화 ===" << std::endl;
        
        player = std::make_unique<Player>(Vector2D(50, 50));
        gameObjects.clear();
        
        // 초기 오브젝트 생성
        spawnEnemy();
        spawnPowerUp();
        
        currentState = GameState::PLAYING;
        gameRunning = true;
        gameTime = 0;
        enemiesDestroyed = 0;
        
        std::cout << "게임 시작!" << std::endl;
    }
    
    void Game::run() {
        initialize();
        
        // 간단한 게임 루프 시뮬레이션
        float deltaTime = 1.0f;
        int gameSteps = 0;
        
        while (gameRunning && gameSteps < 10) {  // 10스텝만 실행
            update(deltaTime);
            render();
            
            // 자동 입력 시뮬레이션
            char inputs[] = {'w', 'd', 's', 'a', 'x'};
            processInput(inputs[gameSteps % 5]);
            
            gameSteps++;
            
            if (isGameOver()) {
                currentState = GameState::GAME_OVER;
                break;
            }
            
            std::cout << "\n--- 다음 프레임 ---" << std::endl;
        }
        
        displayStats();
        shutdown();
    }
    
    void Game::update(float deltaTime) {
        if (currentState != GameState::PLAYING) return;
        
        gameTime += deltaTime;
        
        // 플레이어 업데이트
        if (player) {
            player->update(deltaTime);
        }
        
        // 게임 오브젝트 업데이트
        updateGameObjects(deltaTime);
        
        // 충돌 검사
        checkCollisions();
        
        // 비활성 오브젝트 정리
        cleanupInactiveObjects();
        
        // 새로운 적 생성 (확률적)
        if (Utils::randomInt(1, 100) > 70) {
            spawnEnemy();
        }
        
        // 새로운 파워업 생성 (확률적)
        if (Utils::randomInt(1, 100) > 90) {
            spawnPowerUp();
        }
    }
    
    void Game::render() {
        std::cout << "\n=== 게임 화면 (시간: " << static_cast<int>(gameTime) << "s) ===" << std::endl;
        std::cout << "체력: " << player->getHealth() << " | 점수: " << player->getScore() << std::endl;
        
        std::cout << "오브젝트: ";
        if (player) {
            player->render();
        }
        
        renderGameObjects();
        std::cout << std::endl;
    }
    
    void Game::processInput(char input) {
        if (currentState != GameState::PLAYING) return;
        
        Vector2D newVelocity(0, 0);
        
        switch (input) {
            case 'w': newVelocity = Vector2D(0, -2); break;
            case 's': newVelocity = Vector2D(0, 2); break;
            case 'a': newVelocity = Vector2D(-2, 0); break;
            case 'd': newVelocity = Vector2D(2, 0); break;
            case 'x': newVelocity = Vector2D(0, 0); break;  // 정지
            case 'q': gameRunning = false; break;
        }
        
        if (player) {
            player->setVelocity(newVelocity);
        }
        
        std::cout << "입력: " << input << " -> 속도: (" 
                  << newVelocity.x << ", " << newVelocity.y << ")" << std::endl;
    }
    
    void Game::updateGameObjects(float deltaTime) {
        for (auto& obj : gameObjects) {
            if (obj->isActive()) {
                obj->update(deltaTime);
            }
        }
    }
    
    void Game::renderGameObjects() {
        for (const auto& obj : gameObjects) {
            if (obj->isActive()) {
                obj->render();
            }
        }
    }
    
    void Game::checkCollisions() {
        if (!player || !player->isActive()) return;
        
        for (auto& obj : gameObjects) {
            if (obj->isActive() && Utils::checkCollision(player.get(), obj.get())) {
                player->onCollision(obj.get());
                obj->onCollision(player.get());
            }
        }
    }
    
    void Game::spawnEnemy() {
        Vector2D pos(Utils::randomFloat(0, 100), Utils::randomFloat(0, 100));
        addGameObject(std::make_unique<Enemy>(pos));
    }
    
    void Game::spawnPowerUp() {
        Vector2D pos(Utils::randomFloat(20, 80), Utils::randomFloat(20, 80));
        addGameObject(std::make_unique<PowerUp>(pos));
    }
    
    void Game::cleanupInactiveObjects() {
        auto it = std::remove_if(gameObjects.begin(), gameObjects.end(),
            [this](const std::unique_ptr<GameObject>& obj) {
                if (!obj->isActive() && dynamic_cast<Enemy*>(obj.get())) {
                    enemiesDestroyed++;
                }
                return !obj->isActive();
            });
        gameObjects.erase(it, gameObjects.end());
    }
    
    void Game::addGameObject(std::unique_ptr<GameObject> obj) {
        gameObjects.push_back(std::move(obj));
    }
    
    void Game::removeGameObject(int id) {
        auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
            [id](const std::unique_ptr<GameObject>& obj) {
                return obj->getId() == id;
            });
        if (it != gameObjects.end()) {
            gameObjects.erase(it);
        }
    }
    
    bool Game::isGameOver() const {
        return player && player->getHealth() <= 0;
    }
    
    void Game::displayStats() {
        std::cout << "\n=== 게임 통계 ===" << std::endl;
        std::cout << "게임 시간: " << static_cast<int>(gameTime) << "초" << std::endl;
        std::cout << "최종 점수: " << (player ? player->getScore() : 0) << std::endl;
        std::cout << "처치한 적: " << enemiesDestroyed << std::endl;
        std::cout << "게임 상태: " << Utils::stateToString(currentState) << std::endl;
    }
    
    void Game::shutdown() {
        std::cout << "\n게임 종료" << std::endl;
        gameObjects.clear();
        player.reset();
    }
    
    void Game::restartGame() {
        shutdown();
        initialize();
    }
    
    // Utils 네임스페이스 구현
    namespace Utils {
        float randomFloat(float min, float max) {
            return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));
        }
        
        int randomInt(int min, int max) {
            return min + rand() % (max - min + 1);
        }
        
        bool checkCollision(const GameObject* obj1, const GameObject* obj2, float radius) {
            if (!obj1 || !obj2) return false;
            return obj1->getPosition().distance(obj2->getPosition()) < radius;
        }
        
        std::string stateToString(GameState state) {
            switch (state) {
                case GameState::MENU: return "메뉴";
                case GameState::PLAYING: return "플레이 중";
                case GameState::PAUSED: return "일시정지";
                case GameState::GAME_OVER: return "게임 오버";
                default: return "알 수 없음";
            }
        }
    }
    
} // namespace GameEngine
```

### main.cpp
```cpp
/*
메인 파일 - 게임 엔진 데모
*/

#include "GameEngine.h"

// 게임 엔진 기능 테스트
void demonstrateGameEngine() {
    using namespace GameEngine;
    
    std::cout << "=== 게임 엔진 종합 프로젝트 ===" << std::endl;
    
    try {
        Game game;
        
        std::cout << "\n1. 게임 초기화 및 실행" << std::endl;
        game.run();
        
        std::cout << "\n2. 개별 기능 테스트" << std::endl;
        
        // Vector2D 테스트
        Vector2D pos1(10, 20);
        Vector2D pos2(30, 40);
        Vector2D result = pos1 + pos2;
        std::cout << "벡터 연산: (" << pos1.x << "," << pos1.y << ") + (" 
                  << pos2.x << "," << pos2.y << ") = (" 
                  << result.x << "," << result.y << ")" << std::endl;
        
        // 거리 계산
        float dist = pos1.distance(pos2);
        std::cout << "거리: " << dist << std::endl;
        
        // 게임 오브젝트 다형성 테스트
        std::cout << "\n3. 다형성 테스트" << std::endl;
        std::vector<std::unique_ptr<GameObject>> objects;
        
        objects.push_back(std::make_unique<Player>(Vector2D(0, 0)));
        objects.push_back(std::make_unique<Enemy>(Vector2D(10, 10)));
        objects.push_back(std::make_unique<PowerUp>(Vector2D(20, 20)));
        
        std::cout << "다양한 게임 오브젝트 렌더링:" << std::endl;
        for (auto& obj : objects) {
            obj->render();
        }
        std::cout << std::endl;
        
    } catch (const GameException& e) {
        std::cout << "게임 오류: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "시스템 오류: " << e.what() << std::endl;
    }
}

// 사용된 C++ 개념들 정리
void summarizeConcepts() {
    std::cout << "\n=== 사용된 C++ 개념들 ===" << std::endl;
    
    std::cout << "\nChapter 06 - 상속과 다형성:" << std::endl;
    std::cout << "• GameObject 추상 클래스와 상속" << std::endl;
    std::cout << "• 가상 함수와 오버라이딩" << std::endl;
    std::cout << "• 다형성을 통한 게임 오브젝트 관리" << std::endl;
    std::cout << "• dynamic_cast를 통한 타입 확인" << std::endl;
    
    std::cout << "\nChapter 07 - 템플릿과 STL:" << std::endl;
    std::cout << "• std::vector로 게임 오브젝트 컨테이너" << std::endl;
    std::cout << "• std::unique_ptr로 스마트 포인터 활용" << std::endl;
    std::cout << "• STL 알고리즘 (find_if, remove_if)" << std::endl;
    std::cout << "• auto 키워드로 타입 추론" << std::endl;
    
    std::cout << "\nChapter 08 - 예외 처리와 프로젝트:" << std::endl;
    std::cout << "• 사용자 정의 예외 클래스 (GameException)" << std::endl;
    std::cout, "• try-catch를 통한 안전한 오류 처리" << std::endl;
    std::cout << "• RAII 패턴으로 자원 관리" << std::endl;
    std::cout << "• 프로젝트를 헤더/구현 파일로 구조화" << std::endl;
    
    std::cout << "\n통합된 개념들:" << std::endl;
    std::cout << "• 연산자 오버로딩 (Vector2D)" << std::endl;
    std::cout << "• 네임스페이스로 모듈화" << std::endl;
    std::cout << "• const 정확성과 메모리 안전성" << std::endl;
    std::cout << "• 모던 C++ 기법들 (스마트 포인터, 이동 의미론)" << std::endl;
}

int main() {
    demonstrateGameEngine();
    summarizeConcepts();
    
    std::cout << "\n=== 전체 C++ 커리큘럼 완료! ===" << std::endl;
    std::cout << "8개 챕터를 통해 C++의 핵심 개념들을 모두 학습했습니다." << std::endl;
    std::cout << "이제 실무에서 C++을 활용할 준비가 되었습니다!" << std::endl;
    
    return 0;
}
```cpp
/*
구현 파일
*/

#include "Shape.h"

// 정적 멤버 초기화
int Shape::totalShapes = 0;

// Shape 클래스 구현
Shape::Shape(string n, string c) : name(n), color(c) {
    totalShapes++;
}

Shape::~Shape() {
    totalShapes--;
}

void Shape::displayInfo() {
    cout << name << " (색상: " << color << ")" << endl;
    cout << "넓이: " << getArea() << ", 둘레: " << getPerimeter() << endl;
}

// Circle 클래스 구현
Circle::Circle(double r, string c) : Shape("원", c), radius(r) {}

double Circle::getArea() {
    return 3.14159 * radius * radius;
}

double Circle::getPerimeter() {
    return 2 * 3.14159 * radius;
}

void Circle::draw() {
    cout << "반지름 " << radius << "인 " << color << " 원을 그립니다." << endl;
}

// Rectangle 클래스 구현
Rectangle::Rectangle(double w, double h, string c) 
    : Shape("사각형", c), width(w), height(h) {}

double Rectangle::getArea() {
    return width * height;
}

double Rectangle::getPerimeter() {
    return 2 * (width + height);
}

void Rectangle::draw() {
    cout << width << "x" << height << " " << color << " 사각형을 그립니다." << endl;
}

// ShapeManager 클래스 구현
void ShapeManager::addShape(unique_ptr<Shape> shape) {
    shapes.push_back(move(shape));
}

void ShapeManager::displayAllShapes() {
    cout << "\n=== 모든 도형 정보 ===" << endl;
    for (auto& shape : shapes) {
        shape->displayInfo();
        shape->draw();
        cout << endl;
    }
}

double ShapeManager::getTotalArea() {
    double total = 0;
    for (auto& shape : shapes) {
        total += shape->getArea();
    }
    return total;
}

void ShapeManager::clearShapes() {
    shapes.clear();
}

ShapeManager::~ShapeManager() {
    clearShapes();
}
```

### main.cpp
```cpp
/*
메인 파일
*/

#include "Shape.h"

int main() {
    cout << "=== 상속과 다형성 종합 프로젝트 ===" << endl;
    
    ShapeManager manager;
    
    // 다양한 도형 생성 및 추가
    manager.addShape(make_unique<Circle>(5.0, "빨간색"));
    manager.addShape(make_unique<Rectangle>(4.0, 6.0, "파란색"));
    manager.addShape(make_unique<Circle>(3.0, "초록색"));
    manager.addShape(make_unique<Rectangle>(2.0, 8.0, "노란색"));
    
    // 모든 도형 정보 출력
    manager.displayAllShapes();
    
    // 통계 정보
    cout << "=== 통계 정보 ===" << endl;
    cout << "총 도형 개수: " << Shape::getTotalShapes() << endl;
    cout << "총 넓이: " << manager.getTotalArea() << endl;
    
    return 0;
}
```
