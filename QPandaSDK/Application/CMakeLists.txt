cmake_minimum_required(VERSION 3.1)
project(Application)
add_executable(${PROJECT_NAME} ConsoleApplication.cpp)
target_link_libraries(${PROJECT_NAME} QuantumCommandControl)
