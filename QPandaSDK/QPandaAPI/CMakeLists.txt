cmake_minimum_required(VERSION 3.1)
project(QPandaAPI)

file(GLOB_RECURSE QPandaAPI_SRCS_H ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE QPandaAPI_SRCS_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
add_library(${PROJECT_NAME} STATIC  ${QPandaAPI_SRCS_H} ${QPandaAPI_SRCS_CPP})
target_link_libraries(${PROJECT_NAME} QuantumInstructionHandle QRunesParser)







