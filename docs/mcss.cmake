
include(FetchContent)
FetchContent_Declare(
        mcss
        GIT_REPOSITORY https://github.com/mosra/m.css.git
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(mcss)

set(MCSS_EXECUTABLE ${mcss_SOURCE_DIR}/documentation/doxygen.py)
