set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

# TODO: I Don't love this, but it does work...
include(FetchContent)
FetchContent_Declare(
        QCustomPlot
        URL https://www.qcustomplot.com/release/2.0.1/QCustomPlot-source.tar.gz
)
FetchContent_MakeAvailable(QCustomPlot)
add_library(QCustomPlot "${qcustomplot_SOURCE_DIR}/qcustomplot.h" "${qcustomplot_SOURCE_DIR}/qcustomplot.cpp")
target_link_libraries(QCustomPlot PUBLIC
        Qt5::Widgets)


add_library(PNG
        Writer.h
        Writer.cpp)

target_include_directories(PNG PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${qcustomplot_SOURCE_DIR})

target_link_libraries(PNG
        PUBLIC
        QCustomPlot
        PRIVATE
        Qt5::Widgets
        Qt5::PrintSupport)

target_compile_options(PNG PRIVATE
        -g)
#         -Werror
#         -Wall
#         -Wextra)
