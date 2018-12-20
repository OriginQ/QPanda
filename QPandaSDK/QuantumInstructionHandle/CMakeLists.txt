cmake_minimum_required(VERSION 3.1)
project(QuantumInstructionHandle)

file(GLOB_RECURSE HANDLE_SRCS_H ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE HANDLE_SRCS_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
add_library(${PROJECT_NAME} STATIC  ${HANDLE_SRCS_H} ${HANDLE_SRCS_CPP} )







