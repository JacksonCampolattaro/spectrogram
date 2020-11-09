set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(QtMainApplication
        main.cpp
        QtMainApplication.h
        QtMainApplication.cpp)

target_link_libraries(QtMainApplication
        Qt5::Widgets
        Visualizer
        PNG)

target_include_directories(QtMainApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

# target_compile_options(QtMainApplication PRIVATE
#         -Werror
#         -Wall
#         -Wextra)
