
find_package(Gtkmm)

add_executable(GtkmmApplication
        main.cpp TextSpectrumView.h AudioSystem.h)

target_link_libraries(GtkmmApplication
        Audio
        Fourier
        ${GTKMM_LIBRARIES}
        )

target_include_directories(GtkmmApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(GtkmmApplication PRIVATE
        -Werror
        -Wall
        -Wextra)
