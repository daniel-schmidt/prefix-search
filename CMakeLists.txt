cmake_minimum_required(VERSION 3.14)
project(prefix-search VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.12.x
)

FetchContent_Declare(
  googlebench
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.7.0
)

FetchContent_MakeAvailable(
    googletest
    googlebench
)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)

add_executable(InteractiveSearchDemo main.cpp)
target_include_directories(InteractiveSearchDemo PRIVATE src)
target_link_libraries(InteractiveSearchDemo PRIVATE prefix-search)