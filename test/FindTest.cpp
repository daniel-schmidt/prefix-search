#include "SearchTree.h"

#include <gmock/gmock.h>
#include <vector>
#include <string>

using namespace TreeSearch;
using ::testing::ContainerEq;

TEST(FindTests, ReturnsMatchingSubtree) 
{
    constexpr int num_procs = 1;
    std::vector<std::string> input{"Anananas", "Bratwurst", "Clementine", "Baum", "Bein", "Banane"};
    std::string prefix = "Ba";
    
    SearchTree underTest{input, num_procs};
    std::vector<std::string> result = underTest.Find(prefix);

    EXPECT_THAT(result, ContainerEq(std::vector<std::string>{"Baum", "Banane"}));
}