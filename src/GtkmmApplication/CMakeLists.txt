
find_package(Gtkmm)

add_executable(GtkmmApplication
        main.cpp
        AudioSystem.h
        Visualizer/GtkmmVisualizer.cpp Visualizer/GtkmmVisualizer.h
        Visualizer/TextSpectrumVisualizer.cpp Visualizer/TextSpectrumVisualizer.h)

target_link_libraries(GtkmmApplication
        Audio
        Visualizer
        ${GTKMM_LIBRARIES}
        )

target_include_directories(GtkmmApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(GtkmmApplication PRIVATE
        -Werror
        -Wall
        -Wextra)
