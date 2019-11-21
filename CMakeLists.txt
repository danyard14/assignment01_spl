cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 main.cpp headers/Session.h headers/Watchable.h headers/User.h headers/Action.h headers/json.hpp)