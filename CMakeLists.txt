cmake_minimum_required(VERSION 3.10)

project(unittest)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(encode/include)
link_directories(encode/lib)

add_executable(unittest main.cc)

target_link_libraries(unittest libencode.so)

