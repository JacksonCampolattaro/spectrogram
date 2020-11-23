
include(FetchContent)

find_package(Libsoundio QUIET)
if (NOT Libsoundio_FOUND)

    FetchContent_Declare(Libsoundio
            GIT_REPOSITORY https://github.com/andrewrk/libsoundio
            GIT_TAG 2.0.0
            )
    FetchContent_MakeAvailable(Libsoundio)

endif ()