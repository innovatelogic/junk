#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace max_subarray_probe_a
    {
        TEST(Array, MaxSubarray_probe_a)
        {
            int arr[] = { -2, -5, 6, -2, -3, 1, 5, -6 };
            int n = sizeof(arr) / sizeof(arr[0]);

            int max_val = max_subarray<void>(arr, 0, n - 1);

            EXPECT_EQ(max_val, 7);
        }
    }
}
