
find_package(Catch2 REQUIRED)

add_executable(test main.cpp
                test_Fourier_Process.cpp)

target_link_libraries(test LINK_PUBLIC
        Audio
        Graphics
        Fourier)

target_include_directories(test PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src)