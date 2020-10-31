#cmake_minimum_required(VERSION 3.14)
#project(Qt_Application CXX) # Oops, can't have this bc the only "project" is the top-level one
#include_directories(${CMAKE_BINARY_DIR}) # This might help, it's from 3574 (but only if we properly define the env variable)

# EDIT
# add source for any GUI modules here
set(gui_src
	#settings.h # We might potentially add something like this later
	#output_writer.hpp output_writer.cpp # For Therese's .png writer?
	Qt_Spectrogram.h Qt_Spectrogram.cpp
)

# EDIT
# add source for any GUI tests here
#set(gui_test_src
#	${PROJECT_SOURCE_DIR}/src/QtApplication/QtApp_test.cpp
#)

# main entry point for GUI interface
set(gui_main
	${PROJECT_SOURCE_DIR}/src/QtApplication/main.cpp
)

# Try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# Require a C++11 compiler for all targets
#set(CMAKE_CXX_STANDARD 11) # Does this have to be C++17?
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure Qt
find_package(Qt5 COMPONENTS Core Gui Widgets Charts REQUIRED)
if(Qt5Core_FOUND AND Qt5Gui_FOUND AND Qt5Widgets_FOUND AND Qt5Charts_FOUND)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON) # From Jackson
  set(CMAKE_AUTOUIC ON) # From Jackson
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# --------------------------------------------------------
# Build the application executable and tests if Qt is available
# --------------------------------------------------------
#if (Qt5Widgets_FOUND AND Qt5Test_FOUND)
if(Qt5Core_FOUND AND Qt5Gui_FOUND AND Qt5Widgets_FOUND AND Qt5Charts_FOUND)

	add_executable(Qt_Application ${gui_main} ${gui_src})

	if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
		target_link_libraries(Qt_Application
			# Other Modules' Libraries
			Audio
			Fourier
			
			# Qt Libraries required
			Qt5::Core
			#Qt5::Application
			Qt5::Widgets	# Mandatory
			Qt5::Gui		# Maybe optional? (Trial and error)
			Qt5::Charts		# Mnadatory
			#Qt5::Test		# Ideal, but not necessary
			
			### THIS ### is the important line directly from my
			# 3574 CMake file I was referring to
			pthread gcov
		)
	else(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
		target_link_libraries(Qt_Application
			# Other Modules' Libraries
			Audio
			Fourier
			
			# Qt Libraries required
			Qt5::Core
			#Qt5::Application
			Qt5::Widgets	# Mandatory
			Qt5::Gui		# Maybe optional? (Trial and error)
			Qt5::Charts		# Mandatory
			#Qt5::Test		# Ideal, but not necessary
		)
	endif()
	
	# These next two commands are only from Jackson's format
	target_include_directories(Qt_Application PUBLIC
		${PROJECT_SOURCE_DIR}/src
	)

	target_compile_options(Qt_Application PRIVATE
		-Werror
		-Wall
		-Wextra
	)

#else (Qt5Widgets_FOUND AND Qt5Test_FOUND)
else (Qt5Core_FOUND AND Qt5Gui_FOUND AND Qt5Widgets_FOUND AND Qt5Charts_FOUND)
	message("Qt >= 5.9  needs to be installed to build the spectrogram interface and related tests.")
#endif (Qt5Widgets_FOUND AND Qt5Test_FOUND)
endif (Qt5Core_FOUND AND Qt5Gui_FOUND AND Qt5Widgets_FOUND AND Qt5Charts_FOUND)

