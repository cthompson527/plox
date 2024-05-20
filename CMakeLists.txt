cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

# create project
project(plox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add executable
add_executable(${PROJECT_NAME} main.cpp src/lexer.cpp)

# add dependencies
include(cmake/CPM.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${PROJECT_NAME} PUBLIC
  -Weverything
  -Werror
  -Wno-c++98-compat
  -Wno-missing-prototypes
  -Wno-unsafe-buffer-usage
)
