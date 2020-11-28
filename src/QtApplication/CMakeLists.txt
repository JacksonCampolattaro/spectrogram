set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(QtApplication
        main.cpp
        QtApplication.h QtApplication.cpp
        QtAudioSystem.h QtAudioSystem.cpp)

target_link_libraries(QtApplication
        Qt5::Widgets
        Visualizer)

target_include_directories(QtApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

# target_compile_options(QtApplication PRIVATE
#         -Werror
#         -Wall
#         -Wextra)
