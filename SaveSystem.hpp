#pragma once
#include "GameTypes.hpp"
#include <string>

class SaveSystem {
public:
    static bool save(const GameState& state, const std::string& fileName);
    static bool load(GameState& state, const std::string& fileName);
};
