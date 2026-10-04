#include "Engine.hpp"

#include <string>

namespace {

Tower makeTower(TowerType type, Position position) {
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

bool inRange(Position a, Position b, int range) {
    const int dx = a.x - b.x;
    const int dy = a.y - b.y;
    return dx * dx + dy * dy <= range * range;
}

}

void Engine::start() {
    state_ = GameState{};

    for (int x = 0; x <= 4; ++x) state_.path.push_back({ x, 1 });
    for (int y = 2; y <= 5; ++y) state_.path.push_back({ 4, y });
    for (int x = 5; x < kMapWidth; ++x) state_.path.push_back({ x, 5 });

    enemiesToSpawn_ = 0;
    waveActive_ = false;
    running_ = true;
}

bool Engine::isOnPath(Position position) const {
    for (const Position& p : state_.path) {
        if (p.x == position.x && p.y == position.y) return true;
    }
    return false;
}

bool Engine::isOccupied(Position position) const {
    for (const Tower& tower : state_.towers) {
        if (tower.position.x == position.x && tower.position.y == position.y) return true;
    }
    return false;
}

bool Engine::buildTower(TowerType type, Position position) {
    if (position.x < 0 || position.x >= kMapWidth || position.y < 0 || position.y >= kMapHeight) return false;
    if (isOnPath(position) || isOccupied(position)) return false;

    const Tower tower = makeTower(type, position);
    if (state_.credits < tower.cost) return false;

    state_.credits -= tower.cost;
    state_.towers.push_back(tower);
    return true;
}

bool Engine::startWave() {
    if (waveActive_) return false;

    waveActive_ = true;
    enemiesToSpawn_ = 2 + state_.wave;
    return true;
}

void Engine::update() {
    const int lastIndex = static_cast<int>(state_.path.size()) - 1;

    std::vector<Enemy> stillWalking;
    for (Enemy enemy : state_.enemies) {
        enemy.pathIndex += enemy.speed;
        if (enemy.pathIndex >= lastIndex) {
            --state_.baseHealth;
        }
        else {
            stillWalking.push_back(enemy);
        }
    }
    state_.enemies = stillWalking;

    if (enemiesToSpawn_ > 0) {
        Enemy enemy;
        enemy.health = 30 + 10 * state_.wave;
        enemy.reward = 20;
        state_.enemies.push_back(enemy);
        --enemiesToSpawn_;
    }

    for (const Tower& tower : state_.towers) {
        const int shots = (tower.type == TowerType::Fast) ? 2 : 1;
        for (int s = 0; s < shots; ++s) {
            Enemy* target = nullptr;
            for (Enemy& enemy : state_.enemies) {
                if (enemy.health <= 0) continue;
                if (!inRange(tower.position, state_.path[enemy.pathIndex], tower.range)) continue;
                if (target == nullptr || enemy.pathIndex > target->pathIndex) target = &enemy;
            }
            if (target != nullptr) target->health -= tower.damage;
        }
    }

    std::vector<Enemy> alive;
    for (const Enemy& enemy : state_.enemies) {
        if (enemy.health > 0) {
            alive.push_back(enemy);
        }
        else {
            state_.credits += enemy.reward;
        }
    }
    state_.enemies = alive;

    if (waveActive_ && enemiesToSpawn_ == 0 && state_.enemies.empty()) {
        waveActive_ = false;
        ++state_.wave;
    }
}

const GameState& Engine::getState() const {
    return state_;
}

void Engine::render() const {
    renderer_.clearScreen();
    renderer_.drawMap(state_);
    renderer_.drawTowers(state_);
    renderer_.drawEnemies(state_);
    renderer_.drawInterface(state_);
}

void Engine::run() {
    bool keepPlaying = true;

    while (keepPlaying) {
        start();
        std::string message;

        while (running_) {
            render();
            if (!message.empty()) {
                renderer_.displayMessage(message);
                message.clear();
            }

            listener_.readInput();

            if (listener_.wantsToQuit()) {
                running_ = false;
            }
            else if (listener_.wantsToBuildTower()) {
                const TowerType type = listener_.readTowerType();
                const Position position = listener_.readPosition();
                if (!buildTower(type, position)) {
                    message = "Cant build there (outside the map, on the path, occupied or not enough credits)";
                }
            }
            else if (listener_.wantsToStartWave()) {
                if (!startWave()) {
                    message = "The wave is already in progress";
                }
            }
            else if (listener_.wantsToAdvance()) {
                update();
            }
            else {
                message = "Unknown command";
            }

            if (state_.baseHealth <= 0) {
                render();
                renderer_.displayMessage("Game over: the server was destroyed");
                running_ = false;
            }
        }

        keepPlaying = listener_.askPlayAgain();
    }

    renderer_.displayMessage("\nThanks, bye");
}
