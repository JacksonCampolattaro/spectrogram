
include(ExternalProject)
ExternalProject_Add(
        mcss

        PREFIX mcss
        GIT_REPOSITORY https://github.com/mosra/m.css.git
        GIT_SHALLOW ON

        CONFIGURE_COMMAND ""
        UPDATE_COMMAND    ""
        INSTALL_COMMAND   ""
        BUILD_COMMAND     ""
)

set(MCSS_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/mcss/src/mcss/documentation/doxygen.py)

message(${MCSS_EXECUTABLE})
