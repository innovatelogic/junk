#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace binary_search_probe_a
    {
        TEST(Array, Binary_Search_probe_a)
        {
            int arr[] = { 2, 3, 4, 10, 40 };
            const int n = sizeof(arr) / sizeof(arr[0]);

            EXPECT_EQ(bin_search<void>(arr, 0, n, 0), -1);
            EXPECT_EQ(bin_search<void>(arr, 0, n, 2), 0);
            EXPECT_EQ(bin_search<void>(arr, 0, n, 3), 1);
            EXPECT_EQ(bin_search<void>(arr, 0, n, 4), 2);
            EXPECT_EQ(bin_search<void>(arr, 0, n, 10), 3);
            EXPECT_EQ(bin_search<void>(arr, 0, n, 40), 4);
            EXPECT_EQ(bin_search<void>(arr, 0, n, 50), -1);
        }
    }
}