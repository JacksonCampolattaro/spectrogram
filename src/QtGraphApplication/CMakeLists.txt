set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(QtGraphApplication
        main.cpp)

target_link_libraries(QtGraphApplication
        Qt5::Widgets
        Visualizer)

target_include_directories(QtGraphApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(QtGraphApplication PRIVATE
          -g)
#         -Werror
#         -Wall
#         -Wextra)
