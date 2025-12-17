cmake_minimum_required(VERSION 3.10)

project(CliChess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(chess ${SOURCES})
