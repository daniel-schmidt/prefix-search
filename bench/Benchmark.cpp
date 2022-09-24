#include "SearchTree.h"
#include "StandardAlgorithms.h"

#include <random>
#include <benchmark/benchmark.h>

using namespace TreeSearch;

namespace
{
    // Generation of the input: returns a randomly ordered list of all possible combinations of the
    // letters in the <alphabet> of a fixed <wordLength>.
    std::vector<std::string> GenerateWordList(std::string_view alphabet, size_t wordLength)
    {        
        size_t const listLength = std::pow(alphabet.size(), wordLength);
        std::vector<std::string> wordList(listLength);
        for(size_t i = 0; i < listLength; i++) {
            size_t remainder = i;
            for(size_t j = 0; j < wordLength; j++) {
                size_t const letterIndex = remainder % alphabet.size();
                wordList[i] += alphabet[letterIndex];
                remainder = remainder / alphabet.size();
            }
        }
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(wordList.begin(), wordList.end(), generator);
        return wordList;
    }


    class RandomWordListBench : public benchmark::Fixture
    {
        public:
        std::vector<std::string> input = GenerateWordList("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4);
        std::string prefix = "ABB";
    };


    BENCHMARK_DEFINE_F(RandomWordListBench, FindTwoLetters_Tree)(benchmark::State& state) 
    {
        size_t num_procs = state.range(0);
        SearchTree underTest{input, num_procs};
        
        for (auto _ : state) {
            std::vector<std::string> result = underTest.Find(prefix);
        }
    }


    BENCHMARK_DEFINE_F(RandomWordListBench, FindTwoLetters_CopyIf)(benchmark::State& state) 
    {
        for (auto _ : state) {
            std::vector<std::string> result = StandardAlgorithms::PrefixSearchCopyIf(input, prefix);
        }
    }

    BENCHMARK_REGISTER_F(RandomWordListBench, FindTwoLetters_Tree)
    ->DenseRange(1u, 6u, 1u)->UseRealTime();
    BENCHMARK_REGISTER_F(RandomWordListBench, FindTwoLetters_CopyIf)->UseRealTime();
}

BENCHMARK_MAIN();