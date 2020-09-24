
find_package(OpenGL REQUIRED)

add_library(Graphics
        placeholder.h
        placeholder.cpp)

target_include_directories(Graphics PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Graphics
        OpenGL::GL)
