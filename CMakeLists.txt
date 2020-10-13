cmake_minimum_required(VERSION 3.14)
project(spectrogram)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules)

add_subdirectory(src)
add_subdirectory(test)

find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)

    message(source ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_target(documentation
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating documentation"
            )

endif (DOXYGEN_FOUND)