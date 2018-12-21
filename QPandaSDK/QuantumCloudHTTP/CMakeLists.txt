cmake_minimum_required(VERSION 3.1)
project(QuantumCloudHTTP)

file(GLOB_RECURSE HTTP_SRCS_H ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE HTTP_SRCS_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
add_library(${PROJECT_NAME} STATIC  ${HTTP_SRCS_H} ${HTTP_SRCS_CPP} )
target_link_libraries(${PROJECT_NAME} json ${PYTHON_LIBRARIES}) 







