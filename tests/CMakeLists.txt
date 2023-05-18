cmake_minimum_required(VERSION 3.25)
project(RayTracerChallenge_Test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE TEST_SOURCES "./*.cpp")
include_directories("../src/math")
include_directories("../src/utility")

find_package(doctest REQUIRED)

add_executable(RayTracerChallenge_Test tuple_4.cpp)
add_executable(RayTracerChallenge_Test1 projectiles_playground.cpp)

set_target_properties(RayTracerChallenge_Test PROPERTIES OUTPUT_NAME "test")

target_compile_features(RayTracerChallenge_Test PRIVATE cxx_std_17)
target_link_libraries(RayTracerChallenge_Test PRIVATE doctest::doctest)

target_compile_features(RayTracerChallenge_Test1 PRIVATE cxx_std_17)
target_link_libraries(RayTracerChallenge_Test1 PRIVATE doctest::doctest)