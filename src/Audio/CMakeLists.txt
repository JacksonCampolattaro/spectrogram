
find_package(RtAudio REQUIRED)

add_library(Audio
        placeholder.h
        placeholder.cpp)

target_include_directories(Audio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
