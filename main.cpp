#include "Find.h"
#include "PrefixTree.h"
#include "StandardAlgorithms.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

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


int main(int, char**) 
{
    std::string const alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    constexpr size_t wordLength = 5;
    
    Timer timer{};
    std::vector<std::string> wordList = GenerateWordList(alphabet, wordLength);
    std::cout << "Finished generating word list after " << timer.GetElapsedTime() << " s." << std::endl;
    
    std::cout << "\nEnter prefix to search by copy_if: ";
    std::string userInput;
    std::cin >> userInput;
    
    timer.GetElapsedTime();
    std::vector<std::string> matches = StandardAlgorithms::PrefixSearchCopyIf(wordList, userInput);
    std::cout << "Matching words: ";
    std::copy(matches.begin(), matches.end(), std::ostream_iterator<std::string>(std::cout, " "));
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
            std::copy(matches.begin(), matches.end(), std::ostream_iterator<std::string>(std::cout, " "));
            std::cout << std::endl;
        }
        else {
            std::cout << "Nothing found or everything found." << std::endl;
        }
        std::cout << "Found the result by tree search after " << timer.GetElapsedTime() << " s." << std::endl;
        oldPrefix = userInput;
    }
}
