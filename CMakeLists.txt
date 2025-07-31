cmake_minimum_required(VERSION 3.17.0)

project(graph VERSION 0.1)
set (CMAKE_CXX_STANDARD 23)

# Configure compiler
set(DIR_INCLUDE "include")
set(DIR_SOURCE "src")
set(DIR_TESTS "tests")

# set(SRC_GRAPH_LIB
#     ${DIR_SOURCE}/GraphBFS.cpp
#     ${DIR_SOURCE}/GraphDFS.cpp
# )

# add_library(${PROJECT_NAME} STATIC ${SRC_GRAPH_LIB})
# target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_INCLUDE})
# target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_SOURCE})

add_executable(TestDFS ${DIR_TESTS}/TestDFS.cpp)
target_include_directories(TestDFS PUBLIC ${DIR_INCLUDE})

add_executable(TestBFS ${DIR_TESTS}/TestBFS.cpp)
target_include_directories(TestBFS PUBLIC ${DIR_INCLUDE})

# target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
