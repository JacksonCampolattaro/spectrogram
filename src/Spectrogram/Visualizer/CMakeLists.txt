
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

add_library(Visualizer
        QtSpectrogram.h
        QtSpectrogram.cpp 
        QtAudioSystem.cpp 
        QtAudioSystem.h)

target_link_libraries(Visualizer
#        ${QCustomPlot_LIBRARIES}
        QCustomPlot
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
