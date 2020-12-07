
find_package(Gtkmm)

add_executable(GtkmmApplication
        main.cpp TextSpectrumView.h AudioSystem.h Visualizer/GtkmmVisualizer.cpp Visualizer/GtkmmVisualizer.h Visualizer/SpectrumVisualizer.cpp Visualizer/SpectrumVisualizer.h)

target_link_libraries(GtkmmApplication
        Audio
        Fourier
        Visualizer
        ${GTKMM_LIBRARIES}
        )

target_include_directories(GtkmmApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(GtkmmApplication PRIVATE
        -Werror
        -Wall
        -Wextra)
