# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(beluga LANGUAGES CXX)

# Add external dependencies
add_subdirectory(dependencies/EASTL)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp"
    "src/*.h"
)

# Add the executable and link source files
add_executable(beluga ${SRC_FILES})
target_link_libraries(beluga PRIVATE d3d12.lib dxgi.lib d3dcompiler.lib)
