set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(QCustomPlot REQUIRED)


add_executable(QtMainApplication
        main.cpp
        QtMainApplication.h
        QtMainApplication.cpp
        SpectrogramGraph.h
        SpectrogramGraph.cpp)

target_link_libraries(QtMainApplication
        ${QCustomPlot_LIBRARIES}
        Qt5::Widgets
        Qt5::PrintSupport
        Audio
        Fourier)

target_include_directories(QtMainApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

# target_compile_options(QtMainApplication PRIVATE
#         -Werror
#         -Wall
#         -Wextra)
