
find_package(glfw3 QUIET)
if (NOT glfw3_FOUND)

    include(FetchContent)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(glfw)

endif ()
