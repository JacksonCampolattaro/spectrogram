
find_package(Catch2)

add_executable(test main.cpp
        test_Fourier_Process.cpp
        test_Audio_System.cpp)

target_link_libraries(test LINK_PUBLIC
        Audio
        Graphics
        Fourier
        Catch2::Catch2)

target_include_directories(test PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src)

