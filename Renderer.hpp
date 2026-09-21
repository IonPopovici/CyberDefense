#pragma once

#include <string>
#include <vector>

#include "GameTypes.hpp"

class Renderer {
public:
    void clearScreen() const;
    void drawMap(const GameState& state) const;
    void drawTowers(const GameState& state) const;
    void drawEnemies(const GameState& state) const;
    void drawInterface(const GameState& state) const;
    void displayMessage(const std::string& message) const;

private:
    mutable std::vector<std::string> grid_;
};
