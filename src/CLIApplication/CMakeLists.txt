

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


add_executable(loss_test
        test.cpp)

target_link_libraries(loss_test
        Audio
        Fourier)

target_include_directories(loss_test PUBLIC
        ${PROJECT_SOURCE_DIR}/src)
