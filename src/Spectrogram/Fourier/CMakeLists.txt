find_package(FFTW REQUIRED)
add_library(Fourier
        fourier.h fourier.cpp)

target_include_directories(Fourier PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Fourier
                ${FFTW_LIBRARIES})
