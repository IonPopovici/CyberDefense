cmake_minimum_required(VERSION 3.16)
project(CyberDefense CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cyber_defense
    main.cpp
    Engine.cpp
    Renderer.cpp
    Listener.cpp
    GameTypes.cpp
)

include(CTest)
if(BUILD_TESTING)
    add_executable(lab3_tests tests/Lab3Tests.cpp GameTypes.cpp Engine.cpp Renderer.cpp Listener.cpp)
    target_include_directories(lab3_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME lab3_value_semantics COMMAND lab3_tests)
endif()
