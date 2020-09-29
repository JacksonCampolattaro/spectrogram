
find_package(RtAudio REQUIRED)

add_library(Audio
        RtAudio.h System/System.h Buffer.cpp Buffer.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Audio
        ${RTAUDIO_LIBRARIES})
