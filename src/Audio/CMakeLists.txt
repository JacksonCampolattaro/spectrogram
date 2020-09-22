
# This is causing trouble, and I don't know why...
find_package(portaudio)

add_library(Audio
        placeholder.h
        placeholder.cpp)

target_include_directories(Audio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
