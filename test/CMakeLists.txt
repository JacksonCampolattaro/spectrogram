
find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v2.13.1)
    FetchContent_MakeAvailable(Catch2)

endif ()

add_executable(test main.cpp
        test_Fourier_Process.cpp
        test_Audio_System.cpp
        test_Settings.cpp)

target_link_libraries(test LINK_PUBLIC
        Audio
        Fourier
        Settings
        Catch2::Catch2)

target_include_directories(test PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(test PRIVATE
        -Werror
        -Wall
        -Wextra)
