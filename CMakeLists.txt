cmake_minimum_required(VERSION 3.20)
project(Practice LANGUAGES C CXX)  # changed from GravitySimulator

set(CMAKE_CXX_STANDARD 17)

# Tell CMake to use vcpkg
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please run CMake with -DCMAKE_TOOLCHAIN_FILE pointing to vcpkg.")
endif()

# Find SDL2 (vcpkg provides config)
find_package(SDL2 CONFIG REQUIRED)

# Manually find SDL2_gfx (vcpkg doesn't provide a config)
find_path(SDL2_GFX_INCLUDE_DIR SDL2/SDL2_gfxPrimitives.h
    HINTS "${CMAKE_TOOLCHAIN_FILE}/../../${CMAKE_VCPKG_TARGET_TRIPLET}/include"
)
find_library(SDL2_GFX_LIBRARY
    NAMES SDL2_gfx
    HINTS "${CMAKE_TOOLCHAIN_FILE}/../../${CMAKE_VCPKG_TARGET_TRIPLET}/lib"
)

if(NOT SDL2_GFX_INCLUDE_DIR OR NOT SDL2_GFX_LIBRARY)
    message(FATAL_ERROR "SDL2_gfx not found in vcpkg. Did you install it?")
endif()

# Add executable
add_executable(Practice   # changed from GravitySimulator
    Learning/SDLPractice/main.cpp
    Learning/SDLPractice/Core/EvenManager.cpp
    Learning/SDLPractice/Core/Initializer.cpp
    Learning/SDLPractice/Core/Window.cpp
)

# Include headers
target_include_directories(Practice PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIR})

# Link libraries
target_link_libraries(Practice PRIVATE SDL2::SDL2 SDL2::SDL2main ${SDL2_GFX_LIBRARY})
