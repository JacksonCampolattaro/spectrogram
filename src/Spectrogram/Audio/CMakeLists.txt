
find_package(RtAudio REQUIRED)

add_library(Audio
        System.cpp System.h RtAudio.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Audio
        ${RTAUDIO_LIBRARIES})
