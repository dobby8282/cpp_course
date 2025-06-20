/*
 * 추상 클래스
 * 파일명: 08_abstract_class.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 08_abstract_class 08_abstract_class.cpp
 * 실행: ./08_abstract_class (Linux/Mac) 또는 08_abstract_class.exe (Windows)
 */

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