
find_package(OpenGL)

add_library(Graphics
        placeholder.h
        placeholder.cpp)

target_include_directories(Graphics PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Graphics
        OpenGL::GL)
