#include "Find.h"
#include "PrefixTree.h"
#include "StandardAlgorithms.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace
{
    // Small stop watch class, returning the elapsed time since the last call in seconds.
    class Timer
    {
    public:
        double GetElapsedTime() 
        {
            auto const stop = std::chrono::steady_clock::now();
            auto const oldStart = start;
            start = stop;
            std::chrono::duration<double> elapsed = stop - oldStart;
            return elapsed.count();
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    };
}


int main(int argc, char** argv) 
{   
    std::ifstream input_file{argv[1]};
    std::string line;
    std::vector<std::string> wordList = {};
    while(std::getline(input_file, line)) {
        wordList.push_back(std::move(line));
    }
    std::ranges::copy(wordList, std::ostream_iterator<std::string>(std::cout, " "));
    
    std::cout << "\nEnter prefix to search by copy_if: ";
    std::string userInput;
    std::cin >> userInput;
    
    Timer timer{};
    std::vector<std::string> matches = StandardAlgorithms::PrefixSearchCopyIf(wordList, userInput);
    std::cout << "Matching words: ";
    std::ranges::copy(matches, std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Found the result by copy_if after " << timer.GetElapsedTime() << " s." << std::endl;

    size_t constexpr numTasks = 4;
    auto tree = TreeSearch::VecToTree(wordList, numTasks);
    std::cout << "\nInitialized prefix search after " << timer.GetElapsedTime() << " s." << std::endl;

    std::string oldPrefix{};
    for(size_t i = 0; i < 2; i++) {
        std::cout << "\nEnter prefix to search in prefix tree: ";
        std::cin >> userInput;

        timer.GetElapsedTime();
        tree = TreeSearch::Find(userInput, tree, numTasks);
        if(!tree.empty()) {
            matches = TreeSearch::TreeToVec(oldPrefix + userInput, tree);
            std::cout << "Matching words: ";
            std::ranges::copy(matches, std::ostream_iterator<std::string>(std::cout, " "));
            std::cout << std::endl;
        }
        else {
            std::cout << "Nothing found or everything found." << std::endl;
        }
        std::cout << "Found the result by tree search after " << timer.GetElapsedTime() << " s." << std::endl;
        oldPrefix = userInput;
    }
}
