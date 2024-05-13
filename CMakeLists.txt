cmake_minimum_required(VERSION 3.10)

project(
    TDL
    VERSION 0.1
    DESCRIPTION "A Terminal Drawing Library"
    LANGUAGES CXX
)

find_package(PNG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TDL_EXAMPLES_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(TDL_EXAMPLES_OUTPUT_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/demo)

include(${TDL_EXAMPLES_DIR}/CMakeLists.txt)