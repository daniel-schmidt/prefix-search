#include "Find.h"
#include "PrefixTree.h"

#include <gmock/gmock.h>
#include <vector>
#include <string>

using namespace TreeSearch;
using ::testing::ContainerEq;

TEST(FindTests, ReturnsMatchingSubtree) 
{
    std::vector<std::string> input{"Anananas", "Bratwurst", "Clementine", "Baum", "Bein", "Banane"};
    std::string prefix = "Ba";
    
    NodeContainer const root = VecToTree(input, 1);
    NodeContainer const result_subtree = Find(prefix, root, 1);
    std::vector<std::string> result = TreeToVec(prefix, result_subtree);

    EXPECT_THAT(result, ContainerEq(std::vector<std::string>{"Baum", "Banane"}));
}