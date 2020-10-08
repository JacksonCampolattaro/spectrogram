
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(QtApplication
        main.cpp)

target_link_libraries(QtApplication
        Qt5::Widgets)