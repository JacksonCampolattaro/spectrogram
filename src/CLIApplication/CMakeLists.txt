

add_executable(CLIApplication
        main.cpp)

target_link_libraries(CLIApplication
        Audio
        Fourier)

target_include_directories(CLIApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_compile_options(CLIApplication PRIVATE
        -Werror
        -Wall
        -Wextra)
