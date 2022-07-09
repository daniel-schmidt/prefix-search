#include "SearchTree.h"

#include "Find.h"

namespace TreeSearch
{
    SearchTree::SearchTree(std::vector<std::string> const & word_list_, size_t num_procs_) 
    : full(VecToTree(word_list_, num_procs_))
    , num_procs(num_procs_)
    {

    }


    std::vector<std::string> SearchTree::Find(std::string_view prefix) const 
    {
        NodeContainer subtree = TreeSearch::Find(prefix, full, num_procs);
        return TreeToVec(prefix, subtree);
    }
}