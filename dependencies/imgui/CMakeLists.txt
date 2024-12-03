cmake_minimum_required(VERSION 3.23)
set(LIB_NAME imgui)

file(GLOB LIB_SOURCES "src/*.cpp")
file(GLOB LIB_HEADERS "include/*.h")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

add_library(${LIB_NAME} ${LIB_SOURCES} ${LIB_HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
