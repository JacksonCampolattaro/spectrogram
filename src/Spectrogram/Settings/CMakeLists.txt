
find_package(toml QUIET)
if (NOT toml_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            toml
            GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
            GIT_TAG        v3.6.0)
    FetchContent_MakeAvailable(toml)

endif ()

add_library(Settings
        Settings.h Settings.cpp)

target_include_directories(Settings PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Settings
        toml11::toml11
        )

target_compile_options(Settings PRIVATE
        -Werror
        -Wall
        -Wextra)
