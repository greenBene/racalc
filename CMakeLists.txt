cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

# set the project name
project(racalc)

# add the executable
add_executable(racalc 
    src/main.cpp
    src/Nat.cpp)