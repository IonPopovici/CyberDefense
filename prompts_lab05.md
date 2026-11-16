# AI assistance notes — Lab5

Lab5 separates the game data implementation into a static library and adds a persistence library that uses the external nlohmann/json package. CMake fetches the dependency, builds both libraries, and links them into the game. The engine saves the game state to JSON on exit and restores it on the next start. The Makefile wraps the CMake build and test commands.
