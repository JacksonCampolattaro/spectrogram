
find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            catch
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(catch)

endif ()

add_executable(test main.cpp
        test_Fourier_Process.cpp
        test_Audio_System.cpp)

target_link_libraries(test LINK_PUBLIC
        Audio
        Fourier
        Catch2::Catch2)

target_include_directories(test PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(test PRIVATE
        -Werror
        -Wall
        -Wextra)
