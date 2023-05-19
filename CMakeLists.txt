cmake_minimum_required(VERSION 3.25)
project(RayTracerChallenge)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("tests/")

add_executable(RayTracerChallenge src/main.cpp src/math/tuple.hpp src/math/utility.hpp src/canvas.hpp src/color.hpp src/io/ppm.hpp src/pixel.hpp src/math/matrix.hpp src/math/transformation.hpp)

