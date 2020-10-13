
find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)

    message(source ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_target(documentation
            SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation"
            VERBATIM
            )

endif (DOXYGEN_FOUND)
