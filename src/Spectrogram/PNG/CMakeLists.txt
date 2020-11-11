set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(QCustomPlot REQUIRED)


add_library(PNG
        Writer.h
        Writer.cpp)

target_include_directories(PNG PUBLIC
        ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(PNG
        ${QCustomPlot_LIBRARIES}
        Qt5::Widgets
        Qt5::PrintSupport)

target_compile_options(PNG PRIVATE
          -g)
#         -Werror
#         -Wall
#         -Wextra)
