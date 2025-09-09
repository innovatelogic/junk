#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>

// Go through the list of numbers and store the index of the complement in a map
// If the complement is found, return the indices
// Complexity: O(n)
// Space: O(n)
//
// Requirements:
// output: two indexes of the numbers that add up to the target

// Approach:
// moving from 0 to size of the list of numbers
// 1. check if the complement is found
// 2. store the [element, index] in a map for future reference

// invariant:
// preserve the invariant becouse only second element is needed to find the complement

// 1. if the complement is found, return the indices
// 2. store the index of the complement in a map

// Example:
// [2, 7, 11, 15], target = 9

// 9 - 2 = 7
// not found(empty map)
// frac_idx_map[2] = 0

// 9 - 7 = 2
// found 2 in frac_idx_map -> 0
// result: [0, 1]

// Ex2:
// [2, 7, 11, 0], target = 2

// 2 - 2 = 0
// not found 0
// frac_idx_map[2] = 0

// 2 - 7 = -5
// not found -5
// frac_idx_map[2] = 0
// frac_idx_map[7] = 1 <- added

// 2 - 11 = -9
// not found -9
// frac_idx_map[2] = 0
// frac_idx_map[7] = 1
// frac_idx_map[11] = 2 <- added

// 2 - 0 = 2
// found 2 in frac_idx_map -> 0
// result: [0, 3]


std::vector<int> twoSum(const std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> frac_idx_map;

    for (int i = 0; i < nums.size(); ++i)
    {
        int frac = target - nums[i];

        if (frac_idx_map.find(frac) != frac_idx_map.end()) {
            return {frac_idx_map[frac], i};
        }

        frac_idx_map[nums[i]] = i;
    }
    return {};
}


TEST(TwoSum, Test1)
{
    EXPECT_EQ(twoSum({2, 7, 11, 15}, 9), std::vector<int>({0, 1}));
    EXPECT_EQ(twoSum({2, 7, 11, 15}, 26), std::vector<int>({2, 3}));
}