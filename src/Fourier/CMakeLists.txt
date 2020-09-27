find_package(FFTW REQUIRED)
add_library(Fourier
        fourier.h fourier.cpp)

target_include_directories(Fourier PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Fourier 
                ${FFTW_LIBRARIES})
