
include(${PROJECT_SOURCE_DIR}/cmake/glfw3.cmake)

add_executable(GLFWApplication
        main.cpp)

target_link_libraries(GLFWApplication
        Audio
        Graphics
        Fourier
        glfw)

target_include_directories(GLFWApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)
