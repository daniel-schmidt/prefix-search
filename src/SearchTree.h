#pragma once

#include "PrefixTree.h"

namespace TreeSearch
{
    class SearchTree
    {
    public:
        explicit SearchTree(std::vector<std::string> const & word_list_, size_t num_procs_);

        [[nodiscard]] std::vector<std::string> Find(std::string_view prefix) const;

    private:
        NodeContainer full;
        size_t num_procs;
    };
}