cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 main.cpp include/Session.h include/Watchable.h include/User.h include/Action.h include/json.hpp src/Action.cpp src/Session.cpp src/User.cpp src/Watchable.cpp .gitignore Main2.cpp)