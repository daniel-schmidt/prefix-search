add_library(
    prefix-search 
    Find.cpp 
    PrefixTree.cpp 
    SearchTree.cpp
    StandardAlgorithms.cpp
    )

target_include_directories(prefix-search PRIVATE .)

target_link_libraries(prefix-search PRIVATE tbb pthread)
target_compile_options(prefix-search PRIVATE -std=c++17 -Wall -DTBB_SUPPRESS_DEPRECATED_MESSAGES=1)