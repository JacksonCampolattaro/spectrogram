
find_package(RtAudio REQUIRED)

add_library(Audio
        placeholder.h
        placeholder.cpp System.cpp System.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
