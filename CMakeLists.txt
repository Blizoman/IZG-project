cmake_minimum_required(VERSION 3.10)
project(IZG_Project VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(izg_project ${SOURCES})

# Set output directory
set_target_properties(izg_project PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
