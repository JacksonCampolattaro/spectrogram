
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_library(Audio
        Buffer.cpp Buffer.h Device.cpp Device.h Backend/Backend.h DeviceList.cpp DeviceList.h Backend/Dummy.h System/System.cpp System/System.h Backend/Dummy.cpp System/Blocking.cpp System/Blocking.h Backend/Soundio.cpp Backend/Soundio.h Audio.h System/Event.cpp System/Event.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

find_package(Libsoundio QUIET)
if (NOT Libsoundio_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            Libsoundio
            GIT_REPOSITORY https://github.com/andrewrk/libsoundio
            GIT_TAG 2.0.0
    )
    FetchContent_MakeAvailable(Libsoundio)

    target_include_directories(Audio PUBLIC
            ${PROJECT_BINARY_DIR}/_deps/libsoundio-src)

    # TODO: This isn't working...

endif ()

target_link_libraries(Audio
        ${Libsoundio_LIBRARIES}
        Threads::Threads
        Boost::boost)

target_compile_options(Audio PRIVATE
        -Werror
        -Wall
        -Wextra)
