project(diffcolor)
cmake_minimum_required(VERSION 2.4)

file(GLOB SRCS *.cpp)
add_executable(diffcolor ${SRCS})
