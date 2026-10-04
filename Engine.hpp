#pragma once

#include "GameTypes.hpp"
#include "Renderer.hpp"
#include "Listener.hpp"

class Engine {
public:
    void start();
    void run();
    void update();
    bool buildTower(TowerType type, Position position);
    bool startWave();
    const GameState& getState() const;

private:
    void render() const;

    GameState state_;
    Renderer renderer_;
    Listener listener_;
    int enemiesToSpawn_{0};
    bool waveActive_{false};
    bool running_{false};
};
