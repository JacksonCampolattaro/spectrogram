cmake_minimum_required(VERSION 3.14)
project(spectrogram)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

option(BUILD_APPLICATIONS "Build our application" ON)
option(BUILD_TESTS "Build the test suite" OFF)
option(BUILD_DOCUMENTATION "Build doxygen docs" OFF)

if (BUILD_APPLICATIONS)
    add_subdirectory(src)
endif ()

if (BUILD_TESTS)
    add_subdirectory(test)
endif ()

if (BUILD_DOCUMENTATION)
    add_subdirectory(docs)
endif ()