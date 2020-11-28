set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

find_package(QCustomPlot REQUIRED)
#if (NOT QCustomPlot)
#
#    include(FetchContent)
#    FetchContent_Declare(
#            QCustomPlot
#            URL https://www.qcustomplot.com/release/2.0.1/QCustomPlot.tar.gz
#    )
#    FetchContent_MakeAvailable(QCustomPlot)
#
#    # TODO: How do we automate this? QCustomPlot isn't a CMake project
#endif ()


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
