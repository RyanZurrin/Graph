cmake_minimum_required(VERSION 3.16)
project(Graph C)

set(CMAKE_C_STANDARD 99)

add_executable(Graph Graph.c Graph2.c graph3.c Queue.h Queue.c Heap.h Heap.c Graph.h graphDriver.c)