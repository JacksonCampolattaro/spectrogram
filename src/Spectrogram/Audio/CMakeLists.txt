
find_package(RtAudio REQUIRED)

add_library(Audio
        System/System.h Buffer.cpp Buffer.h Device.cpp Device.h System/RtAudio.cpp System/RtAudio.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Audio
        ${RTAUDIO_LIBRARIES})
