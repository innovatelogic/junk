#include <gtest/gtest.h>
#include <iostream>


std::vector<size_t> twoSum2(const std::vector<int> &svec, int target)
{
    if (svec.empty()){
        return {};
    }

    size_t left = 0;
    size_t right = svec.size() - 1;

    while (left < right)
    {
        int sum = svec[left] + svec[right];

        if (sum > target)
        {
            --right;
        }
        else if (sum < target)
        {
            ++left;
        }
        else {
            return {left, right};
        }
    }

    return {};
}

TEST(Sum2, Test1)
{
    EXPECT_EQ(twoSum2({2, 7, 11, 15}, 9), std::vector<size_t>({0, 1}));
    EXPECT_EQ(twoSum2({2, 7, 11, 15}, 26), std::vector<size_t>({2, 3}));
    EXPECT_EQ(twoSum2({1, 3, 4, 5, 7, 11}, 9), std::vector<size_t>({2, 3}));
}