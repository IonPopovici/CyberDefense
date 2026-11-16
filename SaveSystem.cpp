#include "SaveSystem.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using nlohmann::json;

namespace {
json encodePosition(const Position& value) { return {{"x", value.x}, {"y", value.y}}; }
Position decodePosition(const json& value) { return Position(value.at("x").get<int>(), value.at("y").get<int>()); }
json encodeTower(const Tower& value) {
    return {{"position", encodePosition(value.position)}, {"type", static_cast<int>(value.type)},
            {"damage", value.damage}, {"range", value.range}, {"cost", value.cost}};
}
Tower decodeTower(const json& value) {
    return Tower(decodePosition(value.at("position")), static_cast<TowerType>(value.at("type").get<int>()),
                 value.at("damage").get<int>(), value.at("range").get<int>(), value.at("cost").get<int>());
}
json encodeEnemy(const Enemy& value) {
    return {{"health", value.health}, {"speed", value.speed}, {"reward", value.reward}, {"pathIndex", value.pathIndex}};
}
Enemy decodeEnemy(const json& value) {
    return Enemy(value.at("health").get<int>(), value.at("speed").get<int>(),
                 value.at("reward").get<int>(), value.at("pathIndex").get<int>());
}
}

bool SaveSystem::save(const GameState& state, const std::string& fileName) {
    json data;
    data["credits"] = state.credits;
    data["baseHealth"] = state.baseHealth;
    data["wave"] = state.wave;
    data["path"] = json::array();
    data["towers"] = json::array();
    data["enemies"] = json::array();
    for (const auto& item : state.path) data["path"].push_back(encodePosition(item));
    for (const auto& item : state.towers) data["towers"].push_back(encodeTower(item));
    for (const auto& item : state.enemies) data["enemies"].push_back(encodeEnemy(item));
    std::ofstream output(fileName.c_str());
    if (!output) return false;
    output << data.dump(2);
    return output.good();
}

bool SaveSystem::load(GameState& state, const std::string& fileName) {
    std::ifstream input(fileName.c_str());
    if (!input) return false;
    try {
        json data;
        input >> data;
        GameState loaded;
        loaded.credits = data.at("credits").get<int>();
        loaded.baseHealth = data.at("baseHealth").get<int>();
        loaded.wave = data.at("wave").get<int>();
        for (const auto& item : data.at("path")) loaded.path.push_back(decodePosition(item));
        for (const auto& item : data.at("towers")) loaded.towers.push_back(decodeTower(item));
        for (const auto& item : data.at("enemies")) loaded.enemies.push_back(decodeEnemy(item));
        state = loaded;
        return true;
    } catch (const json::exception&) {
        return false;
    }
}
