#include "PrefixTree.h"

#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(SerializeTests, VecToTree) {
    std::vector<std::string> input{"Banane"};
    TreeSearch::VecToTree(input, 1);
}