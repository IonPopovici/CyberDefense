cmake_minimum_required(VERSION 3.16)
project(CyberDefense CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cyber_defense
    main.cpp
    Engine.cpp
    Renderer.cpp
    Listener.cpp
)
