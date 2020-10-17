
find_package(Libsoundio REQUIRED)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_library(Audio
        Buffer.cpp Buffer.h Device.cpp Device.h Backend/Backend.h DeviceList.cpp DeviceList.h Backend/Dummy.h System/System.cpp System/System.h Backend/Dummy.cpp System/Blocking.cpp System/Blocking.h Backend/Soundio.cpp Backend/Soundio.h Audio.h)

target_include_directories(Audio PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

message(${LIBSOUNDIO_LIBRARIES})
target_link_libraries(Audio
        ${LIBSOUNDIO_LIBRARIES}
        Threads::Threads
        Boost::boost)
