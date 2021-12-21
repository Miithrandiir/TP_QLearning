cmake_minimum_required(VERSION 3.21)
project(QLearning)

set(CMAKE_CXX_STANDARD 17)

add_executable(QLearning main.cpp src/Ile.cpp src/Ile.hpp src/Pirate.cpp src/Pirate.hpp)
