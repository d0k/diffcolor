#=============================================================================#
# (c) Benjamin Kramer
# This file is distributed under the MIT License. See LICENSE.TXT for details.
#=============================================================================#

project(diffcolor)
cmake_minimum_required(VERSION 2.4)

file(GLOB SRCS *.cpp)
add_executable(diffcolor ${SRCS})
