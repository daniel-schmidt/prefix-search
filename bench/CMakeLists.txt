add_executable(
  Benchmarks 
  Benchmark.cpp
)

target_include_directories(Benchmarks PRIVATE ../src)

target_link_libraries(
  Benchmarks
  benchmark::benchmark
  prefix-search
)