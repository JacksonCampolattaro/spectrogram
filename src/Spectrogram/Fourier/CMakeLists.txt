find_package(FFTW)
add_library(Fourier
        processor.h processor.cpp)

target_include_directories(Fourier PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Fourier
                ${FFTW_LIBRARIES})
