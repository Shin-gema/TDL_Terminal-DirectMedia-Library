cmake_minimum_required(VERSION 3.10)

project(
        TDL
        VERSION 0.1
        DESCRIPTION "A Terminal Drawing Library"
        LANGUAGES CXX
)

# Find the libpng library
find_package(PNG REQUIRED)

message(STATUS "PNG_FOUND: ${PNG_FOUND}")
message(STATUS "PNG_LIBRARIES: ${PNG_LIBRARIES}")
message(STATUS "PNG_INCLUDE_DIRS: ${PNG_INCLUDE_DIRS}")

file(GLOB_RECURSE TDL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TDL_EXAMPLES_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(TDL_EXAMPLES_OUTPUT_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/demo)
set(TDL_LIB_DIR                 ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include(${TDL_EXAMPLES_DIR}/CMakeLists.txt)
add_library(
        tdl
        STATIC
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
)
include_directories(${PNG_INCLUDE_DIRS})
foreach (inc ${PNG_INCLUDE_DIRS})
    target_include_directories(tdl PUBLIC ${inc})
    message(STATUS "Including ${inc}")
endforeach ()
foreach (lib ${PNG_LIBRARIES})
    target_link_libraries(tdl PUBLIC ${lib})
    message(STATUS "Linking ${lib}")
endforeach ()

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