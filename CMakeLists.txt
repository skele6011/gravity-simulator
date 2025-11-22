cmake_minimum_required(VERSION 3.10)
project(GravitySimulator)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include SDL2_gfx headers
include_directories(/usr/include/SDL2)

# Collect all source files recursively in SDLPractice
file(GLOB_RECURSE SOURCES "Learning/SDLPractice/*.cpp")

# Create the executable
add_executable(GravitySimulator ${SOURCES})

# Link SDL2 and SDL2_gfx libraries
target_link_libraries(GravitySimulator ${SDL2_LIBRARIES} SDL2_gfx)
