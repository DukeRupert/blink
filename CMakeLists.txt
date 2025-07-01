cmake_minimum_required(VERSION 3.11)
project(Blink)

set(CMAKE_CXX_STANDAR 17)

find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} engine.cpp)
target_link_libraries(${PROJECT_NAME} raylib)
