#pragma once

class Listener {
public:
    void readInput();
    bool wantsToBuildTower() const;
    bool wantsToStartWave() const;
};
