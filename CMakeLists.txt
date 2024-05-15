cmake_minimum_required(VERSION 3.10)

project(
        TDL
        VERSION 0.1
        DESCRIPTION "A Terminal Drawing Library"
        LANGUAGES CXX
)

find_package(PNG REQUIRED)

message(STATUS "libpng library found")
message(STATUS "libpng include directories: ${PNG_INCLUDE_DIRS}")
message(STATUS "libpng libraries: ${PNG_LIBRARIES}")


file(GLOB_RECURSE TDL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${PNG_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TDL_EXAMPLES_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(TDL_EXAMPLES_OUTPUT_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/demo)
set(TDL_LIB_DIR                 ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include(${TDL_EXAMPLES_DIR}/CMakeLists.txt)
add_library(
        tdl
        SHARED
        ${TDL_SOURCE}
)
set_target_properties(
        tdl
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${TDL_LIB_DIR}
)
target_include_directories(tdl PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${PNG_INCLUDE_DIRS}
)

target_link_libraries(tdl LINK_PUBLIC ${PNG_LIBRARIES})


install(TARGETS tdl
        EXPORT tdlTargets
        ARCHIVE DESTINATION /usr/lib
)

install(EXPORT tdlTargets
        FILE tdlConfig.cmake
        NAMESPACE tdl::
        DESTINATION /usr/local/lib/cmake/tdl
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION /usr/local/include
        FILES_MATCHING PATTERN "*.hpp"
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/
        DESTINATION /usr/local/lib
        FILES_MATCHING PATTERN "*.so"
)
