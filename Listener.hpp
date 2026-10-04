#pragma once

#include "GameTypes.hpp"

class Listener {
public:
    void readInput();
    bool wantsToBuildTower() const;
    bool wantsToStartWave() const;
    bool wantsToAdvance() const;
    bool wantsToQuit() const;
    TowerType readTowerType();
    Position readPosition();
    bool askPlayAgain();

private:
    char command_{'n'};
};
