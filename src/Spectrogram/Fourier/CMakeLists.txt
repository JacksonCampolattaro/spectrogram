find_package(FFTW QUIET)
if (NOT FFTW_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            fftw
            URL http://fftw.org/fftw-3.3.8.tar.gz
    )
    FetchContent_MakeAvailable(fftw)

endif ()

add_library(Fourier
        processor.h processor.cpp)

target_include_directories(Fourier PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Fourier
                ${FFTW_LIBRARIES})
