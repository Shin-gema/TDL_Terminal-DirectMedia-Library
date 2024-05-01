cmake_minimum_required(VERSION 3.10)

project(TDL)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/exemple/*.cpp")

add_executable(TDL ${SOURCES})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PNG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(TDL ${PNG_LIBRARY})