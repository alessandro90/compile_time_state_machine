cmake_minimum_required (VERSION 3.10.0)

project(FUNCTIONAL_PROGRAMMING_EXERCISES)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3")
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsuggest-override -Werror)

include_directories(${PROJECT_SOURCE_DIR})

add_definitions(${COMPILER_DEFINITIONS})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(APPEND CMAKE_CXX_CPPCHECK
    "-I${PROJECT_SOURCE_DIR}"
    "--enable=all"
    "--suppress=missingIncludeSystem")
endif()
add_subdirectory(examples)
