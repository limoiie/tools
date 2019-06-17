cmake_minimum_required(VERSION 3.10)
project(ascii2bin)

add_definitions(-std=c++11)

include_directories(.)
include_directories(ext/clipp/include)

add_subdirectory(ascii2bin)
add_subdirectory(hex2ascii)
add_subdirectory(moss)
