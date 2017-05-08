#include "dp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace coin_change_dp_probe_b
    {
        TEST(Dp, CoinChangeDP_probe_b)
        {
            int arr[] = { 1, 2, 3 };
            int m = sizeof(arr) / sizeof(arr[0]);

            std::vector<int> out;
            int k = count<void>(5, arr, sizeof(arr) / sizeof(int), out);
        }
    }
}