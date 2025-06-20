/*
 * 종합 프로젝트 - 게임 엔진
 * 파일명: 10_game_engine.cpp
 * 
 * 컴파일: g++ -std=c++17 -o 10_game_engine 10_game_engine.cpp
 * 실행: ./10_game_engine (Linux/Mac) 또는 10_game_engine.exe (Windows)
 */

/*
주제: 종합 프로젝트 - 간단한 게임 엔진 (헤더 파일)
정의: 모든 C++ 개념을 통합한 실용적인 게임 엔진
*/

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <random>
#include <functional>

namespace GameEngine {

    // 게임 상태 열거형
    enum class GameState {
        MENU,
        PLAYING,
        PAUSED,
        GAME_OVER
    };

    // 2D 벡터 클래스
    struct Vector2D {
        float x, y;

        Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

        Vector2D operator+(const Vector2D& other) const {
            return Vector2D(x + other.x, y + other.y);
        }

        Vector2D& operator+=(const Vector2D& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2D operator*(float scalar) const {
            return Vector2D(x * scalar, y * scalar);
        }

        float distance(const Vector2D& other) const {
            float dx = x - other.x;
            float dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }

        void normalize() {
            float magnitude = sqrt(x * x + y * y);
            if (magnitude > 0) {
                x /= magnitude;
                y /= magnitude;
            }
        }
    };

    // 게임 예외 클래스들
    class GameException : public std::exception {
    protected:
        std::string message;
    public:
        explicit GameException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };

    class InvalidPositionException : public GameException {
    public:
        InvalidPositionException(float x, float y) 
            : GameException("잘못된 위치: (" + std::to_string(x) + ", " + std::to_string(y) + ")") {}
    };

    class GameObjectNotFoundException : public GameException {
    public:
        GameObjectNotFoundException(const std::string& name) 
            : GameException("게임 오브젝트를 찾을 수 없음: " + name) {}
    };

    // 이벤트 시스템
    template<typename T>
    class EventSystem {
    private:
        std::vector<std::function<void(const T&)>> listeners;

    public:
        void addListener(std::function<void(const T&)> listener) {
            listeners.push_back(listener);
        }

        void broadcast(const T& event) {
            for (auto& listener : listeners) {
                try {
                    listener(event);
                } catch (const std::exception& e) {
                    std::cout << "이벤트 처리 오류: " << e.what() << std::endl;
                }
            }
        }
    };

    // 게임 이벤트 타입들
    struct CollisionEvent {
        std::string object1, object2;
        Vector2D position;
    };

    struct ScoreEvent {
        int score;
        std::string playerName;
    };

    // 게임 객체 기본 클래스 (추상 클래스)
    class GameObject {
    protected:
        Vector2D position;
        Vector2D velocity;
        std::string name;
        bool active;
        static int nextId;
        int id;

    public:
        GameObject(const std::string& n, Vector2D pos = Vector2D());
        virtual ~GameObject() = default;

        // 순수 가상 함수
        virtual void update(float deltaTime) = 0;
        virtual void render() const = 0;

        // 가상 함수
        virtual void onCollision(GameObject* other) {}
        virtual void onDestroy() {}

        // Getter/Setter
        const Vector2D& getPosition() const { return position; }
        const Vector2D& getVelocity() const { return velocity; }
        const std::string& getName() const { return name; }
        int getId() const { return id; }
        bool isActive() const { return active; }

        void setPosition(const Vector2D& pos) { position = pos; }
        void setVelocity(const Vector2D& vel) { velocity = vel; }
        void setActive(bool isActive) { active = isActive; }

        // 충돌 검사
        virtual bool checkCollision(const GameObject* other) const;

        // 이동
        void move(const Vector2D& direction, float speed, float deltaTime);
    };

    // 플레이어 클래스
    class Player : public GameObject {
    private:
        int health;
        int score;
        float speed;

    public:
        Player(const std::string& name, Vector2D pos = Vector2D(0, 0));

        void update(float deltaTime) override;
        void render() const override;
        void onCollision(GameObject* other) override;

        // 플레이어 전용 메서드
        void takeDamage(int damage);
        void addScore(int points);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);
        void moveLeft(float deltaTime);
        void moveRight(float deltaTime);

        // Getter
        int getHealth() const { return health; }
        int getScore() const { return score; }
        float getSpeed() const { return speed; }
    };

    // 적 클래스
    class Enemy : public GameObject {
    private:
        int damage;
        float speed;
        Vector2D targetPosition;

    public:
        Enemy(const std::string& name, Vector2D pos = Vector2D(0, 0));

        void update(float deltaTime) override;
        void render() const override;
        void onCollision(GameObject* other) override;

        void setTarget(const Vector2D& target) { targetPosition = target; }
        int getDamage() const { return damage; }
    };

    // 아이템 클래스
    class Item : public GameObject {
    private:
        int value;
        std::string itemType;

    public:
        Item(const std::string& name, const std::string& type, int val, Vector2D pos = Vector2D(0, 0));

        void update(float deltaTime) override;
        void render() const override;
        void onCollision(GameObject* other) override;

        int getValue() const { return value; }
        const std::string& getType() const { return itemType; }
    };

    // 게임 월드 관리자
    class GameWorld {
    private:
        std::vector<std::unique_ptr<GameObject>> gameObjects;
        std::unique_ptr<Player> player;
        GameState currentState;
        float worldWidth, worldHeight;

        // 이벤트 시스템
        EventSystem<CollisionEvent> collisionEvents;
        EventSystem<ScoreEvent> scoreEvents;

        // 랜덤 생성기
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> posDist;

    public:
        GameWorld(float width = 800, float height = 600);
        ~GameWorld() = default;

        // 게임 오브젝트 관리
        void addGameObject(std::unique_ptr<GameObject> obj);
        void removeGameObject(const std::string& name);
        GameObject* findGameObject(const std::string& name);

        // 플레이어 관리
        void setPlayer(std::unique_ptr<Player> p);
        Player* getPlayer() const { return player.get(); }

        // 게임 루프
        void update(float deltaTime);
        void render() const;

        // 충돌 검사
        void checkCollisions();

        // 게임 상태 관리
        void setState(GameState state) { currentState = state; }
        GameState getState() const { return currentState; }

        // 월드 경계 검사
        bool isInBounds(const Vector2D& position) const;
        void clampToBounds(Vector2D& position) const;

        // 적과 아이템 생성
        void spawnEnemy();
        void spawnItem();

        // 이벤트 리스너 등록
        void addCollisionListener(std::function<void(const CollisionEvent&)> listener);
        void addScoreListener(std::function<void(const ScoreEvent&)> listener);

        // 게임 통계
        void displayStatistics() const;

        // 게임 초기화 및 정리
        void initialize();
        void cleanup();
    };

    // 게임 엔진 메인 클래스
    class Game {
    private:
        std::unique_ptr<GameWorld> world;
        bool running;
        std::chrono::high_resolution_clock::time_point lastFrameTime;

        // 성능 측정
        int frameCount;
        float totalTime;
        float averageFPS;

    public:
        Game();
        ~Game() = default;

        // 게임 생명주기
        void initialize();
        void run();
        void shutdown();

        // 게임 루프 구성요소
        void handleInput();
        void update(float deltaTime);
        void render();

        // 유틸리티
        float calculateDeltaTime();
        void updateFPS(float deltaTime);
        void displayFPS() const;

        bool isRunning() const { return running; }
        void stop() { running = false; }
    };

} // namespace GameEngine

#endif