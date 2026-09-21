#pragma once

#include <vector>

constexpr int kMapWidth = 10;
constexpr int kMapHeight = 7;

struct Position {
    int x{0};
    int y{0};

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
};

struct Enemy {
    int health{100};
    int speed{1};
    int reward{10};
    int pathIndex{0};
};

struct GameState {
    int credits{100};
    int baseHealth{10};
    int wave{1};
    std::vector<Position> path;
    std::vector<Tower> towers;
    std::vector<Enemy> enemies;
};
