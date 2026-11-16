cmake_minimum_required(VERSION 3.16)
project(CyberDefense CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(json)

add_library(game_data STATIC GameTypes.cpp)
target_include_directories(game_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(game_persistence STATIC SaveSystem.cpp)
target_include_directories(game_persistence PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game_persistence PUBLIC game_data nlohmann_json::nlohmann_json)

add_executable(cyber_defense main.cpp Engine.cpp Renderer.cpp Listener.cpp)
target_link_libraries(cyber_defense PRIVATE game_data game_persistence)

include(CTest)
if(BUILD_TESTING)
    add_executable(lab5_tests tests/Lab3Tests.cpp Engine.cpp Renderer.cpp Listener.cpp)
    target_link_libraries(lab5_tests PRIVATE game_data game_persistence)
    add_test(NAME lab5_libraries_and_save COMMAND lab5_tests)
endif()
