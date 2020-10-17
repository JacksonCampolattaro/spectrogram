cmake_minimum_required(VERSION 3.14)
project(spectrogram)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)


option(BUILD_APPLICATIONS "Build our application" ON)
option(BUILD_TESTS "Build the test suite" ON)
option(BUILD_DOCUMENTATION "Build doxygen docs" ON)

if (BUILD_APPLICATIONS)
    add_subdirectory(src)
endif ()

if (BUILD_TESTS)
    add_subdirectory(test)
endif ()

if (BUILD_DOCUMENTATION)
    add_subdirectory(docs)
endif ()