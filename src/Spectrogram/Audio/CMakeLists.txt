
find_package(Libsoundio REQUIRED)
find_package(Threads)

add_library(Audio
        System/System.h Buffer.cpp Buffer.h Device.cpp Device.h System/LibSoundio.cpp System/LibSoundio.h Backend/Backend.h DeviceList.cpp DeviceList.h Backend/Dummy.h System/Callback.cpp System/Callback.h Backend/Dummy.cpp System/Blocking.cpp System/Blocking.h Backend/Soundio.cpp Backend/Soundio.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Audio
        ${LIBSOUNDIO_LIBRARIES}
        Threads::Threads)
