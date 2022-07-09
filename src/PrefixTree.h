#include <vector>
#include <string>

namespace TreeSearch
{
    //-------------------------------------------------------------------------------------------------
    // Prefix Tree (Trie) structure for parallel breadth-first prefix search
    //-------------------------------------------------------------------------------------------------
    
    struct Node;
    using NodeContainer = std::vector<Node>;

    struct Node
    {
        Node(char c, NodeContainer new_children)
        : content(c)
        , children(std::move(new_children)) 
        {}

        char content;
        NodeContainer children;
    };

    [[nodiscard]] NodeContainer VecToTree(std::vector<std::string> const & wordList, size_t numProcs);

    [[nodiscard]] std::vector<std::string> TreeToVec(std::string_view prefix, NodeContainer const & tree);
}