#pragma once

#include <string>
#include "GameTypes.hpp"

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void clearScreen() const = 0;
    virtual void drawMap(const GameState& state) const = 0;
    virtual void drawTowers(const GameState& state) const = 0;
    virtual void drawEnemies(const GameState& state) const = 0;
    virtual void drawInterface(const GameState& state) const = 0;
    virtual void displayMessage(const std::string& message) const = 0;
};
