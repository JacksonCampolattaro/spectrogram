
# Sets the possible install locations
set(QCustomPlot_HINTS
        ${QCustomPlot_HINTS}
        $ENV{QCustomPlot_HINTS}
        )
set(QCustomPlot_PATHS
        /usr
        /usr/local
        /usr/local/
        )

# Finds the include directories
find_path(QCustomPlot_INCLUDE_DIRS
        NAMES qcustomplot.h
        HINTS ${QCustomPlot_HINTS}
        PATH_SUFFIXES include api inc include/x86_64 include/x64
        PATHS ${QCustomPlot_PATHS}
        )
mark_as_advanced(QCustomPlot_INCLUDE_DIRS)
#message(${LIBSOUNDIO_INCLUDE_DIRS})

# Finds the library
unset(QCustomPlot_LIBRARIES CACHE)
find_library(QCustomPlot_LIBRARIES
        NAMES libqcustomplot-qt5.so libqcustomplot.so qcustomplot.so
        HINTS ${QCustomPlot_HINTS}
        PATH_SUFFIXES lib lib64 lib/x86_64 lib/x64 lib/x86 lib/Win32
        PATHS ${QCustomPlot_PATHS}
        )
#set(LIBSOUNDIO_LIBRARIES "/usr/lib64/libsoundio.so")
mark_as_advanced(QCustomPlot_LIBRARIES)

# Notification messages
if(NOT QCustomPlot_INCLUDE_DIRS)
    message(STATUS "Could NOT find 'soundio/soundio.h', install qcustomplot or set QCustomPlot_ROOT")
endif()
if(NOT QCustomPlot_LIBRARIES)
    message(STATUS "Could NOT find the qcustomplot library, install it or set QCustomPlot_ROOT")
endif()

# Determines whether or not the library was found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QCustomPlot DEFAULT_MSG QCustomPlot_INCLUDE_DIRS QCustomPlot_LIBRARIES)
