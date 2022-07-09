#include<vector>
#include <string_view>

namespace TreeSearch
{
    struct Node;
    using NodeContainer = std::vector<Node>;

    //-----------------------------------------------------------------------------------------
    // The main search function: looks for the <prefix> in the <tree>.
    //
    // Returns a reference to the sub-tree of all suffixes for the given <prefix> which can be
    // found in the <tree>, or nullptr if the <tree> does not contain the <prefix>.
    [[nodiscard]] NodeContainer Find(std::string_view prefix, NodeContainer const & tree, size_t numTasks);
}