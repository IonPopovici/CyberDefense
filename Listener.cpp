#include "Listener.hpp"

#include <cctype>
#include <iostream>
#include <limits>

void Listener::readInput() {
    std::cout << "Command (b = build tower, s = start wave, n = next step, q = quit): ";
    char input = 'q';
    if (std::cin >> input) {
        command_ = static_cast<char>(std::tolower(static_cast<unsigned char>(input)));
    }
    else {
        command_ = 'q';
    }
}

bool Listener::wantsToBuildTower() const {
    return command_ == 'b';
}

bool Listener::wantsToStartWave() const {
    return command_ == 's';
}

bool Listener::wantsToAdvance() const {
    return command_ == 'n';
}

bool Listener::wantsToQuit() const {
    return command_ == 'q';
}

TowerType Listener::readTowerType() {
    int choice = 0;
    while (choice < 1 || choice > 3) {
        std::cout << "Tower type (1 = Basic, 2 = Fast, 3 = Heavy): ";
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                return TowerType::Basic;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
    }

    if (choice == 2) return TowerType::Fast;
    if (choice == 3) return TowerType::Heavy;
    return TowerType::Basic;
}

Position Listener::readPosition() {
    Position position{-1, -1};
    std::cout << "Type with space the column and row (x y): ";
    if (!(std::cin >> position.x >> position.y)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return Position{-1, -1};
    }
    return position;
}

bool Listener::askPlayAgain() {
    char response = 'n';
    std::cout << "\nPlay again? y/n ";
    std::cin >> response;
    return (response == 'y' || response == 'Y');
}
