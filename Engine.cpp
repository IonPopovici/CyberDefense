#include "Engine.hpp"

#include <string>

void Engine::start() {
    state_ = GameState{};

    for (int x = 0; x <= 4; ++x) state_.path.push_back({ x, 1 });
    for (int y = 2; y <= 5; ++y) state_.path.push_back({ 4, y });
    for (int x = 5; x < kMapWidth; ++x) state_.path.push_back({ x, 5 });

    enemiesToSpawn_ = 0;
    waveActive_ = false;
    running_ = true;
}

bool Engine::buildTower(TowerType type, Position position) {
    if (!position.isInsideMap()) return false;
    if (state_.isPositionOnPath(position) || state_.isPositionOccupied(position)) return false;

    const Tower tower = Tower::create(type, position);
    if (!state_.canAfford(tower.cost)) return false;

    state_.spendCredits(tower.cost);
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

    // 1. Enemies move along the path; the ones that reach the server damage it.
    std::vector<Enemy> stillWalking;
    for (Enemy enemy : state_.enemies) {
        enemy.advance();
        if (enemy.hasReachedEnd(lastIndex)) {
            --state_.baseHealth;
        }
        else {
            stillWalking.push_back(enemy);
        }
    }
    state_.enemies = stillWalking;

    // 2. The wave releases one new enemy per step.
    if (enemiesToSpawn_ > 0) {
        state_.enemies.push_back(Enemy::spawnForWave(state_.wave));
        --enemiesToSpawn_;
    }

    // 3. Towers shoot the enemy closest to the server among those in range.
    for (const Tower& tower : state_.towers) {
        const int shots = tower.shotsPerStep();
        for (int s = 0; s < shots; ++s) {
            Enemy* target = nullptr;
            for (Enemy& enemy : state_.enemies) {
                if (!enemy.isAlive()) continue;
                if (!tower.isInRange(state_.path[enemy.pathIndex])) continue;
                if (target == nullptr || enemy.pathIndex > target->pathIndex) target = &enemy;
            }
            if (target != nullptr) target->applyDamage(tower.damage);
        }
    }

    // 4. Dead enemies give credits.
    std::vector<Enemy> alive;
    for (const Enemy& enemy : state_.enemies) {
        if (enemy.isAlive()) {
            alive.push_back(enemy);
        }
        else {
            state_.addCredits(enemy.reward);
        }
    }
    state_.enemies = alive;

    // 5. The wave is over when nobody is left to spawn or to kill.
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

            if (state_.isGameOver()) {
                render();
                renderer_.displayMessage("Game over: the server was destroyed");
                running_ = false;
            }
        }

        keepPlaying = listener_.askPlayAgain();
    }

    renderer_.displayMessage("\nThanks, bye");
}
