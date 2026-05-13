cmake_minimum_required( VERSION 3.20)
project(esercitazione6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

set(SRC_FILES test_graph.cpp test_edge.cpp)

add_executable(test_graph test_graph.cpp)
add_executable(test_edge test_edge.cpp)

enable_testing()

add_test(NAME graph_test COMMAND test_graph)
add_test(NAME edge_test COMMAND test_edge)