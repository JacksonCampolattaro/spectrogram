
find_package(Catch2 REQUIRED)

find_package(RtAudio REQUIRED)
find_package(Portaudio REQUIRED)
find_package(Libsoundio REQUIRED)

add_executable(test main.cpp
        test_Audio_System.cpp)

target_link_libraries(test LINK_PUBLIC
        Audio
        Graphics
        Fourier
        ${RTAUDIO_LIBRARIES}
        ${PORTAUDIO_LIBRARIES}
        ${LIBSOUNDIO_LIBRARIES})

target_include_directories(test PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src)