# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(rd LANGUAGES CXX)

# Add external dependencies
add_subdirectory(dependencies/EASTL)
add_subdirectory(dependencies/EAThread)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the DirectX 12 library
find_path(DIRECTX12_INCLUDE_DIR d3d12.h
          PATHS "$ENV{DXSDK_DIR}/Include" "C:/Program Files (x86)/Windows Kits/10/Include"
          DOC "Path to the DirectX 12 headers")

find_library(DIRECTX12_LIBRARY d3d12
             PATHS "$ENV{DXSDK_DIR}/Lib" "C:/Program Files (x86)/Windows Kits/10/Lib"
             DOC "Path to the DirectX 12 library")

find_library(DXGI_LIBRARY dxgi
             PATHS "$ENV{DXSDK_DIR}/Lib" "C:/Program Files (x86)/Windows Kits/10/Lib"
             DOC "Path to the DXGI library for DirectX 12")

if (NOT DIRECTX12_INCLUDE_DIR OR NOT DIRECTX12_LIBRARY OR NOT DXGI_LIBRARY)
    message(FATAL_ERROR "DirectX 12 SDK not found")
endif()

# Add include directories
include_directories(${DIRECTX12_INCLUDE_DIR})

# Gather all .cpp files in the src directory
file(GLOB SRC_FILES src/*.cpp)

# Add the executable and link source files
add_executable(DirectX12App ${SRC_FILES})

# Link DirectX 12 libraries
target_link_libraries(DirectX12App PRIVATE ${DIRECTX12_LIBRARY} ${DXGI_LIBRARY})
