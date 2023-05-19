cmake_minimum_required(VERSION 3.25)
project(RayTracerChallenge_Test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE TEST_SOURCES "./*.cpp")
include_directories("../src/math")
include_directories("../src/utility")
include_directories("../src/")

find_package(doctest REQUIRED)

add_executable(RayTracerChallenge_Test_Tuple tuple.cpp)
target_compile_features(RayTracerChallenge_Test_Tuple PRIVATE cxx_std_17)
target_link_libraries(RayTracerChallenge_Test_Tuple PRIVATE doctest::doctest)

add_executable(RayTracerChallenge_Test_Matrix matrix.cpp)
target_compile_features(RayTracerChallenge_Test_Matrix PRIVATE cxx_std_17)
target_link_libraries(RayTracerChallenge_Test_Matrix PRIVATE doctest::doctest)

add_executable(RayTracerChallenge_Test_Projectiles drawings.cpp)
target_compile_features(RayTracerChallenge_Test_Projectiles PRIVATE cxx_std_17)
target_link_libraries(RayTracerChallenge_Test_Projectiles PRIVATE doctest::doctest)

add_executable(RayTracerChallenge_Test_Canvas canvas.cpp)
target_compile_features(RayTracerChallenge_Test_Canvas PRIVATE cxx_std_17)
target_link_libraries(RayTracerChallenge_Test_Canvas PRIVATE doctest::doctest)
