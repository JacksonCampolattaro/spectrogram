#find_package(FFTW REQUIRED)

add_library(Settings
        Settings.h Settings.cpp)

target_include_directories(Settings PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Settings
        )

target_compile_options(Settings PRIVATE
        -Werror
        -Wall
        -Wextra)
