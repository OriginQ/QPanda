cmake_minimum_required(VERSION 3.1)
project(example)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} QRunesGenerator)
