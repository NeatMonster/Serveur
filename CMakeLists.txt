cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Serveur)

add_subdirectory(lib/json11)
add_subdirectory(lib/polarssl)
add_subdirectory(lib/zlib)

include_directories(lib/)
include_directories(lib/polarssl)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.h)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")
endif()
add_executable(Serveur ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Serveur json11)
target_link_libraries(Serveur polarssl)
target_link_libraries(Serveur zlib)
