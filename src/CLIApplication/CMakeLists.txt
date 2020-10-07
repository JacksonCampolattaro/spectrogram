

add_executable(CLIApplication
        main.cpp)

target_link_libraries(CLIApplication
        Audio
        Graphics
        Fourier)

target_include_directories(CLIApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)
