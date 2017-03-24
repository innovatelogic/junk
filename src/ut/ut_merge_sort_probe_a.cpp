#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace merge_sort_probe_a
    {
        TEST(Sorting, MergeSort_probe_a)
        {
            std::vector<int> arr = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
            std::vector<int> tmp = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

            std::vector<int> sorted = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            merge_sort<void>(&arr[0], 0, arr.size(), &tmp[0]);

            EXPECT_EQ(arr, sorted);
        }
    }
}