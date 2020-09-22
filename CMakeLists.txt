cmake_minimum_required(VERSION 3.14)
project(spectrogram)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules)

add_subdirectory(src)
add_subdirectory(test)
