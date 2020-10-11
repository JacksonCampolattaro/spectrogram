cmake_minimum_required(VERSION 3.14)
project(Qt_Application CXX)

# Try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# Require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure Qt
find_package(Qt5 COMPONENTS Widgets Test REQUIRED)
if(Qt5Widgets_FOUND AND Qt5Test_FOUND)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON) # From Jackson
  set(CMAKE_AUTOUIC ON) # From Jackson
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Build the program
add_executable(Qt_Application
  # Add other module files here as needed
  Qt_Spectrogram.h Qt_Spectrogram.cpp
  main.cpp
)

target_link_libraries(Qt_Application
  #Qt5::Application
  Qt5::Widgets
  Qt5::Gui
  #Qt5::Charts # Might need this later
  Qt5::Test # Ideally for Sprint 1, but not necessary
)
