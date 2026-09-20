#pragma once

#include "GameTypes.hpp"

class Renderer {
public:
    void drawMap(const GameState& state) const;
    void drawTowers(const GameState& state) const;
    void drawEnemies(const GameState& state) const;
    void drawInterface(const GameState& state) const;
};
