
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
