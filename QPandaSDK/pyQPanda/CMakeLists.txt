cmake_minimum_required(VERSION 3.1)
project(pyQPanda)

file(GLOB_RECURSE pyQPanda_SRC_CPP *.cpp)
add_library(${PROJECT_NAME} SHARED ${pyQPanda_SRC_CPP})

if (UNIX)
    if (APPLE)
	    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".so")
    endif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
elseif(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
endif(UNIX)
target_link_libraries(${PROJECT_NAME} QPandaAPI ${PYTHON_LIBRARIES})

