cmake_minimum_required(VERSION 3.1)
project(QRunesGenerator)

file(GLOB_RECURSE QRunesGenerator_SRCS_H ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE QRunesGenerator_SRCS_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
add_library(${PROJECT_NAME} STATIC  ${QRunesGenerator_SRCS_H} ${QRunesGenerator_SRCS_CPP} )







