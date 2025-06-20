/*
 * 가상 소멸자
 * 파일명: 06_virtual_destructor.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 06_virtual_destructor 06_virtual_destructor.cpp
 * 실행: ./06_virtual_destructor (Linux/Mac) 또는 06_virtual_destructor.exe (Windows)
 */

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