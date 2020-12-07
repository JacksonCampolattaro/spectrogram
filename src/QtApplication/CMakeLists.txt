set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(QCustomPlot REQUIRED)

find_package(toml QUIET)
if (NOT toml_FOUND)

	include(FetchContent)
	FetchContent_Declare(
			toml
			GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
			GIT_TAG        v3.6.0)
	FetchContent_MakeAvailable(toml)

endif ()


add_executable(QtApplication
		main.cpp
        QtAudioSystem.h QtAudioSystem.cpp
		QtApplication.h QtApplication.cpp
		Visualizer/QtSpectrogram.h Visualizer/QtSpectrogram.cpp
		Settings/Settings.h Settings/Settings.cpp
		PNG/Writer.h PNG/Writer.cpp)

target_link_libraries(QtApplication
        Qt5::Widgets
		toml11::toml11
		${QCustomPlot_LIBRARIES}
		Audio
		Fourier)

target_include_directories(QtApplication PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

# target_compile_options(QtApplication PRIVATE
#         -Werror
#         -Wall
#         -Wextra)
