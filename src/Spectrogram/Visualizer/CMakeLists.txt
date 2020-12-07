
add_library(Visualizer
        Visualizer.h Spectrum.cpp Spectrum.h)

target_link_libraries(Visualizer
        Audio
        Fourier)

target_include_directories(Visualizer PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(Visualizer PRIVATE
        -Werror
        -Wall
        -Wextra)
