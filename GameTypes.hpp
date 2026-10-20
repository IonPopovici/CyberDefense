#pragma once

#include <vector>
#include <iosfwd>

constexpr int kMapWidth = 10;
constexpr int kMapHeight = 7;

struct Position {
    Position();
    Position(const Position& other);
    Position(int xValue, int yValue);
    Position& operator=(const Position& other);

    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    bool operator<(const Position& other) const;
    bool operator>(const Position& other) const;
    bool operator<=(const Position& other) const;
    bool operator>=(const Position& other) const;
    friend std::istream& operator>>(std::istream& in, Position& value);
    friend std::ostream& operator<<(std::ostream& out, const Position& value);

    int x{0};
    int y{0};

    bool isInsideMap() const;
    int distanceSquaredTo(const Position& other) const;
};

enum class TowerType {
    Basic,
    Fast,
    Heavy
};

struct Tower {
    Tower();
    Tower(const Tower& other);
    Tower(Position positionValue, TowerType typeValue, int damageValue, int rangeValue, int costValue);
    Tower& operator=(const Tower& other);

    bool operator==(const Tower& other) const;
    bool operator!=(const Tower& other) const;
    bool operator<(const Tower& other) const;
    bool operator>(const Tower& other) const;
    bool operator<=(const Tower& other) const;
    bool operator>=(const Tower& other) const;
    friend std::istream& operator>>(std::istream& in, Tower& value);
    friend std::ostream& operator<<(std::ostream& out, const Tower& value);

    Position position;
    TowerType type{TowerType::Basic};
    int damage{10};
    int range{2};
    int cost{50};

    static Tower create(TowerType type, Position position);
    bool isInRange(const Position& target) const;
    int shotsPerStep() const;
};

struct Enemy {
    Enemy();
    Enemy(const Enemy& other);
    Enemy(int healthValue, int speedValue, int rewardValue, int pathIndexValue);
    Enemy& operator=(const Enemy& other);

    bool operator==(const Enemy& other) const;
    bool operator!=(const Enemy& other) const;
    bool operator<(const Enemy& other) const;
    bool operator>(const Enemy& other) const;
    bool operator<=(const Enemy& other) const;
    bool operator>=(const Enemy& other) const;
    friend std::istream& operator>>(std::istream& in, Enemy& value);
    friend std::ostream& operator<<(std::ostream& out, const Enemy& value);

    int health{100};
    int speed{1};
    int reward{10};
    int pathIndex{0};

    static Enemy spawnForWave(int wave);
    bool isAlive() const;
    void advance();
    void applyDamage(int damage);
    bool hasReachedEnd(int lastPathIndex) const;
};

struct GameState {
    GameState();
    GameState(const GameState& other);
    GameState(int creditsValue, int baseHealthValue, int waveValue, std::vector<Position> pathValue, std::vector<Tower> towersValue, std::vector<Enemy> enemiesValue);
    GameState& operator=(const GameState& other);

    bool operator==(const GameState& other) const;
    bool operator!=(const GameState& other) const;
    bool operator<(const GameState& other) const;
    bool operator>(const GameState& other) const;
    bool operator<=(const GameState& other) const;
    bool operator>=(const GameState& other) const;
    friend std::istream& operator>>(std::istream& in, GameState& value);
    friend std::ostream& operator<<(std::ostream& out, const GameState& value);

    int credits{100};
    int baseHealth{10};
    int wave{1};
    std::vector<Position> path;
    std::vector<Tower> towers;
    std::vector<Enemy> enemies;

    bool isPositionOnPath(const Position& position) const;
    bool isPositionOccupied(const Position& position) const;
    bool canAfford(int cost) const;
    void spendCredits(int cost);
    void addCredits(int amount);
    bool isGameOver() const;
};
