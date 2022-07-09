#include<vector>
#include<string>

namespace StandardAlgorithms
{
    std::vector<std::string> PrefixSearchCopyIf(
        std::vector<std::string> const & wordList, 
        std::string_view searchPrefix);
}