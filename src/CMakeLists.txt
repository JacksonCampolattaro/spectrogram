
add_subdirectory(Spectrogram)

option(BUILD_CLI "Build CLI based application" ON)
if (BUILD_CLI)
    add_subdirectory(CLIApplication)
endif ()

option(BUILD_QT "Build Qt based application" ON)
if (BUILD_QT)
    add_subdirectory(QtApplication)
endif ()

option(BUILD_GTKMM "Build Gtkmm based application" ON)
if (BUILD_GTKMM)
    add_subdirectory(GtkmmApplication)
endif ()
