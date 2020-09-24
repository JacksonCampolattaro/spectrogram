
add_library(Fourier
        placeholder.h placeholder.cpp)

target_include_directories(Fourier PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
