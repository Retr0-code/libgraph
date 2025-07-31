cmake_minimum_required(VERSION 3.17.0)

project(graph VERSION 0.1)
set (CMAKE_CXX_STANDARD 23)

# Configure compiler
set(DIR_INCLUDE "include")
set(DIR_SOURCE "src")
set(DIR_TESTS "tests")

add_executable(TestDFS ${DIR_TESTS}/TestDFS.cpp)
target_include_directories(TestDFS PUBLIC ${DIR_INCLUDE})

add_executable(TestBFS ${DIR_TESTS}/TestBFS.cpp)
target_include_directories(TestBFS PUBLIC ${DIR_INCLUDE})

add_executable(TestDijkstra ${DIR_TESTS}/TestDijkstra.cpp)
target_include_directories(TestDijkstra PUBLIC ${DIR_INCLUDE})
