cmake_minimum_required(VERSION 3.10)

project(encode)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory(./ Encode)

include_directories(include)
link_directories(lib)

add_library(encode SHARED ${Encode})

target_link_libraries(encode libCode.so)