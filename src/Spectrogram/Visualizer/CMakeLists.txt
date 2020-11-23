set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

find_package(QCustomPlot QUIET)
if (NOT QCustomPlot)

    FetchContent_Declare(
            QCustomPlot
            URL https://www.qcustomplot.com/release/2.0.1/QCustomPlot.tar.gz
    )
    FetchContent_MakeAvailable(QCustomPlot)
    # TODO: How do we automate this? QCustomPlot isn't a CMake project

    find_package(QCustomPlot REQUIRED)
endif ()


add_library(Visualizer
        QtSpectrogram.h
        QtSpectrogram.cpp 
        QtAudioSystem.cpp 
        QtAudioSystem.h)

target_link_libraries(Visualizer
        ${QCustomPlot_LIBRARIES}
        Qt5::Widgets
        Qt5::PrintSupport
        Audio
        Fourier
        PNG)

target_include_directories(Visualizer PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(Visualizer PRIVATE
          -g)
#         -Werror
#         -Wall
#         -Wextra)
