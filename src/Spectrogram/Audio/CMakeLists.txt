
find_package(Libsoundio REQUIRED)

add_library(Audio
        System/System.h Buffer.cpp Buffer.h Device.cpp Device.h System/LibSoundio.cpp System/LibSoundio.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Audio
        ${LIBSOUNDIO_LIBRARIES})
