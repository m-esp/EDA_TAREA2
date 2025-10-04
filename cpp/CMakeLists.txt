cmake_minimum_required(VERSION 3.16)
project(poscodes CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recomendado para release
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

add_compile_options(-O3 -Wall -Wextra -march=native)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(poscodes_lib
    src/poscode.cpp
    src/utils.cpp
)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE poscodes_lib)

add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE poscodes_lib)

