#include "SearchTree.h"
#include "StandardAlgorithms.h"

#include <benchmark/benchmark.h>

using namespace TreeSearch;

static void BM_FindTwoLetters_Tree(benchmark::State& state) 
{
    constexpr int num_procs = 1;
    std::vector<std::string> input{"Anananas", "Bratwurst", "Clementine", "Baum", "Bein", "Banane"};
    std::string prefix = "Ba";
    SearchTree underTest{input, num_procs};
    
    for (auto _ : state) {
        std::vector<std::string> result = underTest.Find(prefix);
    }
}

BENCHMARK(BM_FindTwoLetters_Tree);

static void BM_FindTwoLetters_CopyIf(benchmark::State& state) 
{
    constexpr int num_procs = 1;
    std::vector<std::string> input{"Anananas", "Bratwurst", "Clementine", "Baum", "Bein", "Banane"};
    std::string prefix = "Ba";
    
    for (auto _ : state)
        std::vector<std::string> result = StandardAlgorithms::PrefixSearchCopyIf(input, prefix);
}

BENCHMARK(BM_FindTwoLetters_CopyIf);

BENCHMARK_MAIN();