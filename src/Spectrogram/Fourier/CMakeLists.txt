find_package(FFTW QUIET)
if (NOT FFTW_FOUND)

    # TODO: This isn't working yet!
    include(FetchContent)
    FetchContent_Declare(
            FFTW
            URL http://www.fftw.org/fftw-3.3.8.tar.gz
    )
    FetchContent_MakeAvailable(FFTW)

endif ()

add_library(Fourier
        processor.h processor.cpp FrequencyDomainBuffer.cpp FrequencyDomainBuffer.h Transformer.cpp Transformer.h)

target_include_directories(Fourier PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${fftw_SOURCE_DIR})

target_link_libraries(Fourier
                ${FFTW_LIBRARIES})

target_compile_options(Fourier PRIVATE
        -Werror
        -Wall
        -Wextra)
