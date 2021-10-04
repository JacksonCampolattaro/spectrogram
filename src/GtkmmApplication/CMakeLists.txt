
find_package(Gtkmm)

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

add_executable(GtkmmApplication
        main.cpp
        AudioSystem.h
        Visualizer/GtkmmVisualizer.cpp Visualizer/GtkmmVisualizer.h
        Visualizer/TextSpectrumVisualizer.cpp Visualizer/TextSpectrumVisualizer.h
        mainwindow.glade Visualizer/BarSpectrumVisualizer.cpp Visualizer/BarSpectrumVisualizer.h Visualizer/SpectrogramVisualizer.cpp Visualizer/SpectrogramVisualizer.h)

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
