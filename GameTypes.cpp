#include "GameTypes.hpp"

// ----- Position -----

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

bool Position::isInsideMap() const {
    return x >= 0 && x < kMapWidth && y >= 0 && y < kMapHeight;
}

int Position::distanceSquaredTo(const Position& other) const {
    const int dx = x - other.x;
    const int dy = y - other.y;
    return dx * dx + dy * dy;
}

// ----- Tower -----

Tower Tower::create(TowerType type, Position position) {
    Tower tower;
    tower.position = position;
    tower.type = type;

    switch (type) {
    case TowerType::Basic:
        tower.damage = 10;
        tower.range = 2;
        tower.cost = 50;
        break;
    case TowerType::Fast:
        tower.damage = 6;
        tower.range = 2;
        tower.cost = 60;
        break;
    case TowerType::Heavy:
        tower.damage = 30;
        tower.range = 3;
        tower.cost = 120;
        break;
    }
    return tower;
}

bool Tower::isInRange(const Position& target) const {
    return position.distanceSquaredTo(target) <= range * range;
}

int Tower::shotsPerStep() const {
    return (type == TowerType::Fast) ? 2 : 1;
}

// ----- Enemy -----

Enemy Enemy::spawnForWave(int wave) {
    Enemy enemy;
    enemy.health = 30 + 10 * wave;
    enemy.reward = 20;
    return enemy;
}

bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::advance() {
    pathIndex += speed;
}

void Enemy::applyDamage(int damage) {
    health -= damage;
}

bool Enemy::hasReachedEnd(int lastPathIndex) const {
    return pathIndex >= lastPathIndex;
}

// ----- GameState -----

bool GameState::isPositionOnPath(const Position& position) const {
    for (const Position& p : path) {
        if (p == position) return true;
    }
    return false;
}

bool GameState::isPositionOccupied(const Position& position) const {
    for (const Tower& tower : towers) {
        if (tower.position == position) return true;
    }
    return false;
}

bool GameState::canAfford(int cost) const {
    return credits >= cost;
}

void GameState::spendCredits(int cost) {
    credits -= cost;
}

void GameState::addCredits(int amount) {
    credits += amount;
}

bool GameState::isGameOver() const {
    return baseHealth <= 0;
}
