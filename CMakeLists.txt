cmake_minimum_required(VERSION 3.14)
project(prefix-search VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(test)

add_executable(InteractiveSearchDemo main.cpp)
target_include_directories(InteractiveSearchDemo PRIVATE src)
target_link_libraries(InteractiveSearchDemo PRIVATE prefix-search)