#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

namespace junk
{

// Problem: Given a collection of intervals, merge all overlapping intervals.
// Complexity: O(n log n) where n is the number of intervals

// Example:
// [1, 3], [2, 6], [8, 10], [15, 18]
// [1, 6], [8, 10], [15, 18]
//
// sorted intervals:
// [1, 3] <- [1, 6] <-- [1, 6]
// [2, 6] <- [....]
// [5, 6]           <-- [....]
// [8, 10]
// [15, 18]

std::vector<std::vector<int>> merge_intervals(std::vector<std::vector<int>> intervals)
{
    std::sort(std::begin(intervals), std::end(intervals), [](const std::vector<int> &lhs,  const std::vector<int>& rhs){
        return lhs[0] < rhs[0];
    });

    /*int prev = 0;
    for (int i = 1; i < intervals.size(); ++i)
    {
        // sliding window technique
        //         i - 1  :  i
        // case 1: [1, 3], [2, 6] -> [1, [3]] check [[2], 6] -> [1, 6]
        // case 2: [1, 3], [4, 6]
        // case 3: [1, 3], [3, 6]
        
        if (intervals[i][0] <= intervals[prev][1])
        {
            intervals[prev][1] = std::max(intervals[prev][1], intervals[i][1]);
            intervals[i] = intervals[i - 1];
            intervals.erase(intervals.begin() + i);
            --i;
        }
    }*/

   int prev = 0;

    intervals.erase(std::remove_if(std::next(std::begin(intervals)), std::end(intervals), [&](std::vector<int> &interval)
        {
            auto &i_prev = intervals[prev];
            
            if (&i_prev == &interval) 
            {
                ++prev;
                return false;
            }

            if (i_prev[1] >= interval.front()) 
            {
                i_prev[1] = std::max(i_prev[1], interval[1]);
                return true;
            }
            ++prev;
            
            return false;
        }), std::end(intervals));

    return intervals;
}

TEST(MergeIntervals, Test1)
{
    std::vector<std::vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    std::vector<std::vector<int>> expected = {{1, 6}, {8, 10}, {15, 18}};
    EXPECT_EQ(merge_intervals(intervals), expected);
}

TEST(MergeIntervals, Test2)
{
    // [[2,3],[2,2],[3,3],[1,3],[5,7],[2,2],[4,6]]
    // [[1,3],[4,7]]
    std::vector<std::vector<int>> intervals = {{2, 3}, {2, 2}, {3, 3}, {1, 3}, {5, 7}, {2, 2}, {4, 6}};
    std::vector<std::vector<int>> expected = {{1, 3}, {4, 7}};

    // [2, 3]
    // [2, 2]
    // [3, 3]
    // [1, 3]
    // [5, 7]
    // [2, 2]
    // [4, 6]

    EXPECT_EQ(merge_intervals(intervals), expected);
}

}