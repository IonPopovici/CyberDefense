#include "Renderer.hpp"

#include <cstdlib>
#include <iostream>

void Renderer::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Renderer::drawMap(const GameState& state) const {
    grid_.assign(kMapHeight, std::string(kMapWidth, '.'));

    for (const Position& p : state.path) {
        grid_[p.y][p.x] = '#';
    }
    if (!state.path.empty()) {
        const Position& base = state.path.back();
        grid_[base.y][base.x] = 'S';
    }
}

void Renderer::drawTowers(const GameState& state) const {
    for (const Tower& tower : state.towers) {
        char symbol = 'B';
        if (tower.type == TowerType::Fast) symbol = 'F';
        else if (tower.type == TowerType::Heavy) symbol = 'H';

        grid_[tower.position.y][tower.position.x] = symbol;
    }
}

void Renderer::drawEnemies(const GameState& state) const {
    for (const Enemy& enemy : state.enemies) {
        if (enemy.pathIndex < 0 || enemy.pathIndex >= static_cast<int>(state.path.size())) continue;

        const Position& p = state.path[enemy.pathIndex];
        grid_[p.y][p.x] = 'E';
    }
}

void Renderer::drawInterface(const GameState& state) const {
    std::cout << "\n  ";
    for (int x = 0; x < kMapWidth; ++x) {
        std::cout << x << ' ';
    }
    std::cout << "\n";

    for (int y = 0; y < kMapHeight; ++y) {
        std::cout << y << ' ';
        for (int x = 0; x < kMapWidth; ++x) {
            std::cout << grid_[y][x] << ' ';
        }
        std::cout << "\n";
    }

    std::cout << "\nCredits: " << state.credits
              << " | Base health: " << state.baseHealth
              << " | Wave: " << state.wave
              << " | Enemies: " << state.enemies.size() << "\n";
    std::cout << "# path, S server, B/F/H towers, E enemy\n\n";
}

void Renderer::displayMessage(const std::string& message) const {
    std::cout << message << std::endl;
}
