#include "PrefixTree.h"

#include <gmock/gmock.h>
#include <vector>
#include <string>

using namespace TreeSearch;

using ::testing::SizeIs;
using ::testing::ContainerEq;


TEST(SerializeTests, StoresSingleWord) 
{
    std::vector<std::string> input{"Banane"};
    
    NodeContainer const root = VecToTree(input, 1);
    ASSERT_THAT(root, SizeIs(1));
    EXPECT_EQ(root[0].content, 'B');
    ASSERT_THAT(root[0].children, SizeIs(1));
    EXPECT_EQ(root[0].children[0].content, 'a');

    std::vector<std::string> result = TreeToVec("", root);
    EXPECT_THAT(result, ContainerEq(input));
}

TEST(SerializeTests, StoresMultipleWords) 
{
    std::vector<std::string> input{"Auto", "Banane", "Bein"};
    
    NodeContainer const root = VecToTree(input, 1);
    ASSERT_THAT(root, SizeIs(2));
    EXPECT_EQ(root[0].content, 'A');
    EXPECT_EQ(root[1].content, 'B');

    ASSERT_THAT(root[0].children, SizeIs(1));
    EXPECT_EQ(root[0].children[0].content, 'u');
    
    ASSERT_THAT(root[1].children, SizeIs(2));
    EXPECT_EQ(root[1].children[0].content, 'a');
    EXPECT_EQ(root[1].children[1].content, 'e');

    std::vector<std::string> result = TreeToVec("", root);
    EXPECT_THAT(result, ContainerEq(input));
}