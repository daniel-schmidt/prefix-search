cmake_minimum_required(VERSION 3.0.0)
project(ParallelSearch VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ParallelSearch main.cpp Find.cpp PrefixTree.cpp StandardAlgorithms.cpp)
target_link_libraries(ParallelSearch PRIVATE tbb pthread)
target_compile_options(ParallelSearch PRIVATE -std=c++17 -Wall -DTBB_SUPPRESS_DEPRECATED_MESSAGES=1)