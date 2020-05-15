cmake_minimum_required(VERSION 3.10.2)

project(LTS_V2 C CXX)

include_directories(./)

add_executable(binary main.cpp)

add_subdirectory(circuit)
add_subdirectory(component)
add_subdirectory(input)
add_subdirectory(output)

target_link_libraries(binary input output exception circuit component)