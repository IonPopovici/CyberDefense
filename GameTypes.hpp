#pragma once

#include <vector>

constexpr int kMapWidth = 10;
constexpr int kMapHeight = 7;

struct Position {
    int x{0};
    int y{0};

    bool operator==(const Position& other) const;
    bool isInsideMap() const;
    int distanceSquaredTo(const Position& other) const;
};

enum class TowerType {
    Basic,
    Fast,
    Heavy
};

struct Tower {
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
