cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

# create project
project(plox)

# add executable
add_executable(${PROJECT_NAME} main.cpp src/lexer.cpp)

# add dependencies
include(cmake/CPM.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE include)
