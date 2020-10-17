
# This shouldn't be necessary
#find_package(PulseAudio QUIET)
#if (NOT PulseAudio_FOUND)
#
#    include(FetchContent)
#    FetchContent_Declare(
#            PulseAudio
#            GIT_REPOSITORY https://github.com/pulseaudio/pulseaudio.git
#            GIT_SHALLOW ON
#    )
#    FetchContent_MakeAvailable(PulseAudio)
#
#endif ()

find_package(Libsoundio QUIET)
if (NOT Libsoundio_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            soundio
            GIT_REPOSITORY https://github.com/andrewrk/libsoundio.git
            GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(soundio)

endif ()

find_package(Boost)
if (NOT Boost_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(boost)

endif ()

find_package(Threads)

add_library(Audio
        Buffer.cpp Buffer.h Device.cpp Device.h Backend/Backend.h DeviceList.cpp DeviceList.h Backend/Dummy.h System/System.cpp System/System.h Backend/Dummy.cpp System/Blocking.cpp System/Blocking.h Backend/Soundio.cpp Backend/Soundio.h Audio.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Audio
        ${LIBSOUNDIO_LIBRARIES}
        Threads::Threads
        Boost::boost)
