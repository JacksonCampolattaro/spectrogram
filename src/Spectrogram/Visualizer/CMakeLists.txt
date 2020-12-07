
add_library(Visualizer)

target_link_libraries(Visualizer
        Audio
        Fourier)

target_include_directories(Visualizer PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(Visualizer PRIVATE
         -Werror
         -Wall
         -Wextra)
