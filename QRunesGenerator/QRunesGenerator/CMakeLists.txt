cmake_minimum_required(VERSION 3.1)

include_directories(${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/example
                    ${PROJECT_SOURCE_DIR}/pybind11
                    ${PROJECT_SOURCE_DIR}/QRunesGenerator
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

if(UNIX)
    add_definitions("-std=c++14")
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
    add_compile_options(-fPIC -fpermissive)
endif(UNIX)

add_subdirectory(example)
add_subdirectory(QRunesGenerator)

option(USE_PYQPANDA "use pyQpanda" ON)
if(USE_PYQPANDA)
    include_directories(${PROJECT_SOURCE_DIR}/pyQPandaCpp)
    add_subdirectory(pyQPanda)
endif(USE_PYQPANDA)
