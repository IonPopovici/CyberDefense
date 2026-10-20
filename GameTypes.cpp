#include "GameTypes.hpp"

#include <istream>
#include <ostream>
#include <tuple>
#include <utility>

// ----- Position -----



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

// Value semantics: compare all fields in declaration order.
Position::Position() = default;
Position::Position(const Position& other) = default;
Position::Position(int xValue, int yValue) : x(xValue), y(yValue) {}
Position& Position::operator=(const Position& other) = default;
bool Position::operator==(const Position& other) const {
    return std::tie(x, y) == std::tie(other.x, other.y);
}
bool Position::operator!=(const Position& other) const { return !(*this == other); }
bool Position::operator<(const Position& other) const {
    return std::tie(x, y) < std::tie(other.x, other.y);
}
bool Position::operator>(const Position& other) const { return other < *this; }
bool Position::operator<=(const Position& other) const { return !(other < *this); }
bool Position::operator>=(const Position& other) const { return !(*this < other); }
// Value semantics: compare all fields in declaration order.
Tower::Tower() = default;
Tower::Tower(const Tower& other) = default;
Tower::Tower(Position positionValue, TowerType typeValue, int damageValue, int rangeValue, int costValue) : position(positionValue), type(typeValue), damage(damageValue), range(rangeValue), cost(costValue) {}
Tower& Tower::operator=(const Tower& other) = default;
bool Tower::operator==(const Tower& other) const {
    return std::tie(position, type, damage, range, cost) == std::tie(other.position, other.type, other.damage, other.range, other.cost);
}
bool Tower::operator!=(const Tower& other) const { return !(*this == other); }
bool Tower::operator<(const Tower& other) const {
    return std::tie(position, type, damage, range, cost) < std::tie(other.position, other.type, other.damage, other.range, other.cost);
}
bool Tower::operator>(const Tower& other) const { return other < *this; }
bool Tower::operator<=(const Tower& other) const { return !(other < *this); }
bool Tower::operator>=(const Tower& other) const { return !(*this < other); }
// Value semantics: compare all fields in declaration order.
Enemy::Enemy() = default;
Enemy::Enemy(const Enemy& other) = default;
Enemy::Enemy(int healthValue, int speedValue, int rewardValue, int pathIndexValue) : health(healthValue), speed(speedValue), reward(rewardValue), pathIndex(pathIndexValue) {}
Enemy& Enemy::operator=(const Enemy& other) = default;
bool Enemy::operator==(const Enemy& other) const {
    return std::tie(health, speed, reward, pathIndex) == std::tie(other.health, other.speed, other.reward, other.pathIndex);
}
bool Enemy::operator!=(const Enemy& other) const { return !(*this == other); }
bool Enemy::operator<(const Enemy& other) const {
    return std::tie(health, speed, reward, pathIndex) < std::tie(other.health, other.speed, other.reward, other.pathIndex);
}
bool Enemy::operator>(const Enemy& other) const { return other < *this; }
bool Enemy::operator<=(const Enemy& other) const { return !(other < *this); }
bool Enemy::operator>=(const Enemy& other) const { return !(*this < other); }
// Value semantics: compare all fields in declaration order.
GameState::GameState() = default;
GameState::GameState(const GameState& other) = default;
GameState::GameState(int creditsValue, int baseHealthValue, int waveValue, std::vector<Position> pathValue, std::vector<Tower> towersValue, std::vector<Enemy> enemiesValue) : credits(creditsValue), baseHealth(baseHealthValue), wave(waveValue), path(std::move(pathValue)), towers(std::move(towersValue)), enemies(std::move(enemiesValue)) {}
GameState& GameState::operator=(const GameState& other) = default;
bool GameState::operator==(const GameState& other) const {
    return std::tie(credits, baseHealth, wave, path, towers, enemies) == std::tie(other.credits, other.baseHealth, other.wave, other.path, other.towers, other.enemies);
}
bool GameState::operator!=(const GameState& other) const { return !(*this == other); }
bool GameState::operator<(const GameState& other) const {
    return std::tie(credits, baseHealth, wave, path, towers, enemies) < std::tie(other.credits, other.baseHealth, other.wave, other.path, other.towers, other.enemies);
}
bool GameState::operator>(const GameState& other) const { return other < *this; }
bool GameState::operator<=(const GameState& other) const { return !(other < *this); }
bool GameState::operator>=(const GameState& other) const { return !(*this < other); }
// Extraction uses a temporary so a failed read leaves the destination unchanged.
std::ostream& operator<<(std::ostream& out, const Position& value) {
    return out << value.x << ' ' << value.y;
}
std::istream& operator>>(std::istream& in, Position& value) {
    Position temp;
    if (in >> temp.x >> temp.y) value = temp;
    return in;
}
std::ostream& operator<<(std::ostream& out, const Tower& value) {
    return out << value.position << ' ' << static_cast<int>(value.type) << ' '
               << value.damage << ' ' << value.range << ' ' << value.cost;
}
std::istream& operator>>(std::istream& in, Tower& value) {
    Tower temp;
    int type = 0;
    if (in >> temp.position >> type >> temp.damage >> temp.range >> temp.cost) {
        if (type < static_cast<int>(TowerType::Basic) || type > static_cast<int>(TowerType::Heavy)) {
            in.setstate(std::ios::failbit);
        } else {
            temp.type = static_cast<TowerType>(type);
            value = temp;
        }
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const Enemy& value) {
    return out << value.health << ' ' << value.speed << ' ' << value.reward << ' ' << value.pathIndex;
}
std::istream& operator>>(std::istream& in, Enemy& value) {
    Enemy temp;
    if (in >> temp.health >> temp.speed >> temp.reward >> temp.pathIndex) value = temp;
    return in;
}

namespace {
// Bound collection sizes to avoid allocating arbitrarily large input payloads.
constexpr long long kMaxStreamElements = 100000;
template <typename T>
std::istream& readVector(std::istream& in, std::vector<T>& values) {
    long long count = 0;
    if (!(in >> count)) return in;
    if (count < 0 || count > kMaxStreamElements) {
        in.setstate(std::ios::failbit);
        return in;
    }
    for (long long i = 0; i < count; ++i) {
        T element;
        if (!(in >> element)) return in;
        values.push_back(element);
    }
    return in;
}
template <typename T>
void writeVector(std::ostream& out, const std::vector<T>& values) {
    out << ' ' << values.size();
    for (const T& element : values) out << ' ' << element;
}
}
std::ostream& operator<<(std::ostream& out, const GameState& value) {
    out << value.credits << ' ' << value.baseHealth << ' ' << value.wave;
    writeVector(out, value.path);
    writeVector(out, value.towers);
    writeVector(out, value.enemies);
    return out;
}
std::istream& operator>>(std::istream& in, GameState& value) {
    GameState temp;
    if (in >> temp.credits >> temp.baseHealth >> temp.wave) {
        if (readVector(in, temp.path) && readVector(in, temp.towers) && readVector(in, temp.enemies)) {
            value = temp;
        }
    }
    return in;
}
