add_executable(
  Tests 
  FindTest.cpp
  SerializeTests.cpp
)

target_include_directories(Tests PRIVATE ../src)

target_link_libraries(
  Tests
  gmock_main
  prefix-search
)

include(GoogleTest)
gtest_discover_tests(Tests)