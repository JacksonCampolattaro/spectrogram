
find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)

    message(source ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_target(documentation
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs
            COMMENT "Generating documentation"
            )

endif (DOXYGEN_FOUND)
