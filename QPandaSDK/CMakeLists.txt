cmake_minimum_required(VERSION 3.1)

find_package(PythonLibs REQUIRED 3)
include_directories(${PYTHON_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/Application
                    ${PROJECT_SOURCE_DIR}/ThirdParty
                    ${PROJECT_SOURCE_DIR}/QPandaAPI
                    ${PROJECT_SOURCE_DIR}/QRunesParser
                    ${PROJECT_SOURCE_DIR}/QuantumCloudHTTP
                    ${PROJECT_SOURCE_DIR}/QuantumInstructionHandle
                    ${PROJECT_SOURCE_DIR}/QuantumCommandControl
                    ${PROJECT_SOURCE_DIR}/ThirdParty/gtest
                    ${PROJECT_SOURCE_DIR}/ThirdParty/gtest/include
                    ${PROJECT_SOURCE_DIR}
                    ${PYTHON_PATH_INCLUDE})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/lib)

if (MSVC)
    if (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
        foreach (flag CMAKE_C_FLAGS
                CMAKE_C_FLAGS_DEBUG
                CMAKE_C_FLAGS_RELEASE
                CMAKE_C_FLAGS_MINSIZEREL
                CMAKE_C_FLAGS_RELWITHDEBINFO
                CMAKE_CXX_FLAGS
                CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL
                CMAKE_CXX_FLAGS_RELWITHDEBINFO)

                if (${flag} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
                endif()
                if (${flag} MATCHES "/MDd")
                    string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
                endif()
        endforeach()
    endif()
    Add_Definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
endif()

option(FIND_CUDA "find cuda" ON)
if (FIND_CUDA)
    find_package(CUDA)
endif(FIND_CUDA)
if(CUDA_FOUND)
    option (USE_CUDA "Use cuda" ON)
    include_directories(${CUDA_INCLUDE_DIRS}
                        ${PROJECT_SOURCE_DIR}/GPUEmulator)
    add_subdirectory(GPUEmulator)
else(CUDA_FOUND)
    option (USE_CUDA "Use cuda" OFF)
endif(CUDA_FOUND)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
                 "${PROJECT_SOURCE_DIR}/config.h")

if(UNIX)
    add_definitions("-std=c++14")
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
    add_compile_options(-fPIC -fpermissive)
endif(UNIX)

add_subdirectory(Application)
add_subdirectory(QPandaAPI)
add_subdirectory(QRunesParser)
add_subdirectory(ThirdParty)
add_subdirectory(testMain)
add_subdirectory(QuantumCloudHTTP)
add_subdirectory(QuantumCommandControl)
add_subdirectory(QuantumInstructionHandle)
option(USE_PYQPANDA "use pyQpanda" OFF)

if(USE_PYQPANDA)
    add_subdirectory(pyQPanda)
endif(USE_PYQPANDA)
