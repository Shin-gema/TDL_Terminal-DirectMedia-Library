cmake_minimum_required(VERSION 3.10)

project(libncurse)

add_executable(libncurse testing/main.cpp shape/shape.cpp window/window.cpp texture/texture.cpp input_management/input.cpp logger/logger.cpp
        texture/Vector.hpp window/SignalHandler.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PNG REQUIRED)

target_link_libraries(libncurse ${PNG_LIBRARY})