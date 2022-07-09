#include "StandardAlgorithms.h"

#include <execution>

namespace StandardAlgorithms
{
    std::vector<std::string> PrefixSearchCopyIf(
        std::vector<std::string> const & wordList, 
        std::string_view searchPrefix)
    {
        std::vector<std::string>  matches(wordList.size());
        auto const endIt = std::copy_if(
            std::execution::par, 
            std::cbegin(wordList), 
            std::cend(wordList), 
            matches.begin(), 
            [=](std::string_view word){
                return word.compare(0, searchPrefix.size(), searchPrefix) == 0;
        });
        matches.erase(endIt, matches.end());
        return matches;
    }
}