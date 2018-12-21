cmake_minimum_required(VERSION 3.1)
project(QRunesParser)

file(GLOB_RECURSE QRunesParser_SRCS_H ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE QRunesParser_SRCS_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
add_library(${PROJECT_NAME} STATIC  ${QRunesParser_SRCS_H} ${QRunesParser_SRCS_CPP} )







