set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(QCustomPlot REQUIRED)


add_executable(QtGraphApplication
        main.cpp
        GraphGui.h
        GraphGui.cpp)

target_link_libraries(QtGraphApplication
        ${QCustomPlot_LIBRARIES}
        Qt5::Widgets
        Qt5::PrintSupport
        Audio
        Fourier)

target_include_directories(QtGraphApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

# target_compile_options(QtGraphApplication PRIVATE
#         -Werror
#         -Wall
#         -Wextra)
