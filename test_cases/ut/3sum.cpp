#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

namespace junk
{

std::vector<int> get3sum(const std::vector<int> &nums, int target)
{
    std::vector<int> sorted_nums = nums;

    std::sort(std::begin(sorted_nums), std::end(sorted_nums), [](int lhs, int rhs){
        return lhs < rhs;
    });


    for (int i = 0; i < sorted_nums.size(); ++i)
    {
        int left = i + 1;
        int right = sorted_nums.size() - 1;

        while (left < right)
        {
            int sum = sorted_nums[i] + sorted_nums[left] + sorted_nums[right];

            if (sum > target){
                --right;
            }
            else if (sum < target){
                ++left;
            }
            else {
                return {sorted_nums[i], sorted_nums[left], sorted_nums[right]};
            }
        }
    }
    return {};
}

TEST(Sum3, Test1)
{
    {
        std::vector<int> res{-1, -1, 2};
        EXPECT_EQ(get3sum({-1, 0, 1, 2, -1, -4}, 0), res);
    }
    //EXPECT_EQ(get3sum({0, 0, 0}, 0), std::vector<int>{0, 0, 0});
    //EXPECT_EQ(get3sum({-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4}, 0), std::vector<int>{-4, 0, 4});
}

}