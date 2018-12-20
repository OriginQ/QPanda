cmake_minimum_required(VERSION 3.1)
project(QuantumCommandControl)

file(GLOB_RECURSE CONTROL_SRCS_H ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE CONTROL_SRCS_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
add_library(${PROJECT_NAME} STATIC  ${CONTROL_SRCS_H} ${CONTROL_SRCS_CPP} )
target_link_libraries(${PROJECT_NAME} QuantumCloudHTTP QPandaAPI TinyXML sqlite) 







