#pragma once

#include <string>
#include <vector>

#include "IRenderer.hpp"

class Renderer : public IRenderer {
public:
    void clearScreen() const override;
    void drawMap(const GameState& state) const override;
    void drawTowers(const GameState& state) const override;
    void drawEnemies(const GameState& state) const override;
    void drawInterface(const GameState& state) const override;
    void displayMessage(const std::string& message) const override;

private:
    mutable std::vector<std::string> grid_;
};
