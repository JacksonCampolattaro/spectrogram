
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