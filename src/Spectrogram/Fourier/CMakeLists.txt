
add_library(Fourier
        placeholder.h placeholder.cpp)

target_include_directories(Fourier PUBLIC
        ${CMAKE_SOURCE_DIR}/src)
