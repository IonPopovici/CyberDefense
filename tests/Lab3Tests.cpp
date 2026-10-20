#include "Engine.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <type_traits>

#define CHECK(...) do { if (!(__VA_ARGS__)) { std::cerr << "Failed at line " << __LINE__ << ": " << #__VA_ARGS__ << '\n'; std::exit(1); } } while (false)

template <typename T>
void checkValue(const T& value, const T& larger) {
    T copy(value);
    CHECK(copy == value);
    T assigned;
    CHECK(&(assigned = value) == &assigned);
    CHECK(assigned == value);
    assigned = assigned;
    CHECK(assigned == value);
    CHECK(value != larger && value < larger && larger > value);
    CHECK(value <= value && value >= value && !(value < value));
    CHECK(value <= larger && larger >= value);
    std::stringstream stream;
    CHECK(&(stream << value) == &stream);
    T restored;
    CHECK(&(stream >> restored) == &stream);
    CHECK(!stream.fail() && restored == value);
    std::istringstream invalid("bad");
    invalid >> restored;
    CHECK(invalid.fail() && restored == value);
}

struct TestRenderer : IRenderer {
    mutable int calls = 0;
    void clearScreen() const override { ++calls; }
    void drawMap(const GameState&) const override { ++calls; }
    void drawTowers(const GameState&) const override { ++calls; }
    void drawEnemies(const GameState&) const override { ++calls; }
    void drawInterface(const GameState&) const override { ++calls; }
    void displayMessage(const std::string&) const override { ++calls; }
};

int main() {
    static_assert(std::is_abstract<IRenderer>::value, "Abstract renderer required");
    static_assert(std::has_virtual_destructor<IRenderer>::value, "Virtual destructor required");
    static_assert(std::is_base_of<IRenderer, Renderer>::value, "Renderer must inherit interface");
    CHECK(Position().x == 0 && Position().y == 0);
    CHECK(Tower().damage == 10 && Tower().cost == 50);
    CHECK(Enemy().health == 100 && Enemy().speed == 1);
    CHECK(GameState().credits == 100 && GameState().path.empty());
    checkValue(Position(1, 2), Position(2, 0));
    Tower tower(Position(1, 2), TowerType::Fast, 6, 2, 60);
    Tower largerTower(tower);
    ++largerTower.cost;
    checkValue(tower, largerTower);
    Enemy enemy(40, 1, 20, 0);
    checkValue(enemy, Enemy(41, 1, 20, 0));
    GameState state(150, 10, 2, {Position(0, 1), Position(1, 1)}, {tower}, {enemy});
    GameState later(state);
    ++later.credits;
    checkValue(state, later);
    later = state;
    later.path[0].x = 9;
    later.towers[0].damage = 99;
    later.enemies[0].health = 1;
    CHECK(state.path[0].x == 0 && state.towers[0].damage == 6 && state.enemies[0].health == 40);
    for (const char* text : {"150 10 2 -1", "150 10 2 100001", "150 10 2 1 0", "150 10 2 0 0 1 40 1"}) {
        GameState unchanged(state);
        std::istringstream input(text);
        input >> unchanged;
        CHECK(input.fail() && unchanged == state);
    }
    std::istringstream badType("1 2 99 6 2 60");
    Tower unchanged(tower);
    badType >> unchanged;
    CHECK(badType.fail() && unchanged == tower);
    std::stringstream chain;
    chain << Position(1, 2) << ' ' << Position(3, 4);
    Position first, second;
    chain >> first >> second;
    CHECK(first == Position(1, 2) && second == Position(3, 4));
    std::vector<Position> positions{second, first};
    std::sort(positions.begin(), positions.end());
    CHECK(positions.front() == first);
    CHECK(Tower::create(TowerType::Heavy, first).cost == 120);
    CHECK(Enemy::spawnForWave(1).health == 40);
    TestRenderer renderer;
    Engine engine(renderer);
    engine.start();
    CHECK(engine.getState().path.size() == 14);
    CHECK(engine.buildTower(TowerType::Basic, Position(0, 0)));
    CHECK(engine.getState().credits == 50);
    CHECK(!engine.buildTower(TowerType::Basic, Position(0, 0)));
    CHECK(!engine.buildTower(TowerType::Basic, Position(0, 1)));
    CHECK(engine.startWave() && !engine.startWave());
    for (int i = 0; i < 20; ++i) engine.update();
    CHECK(engine.getState().wave == 2 && engine.getState().enemies.empty());
    std::istringstream commands("q n");
    std::streambuf* original = std::cin.rdbuf(commands.rdbuf());
    engine.run();
    std::cin.rdbuf(original);
    CHECK(renderer.calls == 6);
    std::cout << "All Lab3 checks passed\n";
}
