
find_package(glfw3 REQUIRED)

add_executable(GLFWApplication
        main.cpp)

target_link_libraries(GLFWApplication
        glfw)
