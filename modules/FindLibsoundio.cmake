
# Sets the possible install locations
set(Libsoundio_HINTS
        ${Libsoundio_ROOT}
        $ENV{Libsoundio_ROOT}
        )
set(Libsoundio_PATHS
        /usr
        /usr/local
        /usr/local/
        )

# Finds the include directories
find_path(Libsoundio_INCLUDE_DIRS
        NAMES soundio.h
        HINTS ${Libsoundio_HINTS}
        PATH_SUFFIXES include api inc include/x86_64 include/x64 include/soundio
        PATHS ${Libsoundio_PATHS}
        )
mark_as_advanced(Libsoundio_INCLUDE_DIRS)
#message(${Libsoundio_INCLUDE_DIRS})

# Finds the library
unset(Libsoundio_LIBRARIES CACHE)
find_library(Libsoundio_LIBRARIES
        NAMES libsoundio.so
        HINTS ${Libsoundio_HINTS}
        PATH_SUFFIXES lib lib64 lib/x86_64 lib/x64 lib/x86 lib/Win32
        PATHS ${Libsoundio_PATHS}
        )
#set(Libsoundio_LIBRARIES "/usr/lib64/libsoundio.so")
mark_as_advanced(Libsoundio_LIBRARIES)

# Notification messages
if(NOT Libsoundio_INCLUDE_DIRS)
    message(STATUS "Could NOT find 'soundio/soundio.h', install Libsoundio or set Libsoundio_ROOT")
endif()
if(NOT Libsoundio_LIBRARIES)
    message(STATUS "Could NOT find the Libsoundio library, install it or set Libsoundio_ROOT")
endif()

# Determines whether or not the library was found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libsoundio DEFAULT_MSG Libsoundio_INCLUDE_DIRS Libsoundio_LIBRARIES)
