
find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)

    add_custom_target(documentation
            SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation"
            VERBATIM
            )

    find_package(mcss REQUIRED)

    add_custom_target(documentation-pretty
            SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-mcss
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/mcss/src/mcss/documentation/doxygen.py ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating pretty documentation"
            VERBATIM
            )

    add_dependencies(documentation-pretty
            mcss)

endif (DOXYGEN_FOUND)
