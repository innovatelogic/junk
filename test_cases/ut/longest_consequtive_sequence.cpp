#include <gtest/gtest.h>
#include <unordered_set>
#include <set>


// Problem: Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
// Requirement: Your algorithm should run in O(n) complexity.

namespace junk
{

static int longest_conecutive_sequence_merge(const std::vector<int>& nums)
 {
    if (nums.empty()) {
        return 0;
    }

    int longest_streak = 1;

    // Maps to track the boundaries of consecutive sequences
    std::unordered_map<int, int> start_of_streak; // [left boundary, length]
    std::unordered_map<int, int> end_of_streak;   // [right boundary, length]

    for (int n : nums) {
        if (start_of_streak.count(n) || end_of_streak.count(n)) {
            // Skip if this number is already part of a streak
            continue;
        }

        // Check if there is a consecutive sequence on the left and/or right
        bool has_left = end_of_streak.count(n - 1);
        bool has_right = start_of_streak.count(n + 1);

        if (has_left && has_right) {
            // Merge two sequences
            int left_start = end_of_streak[n - 1] - (n - 1) + 1;
            int right_end = start_of_streak[n + 1] + (n + 1) - 1;

            int merged_length = right_end - left_start + 1;
            start_of_streak[left_start] = merged_length;
            end_of_streak[right_end] = merged_length;

            // Erase intermediate values
            end_of_streak.erase(n - 1);
            start_of_streak.erase(n + 1);

            longest_streak = std::max(longest_streak, merged_length);

        } else if (has_left) {
            // Extend left sequence
            int left_start = end_of_streak[n - 1] - (n - 1) + 1;
            int new_length = n - left_start + 1;

            end_of_streak[n] = new_length;
            start_of_streak[left_start] = new_length;
            end_of_streak.erase(n - 1);

            longest_streak = std::max(longest_streak, new_length);

        } else if (has_right) {
            // Extend right sequence
            int right_end = start_of_streak[n + 1] + (n + 1) - 1;
            int new_length = right_end - n + 1;

            start_of_streak[n] = new_length;
            end_of_streak[right_end] = new_length;
            start_of_streak.erase(n + 1);

            longest_streak = std::max(longest_streak, new_length);

        } else {
            // New standalone sequence of length 1
            start_of_streak[n] = 1;
            end_of_streak[n] = 1;
        }
    }

    return longest_streak;
}

int longest_streak_fixed(const std::vector<int> &nums)
{
    if (nums.empty()){
        return 0;
    }

    int max_len = 1;

    std::unordered_set<int> num_set(nums.begin(), nums.end());
    std::unordered_map<int, int> dyn_precalc_seq;

    // 1, 2, 3
    // 100, 4, 200, 1, 3, 2

    for (auto &n : num_set)
    {
        if (num_set.count(n - 1) == 0)
        {
            int len = 1;
            int curr_n = n + 1;

            while (num_set.count(curr_n) > 0)
            {
                auto iter_find = dyn_precalc_seq.find(curr_n);
                if (iter_find != std::end(dyn_precalc_seq)) {
                    len += iter_find->second;
                    break;
                }

                ++len;
                ++curr_n;
            }

            max_len = std::max(max_len, len);

            dyn_precalc_seq[n] = len;
        }
    }

    return max_len;
}

int longest_streak_memtest_2(const std::vector<int> &nums)
{
    if (nums.empty()){
        return 0;
    }

    int max_len = 1;

    std::set<int> num_seq(std::begin(nums), std::end(nums));

    for (auto n : num_seq)
    {
        if (num_seq.count(n - 1) == 0)
        {
            int len = 1;
            int next_n = n + 1;
            while (num_seq.count(next_n) > 0){
                ++len;
                ++next_n;
            }

            max_len = std::max(max_len, len);
        }
    }

    return max_len;
}

TEST(LongestConsecutiveSequence, Test1)
{
    const auto N = 4;
    std::vector<int> nums = {100, 4, 200, 1, 3, 2};
    EXPECT_EQ(longest_streak_fixed(nums), N);
    EXPECT_EQ(longest_streak_memtest_2(nums), N);
}

TEST(LongestConsecutiveSequence, Test2)
{
    const auto N = 2;
    std::vector<int> nums = {0, -1};
    EXPECT_EQ(longest_streak_fixed(nums), N);
    EXPECT_EQ(longest_streak_memtest_2(nums), N);
}

TEST(LongestConsecutiveSequence, Test3)
{
    const auto N = 5;
    std::vector<int> nums = {1, 3, 5, 2, 4};
    EXPECT_EQ(longest_streak_fixed(nums), N);
    EXPECT_EQ(longest_streak_memtest_2(nums), N);
}

TEST(LongestConsecutiveSequence, Test4)
{
    const auto N = 3;
    std::vector<int> nums = {1, 0, -1};
    EXPECT_EQ(longest_streak_fixed(nums), N);
    EXPECT_EQ(longest_streak_memtest_2(nums), N);
}

}