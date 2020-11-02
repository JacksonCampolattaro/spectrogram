find_package(FFTW REQUIRED)

add_library(Fourier
        processor.h processor.cpp FrequencyDomainBuffer.cpp FrequencyDomainBuffer.h Transformer.cpp Transformer.h)

target_include_directories(Fourier PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Fourier
                ${FFTW_LIBRARIES})

target_compile_options(Fourier PRIVATE
        -Werror
        -Wall
        -Wextra)
