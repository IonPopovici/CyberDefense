#pragma once

#include "GameTypes.hpp"

class Renderer;
class Listener;

class Engine {
public:
    void start();
    void update();
    void buildTower(TowerType type, Position position);
    const GameState& getState() const;

private:
    GameState state_;
};
