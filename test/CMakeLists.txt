include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/4556086674e4dfae2aa5f042d9e7844fc5ef9b89.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  Tests 
  FindTest.cpp
  SerializeTests.cpp
)

target_include_directories(Tests PRIVATE ../src)

target_link_libraries(
  Tests
  gtest_main
  prefix-search
)

include(GoogleTest)
gtest_discover_tests(Tests)