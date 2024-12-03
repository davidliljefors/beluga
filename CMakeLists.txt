# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(beluga LANGUAGES CXX)

set(LIBRARIES
        imgui
        EASTL
        )

# Add external dependencies
add_subdirectory(dependencies/EASTL)
add_subdirectory(dependencies/imgui)

# Enable multi-processor compilation only for Visual Studio
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp"
    "src/*.h"
)

# Add the executable and link source files
add_executable(beluga ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})

target_include_directories(beluga PRIVATE dependencies/EASTL/include dependencies/imgui/include)  # Add include directories

# target_link_libraries(beluga PRIVATE dependencies/EASTL/EASTL dependencies/imgui/imgui d3d12.lib dxgi.lib d3dcompiler.lib)

add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

