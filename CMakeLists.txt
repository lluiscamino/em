cmake_minimum_required(VERSION 3.28)
project(em
  VERSION 1.0
  DESCRIPTION "Em - A small language for mathematical operations"
  LANGUAGES CXX
)

# CMake configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies - None so far

# Library
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(Em SHARED ${SOURCES})

# Executable (CLI application)
add_executable(em src/main.cpp)
target_link_libraries(em PRIVATE Em)

# Testing
add_subdirectory(test)
