
# Sets the possible install locations
set(LIBSOUNDIO_HINTS
        ${LIBSOUNDIO_ROOT}
        $ENV{LIBSOUNDIO_ROOT}
        )
set(LIBSOUNDIO_PATHS
        /usr
        /usr/local
        /usr/local/
        )

# Finds the include directories
find_path(LIBSOUNDIO_INCLUDE_DIRS
        NAMES soundio.h
        HINTS ${LIBSOUNDIO_HINTS}
        PATH_SUFFIXES include api inc include/x86_64 include/x64 include/soundio
        PATHS ${LIBSOUNDIO_PATHS}
        )
mark_as_advanced(LIBSOUNDIO_INCLUDE_DIRS)
#message(${LIBSOUNDIO_INCLUDE_DIRS})

# Finds the library
unset(LIBSOUNDIO_LIBRARIES CACHE)
find_library(LIBSOUNDIO_LIBRARIES
        NAMES libsoundio.so
        HINTS ${LIBSOUNDIO_HINTS}
        PATH_SUFFIXES lib lib64 lib/x86_64 lib/x64 lib/x86 lib/Win32
        PATHS ${LIBSOUNDIO_PATHS}
        )
#set(LIBSOUNDIO_LIBRARIES "/usr/lib64/libsoundio.so")
mark_as_advanced(LIBSOUNDIO_LIBRARIES)

# Notification messages
if(NOT LIBSOUNDIO_INCLUDE_DIRS)
    message(STATUS "Could NOT find 'soundio/soundio.h', install Libsoundio or set LIBSOUNDIO_ROOT")
endif()
if(NOT LIBSOUNDIO_LIBRARIES)
    message(STATUS "Could NOT find the Libsoundio library, install it or set LIBSOUNDIO_ROOT")
endif()

# Determines whether or not the library was found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libsoundio DEFAULT_MSG LIBSOUNDIO_INCLUDE_DIRS LIBSOUNDIO_LIBRARIES)
