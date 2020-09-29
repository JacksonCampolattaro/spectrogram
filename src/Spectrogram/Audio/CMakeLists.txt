
find_package(RtAudio REQUIRED)
find_package(Portaudio REQUIRED)
find_package(Libsoundio REQUIRED)

add_library(Audio
        System/System.h Buffer.cpp Buffer.h Device.cpp Device.h System/LibRtAudio.cpp System/LibRtAudio.h System/LibSoundio.cpp System/LibSoundio.h System/LibPortAudio.cpp System/LibPortAudio.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Audio
        ${RTAUDIO_LIBRARIES}
        ${PORTAUDIO_LIBRARIES}
        ${LIBSOUNDIO_LIBRARIES})
